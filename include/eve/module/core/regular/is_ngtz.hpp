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
#include <eve/module/core/regular/is_lez.hpp>
#include <eve/module/core/regular/is_not_greater.hpp>
#include <eve/module/core/constant/false.hpp>

namespace eve
{
  template<typename Options>
  struct is_ngtz_t : elementwise_callable<is_ngtz_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_ngtz_t, is_ngtz_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_ngtz
//!   @brief `elementwise callable` returning a logical true  if and only if the element value is not greater than zero.
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
//!      constexpr auto is_ngtz(value auto x) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_ngtz[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto is_ngtz[logical_value auto m](value auto x) noexcept;    // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. `is_ngtz(x)` is semantically equivalent to `!(x > 0)`.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!   @note  This is not equivalent to `(x <= 0)` for floating values because of `NaN` properties.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_ngtz.cpp}
//================================================================================================
  inline constexpr auto is_ngtz = functor<is_ngtz_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_ngtz_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( unsigned_value<T> )
        return is_eqz(a);
      else
      {
        if constexpr( scalar_value<T> )
        {
          if constexpr( integral_value<T> ) return is_lez(a);
          else if constexpr( floating_value<T> ) return is_lez(a) || is_nan(a);
        }
        else return is_not_greater(a, zero(eve::as(a)));
      }
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#include <eve/module/core/regular/impl/simd/x86/is_ngtz.hpp>
#endif
