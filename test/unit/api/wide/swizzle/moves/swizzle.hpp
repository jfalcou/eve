//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/logical.hpp>
#include <eve/wide.hpp>

template<typename T, typename Env, typename Filler>
void test_unpack(Env& runtime, bool verbose, Filler filler)
{
  using type4 = typename T::template reshape<eve::fixed<4>>;
  using type2 = typename T::template reshape<eve::fixed<2>>;
  using v_t   = eve::element_type_t<type4>;

  T simd(filler);

  if constexpr(eve::cardinal_v<T> > 1)
  {
    std::cout << "using pattern " << eve::pattern< 0, 1, 0, 1> << "\n";
    TTS_EQUAL((simd[eve::pattern< 0, 1, 0, 1>]), type4(simd[0],simd[1],simd[0],simd[1]));

    std::cout << "using pattern " << eve::pattern< 0, 1,-1,-1> << "\n";
    TTS_EQUAL((simd[eve::pattern< 0, 1,-1,-1>]), type4(simd[0],simd[1],v_t(0),v_t(0)));
  }

  if constexpr(eve::cardinal_v<T> > 2)
  {
    std::cout << "using pattern " << eve::pattern< 2, 3, 2, 3> << "\n";
    TTS_EQUAL((simd[eve::pattern< 2, 3, 2, 3>]), type4(simd[2],simd[3],simd[2],simd[3]));

   std::cout << "using pattern " << eve::pattern< 2, 3,-1,-1> << "\n";
    TTS_EQUAL((simd[eve::pattern< 2, 3,-1,-1>]), type4(simd[2],simd[3],v_t(0),v_t(0)));

    std::cout << "using pattern " << eve::pattern< 2, 3> << "\n";
    TTS_EQUAL((simd[eve::pattern< 2, 3>]), type2(simd[2],simd[3]));
  }
}

TTS_CASE_TPL( "Check unpack swizzle for arithmetic type", EVE_TYPE )
{
  test_unpack<T>(runtime, verbose,  [](int i, int) { return 1+i; });
}

TTS_CASE_TPL( "Check unpack swizzle for logical type", EVE_TYPE )
{
  test_unpack<eve::logical<T>>(runtime, verbose,  [](int i, int) { return i%3==0; });
}
