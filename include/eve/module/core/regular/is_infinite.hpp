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
#include <eve/module/core/constant/true.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_infinite_t : elementwise_callable<is_infinite_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_infinite_t, is_infinite_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_infinite
//!   @brief `elementwise callable` returning a logical true  if and only if the element is an infinite value
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
//!      constexpr auto is_infinite(value auto x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     For real entries the call `is_infinite(x)` is semantically  equivalent to
//!     `eve::is_equal(eve::abs(x), eve::inf(as(x))`,
//!     in particular this is always false for integral types.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_infinite.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_infinite[mask](x)` provides a masked
//!     version of `eve::is_infinite` which
//!     is equivalent to `if_else (mask, is_infinite(x), eve::false( eve::as(x)))`.
//!
//! @}
//================================================================================================
  inline constexpr auto is_infinite = functor<is_infinite_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_infinite_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( integral_value<T> )
        return false_(eve::as(a));
      else
        return (eve::abs(a) == inf(eve::as(a)));
    }
  }
}
