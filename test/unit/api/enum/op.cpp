//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/arch/wide.hpp>

enum class E: uint32_t { };

TTS_CASE_TPL("Wide<enum class> eq/neq", eve::test::simd::integers)
<typename Wb>(tts::type<Wb>)
{
  enum class E: eve::element_type_t<Wb> { };
  using W = typename Wb::template retype<E>;

  W x{ static_cast<E>(3) };
  W y{ static_cast<E>(2) };

  TTS_EQUAL(x, x);
  TTS_NOT_EQUAL(x, y);
  TTS_EQUAL((x != static_cast<E>(0)), (y != static_cast<E>(0)));
};
