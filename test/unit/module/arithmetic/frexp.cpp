//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <tuple>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::frexp(simd)"
              , eve::test::simd::ieee_reals
              )
  <typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::frexp(T()), (kumi::tuple<T, T>) );
  TTS_EXPR_IS( eve::frexp(v_t()), (kumi::tuple<v_t,v_t>) );
  TTS_EXPR_IS( eve::pedantic(eve::frexp)(T()), (kumi::tuple<T, T>) );
  TTS_EXPR_IS( eve::pedantic(eve::frexp)(v_t()), (kumi::tuple<v_t,v_t>) );
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
  {
    auto [x, n] = eve::frexp(a0);
    TTS_EQUAL(x, map([](auto e) -> v_t { int ee; return std::frexp(e, &ee);}, a0));
    TTS_EQUAL(n, map([](auto e) -> v_t { int ee; std::frexp(e, &ee); return v_t(ee); }, a0));
  }
  {
    auto [x, n] = eve::pedantic(eve::frexp)(a0);
    TTS_EQUAL(x, map([](auto e) -> v_t { int ee; return std::frexp(e, &ee);}, a0));
    TTS_EQUAL(n, map([](auto e) -> v_t { int ee; std::frexp(e, &ee); return v_t(ee); }, a0));
  }
};

//==================================================================================================
// Test for corner-cases values pedantic !
//==================================================================================================
EVE_TEST( "Check corner-cases behavior of eve::pedantic(eve::frexp) variants on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::limits())
        )
<typename T>(T const& cases)
{
  using type = typename T::type;
  {
    auto [x, n] = eve::pedantic(eve::frexp)(cases.nan);
    TTS_IEEE_EQUAL(x, cases.nan);
    TTS_EQUAL(n,      cases.zero);
  }
  {
    auto [x, n] = eve::pedantic(eve::frexp)(cases.inf);
    TTS_EQUAL(x, cases.inf);
    TTS_EQUAL(n, cases.zero);
  }
  {
    auto [x, n] = eve::frexp(cases.zero);
    TTS_EQUAL(x, cases.zero);
    TTS_EQUAL(n, cases.zero);
  }
  {
    auto [x, n] = eve::pedantic(eve::frexp)(cases.zero);
    TTS_EQUAL(x, cases.zero);
    TTS_EQUAL(n, cases.zero);
  }
  {
    auto [x, n] = eve::pedantic(eve::frexp)(cases.mzero);
    TTS_EQUAL(x, cases.mzero);
    TTS_EQUAL(n, cases.zero);
  }
  {
    auto [x, n] = eve::pedantic(eve::frexp)(cases.minf);
    TTS_EQUAL(x, cases.minf);
    TTS_EQUAL(n, cases.zero);
  }

  if constexpr(eve::platform::supports_denormals)
  {
    auto [x, n] = eve::pedantic(eve::frexp)(cases.mindenormal);
    TTS_EQUAL(x, eve::half(eve::as<type>()));
    TTS_EQUAL(n, (eve::minlog2denormal(eve::as<type>())+2));
  }
};
