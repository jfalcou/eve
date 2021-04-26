//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/frexp.hpp>
#include <tuple>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::frexp(simd)"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::frexp(T()), (std::tuple<T, T>) );
  TTS_EXPR_IS( eve::frexp(v_t()), (std::tuple<v_t,v_t>) );
};

//==================================================================================================
// Tests for eve::frexp
//==================================================================================================
EVE_TEST( "Check behavior of eve::frexp(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  auto [x, n] = eve::frexp(a0);
  TTS_EQUAL(x, map([](auto e) -> v_t { int ee; return std::frexp(e, &ee);}, a0));
  TTS_EQUAL(n, map([](auto e) -> v_t { int ee; std::frexp(e, &ee); return v_t(ee); }, a0));
};
