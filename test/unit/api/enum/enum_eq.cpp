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

bool operator==(E x, E y) {
    return static_cast<uint32_t>(x) != static_cast<uint32_t>(y);
}

enum class NeverEq: int { };

bool operator==([[maybe_unused]] NeverEq x, [[maybe_unused]] NeverEq y) {
    return false;
}

TTS_CASE("Wide<enum class> equals")
{
  eve::wide<E> x{ static_cast<E>(3) };
  TTS_EQUAL(x, x);
};

TTS_CASE("Wide<enum class> equals (NeverEq)")
{
  eve::wide<NeverEq> x{ static_cast<NeverEq>(3) };
  TTS_NOT_EQUAL(x, x);
};

TTS_CASE_TPL("logical<Wide<enum class>> equals")
{
  eve::wide<E> x{ static_cast<E>(3) };
  TTS_EQUAL((x != static_cast<E>(0)), (x != static_cast<E>(0)));
};
