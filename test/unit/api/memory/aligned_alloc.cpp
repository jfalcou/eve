//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"
#include <eve/memory/is_aligned.hpp>
#include <eve/memory/aligned_alloc.hpp>
#include <eve/memory/aligned_dealloc.hpp>
#include <tts/tests/basic.hpp>

TTS_CASE_TPL("aligned_alloc behavior",
             std::integral_constant<int, 1>,
             std::integral_constant<int, 2>,
             std::integral_constant<int, 4>,
             std::integral_constant<int, 8>,
             std::integral_constant<int, 16>,
             std::integral_constant<int, 32>,
             std::integral_constant<int, 64>,
             std::integral_constant<int, 128>)
{
  auto ptr = eve::aligned_alloc<T::value>(7 * sizeof(float));

  TTS_EXPECT(eve::is_aligned<T::value>(ptr));

  eve::aligned_ptr<int, T::value> iptr = ptr;

  TTS_EXPECT(eve::is_aligned<T::value>(iptr));

  eve::aligned_dealloc(ptr);
}
