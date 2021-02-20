//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"
#include <eve/detail/function/patterns.hpp>

TTS_CASE("Check identity patterns get optimized")
{
  using eve::detail::find_optimized_pattern;

  [&]<std::ptrdiff_t... R>(std::integer_sequence<std::ptrdiff_t,R...>)
  {
    auto g = [&]<std::ptrdiff_t... N>( std::integer_sequence<std::ptrdiff_t,N...>)
    {
      using identity = eve::detail::perform_identity;
      TTS_EXPR_IS( (find_optimized_pattern< N... >()), identity );
    };

    (g( std::make_integer_sequence<std::ptrdiff_t,(1<<(R+1))>{}),...);

  }(std::make_integer_sequence<std::ptrdiff_t,6>{});
}

TTS_CASE("Check zero patterns get optimized")
{
  using eve::detail::find_optimized_pattern;

  [&]<std::ptrdiff_t... R>(std::integer_sequence<std::ptrdiff_t,R...>)
  {
    auto g = [&]<std::ptrdiff_t... N>( std::integer_sequence<std::ptrdiff_t,N...>)
    {
      using eve::callable_zero_;
      TTS_EXPR_IS( (find_optimized_pattern< (N,-1)... >()), callable_zero_ );
    };

    (g( std::make_integer_sequence<std::ptrdiff_t,(1<<R)>{}),...);

  }(std::make_integer_sequence<std::ptrdiff_t,7>{});
}

TTS_CASE("Check broadcast patterns get optimized")
{
  using eve::detail::find_optimized_pattern;
  using eve::callable_broadcast_;

  // Test all broadcast of size 1->64 with every index from 1->64
  [&]<std::ptrdiff_t... R>(std::integer_sequence<std::ptrdiff_t,R...>)
  {
    auto g = [&]< std::ptrdiff_t... N
                , std::ptrdiff_t... Q
                >( std::integer_sequence<std::ptrdiff_t,N...>
                 , std::integer_sequence<std::ptrdiff_t,Q...>
                 )
    {
      auto val = [](auto,auto i) { return i; };
      auto f = [&](auto i)
      {
        TTS_EXPR_IS( (find_optimized_pattern< val(Q,i)... >()), callable_broadcast_ );
      };
      (f(std::integral_constant<std::ptrdiff_t,N>{}),...);
    };

    (g( std::make_integer_sequence<std::ptrdiff_t,64>{}
      , std::make_integer_sequence<std::ptrdiff_t,(1<<R)>{}
      )
    ,...
    );

  }(std::make_integer_sequence<std::ptrdiff_t,7>{});
}

TTS_CASE("Check gather_low patterns get optimized")
{
  using eve::detail::find_optimized_pattern;
  using eve::callable_gather_low_;

  TTS_EXPR_IS( (find_optimized_pattern<-1, 0>()), callable_gather_low_ );
  TTS_EXPR_IS( (find_optimized_pattern< 0,-1>()), callable_gather_low_ );

  [&]<std::ptrdiff_t... R>(std::integer_sequence<std::ptrdiff_t,R...>)
  {
    auto g = [&]<std::ptrdiff_t... N>( std::integer_sequence<std::ptrdiff_t,N...>)
    {
      TTS_EXPR_IS( (find_optimized_pattern<N...     ,N...     >()), callable_gather_low_ );
      TTS_EXPR_IS( (find_optimized_pattern<N...     ,(N,-1)...>()), callable_gather_low_ );
      TTS_EXPR_IS( (find_optimized_pattern<(N,-1)...,N...     >()), callable_gather_low_ );
    };

    (g( std::make_integer_sequence<std::ptrdiff_t,(1<<(R+1))>{}),...);

  }(std::make_integer_sequence<std::ptrdiff_t,6>{});
}


TTS_CASE("Check gather_high patterns get optimized")
{
  using eve::detail::find_optimized_pattern;
  using eve::callable_gather_high_;

  TTS_EXPR_IS( (find_optimized_pattern<-1, 1>()), callable_gather_high_ );
  TTS_EXPR_IS( (find_optimized_pattern< 1,-1>()), callable_gather_high_ );

  [&]<std::ptrdiff_t... R>(std::integer_sequence<std::ptrdiff_t,R...>)
  {
    auto g = [&]<std::ptrdiff_t... N>( std::integer_sequence<std::ptrdiff_t,N...>)
    {
      constexpr auto O = sizeof...(N);

      TTS_EXPR_IS( (find_optimized_pattern<(O+N)...  ,(O+N)...  >()), callable_gather_high_ );
      TTS_EXPR_IS( (find_optimized_pattern<(O+N)...  ,(N,-1)... >()), callable_gather_high_ );
      TTS_EXPR_IS( (find_optimized_pattern<(N,-1)...,(O+N)...   >()), callable_gather_high_ );
    };

    (g( std::make_integer_sequence<std::ptrdiff_t,(1<<(R+1))>{}),...);

  }(std::make_integer_sequence<std::ptrdiff_t,6>{});
}
