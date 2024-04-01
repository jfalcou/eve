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
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_nan_t : elementwise_callable<is_nan_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_nan_t, is_nan_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_nan
//!   @brief Returns a logical true  if and only if the element value is NaN
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
//!      eve::as_logical<T> is_nan(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real argumentargument](@ref eve::value).
//!
//!   **Return value**
//!
//!       For eal entries the call `eve::is_nan(x)`  is semantically  equivalent to:
//!
//!       @code
//!         if   constexpr(floating_value<T>) return is_not_equal(x, x);
//!         else constexpr(integral_value<T>) return false_(as(x));
//!       @endcode
//!
//!       `eve::is_nan(real(z)) || eve::is_nan(imag(z))`,
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_nan.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_nan[mask](x)` provides a masked version of `eve::is_nan` which is
//!     equivalent to `if_else (mask, is_nan(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_nan.cpp}
//!
//! @}
//================================================================================================
  inline constexpr auto is_nan = functor<is_nan_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_nan_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( is_logical_v<T> || integral_value<T>)
        return false_(eve::as(a));
      else
        return a != a;
    }
  }
}
