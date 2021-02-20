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
  using identity = eve::detail::perform_identity;

  TTS_EXPR_IS( (find_optimized_pattern<0,1>())                                  , identity );
  TTS_EXPR_IS( (find_optimized_pattern<0,1,2,3>())                              , identity );
  TTS_EXPR_IS( (find_optimized_pattern<0,1,2,3,4,5,6,7>())                      , identity );
  TTS_EXPR_IS( (find_optimized_pattern<0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15>()), identity );
  TTS_EXPR_IS( (find_optimized_pattern< 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15
                                      ,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
                                      >())                                      , identity );
  TTS_EXPR_IS( (find_optimized_pattern< 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15
                                      ,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
                                      ,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47
                                      ,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63
                                      >())                                      , identity );
}

TTS_CASE("Check zero patterns get optimized")
{
  using eve::detail::find_optimized_pattern;
  using eve::callable_zero_;

  TTS_EXPR_IS( (find_optimized_pattern<-1>())                       , callable_zero_ );
  TTS_EXPR_IS( (find_optimized_pattern<-1,-1>())                    , callable_zero_ );
  TTS_EXPR_IS( (find_optimized_pattern<-1,-1,-1,-1>())              , callable_zero_ );
  TTS_EXPR_IS( (find_optimized_pattern<-1,-1,-1,-1,-1,-1,-1,-1>())  , callable_zero_ );
  TTS_EXPR_IS( (find_optimized_pattern<-1,-1,-1,-1,-1,-1,-1,-1
                                      ,-1,-1,-1,-1,-1,-1,-1,-1>())  , callable_zero_ );
  TTS_EXPR_IS( (find_optimized_pattern<-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      >())                          , callable_zero_ );
  TTS_EXPR_IS( (find_optimized_pattern<-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      , -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      >())                          , callable_zero_ );
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

  // <0 0> is broadcast
  TTS_EXPR_IS( (find_optimized_pattern<-1, 0>()), callable_gather_low_ );
  TTS_EXPR_IS( (find_optimized_pattern< 0,-1>()), callable_gather_low_ );

  TTS_EXPR_IS( (find_optimized_pattern< 0, 1, 0, 1>()), callable_gather_low_ );
  TTS_EXPR_IS( (find_optimized_pattern<-1,-1, 0, 1>()), callable_gather_low_ );
  TTS_EXPR_IS( (find_optimized_pattern< 0, 1,-1,-1>()), callable_gather_low_ );

  TTS_EXPR_IS( (find_optimized_pattern< 0, 1, 2, 3, 0, 1, 2, 3>()), callable_gather_low_ );
  TTS_EXPR_IS( (find_optimized_pattern<-1,-1,-1,-1, 0, 1, 2, 3>()), callable_gather_low_ );
  TTS_EXPR_IS( (find_optimized_pattern< 0, 1, 2, 3,-1,-1,-1,-1>()), callable_gather_low_ );

  TTS_EXPR_IS( (find_optimized_pattern< 0, 1, 2, 3, 4, 5, 6, 7
                                      , 0, 1, 2, 3, 4, 5, 6, 7
                                      >()), callable_gather_low_ );
  TTS_EXPR_IS( (find_optimized_pattern< 0, 1, 2, 3, 4, 5, 6, 7
                                      ,-1,-1,-1,-1,-1,-1,-1,-1
                                      >()), callable_gather_low_ );
  TTS_EXPR_IS( (find_optimized_pattern<-1,-1,-1,-1,-1,-1,-1,-1
                                      , 0, 1, 2, 3, 4, 5, 6, 7
                                      >()), callable_gather_low_ );

  TTS_EXPR_IS( (find_optimized_pattern< 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15
                                      , 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15
                                      >()), callable_gather_low_ );
  TTS_EXPR_IS( (find_optimized_pattern< 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15
                                      ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      >()), callable_gather_low_ );
  TTS_EXPR_IS( (find_optimized_pattern<-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      , 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15
                                      >()), callable_gather_low_ );

  TTS_EXPR_IS( (find_optimized_pattern< 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15
                                      ,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
                                      , 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15
                                      ,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
                                      >()), callable_gather_low_ );
  TTS_EXPR_IS( (find_optimized_pattern< 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15
                                      ,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
                                      ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      >()), callable_gather_low_ );
  TTS_EXPR_IS( (find_optimized_pattern<-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      , 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15
                                      ,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
                                      >()), callable_gather_low_ );
}

TTS_CASE("Check gather_high patterns get optimized")
{
  using eve::detail::find_optimized_pattern;
  using eve::callable_gather_high_;

  // <1 1> is broadcast
  TTS_EXPR_IS( (find_optimized_pattern<-1, 1>()), callable_gather_high_ );
  TTS_EXPR_IS( (find_optimized_pattern< 1,-1>()), callable_gather_high_ );

  TTS_EXPR_IS( (find_optimized_pattern< 2, 3, 2, 3>()), callable_gather_high_ );
  TTS_EXPR_IS( (find_optimized_pattern<-1,-1, 2, 3>()), callable_gather_high_ );
  TTS_EXPR_IS( (find_optimized_pattern< 2, 3,-1,-1>()), callable_gather_high_ );

  TTS_EXPR_IS( (find_optimized_pattern< 4, 5, 6, 7, 4, 5, 6, 7>()), callable_gather_high_ );
  TTS_EXPR_IS( (find_optimized_pattern<-1,-1,-1,-1, 4, 5, 6, 7>()), callable_gather_high_ );
  TTS_EXPR_IS( (find_optimized_pattern< 4, 5, 6, 7,-1,-1,-1,-1>()), callable_gather_high_ );

  TTS_EXPR_IS( (find_optimized_pattern< 8, 9,10,11,12,13,14,15
                                      , 8, 9,10,11,12,13,14,15
                                      >()), callable_gather_high_ );
  TTS_EXPR_IS( (find_optimized_pattern< 8, 9,10,11,12,13,14,15
                                      ,-1,-1,-1,-1,-1,-1,-1,-1
                                      >()), callable_gather_high_ );
  TTS_EXPR_IS( (find_optimized_pattern<-1,-1,-1,-1,-1,-1,-1,-1
                                      , 8, 9,10,11,12,13,14,15
                                      >()), callable_gather_high_ );

  TTS_EXPR_IS( (find_optimized_pattern<16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
                                      ,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
                                      >()), callable_gather_high_ );
  TTS_EXPR_IS( (find_optimized_pattern<16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
                                      ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      >()), callable_gather_high_ );
  TTS_EXPR_IS( (find_optimized_pattern<-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      ,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31
                                      >()), callable_gather_high_ );

  TTS_EXPR_IS( (find_optimized_pattern<32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47
                                      ,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63
                                      ,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47
                                      ,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63
                                      >()), callable_gather_high_ );
  TTS_EXPR_IS( (find_optimized_pattern<32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47
                                      ,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63
                                      ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      >()), callable_gather_high_ );
  TTS_EXPR_IS( (find_optimized_pattern<-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                      ,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47
                                      ,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63
                                      >()), callable_gather_high_ );
}
