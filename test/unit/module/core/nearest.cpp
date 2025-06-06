//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of nearest", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::nearest(T()), T);
  TTS_EXPR_IS(eve::nearest(v_t()), v_t);
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS(eve::nearest(T(), eve::as<signed>()), (eve::as_integer_t<T, signed>));
    TTS_EXPR_IS(eve::nearest(v_t(), eve::as<signed>()), (eve::as_integer_t<v_t, signed>));
    TTS_EXPR_IS(eve::nearest(T(), eve::as<unsigned>()), (eve::as_integer_t<T, unsigned>));
    TTS_EXPR_IS(eve::nearest(v_t(), eve::as<unsigned>()), (eve::as_integer_t<v_t, unsigned>));
  }
};

//==================================================================================================
// nearest signed tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of nearest on wide",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using wi_t  = eve::as_integer_t<T>;
  using uwi_t = eve::as_integer_t<T, unsigned>;
  using v_t   = eve::element_type_t<T>;
  using i_t   = eve::as_integer_t<v_t>;
  using ui_t  = eve::as_integer_t<v_t, unsigned>;
  if constexpr( eve::floating_value<T> )
  {
    TTS_EQUAL(eve::nearest(a0), T([&](auto i, auto) { return v_t(std::nearbyint(a0.get(i))); }));
    TTS_EQUAL(eve::nearest(a0, eve::as<signed>()),
              wi_t([&](auto i, auto) { return i_t(std::nearbyint(a0.get(i))); }));
    TTS_EQUAL(eve::nearest(eve::abs(a0), eve::as<unsigned>()),
              uwi_t([&](auto i, auto) { return ui_t(std::nearbyint(std::abs(a0.get(i)))); }));
  }
  else { TTS_EQUAL(eve::nearest(a0), a0); }
};


//==================================================================================================
// Tests for masked nearest
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::nearest[cx](eve::wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::nearest[mask](a0),
            eve::if_else(mask, eve::nearest(a0), a0));
};
