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
#include <eve/module/core/constant/half.hpp>
#include <eve/module/core/constant/mindenormal.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/smallestposval.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_flint.hpp>
#include <eve/module/core/regular/is_not_equal.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_even_t : elementwise_callable<is_even_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_even_t, is_even_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_even
//!   @brief Returns a logical true  if and only if the element value is even.
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
//!      eve::as_logical<T> is_even(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     The call `is_even(x)` is semantically  equivalent to:
//!      @code
//!      if constexpr(floating_value<T>)   return eve::is_flint (x) && eve::is_flint (x/2);
//!      else constexpr(integral_value<T>) return eve::is_equal (x, (x/2)*2);
//!      @endcode
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_even.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_even[mask](x)` provides a masked version of `eve::is_even` which is
//!     equivalent to `if_else (mask, is_even(x), eve::false( eve::as(x)))`.
//!
//! @}
//================================================================================================
  inline constexpr auto is_even = functor<is_even_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_even_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( floating_value<T> )
      {
        auto aisflt = is_flint(a * half(eve::as(a)));
        auto aa     = eve::abs(a);
        if constexpr( eve::platform::supports_denormals )
          return aisflt && (aa != mindenormal(eve::as<T>()));
        else
          return aisflt && (aa != smallestposval(eve::as<T>()));
      }
      else if constexpr( scalar_value<T> )
        return (!(a & one(eve::as(a))));
      else
        return is_eqz((a & one(eve::as(a))));
    }
  }
}
