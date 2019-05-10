//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_X86_AVX2_LIMITS_HPP_INCLUDED
#define EVE_ARCH_X86_AVX2_LIMITS_HPP_INCLUDED

#include <eve/arch/x86/avx2/tags.hpp>
#include <eve/arch/x86/avx/limits.hpp>

namespace eve
{
  template<>
  struct limits<eve::avx2_> : limits<eve::avx_>
  {
  };
}

#endif
