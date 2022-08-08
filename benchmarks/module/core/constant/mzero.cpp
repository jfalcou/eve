//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include <eve/module/core/constant/mzero.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <cstddef>
#include <limits>

#if defined(EVE_COMP_IS_MSVC)
#  pragma warning(push)
#  pragma warning(disable : 4723) // 1/0 is OK for this test
#endif

TTS_CASE("Check mzero return type")
{
  TTS_EXPR_IS(eve::Mzero<float>(), float);
  TTS_EXPR_IS(eve::Mzero<double>(), double);

  TTS_EXPR_IS(eve::Mzero<std::int8_t>(), std::int8_t);
  TTS_EXPR_IS(eve::Mzero<std::int16_t>(), std::int16_t);
  TTS_EXPR_IS(eve::Mzero<std::int32_t>(), std::int32_t);
  TTS_EXPR_IS(eve::Mzero<std::int64_t>(), std::int64_t);

  TTS_EXPR_IS(eve::Mzero<std::uint8_t>(), std::uint8_t);
  TTS_EXPR_IS(eve::Mzero<std::uint16_t>(), std::uint16_t);
  TTS_EXPR_IS(eve::Mzero<std::uint32_t>(), std::uint32_t);
  TTS_EXPR_IS(eve::Mzero<std::uint64_t>(), std::uint64_t);
}

TTS_CASE("Check mzero behavior")
{
  TTS_EQUAL(eve::Mzero<std::uint8_t>(), std::uint8_t(0));
  TTS_EQUAL(eve::Mzero<std::uint16_t>(), std::uint16_t(0));
  TTS_EQUAL(eve::Mzero<std::int8_t>(), std::int8_t(0));
  TTS_EQUAL(eve::Mzero<std::int16_t>(), std::int16_t(0));

  TTS_EQUAL(1.0 / eve::Mzero<double>(), -std::numeric_limits<double>::infinity());
  TTS_EQUAL(1.0 / eve::Mzero<float>(), -std::numeric_limits<float>::infinity());
}

#if defined(EVE_COMP_IS_MSVC)
#  pragma warning(pop)
#endif
