//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <cstddef>
#include <eve/detail/concepts.hpp>
#include <eve/detail/meta.hpp>

namespace eve
{
  //================================================================================================
  // Dispatching tag for generic implementation
  struct cpu_
  {
  };

  //================================================================================================
  // Dispatching tag for generic SIMD implementation
  struct simd_ : cpu_
  {
    using parent  = cpu_;
  };

  //================================================================================================
  // Dispatching tag for emulated SIMD implementation of large register
  struct aggregated_ : cpu_
  {
    using parent = cpu_;
    static constexpr bool is_wide_logical = true;
  };

  //================================================================================================
  // Concept for discriminatig aggregated from non-agregated ABI
  //================================================================================================
  template<typename T> concept regular_abi = !std::same_as<T,aggregated_>;

  //================================================================================================
  // Dispatching tag for emulated SIMD implementation
  struct emulated_ : cpu_
  {
    static constexpr std::size_t bits                     = 128;
    static constexpr std::size_t bytes                    = 16;
    static constexpr bool        is_wide_logical = true;

    template<typename Type>
    static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);
  };

  template<typename T>
  concept non_native_abi = detail::is_one_of<T>(detail::types<aggregated_, emulated_> {});

  template<typename T>
  concept native_abi = !detail::is_one_of<T>(detail::types<aggregated_, emulated_> {});

  //================================================================================================
  // Checks for logical status in ABI
  template<typename ABI>
  struct use_is_wide_logical : std::integral_constant<bool,ABI::is_wide_logical>
  {};
}
