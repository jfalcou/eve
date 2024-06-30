//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/is_eqz.hpp>

namespace eve
{
  template<typename Options>
  struct is_not_nan_t : elementwise_callable<is_not_nan_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_not_nan_t, is_not_nan_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_not_nan
//!   @brief `elementwise callable` returning a logical true  if and only if the element value is not NaN
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
//!      constexpr auto is_not_nan(value auto x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real argument](@ref eve::value).
//!
//!   **Return value**
//!
//!       For real entries the call `eve::is_not_nan(x)`  is semantically  equivalent to:
//!       `eve::is_equal(x, x)` in particular this is always true for integral types.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_not_nan.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_not_nan[mask](x)` provides a masked version of `eve::is_not_nan` which is
//!     equivalent to `if_else (mask, is_not_nan(x), eve::false( eve::as(x)))`.
//!
//! @}
//================================================================================================
  inline constexpr auto is_not_nan = functor<is_not_nan_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_not_nan_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr(integral_value<T>) return true_(eve::as(a));
      else                            return a == a;
    }
  }
}
