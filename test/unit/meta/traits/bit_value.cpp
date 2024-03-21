//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/traits/bit_value.hpp>

template<typename T>
constexpr eve::bit_value_t<T,float> f(T) { return {}; }

template<typename T>
constexpr eve::bit_value_t<T,eve::wide<float,eve::fixed<4>>> g(T) { return {}; }

TTS_CASE("Scalar bit_value")
{
  TTS_TYPE_IS( eve::bit_value_t<double>                             , double      );
  TTS_TYPE_IS((eve::bit_value_t<std::uint8_t, std::int8_t>)         , std::uint8_t);
  TTS_TYPE_IS((eve::bit_value_t<float, std::int32_t, std::uint32_t>), float       );

  [[maybe_unused]] double x = {};
  TTS_EXPECT_NOT_COMPILES(x, { f(x); });
};

TTS_CASE("SIMD bit_value")
{
  using eve::wide;

  TTS_TYPE_IS( eve::bit_value_t<wide<double>>                                         , wide<double>      );
  TTS_TYPE_IS((eve::bit_value_t<wide<std::uint8_t>, wide<std::int16_t>>)              , wide<std::uint8_t>);
  TTS_TYPE_IS((eve::bit_value_t<wide<float>, wide<std::int64_t>, wide<std::uint32_t>>), wide<float>       );

  [[maybe_unused]] eve::wide<double,eve::fixed<4>> x = {};
  TTS_EXPECT_NOT_COMPILES(x, { g(x); });
};

TTS_CASE("Mixed scalar/SIMD bit_value")
{
  using eve::wide;

  TTS_TYPE_IS((eve::bit_value_t<wide<std::uint8_t>, std::int8_t>)                   , wide<std::uint8_t>);
  TTS_TYPE_IS((eve::bit_value_t<wide<std::uint8_t>, std::int8_t, eve::wide<double>>), wide<std::uint8_t>);
  TTS_TYPE_IS((eve::bit_value_t<wide<float>, wide<std::int64_t>, std::uint32_t>)    , wide<float>       );
  TTS_TYPE_IS((eve::bit_value_t<wide<std::int32_t>, float>)                         , wide<std::int32_t>);

  [[maybe_unused]] double                   x = {};
  TTS_EXPECT_NOT_COMPILES (x, { g(x); });

  [[maybe_unused]] eve::wide<std::int32_t>  y = {};
  TTS_EXPECT_COMPILES     (y, { f(y); });

  [[maybe_unused]] eve::wide<std::int64_t>  z = {};
  TTS_EXPECT_NOT_COMPILES (z, { f(z); });
};

