//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_PPC_SPEC_HPP_INCLUDED
#define EVE_ARCH_PPC_SPEC_HPP_INCLUDED

#include <eve/detail/compiler.hpp>
#include <eve/arch/ppc/predef.hpp>
#include <cstddef>

#if defined(EVE_HW_POWERPC)
namespace eve
{
struct register_count
  {
    static constexpr std::size_t general = 32;

#  if EVE_HW_POWERPC == EVE_VMX_VERSION
    static constexpr std::size_t simd = 32;
#  else
    static constexpr std::size_t simd = 64;
#  endif
  };
}

// PPC SIMD ABI
#  if !defined(EVE_CURRENT_ABI)
#    if EVE_HW_POWERPC >= EVE_VMX_VERSION
#      define EVE_CURRENT_ABI ::eve::ppc_

#      ifndef EVE_NO_DENORMALS
#        define EVE_NO_DENORMALS
#      endif

#      if !defined(__APPLE_CC__) || __APPLE_CC__ <= 1 || __GNUC__ >= 4
#        include <altivec.h>
#      endif

#      ifdef bool
#        undef bool
#      endif

#      ifdef pixel
#        undef pixel
#      endif

#      ifdef vector
#       undef vector
#      endif

#      if defined(__IBMCPP__) || defined(__MWERKS__)
#        define __bool bool
#      endif
#    endif
#  endif
#endif

// PPC SIMD API
#if !defined(EVE_CURRENT_API)
#  if EVE_HW_POWERPC == EVE_VMX_VERSION
#    define EVE_CURRENT_API ::eve::vmx_
#  elif EVE_HW_POWERPC == EVE_VSX_VERSION
#    define EVE_CURRENT_API ::eve::vsx_
#  endif
#endif

#endif
