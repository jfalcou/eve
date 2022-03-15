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
EVE_TEST_TYPES( "Check return types of sinc"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::sinc(T())  , T);
  TTS_EXPR_IS( eve::sinc(v_t()), v_t);
};

//==================================================================================================
// sinc  tests
//==================================================================================================
auto mini = [](auto tgt) { return eve::next(eve::mindenormal(tgt)); };
auto maxi = [](auto tgt) { return eve::valmax(tgt)/2; };

EVE_TEST( "Check behavior of sinc on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(mini, maxi)
                            , eve::test::randoms(-10.0, 10.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using eve::sinc;
  using eve::diff;
  using v_t = eve::element_type_t<T>;

  auto ref = [](auto e) -> v_t { return e ? std::sin(e)/e : v_t(1); };
  TTS_ULP_EQUAL(sinc(a0), map(ref, a0), 2);
  TTS_ULP_EQUAL(sinc(a1), map(ref, a1), 2);

  auto ds = [](auto x) -> v_t
  {
    auto [s, c] = eve::sincos(x);
    return x ? eve::fms(x, c, s)/(x*x) : v_t(0);
  };

  TTS_ULP_EQUAL(diff(sinc)(a0), map(ds, a0), 2);
  TTS_ULP_EQUAL(diff(sinc)(a1), map(ds, a1), 10);
};
