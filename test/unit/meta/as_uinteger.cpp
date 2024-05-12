//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/traits/as_integer.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <type_traits>

TTS_CASE_TPL( "Check as_uinteger on integral scalar", tts::integral_types)
<typename T>(::tts::type<T>)
{
  using eve::as_uinteger_t;

  TTS_TYPE_IS((as_uinteger_t<T>) , std::make_unsigned_t<T> );
};

TTS_CASE("Check as_uinteger on floating-point scalar")
{
  using eve::as_uinteger_t;

  TTS_TYPE_IS((as_uinteger_t<float>)  , std::uint32_t );
  TTS_TYPE_IS((as_uinteger_t<double>) , std::uint64_t );
};

TTS_CASE_TPL( "Check as_uinteger on logical scalar", tts::arithmetic_types)
<typename T>(::tts::type<T>)
{
  using eve::as_uinteger_t;
  using eve::logical;

  TTS_TYPE_IS((as_uinteger_t<logical<T>>), (logical<as_uinteger_t<T>>));
};

TTS_CASE_TPL( "Check as_uinteger on integral wide", tts::integral_types)
<typename T>(::tts::type<T>)
{
  using eve::as_uinteger_t;
  using eve::wide;

  if constexpr( std::is_same_v<T,char> )
  {
    TTS_TYPE_IS((as_uinteger_t<wide<T>>) , wide<std::uint8_t> );
  }

  TTS_TYPE_IS((as_uinteger_t<wide<T>>) , wide<std::make_unsigned_t<T>> );
};

TTS_CASE("Check as_uinteger on floating-point wide")
{
  using eve::as_uinteger_t;
  using eve::wide;

  TTS_TYPE_IS((as_uinteger_t<wide<float>> ) , wide<std::uint32_t> );
  TTS_TYPE_IS((as_uinteger_t<wide<double>>) , wide<std::uint64_t> );
};

TTS_CASE_TPL( "Check as_uinteger on logical wide", tts::arithmetic_types)
<typename T>(::tts::type<T>)
{
  using eve::as_uinteger_t;
  using eve::logical;
  using eve::wide;

  TTS_TYPE_IS((as_uinteger_t<logical<wide<T>>>), (logical<as_uinteger_t<wide<T>>>));
};
