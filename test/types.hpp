//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once
#include <array>

namespace eve::test
{
  template<typename T, typename Indexes> struct to_wide;

  template<typename T, std::size_t... N>
  struct to_wide<T, std::index_sequence<N...>>
  {
    using type = ::tts::types<as_wide_t<T,eve::fixed<1ULL << N>>...>;
  };

  template<typename T, typename I>
  using to_wide_t = typename to_wide<T,I>::type;

  template<typename L> struct wides;
  template<typename... Ts> struct wides<::tts::types<Ts...>>
  {
    // Precomputed # of repetitions based on ABI and sizeof(T)
    static constexpr std::array<std::size_t,9> cardinals()
    {
      // This is a precomputed map of the maximum number of cardinal to generate depending
      // on the current ABI bits size. This prevents us to use std::bit_width and other complex
      // computations.
      switch(EVE_CURRENT_ABI::bits)
      {
        case 64 : return {0,5,4,0,3,0,0,0,2};
        case 128: return {0,6,5,0,4,0,0,0,3};
        case 256: return {0,7,6,0,5,0,0,0,4};
        case 512: return {0,8,7,0,6,0,0,0,5};
        default : return {};
      };
    };

    using type = tts::concatenate_t < to_wide_t < Ts
                                                , std::make_index_sequence<cardinals()[sizeof(Ts)]>
                                                >...
                                    >;
  };

  // Prevent calling remove_cvref_t
  template<typename L> struct wides<L const>  : wides<L>  {};
  template<typename L> struct wides<L&>       : wides<L>  {};

  template<typename L> using wides_t = typename wides<L>::type;

  using sizes = tts::types< std::integral_constant<int,    8>
                          , std::integral_constant<int,   16>
                          , std::integral_constant<int,   32>
                          , std::integral_constant<int,   64>
                          , std::integral_constant<int,  128>
                          , std::integral_constant<int,  256>
                          , std::integral_constant<int,  512>
                          , std::integral_constant<int, 1024>
                          >;

  using cardinals = tts::types< eve::fixed<   1>
                              , eve::fixed<   2>
                              , eve::fixed<   4>
                              , eve::fixed<   8>
                              , eve::fixed<  16>
                              , eve::fixed<  32>
                              , eve::fixed<  64>
                              , eve::fixed< 128>
                              , eve::fixed< 256>
                              , eve::fixed< 512>
                              , eve::fixed<1024>
                              >;
}

namespace eve::test::scalar
{
  using ieee_reals        = ::tts::real_types;
  using signed_integers   = ::tts::signed_types;
  using unsigned_integers = ::tts::uint_types;
  using integers          = ::tts::integral_types;
  using all_types         = ::tts::arithmetic_types;
}

namespace eve::test::simd
{
  using ieee_reals        = eve::test::wides<::tts::real_types>::type;
  using signed_integers   = eve::test::wides<::tts::signed_types>::type;
  using unsigned_integers = eve::test::wides<::tts::uint_types>::type;
  using integers          = eve::test::wides<::tts::integral_types>::type;
  using all_types         = eve::test::wides<::tts::arithmetic_types>::type;
}
