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
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/regular/is_even.hpp>
#include <eve/module/core/regular/dec.hpp>
#include <eve/module/core/regular/is_nez.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_odd_t : elementwise_callable<is_odd_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_odd_t, is_odd_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_odd
//!   @brief Returns a logical true  if and only if the element value is odd.
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
//!      eve::as_logical<T> is_odd(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     The call `is_odd(x)` is semantically  equivalent to:
//!      @code
//!      if constexpr(floating_value<T>)   return (x != dec(x)) && eve::is_odd(dec(x));
//!      else constexpr(integral_value<T>) return eve::is_nez (x & one(as(x));
//!      @endcode
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/is_odd.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_odd[mask](x)` provides a masked version of `eve::is_odd` which is
//!     equivalent to `if_else (mask, is_odd(x), eve::false( eve::as(x)))`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/is_odd.cpp}
//!
//! @}
//================================================================================================
  inline constexpr auto is_odd = functor<is_odd_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_odd_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( floating_value<T> )
      {
        auto da = dec(a);
        return (a != da) && is_even(da);
      }
      else if constexpr( scalar_value<T> )
        return (a & one(eve::as(a)));
      else return
        is_nez((a & one(eve::as(a))));
    }
  }
}
