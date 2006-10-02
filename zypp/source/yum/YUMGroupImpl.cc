/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file zypp/source/yum/YUMGroupImpl.cc
 *
*/

#include "zypp/source/yum/YUMGroupImpl.h"
#include "zypp/CapFactory.h"

using namespace std;
using namespace zypp::detail;
using namespace zypp::parser::yum;

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////
namespace source
{ /////////////////////////////////////////////////////////////////
namespace yum
{
///////////////////////////////////////////////////////////////////
//
//        CLASS NAME : YUMGroupImpl
//
///////////////////////////////////////////////////////////////////

/** Default ctor
*/
YUMGroupImpl::YUMGroupImpl(
  Source_Ref source_r,
  const zypp::parser::yum::YUMGroupData & parsed
)
    : _summary(parsed.name)
    , _description(parsed.description)
    , _user_visible(parsed.userVisible == "true")
    , _source(source_r)
{
// to name        std::string groupId;
// as _summary        std::list<multilang> name;
// _description
}

YUMGroupImpl::~YUMGroupImpl()
{}

/** Is to be visible for user? */
bool YUMGroupImpl::visible() const
{
  return _user_visible;
}

TranslatedText YUMGroupImpl::summary() const
{
  return _summary;
}

TranslatedText YUMGroupImpl::description() const
{
  return _description;
}

Label YUMGroupImpl::order() const
{
#warning Ordering support in YUM?
  return Label("0");
}

Label YUMGroupImpl::category() const
{
#warning Category support in YUM missing!
  return Label("base");
}

Source_Ref YUMGroupImpl::source() const
{
  return _source;
}


} // namespace yum
/////////////////////////////////////////////////////////////////
} // namespace source
///////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
