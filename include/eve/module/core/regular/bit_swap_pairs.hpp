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
#include <eve/forward.hpp>
#include <eve/assert.hpp>
#include <eve/module/core/regular/bit_cast.hpp>
#include <eve/module/core/regular/bit_xor.hpp>
#include <eve/module/core/regular/bit_shl.hpp>
#include <eve/module/core/constant/one.hpp>

namespace eve
{

  template<typename Options>
  struct bit_swap_pairs_t : strict_elementwise_callable<bit_swap_pairs_t, Options>
  {
    template<eve::integral_value T, integral_value I0, integral_value I1>
    constexpr EVE_FORCEINLINE T operator()(T v, I0 i0,  I1 i1) const noexcept
    { return EVE_DISPATCH_CALL(v, i0, i1); }

    EVE_CALLABLE_OBJECT(bit_swap_pairs_t, bit_swap_pairs_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_swap_pairs
//!   @brief `strict_elementwise_callable` object swapping pairs.
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
//!      constexpr auto bit_swap_pairs(integral_value auto x,
//!                                    integral_value auto i0, integral_value auto i1) noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto bit_swap_pairs[conditional_expr auto c](integral_value auto x,
//!                                    integral_value auto i0, integral_value auto i1) noexcept; // 2
//!      constexpr auto bit_swap_pairs[logical_value auto m](integral_value auto x,
//!                                     integral_value i0, integral_value auto i1) noexcept;     // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::integral_value).
//!     * `i0`: first index
//!     * `i1`: second index
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!       1. Return `x` with bit `i0` and `i1` swapped in each element of `x`. Assert if i0 or i1 are out of range.
//!       2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_swap_pairs.cpp}
//================================================================================================
  inline constexpr auto bit_swap_pairs = functor<bit_swap_pairs_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {

    template<value T, integral_value I0, integral_value I1, callable_options O>
    constexpr T  bit_swap_pairs_(EVE_REQUIRES(cpu_), O const&, T a, I0 i0,  I1 i1) noexcept
    {
      [[maybe_unused]] constexpr std::ptrdiff_t S8 = sizeof(element_type_t<T>)*8;
      EVE_ASSERT(eve::all(i0 < S8 && i1 < S8), "some indexes are out or range");
      auto x = bit_and(bit_xor(bit_shr(a, i0), bit_shr(a, i1)), one(as(a)));
      a ^= bit_shl(x, i1);
      a ^= bit_shl(x, i0);
      return a;
    }
  }
}
