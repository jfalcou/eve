//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/traits/overload.hpp>

namespace eve
{
  template<typename Options>
  struct byte_swap_pairs_t : strict_elementwise_callable<byte_swap_pairs_t, Options>
  {
    template<integral_value T, std::ptrdiff_t I0, std::ptrdiff_t I1>
    EVE_FORCEINLINE T operator()(T a, index_t<I0> const & i0,  index_t<I1> const & i1) const noexcept
    { return EVE_DISPATCH_CALL(a, i0, i1); }

    EVE_CALLABLE_OBJECT(byte_swap_pairs_t, byte_swap_pairs_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var byte_swap_pairs
//!   @brief  `strict_elementwise_callable` object swapping chosen pairs of bytes in each vector element.
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
//!      // Regular overload
//!      constexpr auto byte_swap_pairs(integral_value auto x,
//!                                    index_t<I0> auto i0, index_t<I1> auto i1) noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto byte_swap_pairs[conditional_expr auto c](integral_value auto x,
//!                                    index_t<I0> auto i0, index_t<I1> auto i1) noexcept; // 2
//!      constexpr auto byte_swap_pairs[logical_value auto m](integral_value auto x,
//!                                    index_t<I0> auto i0, index_t<I1> auto i1) noexcept; // 2
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::integral_value).
//!     * `i0` : first index
//!     * `i1` : second index
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!       1. Return x byte i0 and i1 swapped in each element of x. Assert if i0 or i1 are out of range.
//!       2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/byte_swap_pairs.cpp}
//! @}
//================================================================================================
  inline constexpr auto byte_swap_pairs = functor<byte_swap_pairs_t>;

}

#include <eve/module/core/regular/impl/byte_swap_pairs.hpp>
