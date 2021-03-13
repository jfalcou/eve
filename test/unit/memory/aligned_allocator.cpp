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
#include <eve/memory/aligned_allocator.hpp>

#include <vector>

TTS_CASE_TPL("aligned_allocator behavior"
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
  std::vector<double, eve::aligned_allocator<double, T::value>> x(1337);

  TTS_EXPECT(eve::is_aligned<T::value>(x.data()));
}

TTS_CASE_TPL("aligned_allocator comparisons"
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
  eve::aligned_allocator<double, T::value>     a1, a2;
  eve::aligned_allocator<float, T::value>      b1;
  eve::aligned_allocator<double, 2 * T::value> c1;

  TTS_EQUAL(a1, a2);
  TTS_NOT_EQUAL(a1, b1);
  TTS_NOT_EQUAL(a1, c1);
}

TTS_CASE_TPL("aligned_allocator rebind"
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
  TTS_TYPE_IS((typename eve::aligned_allocator<double, T::value>::template rebind<float>::other),
              (eve::aligned_allocator<float, T::value>));
}
