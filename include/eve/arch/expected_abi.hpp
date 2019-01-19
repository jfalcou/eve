//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_EXPECTED_ABI_HPP_INCLUDED
#define EVE_ARCH_EXPECTED_ABI_HPP_INCLUDED

#include <eve/ext/abi_of.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/forward.hpp>

namespace eve
{
  namespace detail
  {
    // Is this type ABI emulated_ ?
    template<typename Type> constexpr bool is_emulated()
    {
      using abi_t   = ext::abi_of_t<Type,expected_cardinal_v<Type>>;
      return std::is_same_v<abi_t, eve::emulated_>;
    }

    // Types that are too big and are not emulated require aggregation
    template<typename Type, typename Size> constexpr bool require_aggregation()
    {
      return (Size::value > expected_cardinal_v<Type>) && !is_emulated<Type>();
    }
  }

  // Find proper ABI for wide
  template<typename Type, typename Size, typename Enable= void>
  struct expected_abi;

  template<typename Type, typename Size>
  struct expected_abi<Type, Size, std::enable_if_t<std::is_arithmetic_v<Type>>>
  {
    using type  = std::conditional_t< detail::require_aggregation<Type,Size>()
                                    , eve::aggregated_
                                    , ext::abi_of_t<Type,Size::value>
                                    >;
  };

  // Wrapper for SIMD registers holding logical type
  template<typename Type, typename Size>
  struct expected_abi<logical<Type>, Size, std::enable_if_t<std::is_arithmetic_v<Type>>>
  {
    using type  = std::conditional_t< detail::require_aggregation<Type,Size>()
                                    , eve::aggregated_
                                    , ext::abi_of_t<logical<Type>,Size::value>
                                    >;
  };

  template<typename Type, typename Size>
  using expected_abi_t = typename expected_abi<Type,Size>::type;
}

#endif
