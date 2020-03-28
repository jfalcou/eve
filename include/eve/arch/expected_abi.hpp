//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_EXPECTED_ABI_HPP_INCLUDED
#define EVE_ARCH_EXPECTED_ABI_HPP_INCLUDED

#include <eve/arch/expected_cardinal.hpp>
#include <eve/concept/stdconcepts.hpp>
#include <eve/arch/abi_of.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  // Types that are too big and are not emulated require aggregation
  template<typename Type, typename Size>
  inline constexpr bool require_aggregation =     (Size::value > expected_cardinal_v<Type>)
                                              && !std::is_same_v
                                                        < abi_of_t< Type
                                                                  , expected_cardinal_v<Type>
                                                                  >
                                                        , eve::emulated_
                                                        >;
}

namespace eve
{
  // Find proper ABI for wide
  template<typename Type, typename Size> struct expected_abi {};

  template<typename Type, typename Size>
  requires( std::arithmetic<Type> && detail::require_aggregation<Type, Size> )
  struct expected_abi<Type, Size>
  {
    using type = eve::aggregated_;
  };

  template<typename Type, typename Size>
  requires( std::arithmetic<Type> && !detail::require_aggregation<Type, Size> )
  struct expected_abi<Type, Size> : abi_of<Type, Size::value>
  {};

  // Wrapper for SIMD registers holding logical type
  template<typename Type, typename Size>
  requires( std::arithmetic<Type> && detail::require_aggregation<Type, Size> )
  struct expected_abi<logical<Type>, Size>
  {
    using type = eve::aggregated_;
  };

  template<typename Type, typename Size>
  requires( std::arithmetic<Type> && !detail::require_aggregation<Type, Size> )
  struct expected_abi<logical<Type>, Size> : abi_of<logical<Type>, Size::value>
  {};

  // Type short-cut
  template<typename Type, typename Size>
  using expected_abi_t = typename expected_abi<Type, Size>::type;
}

#endif
