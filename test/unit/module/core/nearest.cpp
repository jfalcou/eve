//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
  TTS_EXPR_IS(eve::int_(eve::nearest)(T()), eve::as_integer_t<T>);
  TTS_EXPR_IS(eve::int_(eve::nearest)(v_t()), eve::as_integer_t<v_t>);
  TTS_EXPR_IS(eve::uint_(eve::nearest)(T()), (eve::as_integer_t<T, unsigned>));
  TTS_EXPR_IS(eve::uint_(eve::nearest)(v_t()), (eve::as_integer_t<v_t, unsigned>));

  if constexpr( eve::floating_real_value<T> ) {}
};

//==================================================================================================
// nearest signed tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of nearest on wide",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(-50, +50)))
<typename T>(T const& a0)
{
  using wi_t  = eve::as_integer_t<T>;
  using uwi_t = eve::as_integer_t<T, unsigned>;
  using v_t   = eve::element_type_t<T>;
  using i_t   = eve::as_integer_t<v_t>;
  using ui_t  = eve::as_integer_t<v_t, unsigned>;
  if constexpr( eve::floating_real_value<T> )
  {
    TTS_EQUAL(eve::nearest(a0), T([&](auto i, auto) { return v_t(std::nearbyint(a0.get(i))); }));
    TTS_EQUAL(eve::int_(eve::nearest)(a0),
              wi_t([&](auto i, auto) { return i_t(std::nearbyint(a0.get(i))); }));
    TTS_EQUAL(eve::uint_(eve::nearest)(eve::abs(a0)),
              uwi_t([&](auto i, auto) { return ui_t(std::nearbyint(std::abs(a0.get(i)))); }));
  }
  else { TTS_EQUAL(eve::nearest(a0), a0); }
};
