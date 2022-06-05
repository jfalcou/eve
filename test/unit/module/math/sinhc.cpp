//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of sinhc"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::sinhc(T())  , T);
  TTS_EXPR_IS( eve::sinhc(v_t()), v_t);
};

//==================================================================================================
// sinhc  tests
//==================================================================================================
auto mini = []<typename T>(eve::as<T> const & tgt)
{
  return -eve::maxlog(tgt);
};

EVE_TEST( "Check behavior of sinhc on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(mini, eve::maxlog)
                            , eve::test::randoms(-10.0, 10.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using eve::sinhc;

  using v_t = eve::element_type_t<T>;
  auto ref = [](auto e) -> v_t { return e ? std::sinh(e)/e : v_t(1); };
  TTS_ULP_EQUAL(sinhc(a0)                       , map(ref, a0), 2);
  TTS_ULP_EQUAL(sinhc(a1)                       , map(ref, a1), 2);
};
