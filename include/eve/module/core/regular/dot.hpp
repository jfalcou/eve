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
    template<value T, value U>
    constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U b) const
      requires (same_lanes_or_scalar<T, U>)
    {
      return this->behavior(as<common_value_t<T, U>>{}, eve::current_api, this->options(), a, b);
    }

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
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
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
    template<callable_options O, typename T, typename U>
    EVE_FORCEINLINE constexpr common_value_t<T, U>
    dot_(EVE_REQUIRES(cpu_), O const&, T a,  U b) noexcept
    {
      return mul(a, b);
    }
  }
}
