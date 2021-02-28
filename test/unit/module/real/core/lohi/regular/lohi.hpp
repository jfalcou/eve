//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/lohi.hpp>
#include <tuple>

TTS_CASE_TPL("Check lohi return type", EVE_TYPE)
{
  TTS_EXPR_IS((eve::lohi(T())), (std::tuple<T,T>));
}

TTS_CASE_TPL("Check (eve::lohi behavior", EVE_TYPE)
{
  {
    auto [p0, p1] = eve::lohi(T(1));
    TTS_EQUAL(p0, T(0.5));
    TTS_EQUAL(p1, T(1  ));
  }

  {
    auto [p0, p1] = eve::lohi(T(0));
    TTS_EQUAL (p0, T(0));
    TTS_EQUAL (p1, T(0));
  }
}
