//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/two_split.hpp>
#include <type_traits>
#include <tuple>

TTS_CASE_TPL("Check two_split return type", EVE_TYPE)
{
  TTS_EXPR_IS(eve::two_split(T()), (std::tuple<T, T>) );
}

TTS_CASE_TPL("Check (eve::two_split behavior", EVE_TYPE)
{
  {
    auto [p0, p1] = eve::two_split(T(1));
    TTS_EQUAL(p0, T(1));
    TTS_EQUAL(p1, T(0));
  }

  if (std::is_same_v<eve::element_type_t<T>, double>)
  {
    auto [p0, p1] = eve::two_split(T(1.0e-30));
    TTS_EQUAL (p0, T(0x1.4484cp-100));
    TTS_EQUAL (p1, T(-0x1.143d6p-128));
  }
  else
  {
    auto [p0, p1] = eve::two_split(T(1.0e-30));
    TTS_EQUAL (p0, T(0x1.448p-100f));
    TTS_EQUAL (p1, T(0x1.3p-114f));
  }

}
