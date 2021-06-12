//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/function/all.hpp>
#include <eve/function/zeta.hpp>
#include <eve/function/ulpdist.hpp>
#include <type_traits>
#include <cmath>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/one.hpp>
#include <eve/platform.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of zeta"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::zeta(T())  , T);
  TTS_EXPR_IS( eve::zeta(v_t()), v_t);
};

//==================================================================================================
// zeta  tests
//==================================================================================================
EVE_TEST( "Check behavior of zeta on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-10.0, 10.0))
        )
<typename T>(T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  using eve::zeta;
  using eve::as;
  TTS_ULP_EQUAL( zeta(a0),  map([](auto e) -> v_t{ return std::riemann_zeta(v_t(e)); }, a0), 40);

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::zeta(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::zeta(eve::inf(eve::as<T>())) , eve::one(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::zeta(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()));
  }

  TTS_IEEE_EQUAL(eve::zeta(T(1))   , eve::nan(eve::as<T>()));
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(eve::zeta(T(0))    , T(std::riemann_zeta(v_t(0))), 0.5);
  TTS_ULP_EQUAL(eve::zeta(T(-0.0))   ,T(std::riemann_zeta(v_t(-0.0))), 0.5);
  TTS_ULP_EQUAL(eve::zeta(T(1.5))    , T(std::riemann_zeta(v_t(1.5))), 1.5);
  TTS_ULP_EQUAL(eve::zeta(T(-1.5))   ,T(std::riemann_zeta(v_t(-1.5))), 2.5);
  TTS_ULP_EQUAL(eve::zeta(T(14))    , T(std::riemann_zeta(v_t(14))), 0.5);
  TTS_ULP_EQUAL(eve::zeta(T(-14))   ,T(std::riemann_zeta(v_t(-14))), 0.5);
  TTS_ULP_EQUAL(eve::zeta(T(14.5))    , T(std::riemann_zeta(v_t(14.5))), 0.5);
  TTS_ULP_EQUAL(eve::zeta(T(-14.5))   ,T(std::riemann_zeta(v_t(-14.5))), 15);

};
