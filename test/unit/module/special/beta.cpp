//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/special.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of beta", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::beta(T(), T()), T);
  TTS_EXPR_IS(eve::beta(T(), v_t()), T);
  TTS_EXPR_IS(eve::beta(v_t(), T()), T);
  TTS_EXPR_IS(eve::beta(v_t(), v_t()), v_t);
};

//==================================================================================================
// beta  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of beta on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(0.0, 10.0), tts::randoms(0.0, 10.0)))
<typename T>([[maybe_unused]] T const& a0, [[maybe_unused]] T const& a1)
{
  using eve::as;
  using eve::beta;

#if defined(__cpp_lib_math_special_functions)
  using elt_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(
      eve::beta(a0, a1), map([&](auto e, auto f) -> elt_t { return std::beta(e, f); }, a0, a1), 64);
  TTS_ULP_EQUAL(beta(T(-0.0), T(-0.0)), T(std::beta(elt_t(-0.0), elt_t(-0.0))), 0);
  TTS_ULP_EQUAL(beta(T(0.0), T(0.0)), T(std::beta(elt_t(0.0), elt_t(0.0))), 0);
  TTS_ULP_EQUAL(beta(T(1.0), T(1.0)), T(std::beta(elt_t(1.0), elt_t(1.0))), 0);
  TTS_ULP_EQUAL(beta(T(2.0), T(3.0)), T(std::beta(elt_t(2.0), elt_t(3.0))), 0);
  TTS_ULP_EQUAL(beta(T(2.5), T(3.7)), T(std::beta(elt_t(2.5), elt_t(3.7))), 0);
#endif // __cpp_lib_math_special_functions

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(beta(eve::inf(eve::as<T>()), eve::inf(eve::as<T>())), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(beta(eve::inf(eve::as<T>()), T(1)), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(beta(T(1), eve::inf(eve::as<T>())), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(beta(eve::minf(eve::as<T>()), eve::minf(eve::as<T>())), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(beta(eve::minf(eve::as<T>()), T(1)), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(beta(T(1), eve::minf(eve::as<T>())), eve::nan(as<T>()), 0);

    TTS_ULP_EQUAL(beta(eve::nan(eve::as<T>()), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()), 0);
    TTS_ULP_EQUAL(beta(eve::nan(eve::as<T>()), T(1)), eve::nan(as<T>()), 0);
    TTS_ULP_EQUAL(beta(T(1), eve::nan(eve::as<T>())), eve::nan(as<T>()), 0);
  }
};
