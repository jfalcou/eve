//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  template<typename Options>
  struct dot_t : elementwise_callable<dot_t, Options>
  {
    template<eve::value T,  value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U b) const
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(dot_t, dot_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var dot
//!   @brief `elementwise_callable` object computing elementwise the dot product of the two parameters.
//!
//!   @warning This is not a reduction ! For reals the dot product is the product
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
//!      constexpr auto dot(auto value x, auto value y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`  :  [value arguments](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!
//!    dot product. For values it is just the product.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/dot.cpp}
//================================================================================================
  inline constexpr auto dot = functor<dot_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T, U>
    dot_(EVE_REQUIRES(cpu_), O const &, T a,  U b) noexcept
    {
      return mul(a, b);
    }
  }
}
