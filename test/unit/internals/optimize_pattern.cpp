//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

TTS_CASE("Check identity patterns get optimized")
{
  using eve::detail::find_optimized_shuffle_pattern;
  using eve::detail::bound;
  using identity = eve::detail::identity_swizzle;

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<2,0,1>())
              , (bound<identity, eve::pattern_t<0, 1>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<4,0, 1, 2, 3>())
              , (bound<identity, eve::pattern_t<0, 1, 2, 3>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,0, 1, 2, 3, 4, 5, 6, 7>())
              , (bound<identity, eve::pattern_t<0, 1, 2, 3, 4, 5, 6, 7> >)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern < 16
                                        , 0, 1, 2, 3, 4, 5, 6, 7
                                        , 8, 9, 10, 11, 12, 13, 14, 15
                                        >())
              , (bound<identity, eve::pattern_t < 0, 1, 2, 3, 4, 5, 6, 7
                                                , 8, 9, 10, 11, 12, 13, 14, 15
                                                >>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern < 32
                                        , 0, 1, 2, 3, 4, 5, 6, 7
                                        , 8, 9, 10, 11, 12, 13, 14, 15
                                        , 16, 17, 18, 19, 20, 21, 22, 23
                                        , 24, 25, 26, 27, 28, 29, 30, 31
                                        >())
              , (bound<identity, eve::pattern_t < 0, 1, 2, 3, 4, 5, 6, 7
                                                , 8, 9, 10, 11, 12, 13, 14, 15
                                                , 16, 17, 18, 19, 20, 21, 22, 23
                                                , 24, 25, 26, 27, 28, 29, 30, 31
                                                >>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern < 64
                                        , 0, 1, 2, 3, 4, 5, 6, 7
                                        , 8, 9, 10, 11, 12, 13, 14, 15
                                        , 16, 17, 18, 19, 20, 21, 22, 23
                                        , 24, 25, 26, 27, 28, 29, 30, 31
                                        , 32, 33, 34, 35, 36, 37, 38, 39
                                        , 40, 41, 42, 43, 44, 45, 46, 47
                                        , 48, 49, 50, 51, 52, 53, 54, 55
                                        , 56, 57, 58, 59, 60, 61, 62, 63
                                        >())
              , (bound<identity, eve::pattern_t < 0, 1, 2, 3, 4, 5, 6, 7
                                                , 8, 9, 10, 11, 12, 13, 14, 15
                                                , 16, 17, 18, 19, 20, 21, 22, 23
                                                , 24, 25, 26, 27, 28, 29, 30, 31
                                                , 32, 33, 34, 35, 36, 37, 38, 39
                                                , 40, 41, 42, 43, 44, 45, 46, 47
                                                , 48, 49, 50, 51, 52, 53, 54, 55
                                                , 56, 57, 58, 59, 60, 61, 62, 63
                                                >>)
              );
};

TTS_CASE("Check zero patterns get optimized")
{
  using eve::detail::find_optimized_shuffle_pattern;
  using eve::detail::bound;
  using zero = eve::detail::zero_swizzle;

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern< 1,-1>()), (bound<zero,eve::fixed<1>>));
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern< 2,-1,-1>()), (bound<zero,eve::fixed<2>>));
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern< 4,-1,-1,-1,-1>()), (bound<zero,eve::fixed<4>>));
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern< 8,-1,-1,-1,-1,-1,-1,-1,-1>()), (bound<zero,eve::fixed<8>>));
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1>())
              , (bound<zero,eve::fixed<16>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern <32
                                        ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                        ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                        >()
                )
              , (bound<zero,eve::fixed<32>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern <64
                                        ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                        ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                        ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                        ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                        >()
                )
              , (bound<zero,eve::fixed<64>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern <128
                                        ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                        ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                        ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                        ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                        ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                        ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                        ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                        ,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
                                        >()
                )
              , (bound<zero,eve::fixed<128>>)
              );
};

TTS_CASE("Check broadcast patterns get optimized")
{
  using eve::detail::find_optimized_shuffle_pattern;
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
        TTS_EXPR_IS ( (find_optimized_shuffle_pattern< sizeof...(Q), val(Q,i)... >())
                    , (bound< callable_broadcast_
                            , eve::index_t<i>
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
};

TTS_CASE("Check swap_adjacent_groups patterns get optimized")
{
  using eve::fixed;
  using eve::detail::find_optimized_shuffle_pattern;
  using eve::detail::bound;
  using eve::callable_swap_adjacent_groups_;

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<4,1,0>())
              , (bound<callable_swap_adjacent_groups_,fixed<1>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<2,1,0>())
              , (bound<callable_swap_adjacent_groups_,fixed<1>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<4,1,0,3,2>())
              , (bound<callable_swap_adjacent_groups_,fixed<1>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<4,2,3,0,1>())
              , (bound<callable_swap_adjacent_groups_,fixed<2>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,1,0,3,2,5,4,7,6>())
              , (bound<callable_swap_adjacent_groups_,fixed<1>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,2,3,0,1,6,7,4,5>())
              , (bound<callable_swap_adjacent_groups_,fixed<2>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,4,5,6,7,0,1,2,3>())
              , (bound<callable_swap_adjacent_groups_,fixed<4>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,1,0,3,2,5,4,7,6,9,8,11,10,13,12,15,14>())
              , (bound<callable_swap_adjacent_groups_,fixed<1>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,2,3,0,1,6,7,4,5,10,11,8,9,14,15,12,13 >())
              , (bound<callable_swap_adjacent_groups_,fixed<2>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,4,5,6,7,0,1,2,3,12,13,14,15,8,9,10,11 >())
              , (bound<callable_swap_adjacent_groups_,fixed<4>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7 >())
              , (bound<callable_swap_adjacent_groups_,fixed<8>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<32,1,0,3,2,5,4,7,6,9,8,11,10,13,12,15,14,17,16,19,18,21,20,23,22,25,24,27,26,29,28,31,30 >())
              , (bound<callable_swap_adjacent_groups_,fixed<1>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<32,2,3,0,1,6,7,4,5,10,11,8,9,14,15,12,13,18,19,16,17,22,23,20,21,26,27,24,25,30,31,28,29 >())
              , (bound<callable_swap_adjacent_groups_,fixed<2>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<32,4,5,6,7,0,1,2,3,12,13,14,15,8,9,10,11,20,21,22,23,16,17,18,19,28,29,30,31,24,25,26,27 >())
              , (bound<callable_swap_adjacent_groups_,fixed<4>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<32,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,24,25,26,27,28,29,30,31,16,17,18,19,20,21,22,23 >())
              , (bound<callable_swap_adjacent_groups_,fixed<8>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<32,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15 >())
              , (bound<callable_swap_adjacent_groups_,fixed<16>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<64,1,0,3,2,5,4,7,6,9,8,11,10,13,12,15,14,17,16,19,18,21,20,23,22,25,24,27,26,29,28,31,30,33,32,35,34,37,36,39,38,41,40,43,42,45,44,47,46,49,48,51,50,53,52,55,54,57,56,59,58,61,60,63,62 >())
              , (bound<callable_swap_adjacent_groups_,fixed<1>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<64,2,3,0,1,6,7,4,5,10,11,8,9,14,15,12,13,18,19,16,17,22,23,20,21,26,27,24,25,30,31,28,29,34,35,32,33,38,39,36,37,42,43,40,41,46,47,44,45,50,51,48,49,54,55,52,53,58,59,56,57,62,63,60,61 >())
              , (bound<callable_swap_adjacent_groups_,fixed<2>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<64,4,5,6,7,0,1,2,3,12,13,14,15,8,9,10,11,20,21,22,23,16,17,18,19,28,29,30,31,24,25,26,27,36,37,38,39,32,33,34,35,44,45,46,47,40,41,42,43,52,53,54,55,48,49,50,51,60,61,62,63,56,57,58,59 >())
              , (bound<callable_swap_adjacent_groups_,fixed<4>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<64,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,7,24,25,26,27,28,29,30,31,16,17,18,19,20,21,22,23,40,41,42,43,44,45,46,47,32,33,34,35,36,37,38,39,56,57,58,59,60,61,62,63,48,49,50,51,52,53,54,55 >())
              , (bound<callable_swap_adjacent_groups_,fixed<8>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<64,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47 >())
              , (bound<callable_swap_adjacent_groups_,fixed<16>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<64,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31 >())
              , (bound<callable_swap_adjacent_groups_,fixed<32>>)
              );
};

TTS_CASE("Check broadcast_group patterns get optimized")
{
  using eve::fixed;
  using eve::index_t;
  using eve::detail::find_optimized_shuffle_pattern;
  using eve::detail::bound;
  using eve::callable_broadcast_group_;

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<4,0,1,0,1>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<0>,fixed<4>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<4,2,3,2,3>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<1>,fixed<4>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,0,1,0,1>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<0>,fixed<4>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,2,3,2,3>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<1>,fixed<4>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,4,5,4,5>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<2>,fixed<4>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,6,7,6,7>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<3>,fixed<4>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,0,1,0,1,0,1,0,1>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<0>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,2,3,2,3,2,3,2,3>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<1>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,4,5,4,5,4,5,4,5>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<2>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,6,7,6,7,6,7,6,7>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<3>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,0,1,2,3,0,1,2,3>())
              , (bound<callable_broadcast_group_,fixed<4>,index_t<0>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,4,5,6,7,4,5,6,7>())
              , (bound<callable_broadcast_group_,fixed<4>,index_t<1>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,0,1,0,1>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<0>,fixed<4>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,2,3,2,3>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<1>,fixed<4>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,4,5,4,5>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<2>,fixed<4>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,6,7,6,7>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<3>,fixed<4>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,8,9,8,9>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<4>,fixed<4>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,10,11,10,11>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<5>,fixed<4>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,12,13,12,13>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<6>,fixed<4>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,14,15,14,15>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<7>,fixed<4>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,0,1,0,1,0,1,0,1>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<0>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,2,3,2,3,2,3,2,3>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<1>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,4,5,4,5,4,5,4,5>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<2>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,6,7,6,7,6,7,6,7>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<3>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,8,9,8,9,8,9,8,9>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<4>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,10,11,10,11,10,11,10,11>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<5>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,12,13,12,13,12,13,12,13>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<6>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,14,15,14,15,14,15,14,15>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<7>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,0,1,2,3,0,1,2,3>())
              , (bound<callable_broadcast_group_,fixed<4>,index_t<0>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,4,5,6,7,4,5,6,7>())
              , (bound<callable_broadcast_group_,fixed<4>,index_t<1>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,8,9,10,11,8,9,10,11>())
              , (bound<callable_broadcast_group_,fixed<4>,index_t<2>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,12,13,14,15,12,13,14,15>())
              , (bound<callable_broadcast_group_,fixed<4>,index_t<3>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,8,9,10,11,12,13,14,15>())
              , (bound<callable_broadcast_group_,fixed<8>,index_t<1>,fixed<8>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<0>,fixed<16>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,2,3,2,3,2,3,2,3,2,3,2,3,2,3,2,3>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<1>,fixed<16>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,4,5,4,5,4,5,4,5,4,5,4,5,4,5,4,5>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<2>,fixed<16>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,6,7,6,7,6,7,6,7,6,7,6,7,6,7,6,7>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<3>,fixed<16>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,8,9,8,9,8,9,8,9,8,9,8,9,8,9,8,9>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<4>,fixed<16>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,10,11,10,11,10,11,10,11,10,11,10,11,10,11,10,11>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<5>,fixed<16>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,12,13,12,13,12,13,12,13,12,13,12,13,12,13,12,13>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<6>,fixed<16>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,14,15,14,15,14,15,14,15,14,15,14,15,14,15,14,15>())
              , (bound<callable_broadcast_group_,fixed<2>,index_t<7>,fixed<16>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,0,1,2,3,0,1,2,3,0,1,2,3,0,1,2,3>())
              , (bound<callable_broadcast_group_,fixed<4>,index_t<0>,fixed<16>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,4,5,6,7,4,5,6,7,4,5,6,7,4,5,6,7>())
              , (bound<callable_broadcast_group_,fixed<4>,index_t<1>,fixed<16>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,8,9,10,11,8,9,10,11,8,9,10,11,8,9,10,11>())
              , (bound<callable_broadcast_group_,fixed<4>,index_t<2>,fixed<16>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,12,13,14,15,12,13,14,15,12,13,14,15,12,13,14,15>())
              , (bound<callable_broadcast_group_,fixed<4>,index_t<3>,fixed<16>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7>())
              , (bound<callable_broadcast_group_,fixed<8>,index_t<0>,fixed<16>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,8,9,10,11,12,13,14,15,8,9,10,11,12,13,14,15>())
              , (bound<callable_broadcast_group_,fixed<8>,index_t<1>,fixed<16>>)
              );
};

TTS_CASE("Check reverse get optimized")
{
  using eve::fixed;
  using eve::detail::find_optimized_shuffle_pattern;
  using eve::detail::bound;
  using eve::callable_reverse_;

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<4, 3, 2, 1,0>())
              , (bound<callable_reverse_>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8, 7, 6, 5, 4, 3, 2, 1, 0>())
              , (bound<callable_reverse_>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0>())
              , (bound<callable_reverse_>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16, 3, 2, 1, 0>())
              , (bound<eve::callable_basic_shuffle_,
                       eve::pattern_t<3, 2, 1,0>>)
              );
};

TTS_CASE("Check slide_left get optimized")
{
  using eve::index_t;
  using eve::detail::find_optimized_shuffle_pattern;
  using eve::detail::bound;
  using eve::callable_slide_left_;

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<2,1,-1>())
              , (bound<callable_slide_left_,index_t<1>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<4,1,2,3,-1>())
              , (bound<callable_slide_left_,index_t<1>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<4,2,3,-1,-1>())
              , (bound<callable_slide_left_,index_t<2>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<4,3,-1,-1,-1>())
              , (bound<callable_slide_left_,index_t<3>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,1,2,3,4,5,6,7,-1>())
              , (bound<callable_slide_left_,index_t<1>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,2,3,4,5,6,7,-1,-1>())
              , (bound<callable_slide_left_,index_t<2>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,3,4,5,6,7,-1,-1,-1>())
              , (bound<callable_slide_left_,index_t<3>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,4,5,6,7,-1,-1,-1,-1>())
              , (bound<callable_slide_left_,index_t<4>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,5,6,7,-1,-1,-1,-1,-1>())
              , (bound<callable_slide_left_,index_t<5>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,6,7,-1,-1,-1,-1,-1,-1>())
              , (bound<callable_slide_left_,index_t<6>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,7,-1,-1,-1,-1,-1,-1,-1>())
              , (bound<callable_slide_left_,index_t<7>>)
              );
};


TTS_CASE("Check slide_right get optimized")
{
  using eve::index_t;
  using eve::detail::find_optimized_shuffle_pattern;
  using eve::detail::bound;
  using eve::callable_slide_right_;

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<2,-1,0>())
              , (bound<callable_slide_right_,index_t<1>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<4,-1,0,1,2>())
              , (bound<callable_slide_right_,index_t<1>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<4,-1,-1,0,1>())
              , (bound<callable_slide_right_,index_t<2>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<4,-1,-1,-1,0>())
              , (bound<callable_slide_right_,index_t<3>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,-1,0,1,2,3,4,5,6>())
              , (bound<callable_slide_right_,index_t<1>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,-1,-1,0,1,2,3,4,5>())
              , (bound<callable_slide_right_,index_t<2>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,-1,-1,-1,0,1,2,3,4>())
              , (bound<callable_slide_right_,index_t<3>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,-1,-1,-1,-1,0,1,2,3>())
              , (bound<callable_slide_right_,index_t<4>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,-1,-1,-1,-1,-1,0,1,2>())
              , (bound<callable_slide_right_,index_t<5>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,-1,-1,-1,-1,-1,-1,0,1>())
              , (bound<callable_slide_right_,index_t<6>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,-1,-1,-1,-1,-1,-1,-1,0>())
              , (bound<callable_slide_right_,index_t<7>>)
              );
};

TTS_CASE("Check slide_right get optimized")
{
  using eve::fixed;
  using eve::detail::find_optimized_shuffle_pattern;
  using eve::detail::bound;
  using deinter = eve::callable_deinterleave_groups_shuffle_;

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<4,0,2,1,3>())
              , (bound<deinter, fixed<1>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,0,2,4,6,1,3,5,7>())
              , (bound<deinter, fixed<1>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<8,0,1,4,5,2,3,6,7>())
              , (bound<deinter, fixed<2>>)
              );

  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,0,2,4,6,8,10,12,14,1,3,5,7,9,11,13,15>())
              , (bound<deinter, fixed<1>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,0,1,4,5,8,9,12,13,2,3,6,7,10,11,14,15>())
              , (bound<deinter, fixed<2>>)
              );
  TTS_EXPR_IS ( (find_optimized_shuffle_pattern<16,0,1,2,3,8,9,10,11,4,5,6,7,12,13,14,15>())
              , (bound<deinter, fixed<4>>)
              );
};
