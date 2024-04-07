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
#include <eve/module/core/constant/true.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_finite_t : elementwise_callable<is_finite_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_finite_t, is_finite_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_finite
//!   @brief Returns a logical true  if and only if the element is a finite value
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
//!      eve::as_logical<T> is_finite(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     `is_finite(x)` is semantically  equivalent to `eve::is_not_nan(x-x)`, in particular
//!     this is always true for integral types.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_finite.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_finite[mask](x)` provides a masked version of `eve::is_finite` which is
//!     equivalent to `if_else (mask, is_finite(x), eve::false( eve::as(x)))`.
//!
//! @}
//================================================================================================
  inline constexpr auto is_finite = functor<is_finite_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_finite_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( is_logical_v<T> || integral_value<T>)
        return true_(eve::as(a));
      else
        return is_eqz(a - a);
    }
  }
}
