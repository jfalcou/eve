//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_TYPE_PACK_HPP_INCLUDED
#define EVE_MODULE_CORE_TYPE_PACK_HPP_INCLUDED

#include <eve/arch/spec.hpp>
#include <eve/arch/limits.hpp>
#include <eve/ext/as_pack.hpp>
#include <eve/module/core/detail/pack.hpp>
#include <eve/module/core/detail/aggregate_pack.hpp>

namespace eve
{
  template<typename T> struct logical;

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

  namespace ext
  {

    // Wrapper for SIMD registers holding arithmetic types
    template<typename Type, typename Size>
    struct as_pack< Type, Size
                  , std::enable_if_t<   std::is_arithmetic_v<Type>
                                    && !detail::require_aggregation<Type,Size>()
                                    >
                  >
    {
      using abi_type  = ext::abi_of_t<Type,Size::value>;
      using type      = eve::detail::pack<Type,Size,abi_type>;
    };

    // Wrapper for SIMD registers holding logical type
    template<typename Type, typename Size>
    struct as_pack< logical<Type>, Size
                  , std::enable_if_t<   std::is_arithmetic_v<Type>
                                    && !detail::require_aggregation<Type,Size>()
                                    >
                  >
    {
      using abi_type  = ext::abi_of_t<logical<Type>,Size::value>;
      using type      = eve::detail::pack<logical<Type>,Size,abi_type>;
    };

    // Large pack wrapper
    template< typename Type, typename Size>
    struct as_pack< Type, Size
                  , std::enable_if_t<   std::is_arithmetic_v<Type>
                                    && detail::require_aggregation<Type,Size>()
                                    >
                  >
    {
      using type = eve::detail::pack<Type,Size,eve::aggregated_>;
    };

  }
}

#endif
