//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/bit_swap_adjacent.hpp>

namespace eve
{

  template<typename Options>
  struct byte_swap_adjacent_t : strict_elementwise_callable<byte_swap_adjacent_t, Options>
  {
    template<eve::integral_value T, integral_value I>
    constexpr EVE_FORCEINLINE T operator()(T v,  I i) const
    { return EVE_DISPATCH_CALL(v, i); }

    EVE_CALLABLE_OBJECT(byte_swap_adjacent_t, byte_swap_adjacent_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var byte_swap_adjacent
//!   @brief `strict_elementwise_callable` object that swap adjacent groups of N bytes.
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
//!      // Regular overload
//!      constexpr auto byte_swap_adjacent(integral_value auto x, integral_value auto n)   noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto byte_swap_adjacent[conditional_expr auto c](integral_value auto x,
//!                                        integral_value auto n)                          noexcept; // 2
//!      constexpr auto byte_swap_adjacent[logical_value auto m](integral_value auto x,
//!                                        integral_value auto n)                          noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::integral_value).
//!     * `n` :  size of the groups of bytes to be swapped. Must be a power of 2 and
//!              less than the half size of the elements of x
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!       1. Return x with elementwise groups of N bytes swapped.
//!          - If N is greater to sizeof(x) 0 is returned.
//!          - If N is equal   to sizeof(x) x is returned.
//!       2. [The operation is performed conditionnaly](@ref conditional).
//!
//!   @note Take care that eve::byte_swap_adjacent is NOT the EVE functional equivalent to std::byteswap.
//!   eve::byte_reverse IS. As the name does not say, std::byteswap reverse the order
//!   of the bytes which is not an adjacent swapping except for 16 bits words.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/byte_swap_adjacent.cpp}
//================================================================================================
  inline constexpr auto byte_swap_adjacent = functor<byte_swap_adjacent_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, integral_value N, callable_options O>
    EVE_FORCEINLINE constexpr T
    byte_swap_adjacent_(EVE_REQUIRES(cpu_), O const&, T const& x, N const & n) noexcept
    {
    using v_t = element_type_t<T>;
    if constexpr(sizeof(v_t) == 0) return x;
    else return bit_swap_adjacent(x, n*8);
    }
  }
}
