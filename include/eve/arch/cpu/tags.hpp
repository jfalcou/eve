//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/deps/spy.hpp>
#include <eve/arch/predef.hpp>

#include <cstddef>
#include <concepts>
#include <iosfwd>

EVE_NAMESPACE
{
  //================================================================================================
  // SPY SIMD API wrapper
  template<typename Base, auto API> struct simd_api : Base
  {
    static constexpr auto version = API;
    using api_type = std::decay_t<decltype(API)>;

    constexpr api_type const& value() const noexcept { return API; }

    friend std::ostream& operator<<(std::ostream& os, simd_api) { return os << API; }

    template<typename B, auto O>
    friend constexpr bool operator==(simd_api , simd_api<B,O> ) noexcept { return API == O; }
    template<typename B, auto O>
    friend constexpr bool operator> (simd_api , simd_api<B,O> ) noexcept { return API >  O; }
    template<typename B, auto O>
    friend constexpr bool operator>=(simd_api , simd_api<B,O> ) noexcept { return API >= O; }
    template<typename B, auto O>
    friend constexpr bool operator< (simd_api , simd_api<B,O> ) noexcept { return API <  O; }
    template<typename B, auto O>
    friend constexpr bool operator<=(simd_api , simd_api<B,O> ) noexcept { return API <= O; }
  };

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

  using undefined_simd_ = simd_api<simd_, spy::undefined_simd_>;
  inline constexpr undefined_simd_ undefined_simd   = {};

  //================================================================================================
  // Dispatching tag for emulated SIMD implementation of large register
  struct aggregated_ : cpu_
  {
    using parent = cpu_;
#   if defined(SPY_SIMD_IS_X86_AVX512) || defined(EVE_SIMD_IS_ANY_FIXED_SVE) || defined(SPY_SIMD_IS_RISCV_FIXED_RVV)
    static constexpr bool is_wide_logical = false;
#   else
    static constexpr bool is_wide_logical = true;
#   endif
    static constexpr bool has_defined_logical_tail = true;
  };

  struct bundle_ : cpu_
  {
    using parent = cpu_;
    static constexpr bool is_wide_logical = aggregated_::is_wide_logical;
    static constexpr bool has_defined_logical_tail = true;
  };

  //================================================================================================
  // Dispatching tag for emulated SIMD implementation
  struct emulated_
  {
    static constexpr std::size_t bits             = 128;
    static constexpr std::size_t bytes            = 16;
    static constexpr bool        is_wide_logical  = true;
    static constexpr bool        has_defined_logical_tail = true;
  };

  namespace _
  {
    template<typename T, typename ABI>
    inline constexpr bool use_complete_storage = true;

    template<typename T, typename ABI>
    extern width_type expected_width;

    template<typename T, typename ABI>
    extern width_type fundamental_width;

    template<typename T>
    inline constexpr width_type expected_width<T,emulated_> = emulated_::bytes / sizeof(T);

    template<typename T>
    inline constexpr width_type fundamental_width<T, emulated_> = emulated_::bytes / sizeof(T);
  }

  //================================================================================================
  // Checks if a type fills all its storage
  template<typename T>
  inline constexpr bool use_complete_storage = _::use_complete_storage<T, typename T::abi_type>;

  //================================================================================================
  // Checks for logical status in ABI
  template<typename ABI>
  inline constexpr bool use_is_wide_logical = ABI::is_wide_logical;
}
