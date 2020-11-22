//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#if defined(SPY_ARCH_IS_AMD64) && !defined(EVE_NO_SIMD)

#include <eve/logical.hpp>
#include <eve/detail/top_bits.hpp>

TTS_CASE_TPL("Check top_bits and first_true implementation", EVE_TYPE)
{
  eve::logical<T> f(false);
  TTS_EXPECT_NOT( eve::detail::first_true(eve::detail::top_bits(f)) );

  for(std::size_t n = 0;n < EVE_CARDINAL;++n)
  {
    eve::logical<T> l( [n](std::size_t i, auto) { return i == n; } );
    TTS_EXPECT( eve::detail::first_true(eve::detail::top_bits(l)) );
    TTS_EQUAL( *eve::detail::first_true(eve::detail::top_bits(l)), n );
  }
}

#endif
