//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SSSE4_1_LIMITS_HPP_INCLUDED
#define EVE_ARCH_X86_SSSE4_1_LIMITS_HPP_INCLUDED

#include <eve/arch/x86/sse4_1/tags.hpp>
#include <eve/arch/x86/sse2/limits.hpp>

namespace eve
{
  template<>
  struct limits<eve::sse4_1_> : limits<eve::sse2_>
  {
  };
}

#endif
