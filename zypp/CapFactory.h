/*---------------------------------------------------------------------\
|                          ____ _   __ __ ___                          |
|                         |__  / \ / / . \ . \                         |
|                           / / \ V /|  _/  _/                         |
|                          / /__ | | | | | |                           |
|                         /_____||_| |_| |_|                           |
|                                                                      |
\---------------------------------------------------------------------*/
/** \file	zypp/CapFactory.h
 *
*/
#ifndef ZYPP_CAPFACTORY_H
#define ZYPP_CAPFACTORY_H

#include <iosfwd>

#include "zypp/base/PtrTypes.h"

#include "zypp/Capability.h"

///////////////////////////////////////////////////////////////////
namespace zypp
{ /////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////
  namespace detail
  { /////////////////////////////////////////////////////////////////
    DEFINE_PTR_TYPE(CapFactoryImpl)
    /////////////////////////////////////////////////////////////////
  } // namespace detail
  ///////////////////////////////////////////////////////////////////

  ///////////////////////////////////////////////////////////////////
  //
  //	CLASS NAME : CapFactory
  //
  /**
   * \todo define EXCEPTIONS
  */
  class CapFactory
  {
  public:
    /** Default ctor */
    CapFactory();
    /** Factory ctor */
    explicit
    CapFactory( detail::CapFactoryImplPtr impl_r );
    /** Dtor */
    ~CapFactory();

  public:
    /** Parse Capability from string (incl. ResKind).
     * \c strval_r is expected to define a valid Capability \em including
     * the ResKind.
     * \throw EXCEPTION on parse error.
    */
    Capability parse( const std::string & strval_r ) const;
    /** Parse Capability from string (default ResKind).
     * \c strval_r is expected to define a valid Capability. If it does
     * not define the ResKind, \c defaultRefers_r is used instead.
     * \throw EXCEPTION on parse error.
    */
    Capability parse( const std::string & strval_r, const ResKind & defaultRefers_r ) const;

  private:
    /** Pointer to implementation */
    detail::CapFactoryImplPtr _pimpl;
  public:
    /** Avoid a bunch of friend decl. */
    detail::constCapFactoryImplPtr sayFriend() const;
  };
  ///////////////////////////////////////////////////////////////////

  /** \relates CapFactory Stream output */
  extern std::ostream & operator<<( std::ostream & str, const CapFactory & obj );

  /////////////////////////////////////////////////////////////////
} // namespace zypp
///////////////////////////////////////////////////////////////////
#endif // ZYPP_CAPFACTORY_H
