/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of bit_cast", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using ut_t = eve::as_integer_t<T, unsigned>;
  using it_t = eve::as_integer_t<T, signed>;
  using v_t  = eve::element_type_t<T>;
  using u8_t = eve::as_wide_t<std::int8_t, eve::fixed<eve::cardinal_v<T> * sizeof(v_t)>>;
  // regular
  TTS_EXPR_IS(eve::bit_cast(T(), eve::as<it_t>()), it_t);
  TTS_EXPR_IS(eve::bit_cast(T(), eve::as<ut_t>()), ut_t);
  TTS_EXPR_IS(eve::bit_cast(T(), eve::as<T>()), T);
  TTS_EXPR_IS(eve::bit_cast(T(), eve::as<u8_t>()), u8_t);
};

//==================================================================================================
//== bit_cast tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of bit_cast(simd) on integral types",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  using eve::as;
  using eve::bit_cast;
  using eve::detail::map;
  using elt_t = eve::element_type_t<T>;
  using ut_t  = eve::as_integer_t<T, unsigned>;
  using it_t  = eve::as_integer_t<T, signed>;
  using vut_t = eve::as_integer_t<elt_t, unsigned>;
  using vit_t = eve::as_integer_t<elt_t, signed>;

  TTS_EQUAL(
      bit_cast(a0, eve::as<T>()),
      map([](auto e, auto) -> elt_t { return bit_cast(e, eve::as<elt_t>()); }, a0, eve::as<T>()));
  TTS_EQUAL(bit_cast(a0, eve::as<ut_t>()),
            map([](auto e, auto) -> vut_t { return bit_cast(e, eve::as<vut_t>()); },
                a0,
                eve::as<ut_t>()));
  TTS_EQUAL(bit_cast(a0, eve::as<it_t>()),
            map([](auto e, auto) -> vit_t { return bit_cast(e, eve::as<vit_t>()); },
                a0,
                eve::as<it_t>()));
  //== more tests to write when std::bit_cast will be available
};
