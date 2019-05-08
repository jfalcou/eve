//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_SSE4_2_LIMITS_HPP_INCLUDED
#define EVE_ARCH_X86_SSE4_2_LIMITS_HPP_INCLUDED

#include <eve/arch/x86/sse4_2/tags.hpp>
#include <eve/arch/x86/sse2/limits.hpp>

namespace eve
{
  template<>
  struct limits<eve::sse4_2_> : limits<eve::sse2_>
  {
  };
}

#endif
