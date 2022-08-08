//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of negate", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  // regular
  TTS_EXPR_IS(eve::negate(T(), T()), T);
  TTS_EXPR_IS(eve::negate(T(), v_t()), T);
  TTS_EXPR_IS(eve::negate(v_t(), T()), T);
  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::negate(T(), int()), T);
    TTS_EXPR_IS(eve::negate(int(), T()), T);
  }
  TTS_EXPR_IS(eve::negate(v_t(), v_t()), v_t);
};

//==================================================================================================
//== negate tests
//==================================================================================================
TTS_CASE_TPL("Check return types of negate", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  if constexpr( eve::floating_value<T> )
  {
    if constexpr( eve::platform::supports_invalids )
    {
      TTS_EQUAL(eve::negate(eve::inf(eve::as<T>()), eve::inf(eve::as<T>())),
                eve::inf(eve::as<T>()));
      TTS_EQUAL(eve::negate(eve::minf(eve::as<T>()), eve::minf(eve::as<T>())),
                eve::inf(eve::as<T>()));

      TTS_IEEE_EQUAL(eve::negate(eve::nan(eve::as<T>()), eve::nan(eve::as<T>())),
                     eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(eve::negate(eve::nan(eve::as<T>()), T(0)), eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(eve::negate(T(0), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(eve::negate(eve::nan(eve::as<T>()), T(0)), eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(eve::negate(T(1), eve::nan(eve::as<T>())), eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(eve::negate(eve::nan(eve::as<T>()), T(1)), eve::nan(eve::as<T>()));
    }

    TTS_EQUAL(eve::negate(T(-1), T(-1)), T(1));
    TTS_EQUAL(eve::negate(T(1), T(1)), T(1));
    TTS_EQUAL(eve::negate(T(0), T(0)), T(0));
    TTS_EQUAL(eve::negate(T(1), T(0)), T(0));
    TTS_EQUAL(eve::negate(T(2), T(-3)), T(-2));
    TTS_EQUAL(eve::negate(T(2), T(3)), T(2));
  }
  else if constexpr( eve::signed_value<T> )
  {
    TTS_EQUAL(eve::negate(T(-1), T(-1)), T(1));
    TTS_EQUAL(eve::negate(T(-1), T(1)), T(-1));
  }

  TTS_EQUAL(eve::negate(T(1), T(1)), T(1));
  TTS_EQUAL(eve::negate(T(0), T(0)), T(0));
  TTS_EQUAL(eve::negate(T(1), T(0)), T(0));
};

TTS_CASE_WITH("Check behavior of negate(wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0, T const& a1)
{
  using eve::negate;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(
      negate(a0, a1), map([](auto e, auto f) -> v_t { return e * eve::sign(f); }, a0, a1), 2);
};
