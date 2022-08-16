//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
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
TTS_CASE_TPL("Check return types of tgamma", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::tgamma(T()), T);
  TTS_EXPR_IS(eve::tgamma(v_t()), v_t);
};

//==================================================================================================
// tgamma  tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of tgamma on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10.0, 10.0)))
<typename T>([[maybe_unused]] T const& a0)
{
  using eve::tgamma;

#if defined(__cpp_lib_math_special_functions)
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(tgamma(a0), map([&](auto e) -> v_t { return std::tgamma(e); }, a0), 4);
#endif // __cpp_lib_math_special_functions

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(tgamma(eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
    TTS_IEEE_EQUAL(tgamma(eve::inf(eve::as<T>())), eve::inf(eve::as<T>()));
    TTS_IEEE_EQUAL(tgamma(eve::minf(eve::as<T>())), eve::nan(eve::as<T>()));
  }
  TTS_IEEE_EQUAL(tgamma(T(0)), eve::inf(eve::as<T>()));
  TTS_IEEE_EQUAL(tgamma(T(-0.)), eve::minf(eve::as<T>()));
  TTS_IEEE_EQUAL(tgamma(T(1)), T(1));
  TTS_IEEE_EQUAL(tgamma(T(2)), T(1));
  TTS_IEEE_EQUAL(tgamma(T(3)), T(2));
  TTS_IEEE_EQUAL(tgamma(T(5)), T(24.0));
  TTS_ULP_EQUAL(tgamma(T(0.5)), T(1.772453850905516), 0.5);
};


//==================================================================================================
// Tests for masked tgamma
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::tgamma)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::tgamma[mask](a0),
            eve::if_else(mask, eve::tgamma(a0), a0));
};
