//================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>

namespace eve
{
  template<typename Options>
  struct rotl_t : strict_elementwise_callable<rotl_t, Options>
  {
    template<unsigned_value T, integral_value S>
    constexpr EVE_FORCEINLINE as_wide_as_t<T, S> operator()(T v, S s) const
      requires (same_lanes_or_scalar<T, S>)
    {
      return this->behavior(as<as_wide_as_t<T, S>>{}, eve::current_api, this->options(), v, s);
    }

    template<unsigned_value T, auto S>
    constexpr EVE_FORCEINLINE T operator()(T v, index_t<S> s) const
    {
      constexpr std::ptrdiff_t l = sizeof(element_type_t<T>) * 8;
      static_assert((S < l) && (S > -l), "[eve::rotl] Rotation is out of range.");

      return this->behavior(as<T>{}, eve::current_api, this->options(), v, s);
    }

    EVE_CALLABLE_OBJECT(rotl_t, rotl_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var rotl
//!   @brief Bitwise rotation to the left
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overloads
//!      constexpr auto rotl(unsigned_value auto x, integral_value auto n)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto rotl[conditional_expr auto c](unsigned_value auto x, integral_value auto n) noexcept; // 3
//!      constexpr auto rotl[logical_value auto m](unsigned_value auto x, integral_value auto n)    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::unsigned_value) to be rotated.
//!     * `n`: [shift](@ref eve::integral_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!       1. Bitwise rotation of each lane of `x` by `n` bits to the left.
//!          The types must share the same cardinal or be scalar and if `N` is the size in bits of
//!          the element type of `T`, all [elements](@ref glossary_elementwise) of n must belong to the
//!          interval: `[0, N[` or the result is undefined.
//!       2. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/rotl.cpp}
//================================================================================================
  inline constexpr auto rotl = functor<rotl_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/rotl.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/rotl.hpp>
#endif
