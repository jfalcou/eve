//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef CLAMP_HPP
#define CLAMP_HPP

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/clamp.hpp>
#include <eve/wide.hpp>

using eve::fixed;

TTS_CASE_TPL("Check clamp behavior on wide",EVE_WIDE_SIZE_RANGE())
{
  using eve::wide;

  wide<Type, T> arg0([](auto i, auto) { return Type(i + 2); }),
                arg1([](auto i, auto) { return Type(i); }),
                arg2([](auto i, auto) { return Type(i < 2 * i - 1 ? 2 * i - 1 : i + 1); }),
                ref ([](auto i, auto) { return eve::clamp ( Type(i + 2),
                                                            Type(i),
                                                            Type(i < 2 * i - 1 ? 2 * i - 1 : i + 1)
                                                          );
                                      }
                    );

  TTS_EQUAL(ref, eve::clamp(arg0, arg1, arg2));
}

TTS_CASE_TPL("Check clamp behavior on wide + scalar",EVE_WIDE_SIZE_RANGE())
{
  using eve::wide;

  wide<Type, T> arg0  ([](auto i, auto  ) { return i; }), arg1([](auto i, auto) { return i + 2; }),
                arg2  ([](auto i, auto c) { return c + i - 1; }),
                refvvs([](auto i, auto c) { return eve::clamp(Type(i), Type(i + 2), Type(100)); }),
                refvss([](auto i, auto c) { return eve::clamp(Type(i), Type(10), Type(100)); }),
                refvsv([](auto i, auto c) { return eve::clamp(Type(i), Type(0), Type(c + i - 1)); });

  TTS_EQUAL(refvvs, eve::clamp(arg0, arg1, Type(100)));
  TTS_EQUAL(refvss, eve::clamp(arg0, Type(10), Type(100)));
  TTS_EQUAL(refvsv, eve::clamp(arg0, Type(0), arg2));
}

#endif
