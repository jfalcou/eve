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
#include <eve/module/core/regular/is_gez.hpp>
#include <eve/module/core/regular/is_not_less.hpp>
#include <eve/module/core/constant/false.hpp>

namespace eve
{
  template<typename Options>
  struct is_nltz_t : elementwise_callable<is_nltz_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_nltz_t, is_nltz_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_nltz
//!   @brief `elementwise callable` returning a logical true  if and only if the element value is not less than zero.
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
//!      constexpr auto is_nltz(value auto x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    Returns [elementwise](@ref glossary_elementwise) `!(x < 0)`.
//!
//!   @note
//!    This is not equivalent to `(x < >= 0)` for floating values.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_nltz.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_nltz[mask](x)` provides a masked version of `eve::is_nltz` which is
//!     equivalent to `if_else (mask, is_nltz(x), eve::false( eve::as(x)))`.
//!
//! @}
//================================================================================================
 inline constexpr auto is_nltz = functor<is_nltz_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_nltz_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( unsigned_value<T> )
        return  true_(eve::as(a));
      else
      {
        if constexpr( scalar_value<T> )
        {
          if      constexpr( integral_value<T> ) return is_gez(a);
          else if constexpr( floating_value<T> ) return is_gez(a) || is_nan(a);
        }
        else
          return is_not_less(a, zero(eve::as(a)));
      }
    }
  }
}
