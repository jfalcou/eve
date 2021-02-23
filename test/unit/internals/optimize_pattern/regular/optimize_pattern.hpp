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
  using eve::detail::bound;
  using identity = eve::detail::perform_identity;

  [&]<std::ptrdiff_t... R>(std::integer_sequence<std::ptrdiff_t,R...>)
  {
    auto g = [&]<std::ptrdiff_t... N>( std::integer_sequence<std::ptrdiff_t,N...>)
    {
      TTS_EXPR_IS ( (find_optimized_pattern< N... >())
                  , (bound<identity,eve::pattern_t<N...>>)
                  );
    };

    (g( std::make_integer_sequence<std::ptrdiff_t,(1<<(R+1))>{}),...);

  }(std::make_integer_sequence<std::ptrdiff_t,6>{});
}

TTS_CASE("Check zero patterns get optimized")
{
  using eve::detail::find_optimized_pattern;
  using eve::detail::bound;
  using zero = eve::detail::perform_zero;

  [&]<std::ptrdiff_t... R>(std::integer_sequence<std::ptrdiff_t,R...>)
  {
    auto g = [&]<std::ptrdiff_t... N>( std::integer_sequence<std::ptrdiff_t,N...>)
    {
      TTS_EXPR_IS ( (find_optimized_pattern< (N,-1)... >())
                  , (bound<zero,eve::fixed<sizeof...(N)>>)
                  );
    };

    (g( std::make_integer_sequence<std::ptrdiff_t,(1<<R)>{}),...);

  }(std::make_integer_sequence<std::ptrdiff_t,7>{});
}

TTS_CASE("Check broadcast patterns get optimized")
{
  using eve::detail::find_optimized_pattern;
  using eve::detail::bound;
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
        TTS_EXPR_IS ( (find_optimized_pattern< val(Q,i)... >())
                    , (bound< callable_broadcast_
                            , std::integral_constant<std::ptrdiff_t,i>
                            , eve::fixed<sizeof...(Q)>
                            >
                      )
                    );
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
