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
void test_gather_high(Env& runtime, bool verbose, Filler filler)
{
  if constexpr(EVE_CARDINAL > 1)
  {
    T simd(filler);
    using out_t = eve::as_wide_t<T,eve::fixed<2>>;

    TTS_EQUAL( (simd[eve::pattern<-1, 1>]), (out_t{0           , simd.get(1)}));
    TTS_EQUAL( (simd[eve::pattern< 1,-1>]), (out_t{simd.get(1) , 0}          ));

    auto f = [&]<std::ptrdiff_t... N>( std::integer_sequence<std::ptrdiff_t,N...>)
    {
      using value_t = eve::element_type_t<T>;
      T ref  ([&](auto i, auto c) { return simd.get(c/2 + i%(c/2));                  });
      T refl0([&](auto i, auto c) { return i < (c/2) ? simd.get(i+c/2) : value_t{0}; });
      T ref0l([&](auto i, auto c) { return i < (c/2) ? value_t{0}      : simd.get(i);});

      constexpr int O = sizeof...(N);
      TTS_EQUAL( (eve::gather_high(simd)                                  ), ref  );
      TTS_EQUAL( (simd[eve::pattern<O+N...          , O+N...          > ] ), ref  );
      TTS_EQUAL( (simd[eve::pattern<O+N...          , ((void)N,-1 )...> ] ), refl0);
      TTS_EQUAL( (simd[eve::pattern<((void)N,-1)... , O+N...          > ] ), ref0l);
    };

    f( std::make_integer_sequence<std::ptrdiff_t,EVE_CARDINAL/2>{});
  }
  else
  {
    TTS_PASS("No eve::gather_high on cardinal 1 wide");
  }
}

TTS_CASE_TPL("Check gather_high swizzle for arithmetic type", EVE_TYPE )
{
  test_gather_high<T>(runtime, verbose, [](int i, int) { return 1+i; } );
}

TTS_CASE_TPL("Check gather_high swizzle for logical type", EVE_TYPE )
{
  test_gather_high<eve::logical<T>>(runtime, verbose, [](int i, int) { return i%3 == 0; });
}
