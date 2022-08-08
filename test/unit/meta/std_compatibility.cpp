//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/std.hpp>

TTS_CASE_TPL( "Check for experimental::simd compliance", ::tts::arithmetic_types)
<typename T>(::tts::type<T>)
{
  using eve_type      = eve::experimental::simd<T>;
  using eve_mask_type = eve::experimental::simd_mask<T>;

  TTS_EQUAL(sizeof(eve_type)      , sizeof(eve::wide<T,eve::fixed<16/sizeof(T)>>));
  TTS_EQUAL(sizeof(eve_mask_type) , sizeof(eve::logical<eve::wide<T,eve::fixed<16/sizeof(T)>>>));
};

TTS_CASE_TPL( "Check for experimental::native_simd compliance", ::tts::arithmetic_types)
<typename T>(::tts::type<T>)
{
  using eve_type      = eve::experimental::native_simd<T>;
  using eve_mask_type = eve::experimental::native_simd_mask<T>;

  if constexpr( std::integral<T> && eve::current_api == eve::avx )
  {
    TTS_EQUAL(sizeof(eve_type)     , sizeof(eve::wide<T,eve::fixed<16/sizeof(T)>>));
    TTS_EQUAL(sizeof(eve_mask_type), sizeof(eve::logical<eve::wide<T,eve::fixed<16/sizeof(T)>>>));
  }
  else
  {
    TTS_EQUAL(sizeof(eve_type)     , sizeof(eve::wide<T>));
    TTS_EQUAL(sizeof(eve_mask_type), sizeof(eve::logical<eve::wide<T>>));
  }
};
