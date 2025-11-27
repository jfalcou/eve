//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <cmath>

 //==================================================================================================
 //= Types tests
 //==================================================================================================
TTS_CASE_TPL("Check return types of eve::bitfloating",eve::test::simd::signed_integers)
  <typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  if constexpr(sizeof(v_t) >=  2)
  {
    using f_t = eve::as_floating_point_t<T>;
    using sf_t =eve::element_type_t<f_t>;
    TTS_EXPR_IS(eve::detail::bitfloating(T()), f_t);
    TTS_EXPR_IS(eve::detail::bitinteger(f_t()), T);
    TTS_EXPR_IS(eve::detail::bitfloating(v_t()), sf_t);
    TTS_EXPR_IS(eve::detail::bitinteger(sf_t()), v_t);
  }
};

//==================================================================================================
//= Tests for eve::detail::bitfloating
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::detail::bitfloating(eve::scalar)",
              eve::test::scalar::signed_integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
  <typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  if constexpr( (sizeof(v_t) >=  2) )
  {
   TTS_EQUAL(eve::detail::bitinteger(eve::detail::bitfloating(a0)), a0);
  }
};

TTS_CASE_WITH("Check behavior of eve::detail::bitfloating(eve::scalar)",
              eve::test::scalar::ieee_reals_wf16,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
  <typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  if constexpr( (sizeof(v_t) >=  2) )
  {
    TTS_EQUAL(eve::detail::bitfloating(eve::detail::bitinteger(a0)), a0);
  }
};

TTS_CASE_WITH("Check behavior of eve::detail::bitfloating(eve::simd)",
              eve::test::simd::signed_integers,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
  <typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  if constexpr( (sizeof(v_t) >=  2) )
  {
    TTS_EQUAL(eve::detail::bitinteger(eve::detail::bitfloating(a0)), a0);
  }
};

TTS_CASE_WITH("Check behavior of eve::detail::bitfloating(eve::simd)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
  <typename T>(T const& a0)
{
    TTS_EQUAL(eve::detail::bitfloating(eve::detail::bitinteger(a0)), a0);
};
