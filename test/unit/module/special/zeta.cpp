//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/special.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of zeta", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::zeta(T()), T);
  TTS_EXPR_IS(eve::zeta(v_t()), v_t);
};

//==================================================================================================
// zeta  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of zeta on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10.0, 10.0)))
<typename T>([[maybe_unused]] T const& a0)
{
  using eve::as;
  using eve::zeta;

#if defined(__cpp_lib_math_special_functions)
  using v_t = eve::element_type_t<T>;
  TTS_RELATIVE_EQUAL(
      zeta(a0), map([](auto e) -> v_t { return std::riemann_zeta(v_t(e)); }, a0), 0.4);
  TTS_ULP_EQUAL(eve::zeta(T(0)), T(std::riemann_zeta(v_t(0))), 0.5);
  TTS_ULP_EQUAL(eve::zeta(T(-0.0)), T(std::riemann_zeta(v_t(-0.0))), 0.5);
  TTS_ULP_EQUAL(eve::zeta(T(1.5)), T(std::riemann_zeta(v_t(1.5))), 1.5);
  TTS_ULP_EQUAL(eve::zeta(T(-1.5)), T(std::riemann_zeta(v_t(-1.5))), 2.5);
  TTS_ULP_EQUAL(eve::zeta(T(14)), T(std::riemann_zeta(v_t(14))), 0.5);
  TTS_ULP_EQUAL(eve::zeta(T(-14)), T(std::riemann_zeta(v_t(-14))), 0.5);
  TTS_ULP_EQUAL(eve::zeta(T(14.5)), T(std::riemann_zeta(v_t(14.5))), 0.5);
  TTS_ULP_EQUAL(eve::zeta(T(-14.5)), T(std::riemann_zeta(v_t(-14.5))), 15);
#endif

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(eve::zeta(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::zeta(eve::inf(eve::as<T>())), eve::one(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::zeta(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()));
  }

  TTS_IEEE_EQUAL(eve::zeta(T(1)), eve::nan(eve::as<T>()));
};
