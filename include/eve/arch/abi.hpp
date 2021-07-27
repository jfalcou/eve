//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/expected_cardinal.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/arch/abi_of.hpp>
#include <eve/forward.hpp>

#include <concepts>
#include <type_traits>

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
  template<typename T> concept arithmetic = std::is_arithmetic_v<T>;

  // Find proper ABI for wide
  template<typename Type, typename Size> struct abi {};

  template<typename Type, typename Size>
  requires( arithmetic<Type> && detail::require_aggregation<Type, Size> )
  struct abi<Type, Size>
  {
    using type = eve::aggregated_;
  };

  template<typename Type, typename Size>
  requires( kumi::product_type<Type> )
  struct abi<Type, Size>
  {
    using type = eve::bundle_;
  };

  template<typename Type, typename Size>
  requires( arithmetic<Type> && !detail::require_aggregation<Type, Size> )
  struct abi<Type, Size> : abi_of<Type, Size::value>
  {};

  // Wrapper for SIMD registers holding logical type
  template<typename Type, typename Size>
  requires( arithmetic<Type> && detail::require_aggregation<Type, Size> )
  struct abi<logical<Type>, Size>
  {
    using type = eve::aggregated_;
  };

  template<typename Type, typename Size>
  requires( arithmetic<Type> && !detail::require_aggregation<Type, Size> )
  struct abi<logical<Type>, Size> : abi_of<logical<Type>, Size::value>
  {};

  // Type short-cut
  template<typename Type, typename Size>
  using abi_t = typename abi<Type, Size>::type;
}
