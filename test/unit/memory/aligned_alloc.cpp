//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"
#include <eve/memory/is_aligned.hpp>
#include <eve/memory/aligned_alloc.hpp>
#include <eve/memory/aligned_dealloc.hpp>

TTS_CASE_TPL( "aligned_alloc behavior"
            , std::integral_constant<int,    8>
            , std::integral_constant<int,   16>
            , std::integral_constant<int,   32>
            , std::integral_constant<int,   64>
            , std::integral_constant<int,  128>
            , std::integral_constant<int,  256>
            , std::integral_constant<int,  512>
            , std::integral_constant<int, 1024>
            )
{
  auto ptr = eve::aligned_alloc<T::value>( (3 + sizeof(float)) * T::value);

  TTS_EXPECT(eve::is_aligned<T::value>(ptr));

  eve::aligned_ptr<int, T::value> iptr = ptr;

  TTS_EXPECT(eve::is_aligned<T::value>(iptr));

  eve::aligned_dealloc(ptr);
}
