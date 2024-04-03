//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/false.hpp>
#include <eve/module/core/constant/maxflint.hpp>
#include <eve/module/core/is_nez.hpp>
#include <eve/module/core/frac.hpp>

namespace eve
{
  template<typename Options>
  struct is_not_flint_t : elementwise_callable<is_not_flint_t, Options,  pedantic_option>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_not_flint_t, is_not_flint_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_not_flint
//!   @brief Returns a logical true  if and only if the element value is a floating value
//!   not representing an integer
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
//!      template< eve::floating_value T >
//!      eve::as_logical<T> is_not_flint(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::floating_value).
//!
//!   **Return value**
//!
//!     The call `eve;::is_not_flint[mask](x)` is semantically  equivalent to: `eve::is_nez
//!     (eve::frac (x))`;
//!
//!     This means that x is a [floating real value](@ref eve::floating_value) not representing an
//!     integer (flint is a shorcut for 'floating integer').
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_not_flint.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_not_flint[mask](x)` provides a masked version of `eve::is_not_flint`
//!     which is equivalent to `if_else (mask, is_not_flint(x), eve::false( eve::as(x)))`.
//!
//! @}
//================================================================================================
  inline constexpr auto is_not_flint = functor<is_not_flint_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_not_flint_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( integral_value<T> )
        return false_(eve::as<T>());
      else if (O::contains(pedantic2))
        return is_nez(frac(a)) || (a > eve::maxflint(eve::as<T>()));
      else
        return is_nez(frac(a));
    }
  }
}
