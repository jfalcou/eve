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
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

TTS_CASE_TPL("Check as_integer on integral scalar", TTS_INTEGRAL_TYPES)
{
  using eve::detail::as_integer_t;

  if constexpr( std::is_same_v<T,char> )
  {
    TTS_TYPE_IS((as_integer_t<T>) , std::int8_t );
  }
  else
  {
    TTS_TYPE_IS((as_integer_t<T>) , T );
  }

  TTS_TYPE_IS((as_integer_t<T, unsigned>) , std::make_unsigned_t<T> );
  TTS_TYPE_IS((as_integer_t<T,   signed>) , std::make_signed_t<T>   );
}

TTS_CASE("Check as_integer on floating-point scalar")
{
  using eve::detail::as_integer_t;

  TTS_TYPE_IS((as_integer_t<float>)          , std::int32_t  );
  TTS_TYPE_IS((as_integer_t<float, unsigned>), std::uint32_t );
  TTS_TYPE_IS((as_integer_t<float,   signed>), std::int32_t  );

  TTS_TYPE_IS((as_integer_t<double>)          , std::int64_t  );
  TTS_TYPE_IS((as_integer_t<double, unsigned>), std::uint64_t );
  TTS_TYPE_IS((as_integer_t<double,   signed>), std::int64_t  );
}

TTS_CASE_TPL("Check as_integer on logical scalar", TTS_NUMERIC_TYPES)
{
  using eve::detail::as_integer_t;
  using eve::logical;

  TTS_TYPE_IS((as_integer_t<logical<T>>)           , (logical<as_integer_t<T>>          ));
  TTS_TYPE_IS((as_integer_t<logical<T>, unsigned>) , (logical<as_integer_t<T, unsigned>>));
  TTS_TYPE_IS((as_integer_t<logical<T>,   signed>) , (logical<as_integer_t<T, signed>>  ));
}

TTS_CASE_TPL("Check as_integer on integral wide", TTS_INTEGRAL_TYPES)
{
  using eve::detail::as_integer_t;
  using eve::wide;

  if constexpr( std::is_same_v<T,char> )
  {
    TTS_TYPE_IS((as_integer_t<wide<T>>) , wide<std::int8_t> );
  }
  else
  {
    TTS_TYPE_IS((as_integer_t<wide<T>>) , wide<T> );
  }

  TTS_TYPE_IS((as_integer_t<wide<T>, unsigned>) , wide<std::make_unsigned_t<T>> );
  TTS_TYPE_IS((as_integer_t<wide<T>,   signed>) , wide<std::make_signed_t<T>>   );
}

TTS_CASE("Check as_integer on floating-point wide")
{
  using eve::detail::as_integer_t;
  using eve::wide;

  TTS_TYPE_IS((as_integer_t<wide<float>>)          , wide<std::int32_t>  );
  TTS_TYPE_IS((as_integer_t<wide<float>, unsigned>), wide<std::uint32_t> );
  TTS_TYPE_IS((as_integer_t<wide<float>,   signed>), wide<std::int32_t>  );

  TTS_TYPE_IS((as_integer_t<wide<double>>)          , wide<std::int64_t>  );
  TTS_TYPE_IS((as_integer_t<wide<double>, unsigned>), wide<std::uint64_t> );
  TTS_TYPE_IS((as_integer_t<wide<double>,   signed>), wide<std::int64_t>  );
}

TTS_CASE_TPL("Check as_integer on logical wide", TTS_NUMERIC_TYPES)
{
  using eve::detail::as_integer_t;
  using eve::logical;
  using eve::wide;

  TTS_TYPE_IS((as_integer_t<logical<wide<T>>>)           , (logical<as_integer_t<wide<T>>>          ));
  TTS_TYPE_IS((as_integer_t<logical<wide<T>>, unsigned>) , (logical<as_integer_t<wide<T>, unsigned>>));
  TTS_TYPE_IS((as_integer_t<logical<wide<T>>,   signed>) , (logical<as_integer_t<wide<T>, signed>>  ));
}
