// -*- C++ -*-
/**
 * Code generated by the The ACE ORB (TAO) IDL Compiler v2.5.19
 * TAO and the TAO IDL Compiler have been developed by:
 *       Center for Distributed Object Computing
 *       Washington University
 *       St. Louis, MO
 *       USA
 * and
 *       Distributed Object Computing Laboratory
 *       University of California at Irvine
 *       Irvine, CA
 *       USA
 * and
 *       Institute for Software Integrated Systems
 *       Vanderbilt University
 *       Nashville, TN
 *       USA
 *       https://www.isis.vanderbilt.edu/
 *
 * Information about TAO is available at:
 *     https://www.dre.vanderbilt.edu/~schmidt/TAO.html
 **/

// TAO_IDL - Generated from
// /home/tarun/dds/OpenDDS-3.24.1/ACE_wrappers/TAO/TAO_IDL/be/be_codegen.cpp:148

#ifndef _TAO_IDL_TONNAGEC_8YKVHM_H_
#define _TAO_IDL_TONNAGEC_8YKVHM_H_

#include /**/ "ace/pre.h"


#include /**/ "ace/config-all.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */


#include "tao/ORB.h"
#include "tao/Basic_Types_IDLv4.h"
TAO_BEGIN_VERSIONED_NAMESPACE_DECL

namespace CORBA
{
  using namespace IDLv4;
}

TAO_END_VERSIONED_NAMESPACE_DECL

#include "tao/VarOut_T.h"
#include "tao/Arg_Traits_T.h"
#include "tao/Basic_Arguments.h"
#include "tao/Special_Basic_Arguments.h"
#include "tao/Any_Insert_Policy_T.h"
#include "tao/Fixed_Size_Argument_T.h"
#include "tao/Var_Size_Argument_T.h"
#include /**/ "tao/Version.h"
#include /**/ "tao/Versioned_Namespace.h"

#if TAO_MAJOR_VERSION != 2 || TAO_MINOR_VERSION != 5 || TAO_MICRO_VERSION != 19
#error This file should be regenerated with TAO_IDL
#endif
// TAO_IDL - Generated from
// /home/tarun/dds/OpenDDS-3.24.1/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_module/module_ch.cpp:34

namespace Mining
{
  // TAO_IDL - Generated from
  // /home/tarun/dds/OpenDDS-3.24.1/ACE_wrappers/TAO/TAO_IDL/be/be_type.cpp:257

  

  struct Tonnage;

  typedef
    ::TAO_Fixed_Var_T<
        Tonnage
      >
    Tonnage_var;

  typedef
    Tonnage &
    Tonnage_out;

  
  // TAO_IDL - Generated from
  // /home/tarun/dds/OpenDDS-3.24.1/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_structure/structure_ch.cpp:47

  

  struct  Tonnage
  {
    // TAO_IDL - Generated from
    // /home/tarun/dds/OpenDDS-3.24.1/ACE_wrappers/TAO/TAO_IDL/be/be_type.cpp:301

    
    typedef Tonnage_var _var_type;
    typedef Tonnage_out _out_type;
    
    ::CORBA::Double value;
    ::CORBA::LongLong timeStamp;
    ::CORBA::Long seqNumber;
  };


// TAO_IDL - Generated from
// /home/tarun/dds/OpenDDS-3.24.1/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_module/module_ch.cpp:62


} // module Mining
// TAO_IDL - Generated from
// /home/tarun/dds/OpenDDS-3.24.1/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_arg_traits.cpp:64



TAO_BEGIN_VERSIONED_NAMESPACE_DECL


// Arg traits specializations.
namespace TAO
{
  // TAO_IDL - Generated from
  // /home/tarun/dds/OpenDDS-3.24.1/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_arg_traits.cpp:932

  

  template<>
  class Arg_Traits< ::Mining::Tonnage>
    : public
        Fixed_Size_Arg_Traits_T<
            ::Mining::Tonnage,
            TAO::Any_Insert_Policy_Noop
          >
  {
  };
}

TAO_END_VERSIONED_NAMESPACE_DECL


// TAO_IDL - Generated from
// /home/tarun/dds/OpenDDS-3.24.1/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_traits.cpp:58



TAO_BEGIN_VERSIONED_NAMESPACE_DECL

// Traits specializations.
namespace TAO
{
}
TAO_END_VERSIONED_NAMESPACE_DECL


// TAO_IDL - Generated from
// /home/tarun/dds/OpenDDS-3.24.1/ACE_wrappers/TAO/TAO_IDL/be/be_visitor_structure/cdr_op_ch.cpp:42


TAO_BEGIN_VERSIONED_NAMESPACE_DECL

 ::CORBA::Boolean operator<< (TAO_OutputCDR &, const Mining::Tonnage &);
 ::CORBA::Boolean operator>> (TAO_InputCDR &, Mining::Tonnage &);

TAO_END_VERSIONED_NAMESPACE_DECL


// TAO_IDL - Generated from
// /home/tarun/dds/OpenDDS-3.24.1/ACE_wrappers/TAO/TAO_IDL/be/be_codegen.cpp:1649

#if defined (__ACE_INLINE__)
#include "TonnageC.inl"
#endif /* defined INLINE */

#include /**/ "ace/post.h"

#endif /* ifndef */

