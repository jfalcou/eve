//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <type_traits>

TTS_CASE_TPL( "Check sign_of on scalar",
              TTS_SIGNED_NUMERIC_TYPES, TTS_UNSIGNED_NUMERIC_TYPES
            )
<typename T>(::tts::type<T>)
{
  using eve::detail::sign_of_t;

  if constexpr( std::is_signed_v<T> )
  {
    TTS_TYPE_IS((sign_of_t<T>) , signed );
  }
  else
  {
    TTS_TYPE_IS((sign_of_t<T>) , unsigned );
  }
};

TTS_CASE_TPL( "Check sign_of on logical scalar",
              TTS_SIGNED_NUMERIC_TYPES, TTS_UNSIGNED_NUMERIC_TYPES
            )
<typename T>(::tts::type<T>)
{
  using eve::detail::sign_of_t;
  using eve::logical;

  if constexpr( std::is_signed_v<T> )
  {
    TTS_TYPE_IS((sign_of_t<logical<T>>) , signed );
  }
  else
  {
    TTS_TYPE_IS((sign_of_t<logical<T>>) , unsigned );
  }
};

TTS_CASE_TPL( "Check sign_of on wide",
              TTS_SIGNED_NUMERIC_TYPES, TTS_UNSIGNED_NUMERIC_TYPES
            )
<typename T>(::tts::type<T>)
{
  using eve::detail::sign_of_t;
  using eve::wide;

  if constexpr( std::is_signed_v<T> )
  {
    TTS_TYPE_IS((sign_of_t<wide<T>>) , signed );
  }
  else
  {
    TTS_TYPE_IS((sign_of_t<wide<T>>) , unsigned );
  }
};

TTS_CASE_TPL( "Check sign_of on logical wide",
              TTS_SIGNED_NUMERIC_TYPES, TTS_UNSIGNED_NUMERIC_TYPES
            )
<typename T>(::tts::type<T>)
{
  using eve::detail::sign_of_t;
  using eve::logical;
  using eve::wide;

  if constexpr( std::is_signed_v<T> )
  {
    TTS_TYPE_IS((sign_of_t<logical<wide<T>>>) , signed );
  }
  else
  {
    TTS_TYPE_IS((sign_of_t<logical<wide<T>>>) , unsigned );
  }
};
