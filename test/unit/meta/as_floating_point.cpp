//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/traits/as_floating_point.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>
#include <type_traits>

TTS_CASE("Check as_floating_point on scalar")
{
  using eve::as_floating_point_t;

  TTS_TYPE_IS((as_floating_point_t<float>         ) , float );
  TTS_TYPE_IS((as_floating_point_t<std::int32_t>  ) , float );
  TTS_TYPE_IS((as_floating_point_t<std::uint32_t> ) , float );

  TTS_TYPE_IS((as_floating_point_t<double>        ) , double );
  TTS_TYPE_IS((as_floating_point_t<std::int64_t>  ) , double );
  TTS_TYPE_IS((as_floating_point_t<std::uint64_t> ) , double );
};

TTS_CASE("Check as_floating_point on logical scalar")
{
  using eve::as_floating_point_t;
  using eve::logical;

  TTS_TYPE_IS((as_floating_point_t<logical<float>>        ) , logical<float> );
  TTS_TYPE_IS((as_floating_point_t<logical<std::int32_t>> ) , logical<float> );
  TTS_TYPE_IS((as_floating_point_t<logical<std::uint32_t>>) , logical<float> );

  TTS_TYPE_IS((as_floating_point_t<logical<double>>       ) , logical<double> );
  TTS_TYPE_IS((as_floating_point_t<logical<std::int64_t>> ) , logical<double> );
  TTS_TYPE_IS((as_floating_point_t<logical<std::uint64_t>>) , logical<double> );
};

TTS_CASE("Check as_floating_point on wide")
{
  using eve::as_floating_point_t;
  using eve::wide;

  TTS_TYPE_IS((as_floating_point_t<wide<float>>        ) , wide<float> );
  TTS_TYPE_IS((as_floating_point_t<wide<std::int32_t>> ) , wide<float> );
  TTS_TYPE_IS((as_floating_point_t<wide<std::uint32_t>>) , wide<float> );

  TTS_TYPE_IS((as_floating_point_t<wide<double>>       ) , wide<double> );
  TTS_TYPE_IS((as_floating_point_t<wide<std::int64_t>> ) , wide<double> );
  TTS_TYPE_IS((as_floating_point_t<wide<std::uint64_t>>) , wide<double> );
};

TTS_CASE("Check as_floating_point on logical wide")
{
  using eve::as_floating_point_t;
  using eve::logical;
  using eve::wide;

  TTS_TYPE_IS((as_floating_point_t<logical<wide<float>>>        ) , logical<wide<float>> );
  TTS_TYPE_IS((as_floating_point_t<logical<wide<std::int32_t>>> ) , logical<wide<float>> );
  TTS_TYPE_IS((as_floating_point_t<logical<wide<std::uint32_t>>>) , logical<wide<float>> );

  TTS_TYPE_IS((as_floating_point_t<logical<wide<double>>>       ) , logical<wide<double>> );
  TTS_TYPE_IS((as_floating_point_t<logical<wide<std::int64_t>>> ) , logical<wide<double>> );
  TTS_TYPE_IS((as_floating_point_t<logical<wide<std::uint64_t>>>) , logical<wide<double>> );
};
