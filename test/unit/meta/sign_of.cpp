//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <tts/tests/types.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <type_traits>

TTS_CASE_TPL("Check as_integer on scalar", TTS_NUMERIC_TYPES)
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
}

TTS_CASE_TPL("Check as_integer on logical scalar", TTS_NUMERIC_TYPES)
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
}

TTS_CASE_TPL("Check as_integer on wide", TTS_NUMERIC_TYPES)
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
}

TTS_CASE_TPL("Check as_integer on logical wide", TTS_NUMERIC_TYPES)
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
}
