//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/ad.hpp>

//==================================================================================================
// Tests for eve::reduce
//==================================================================================================

EVE_TEST( "Check behavior of eve::reduce"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-10, 10)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0, M const & )
{
  auto vda0 = eve::var(a0);

  TTS_EQUAL(eve::reduce(vda0), eve::reduce(a0));
  TTS_EQUAL(eve::reduce(vda0, eve::add), eve::reduce(a0, eve::add));

};
