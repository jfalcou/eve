/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
//==================================================================================================
// Types tests
//==================================================================================================

// We use sizeof(Wide) to get real occupied size, so if we divide it to the sizeof(Scalar),
// we get the number of Scalar elements that we need to occupy the same size.
template<eve::arithmetic_simd_value Wide, typename Scalar>
using same_size_of =
    eve::wide<Scalar, eve::fixed<std::max<size_t>(1, sizeof(Wide) / sizeof(Scalar))>>;

TTS_CASE_TPL("Check return types of bit_cast", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using ut_t = eve::as_integer_t<T, unsigned>;
  using it_t = eve::as_integer_t<T, signed>;
  using u8_t  = same_size_of<T, std::int8_t>;
  using u16_t = same_size_of<T, std::int16_t>;
  using u32_t = same_size_of<T, std::int32_t>;
  using u64_t = same_size_of<T, std::int64_t>;
  using f32_t = same_size_of<T, float>;
  using f64_t = same_size_of<T, double>;
  // regular
  TTS_EXPR_IS(eve::bit_cast(T(), eve::as<it_t>()), it_t);
  TTS_EXPR_IS(eve::bit_cast(T(), eve::as<ut_t>()), ut_t);
  TTS_EXPR_IS(eve::bit_cast(T(), eve::as<T>()), T);
  TTS_EXPR_IS(eve::bit_cast(T(), eve::as<u8_t>()), u8_t);
  if constexpr( sizeof(T) == sizeof(u16_t) )
    TTS_EXPR_IS(eve::bit_cast(T(), eve::as<u16_t>()), u16_t);
  if constexpr( sizeof(T) == sizeof(u32_t) )
    TTS_EXPR_IS(eve::bit_cast(T(), eve::as<u32_t>()), u32_t);
  if constexpr( sizeof(T) == sizeof(f32_t) )
    TTS_EXPR_IS(eve::bit_cast(T(), eve::as<f32_t>()), f32_t);
  if constexpr( sizeof(T) == sizeof(u64_t) )
    TTS_EXPR_IS(eve::bit_cast(T(), eve::as<u64_t>()), u64_t);
  if constexpr( sizeof(T) == sizeof(f64_t) )
    TTS_EXPR_IS(eve::bit_cast(T(), eve::as<f64_t>()), f64_t);
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
  using elt_t = eve::element_type_t<T>;
  using ut_t  = eve::as_integer_t<T, unsigned>;
  using it_t  = eve::as_integer_t<T, signed>;
  using vut_t = eve::as_integer_t<elt_t, unsigned>;
  using vit_t = eve::as_integer_t<elt_t, signed>;

  TTS_EQUAL(
      bit_cast(a0, eve::as<T>()),
      tts::map([](auto e, auto) -> elt_t { return bit_cast(e, eve::as<elt_t>()); }, a0, eve::as<T>()));
  TTS_EQUAL(bit_cast(a0, eve::as<ut_t>()),
            tts::map([](auto e, auto) -> vut_t { return bit_cast(e, eve::as<vut_t>()); },
                a0,
                eve::as<ut_t>()));
  TTS_EQUAL(bit_cast(a0, eve::as<it_t>()),
            tts::map([](auto e, auto) -> vit_t { return bit_cast(e, eve::as<vit_t>()); },
                a0,
                eve::as<it_t>()));
  //== more tests to write when std::bit_cast will be available
};
