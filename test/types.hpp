//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include "test_distribution.hpp"
#include <eve/detail/meta.hpp>
#include <tuple>

namespace eve::test::scalar
{
  using detail::types;

  inline constexpr types< std::int8_t , std::int16_t
                        , std::int32_t, std::int64_t
                        >                                   signed_integers   = {};

  inline constexpr types< std::uint8_t  , std::uint16_t
                        , std::uint32_t , std::uint64_t
                        >                                   unsigned_integers = {};
  inline constexpr types< std::int8_t   , std::int16_t
                        , std::int32_t  , std::int64_t
                        , std::uint8_t  , std::uint16_t
                        , std::uint32_t , std::uint64_t
                        >                                   integers          = {};
  inline constexpr types<float, double>                     ieee_reals        = {};
  inline constexpr types< float       , double
                        , std::int8_t , std::int16_t
                        , std::int32_t, std::int64_t
                        >                                   signed_types      = {};
  inline constexpr auto                                     unsigned_types    = unsigned_integers;
  inline constexpr types< float         , double
                        , std::int8_t   , std::int16_t
                        , std::int32_t  , std::int64_t
                        , std::uint8_t  , std::uint16_t
                        , std::uint32_t , std::uint64_t
                        >                                   all_types         = {};
}

namespace eve::detail
{
  template<typename T, typename Indexes> struct to_wide;

  template<typename T, std::size_t... N>
  struct to_wide<T, std::index_sequence<N...>>
  {
    using type = types<as_wide_t<T,fixed<1ULL << N>>...>;
  };

  template<typename T, typename I>
  using to_wide_t = typename to_wide<T,I>::type;

  template<typename L> struct wides;
  template<typename... Ts> struct wides<types<Ts...>>
  {
    // Precomputed # of repetitions based on ABI and sizeof(T)
    static constexpr std::array<std::size_t,9> cardinal_map()
    {
      // This is a precomputed map of the maximum number of cardinal to generate depending
      // on the current ABI bits size. This prevents us to use std::bit_width and other complex
      // computations.
      switch(EVE_CURRENT_ABI::bits)
      {
        case 64 : return {0,5,4,0,3,0,0,0,2};
        case 128: return {0,6,5,0,4,0,0,0,3};
        case 256: return {0,7,6,0,5,0,0,0,4};
        case 512: return {0,7,6,0,5,0,0,0,4}; // no aggregation on AVX512 for now
        default : return {};
      };
    };

    using type = concatenate_t< to_wide_t < Ts
                                          , std::make_index_sequence<cardinal_map()[sizeof(Ts)]>
                                          >...
                              >;
  };

  // Prevent calling remove_cvref_t
  template<typename L> struct wides<L const>  : wides<L> {};
  template<typename L> struct wides<L&>       : wides<L> {};
}

namespace eve::test::simd
{
  inline constexpr detail::wides< decltype(scalar::signed_integers) >::type   signed_integers   {};
  inline constexpr detail::wides< decltype(scalar::unsigned_integers) >::type unsigned_integers {};
  inline constexpr detail::wides< decltype(scalar::integers) >::type          integers          {};
  inline constexpr detail::wides< decltype(scalar::ieee_reals) >::type        ieee_reals        {};
  inline constexpr detail::wides< decltype(scalar::signed_types) >::type      signed_types      {};
  inline constexpr auto                                   unsigned_types    = unsigned_integers;
  inline constexpr detail::wides< decltype(scalar::all_types) >::type         all_types         {};
}
