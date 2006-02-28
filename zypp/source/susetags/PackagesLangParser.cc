/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file	zypp/source/susetags/PackagesLangParser.cc
 *
*/
#include <iostream>
#include "zypp/base/Logger.h"

#include "zypp/source/susetags/PackagesLangParser.h"
#include "zypp/parser/tagfile/TagFileParser.h"
#include "zypp/Package.h"
#include "zypp/source/susetags/SuseTagsPackageImpl.h"


using std::endl;

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  namespace source
  { /////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////
    namespace susetags
    { /////////////////////////////////////////////////////////////////

      using namespace parser::tagfile;

      struct PackagesLangParser : public parser::tagfile::TagFileParser
      {
        const PkgContent & _content;
	const Locale & _lang;
	PkgImplPtr _current;
        NVRAD _nvrad;
	int _count;
        std::set<NVRAD> _notfound;

	PackagesLangParser (const PkgContent & content_r, const Locale & lang_r)
	    : _content( content_r )
	    , _lang( lang_r)
	    , _count(0)
        { }

        /* Consume SingleTag data. */
        virtual void consume( const SingleTag & stag_r )
        {
          if ( stag_r.name == "Pkg" )
          {
            std::vector<std::string> words;
            str::split( stag_r.value, std::back_inserter(words) );

            if ( str::split( stag_r.value, std::back_inserter(words) ) != 4 )
              ZYPP_THROW( ParseException( "[" + _file_r.asString() + "] Parse error in tag Pkg, expected [name version release arch], found: [" + stag_r.value + "]" ) );
            
            _nvrad = NVRAD( words[0], Edition(words[1],words[2]), Arch(words[3]) );
	    PkgContent::const_iterator it = _content.find(_nvrad);
	    if (it == _content.end())
            {
              WAR << words[0] << " " << words[1] << " " << words[2] << "  " << Arch(words[3]) << " has a description   in " << _file_r << " but can't find it in package list (" << _content.size() << " packages)" << endl;
		_current = NULL;
                _notfound.insert(_nvrad);
	    }
	    else
            {
              //WAR << "Data for package " << words[0] << " " << words[1] << " " << words[2] << "  " << Arch(words[3]) << " coming..." << endl;
		_count++;
		_current = it->second;
	    }

          }
	  else if ( stag_r.name == "Sum" )
          {
	    if (_current != NULL)
	      _current->_summary = TranslatedText( stag_r.value, _lang);
            else
              ERR << "Package [" << _nvrad.name << " " << _nvrad.edition << " " << _nvrad.arch << "] was not found in package list. Skipping " << stag_r.name << " tag" << endl;
          }
        }

        /* Consume MulitTag data. */
        virtual void consume( const MultiTag & mtag_r )
        {
          if ( mtag_r.name == "Des" )
            {
	      if ( _current != NULL )
                 _current->_description = TranslatedText (mtag_r.values, _lang);
	      else
                ERR << "Package [" << _nvrad.name << " " << _nvrad.edition << " " << _nvrad.arch << "] was not found in package list. Skipping " << mtag_r.name << " tag" << endl;
            }
        }
      };

      ////////////////////////////////////////////////////////////////////////////

      void parsePackagesLang( const Pathname & file_r, const Locale & lang_r, const PkgContent & content_r )
      {
        PackagesLangParser p (content_r, lang_r);
	MIL << "Starting with " << content_r.size() << " packages" << endl;
        p.parse( file_r );
        MIL << "Ending after " << p._count << " langs with " << content_r.size() << " packages and " << p._notfound.size() << " not founds." <<endl;
        WAR << "Not found packages:" << std::endl;
        for ( std::set<NVRAD>::const_iterator it = p._notfound.begin(); it != p._notfound.end(); ++it)
        {
          NVRAD nvrad = *it;
          WAR << "-> " << nvrad.name << " " << nvrad.edition << " " << nvrad.arch << std::endl;
        }
        return;
      }

      /////////////////////////////////////////////////////////////////
    } // namespace susetags
    ///////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////
  } // namespace source
  ///////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
