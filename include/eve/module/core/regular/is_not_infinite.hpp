//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/true.hpp>
#include <eve/module/core/is_finite.hpp>
#include <eve/module/core/is_nan.hpp>

namespace eve
{
  template<typename Options>
  struct is_not_infinite_t : elementwise_callable<is_not_infinite_t, Options,  pedantic_option>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_not_infinite_t, is_not_infinite_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_not_infinite
//!   @brief Returns a logical true  if and only if the element is not an infinite value
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
//!      template< eve::value T >
//!      eve::as_logical<T> is_not_infinite(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     The call `is_not_infinite(x)` is semantically  equivalent to:
//!     @code
//!     if   constexpr(floating_value<T>) return is_not_equal(abs(x), inf(as(x));
//!     else constexpr(integral_value<T>) return true_(as(x));
//!     @endcode
//!
//!     `eve::is_not_infinite(real(z)) && eve::is_not_infinite(imag(z))`,
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_not_infinite.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_not_infinite[mask](x)` provides a masked version of
//!     `eve::is_not_infinite` which is equivalent to `if_else (mask, is_not_infinite(x),
//!     eve::false( eve::as(x)))`.
//!
//! @}
//================================================================================================
 inline constexpr auto is_not_infinite = functor<is_not_infinite_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_not_infinite_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( integral_value<T> )
        return true_(eve::as<T>());
      else
        return eve::is_finite(a) || is_nan(a);
    }
  }
}
