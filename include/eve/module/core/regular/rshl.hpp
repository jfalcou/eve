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
#include <eve/detail/assert_utils.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/detail/assert_utils.hpp>

namespace eve
{
  template<typename Options>
  struct rshl_t : strict_elementwise_callable<rshl_t, Options>
  {
    template<integral_value T, integral_value N>
    requires(eve::same_lanes_or_scalar<T, N>)
    EVE_FORCEINLINE constexpr as_wide_as_t<T, N> operator()(T t0, N s) const noexcept
    {
      EVE_ASSERT(detail::assert_good_shift<T>(s),
                 "[eve::rshl] - Shifting by " << s << " is out of the range ]"
                 << -int(sizeof(element_type_t<T>) * 8) << ", "
                 << sizeof(element_type_t<T>) * 8 << "[.");
      return EVE_DISPATCH_CALL(t0, s);
    }

    template<integral_value T, std::ptrdiff_t S>
    EVE_FORCEINLINE constexpr T operator()(T t0, index_t<S> s) const noexcept
    {
      EVE_ASSERT(detail::assert_good_shift<T>(S),
                 "[eve::rshl] - Shifting by " << S << " is out of the range ]"
                 << -int(sizeof(element_type_t<T>) * 8) << ", "
                 << sizeof(element_type_t<T>) * 8 << "[.");
      return EVE_DISPATCH_CALL(t0, s);
    }

    EVE_CALLABLE_OBJECT(rshl_t, rshl_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var rshl
//!   @brief Computes the arithmetic left/right shift operation according to shift sign.
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
//!      constexpr auto rshl(integral_value auto x, integral_value auto n)                          noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto rshl[conditional_expr auto c](integral_value auto x, integral_value auto n) noexcept; // 3
//!      constexpr auto rshl[logical_value auto m](integral_value auto x, integral_value auto n)    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::value) to be shifted.
//!     * `n`: [shift](@ref eve::integral_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of the arithmetic left/right shift operation according to shift
//!         sign is returned. This is equivalent to `if_else(n>0, shl(x, n), shr(x, -n))`
//!         If `N`is the size in bits  of the element type of `x`, all
//!         [elements](@ref glossary_elementwise) of n must belong to the
//!         interval: `]-N, N[` or the result is undefined.
//!      2. [The operation is performed conditionnaly](@ref conditional)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/rshl.cpp}
//================================================================================================
  inline constexpr auto rshl = functor<rshl_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/impl/rshl.hpp>

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/rshl.hpp>
#endif
