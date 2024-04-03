/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/to_logical.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/constant/false.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_not_finite_t : elementwise_callable<is_not_finite_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_not_finite_t, is_not_finite_);
  };


//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_not_finite
//!   @brief Returns a logical true  if and only if the element is not a finite value
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
//!      eve::as_logical<T> is_not_finite(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     For real entries the call `is_not_finite(x)` is semantically  equivalent to:
//!     @code
//!     if   constexpr(floating_value<T>) return is_nan(x-x);
//!     else constexpr(integral_value<T>) return false_(as(x));
//!     @endcode
//!
//!     `eve::is_not_finite(real(z)) || eve::is_not_finite(imag(z))`,
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_not_finite.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `is_not_finite[mask](x)` provides a masked version of eve::is_not_finite
//!     which is equivalent to `if_else (mask, is_not_finite(x), eve::false( eve::as(x)))`.
//!
//! @}
//================================================================================================
  inline constexpr auto is_not_finite = functor<is_not_finite_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_not_finite_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( integral_value<T> )
        return false_(eve::as(a));
      else
        return is_nan(a - a);
    }
  }
}
