//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once
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
  inline constexpr types<float>                             ieee_floats       = {};
  inline constexpr types<double>                            ieee_doubles      = {};
  inline constexpr types<std::uint64_t>                     uints_64          = {};
  inline constexpr types<std::uint32_t>                     uints_32          = {};
  inline constexpr types<std::uint16_t>                     uints_16          = {};
  inline constexpr types<std::uint8_t>                      uints_8           = {};
  inline constexpr types<std::int64_t>                      ints_64           = {};
  inline constexpr types<std::int32_t>                      ints_32           = {};
  inline constexpr types<std::int16_t>                      ints_16           = {};
  inline constexpr types<std::int8_t>                       ints_8            = {};

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
        case 512: return {0,8,7,0,6,0,0,0,5};
        default : return {};
      };
    };

    using type = concatenate_t< to_wide_t < Ts
                                          , std::make_index_sequence<cardinal_map()[sizeof(Ts)]>
                                          >...
                              >;
  };

  // Prevent calling remove_cvref_t
  template<typename L> struct wides<L const>            : wides<L>            {};
  template<typename L> struct wides<L&>                 : wides<L>            {};
}

namespace eve::test::simd
{
  inline constexpr detail::wides< decltype(scalar::signed_integers) >::type   signed_integers   {};
  inline constexpr detail::wides< decltype(scalar::unsigned_integers) >::type unsigned_integers {};
  inline constexpr detail::wides< decltype(scalar::integers) >::type          integers          {};
  inline constexpr detail::wides< decltype(scalar::ieee_reals) >::type        ieee_reals        {};
  inline constexpr detail::wides< decltype(scalar::ieee_floats) >::type       ieee_floats       {};
  inline constexpr detail::wides< decltype(scalar::ieee_doubles) >::type      ieee_doubles      {};
  inline constexpr detail::wides< decltype(scalar::uints_64) >::type          uints_64          {};
  inline constexpr detail::wides< decltype(scalar::uints_32) >::type          uints_32          {};
  inline constexpr detail::wides< decltype(scalar::uints_16) >::type          uints_16          {};
  inline constexpr detail::wides< decltype(scalar::uints_8 ) >::type          uints_8           {};
  inline constexpr detail::wides< decltype(scalar::ints_64) >::type           ints_64           {};
  inline constexpr detail::wides< decltype(scalar::ints_32) >::type           ints_32           {};
  inline constexpr detail::wides< decltype(scalar::ints_16) >::type           ints_16           {};
  inline constexpr detail::wides< decltype(scalar::ints_8 ) >::type           ints_8            {};
  inline constexpr detail::wides< decltype(scalar::signed_types) >::type      signed_types      {};
  inline constexpr auto                                   unsigned_types    = unsigned_integers;
  inline constexpr detail::wides< decltype(scalar::all_types) >::type         all_types         {};

  using detail::types;
  inline constexpr types< std::integral_constant<int,    8>
                        , std::integral_constant<int,   16>
                        , std::integral_constant<int,   32>
                        , std::integral_constant<int,   64>
                        , std::integral_constant<int,  128>
                        , std::integral_constant<int,  256>
                        , std::integral_constant<int,  512>
                        , std::integral_constant<int, 1024>
                        > sizes = {};

  inline constexpr types< eve::fixed<   1>
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
                        > cardinals = {};
}
