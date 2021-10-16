//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/meta.hpp>
#include <eve/detail/spy.hpp>

#include <cstddef>
#include <concepts>

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

# if defined(SPY_SIMD_IS_X86_AVX512)
#define EVE_WIDE_LOGICAL_NAMESPACE
#define EVE_BIT_LOGICAL_NAMESPACE   inline
#else
#define EVE_WIDE_LOGICAL_NAMESPACE  inline
#define EVE_BIT_LOGICAL_NAMESPACE
#endif

  //================================================================================================
  // Dispatching tag for emulated SIMD implementation of large register
  // We use inline namespace to ensure mangling ends up different when using AVX512 like ABI
  EVE_WIDE_LOGICAL_NAMESPACE namespace internal_wide_logical
  {
    struct aggregated_ : cpu_
    {
      using parent = cpu_;
      static constexpr bool is_wide_logical = true;
      template<typename> static constexpr bool is_full = true;
    };

    struct bundle_ : cpu_
    {
      using parent = cpu_;
      static constexpr bool is_wide_logical = true;
      template<typename> static constexpr bool is_full = true;
    };
  }

  EVE_BIT_LOGICAL_NAMESPACE namespace internal_bit_logical
  {
    struct aggregated_ : cpu_
    {
      using parent = cpu_;
      static constexpr bool is_wide_logical = false;
      template<typename> static constexpr bool is_full = true;
    };

    struct bundle_ : cpu_
    {
      using parent = cpu_;
      static constexpr bool is_wide_logical = false;
      template<typename> static constexpr bool is_full = true;
    };
  }

  //================================================================================================
  // Concept for discriminating aggregated from non-agregated ABI
  //================================================================================================
  template<typename T> concept regular_abi = !std::same_as<T,aggregated_>;

  //================================================================================================
  // Dispatching tag for emulated SIMD implementation
  struct emulated_ : cpu_
  {
    static constexpr std::size_t bits                     = 128;
    static constexpr std::size_t bytes                    = 16;
    static constexpr bool        is_wide_logical = true;

    template<typename> static constexpr bool is_full = true;

    template<typename Type>
    static constexpr std::size_t expected_cardinal = bytes / sizeof(Type);

    template<typename Type>
    static constexpr std::size_t fundamental_cardinal = bytes / sizeof(Type);
  };

  template<typename T>
  concept non_native_abi = detail::is_one_of<T>(detail::types<aggregated_, emulated_, bundle_> {});

  template<typename T>
  concept native_abi = !detail::is_one_of<T>(detail::types<aggregated_, emulated_, bundle_> {});

  //================================================================================================
  // Checks if a type fills all its storage
  template<typename Type>
  inline constexpr bool use_complete_storage = Type::abi_type::template is_full<Type>;

  //================================================================================================
  // Checks for logical status in ABI
  template<typename ABI>
  struct use_is_wide_logical : std::integral_constant<bool, ABI::is_wide_logical>
  {};
}
