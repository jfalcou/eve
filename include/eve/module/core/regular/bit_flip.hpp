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
#include <eve/module/core/regular/bit_xor.hpp>
#include <eve/module/core/regular/bit_shl.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/regular/all.hpp>

namespace eve
{
  template<typename Options>
  struct bit_flip_t : strict_elementwise_callable<bit_flip_t, Options>
  {
    template<eve::value T, integral_value I>
    constexpr EVE_FORCEINLINE T operator()(T v,  I i) const
    { return EVE_DISPATCH_CALL(v, i); }

    EVE_CALLABLE_OBJECT(bit_flip_t, bit_flip_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_flip
//!   @brief  `strict_elementwise_callable` object flipping the value the ith bit of each element.
//!
//!   **Defined in Header**
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
//!      constexpr auto bit_flip(integral_value auto x, integral_value auto i)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto bit_flip[conditional_expr auto c](integral_value auto x, integral_value auto i) noexcept; // 2
//!      constexpr auto bit_flip[logical_value auto m](integral_value auto x, integral_value auto i)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [integral argument](@ref eve::integral_value).
//!     * `i`: index to flip.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of the parameter is returned with the ith bit flipped.
//!         if the index is out of range the call will assert.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_flip.cpp}
//================================================================================================
  inline constexpr auto bit_flip = functor<bit_flip_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, integral_value I, callable_options O>
    EVE_FORCEINLINE constexpr T
    bit_flip_(EVE_REQUIRES(cpu_), O const&, T const& a, I const & i) noexcept
    {
      [[maybe_unused]] constexpr std::ptrdiff_t S8 = sizeof(element_type_t<T>)*8;
      EVE_ASSERT(eve::all(i >= 0 && i < S8), "some index elements are out or range");
      return bit_xor(a, bit_shl(one(as(a)), i));
    }
  }
}
