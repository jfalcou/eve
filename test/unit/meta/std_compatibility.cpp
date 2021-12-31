//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/std.hpp>

#if defined __has_include
#  if __has_include (<experimental/simd>)
#    include <experimental/simd>
#  endif
#endif

#if __cpp_lib_experimental_parallel_simd >= 201803

TTS_CASE_TPL( "Check for experimental::simd compliance"
            , TTS_SIGNED_NUMERIC_TYPES, TTS_UNSIGNED_NUMERIC_TYPES
            )
<typename T>(::tts::type<T>)
{
  using std_type      = std::experimental::simd<T>;
  using eve_type      = eve::experimental::simd<T>;
  using std_mask_type = std::experimental::simd_mask<T>;
  using eve_mask_type = eve::experimental::simd_mask<T>;

  TTS_EQUAL(sizeof(std_type)      , sizeof(eve_type)      );
  TTS_EQUAL(sizeof(std_mask_type) , sizeof(eve_mask_type) );
};

TTS_CASE_TPL( "Check for experimental::native_simd compliance"
            , TTS_SIGNED_NUMERIC_TYPES, TTS_UNSIGNED_NUMERIC_TYPES
            )
<typename T>(::tts::type<T>)
{
  using std_type      = std::experimental::native_simd<T>;
  using eve_type      = eve::experimental::native_simd<T>;
  using std_mask_type = std::experimental::native_simd_mask<T>;
  using eve_mask_type = eve::experimental::native_simd_mask<T>;

  TTS_EQUAL(sizeof(std_type)      , sizeof(eve_type)      );
  TTS_EQUAL(sizeof(std_mask_type) , sizeof(eve_mask_type) );
};
#endif
