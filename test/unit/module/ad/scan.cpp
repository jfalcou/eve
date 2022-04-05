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
// Tests for eve::scan
//==================================================================================================

EVE_TEST( "Check behavior of eve::scan"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-10, 10)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0, M const & )
{
  auto vda0 = eve::var(a0);
  using elt_t =  eve::element_type_t<T>;
  TTS_EQUAL(eve::scan(vda0, eve::add, elt_t(0)), eve::scan(a0, eve::add, elt_t(0)));
  TTS_EQUAL(eve::scan(vda0, eve::add, eve::var(elt_t(0))), eve::scan(a0, eve::add, elt_t(0)));

};
