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
#include <eve/module/core/regular/frac.hpp>
#include <eve/module/core/regular/is_eqz.hpp>

namespace eve
{
  template<typename Options>
  struct is_flint_t : elementwise_callable<is_flint_t, Options, pedantic_option>
  {
    template<eve::value T>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(is_flint_t, is_flint_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_flint
//!   @brief Returns a logical true  if and only if the element value is a floating value
//!   representing an integer
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
//!      eve::as_logical<T> is_flint(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     The call `eve;::is_flint[mask](x)` is semantically  equivalent to: `eve::is_eqz (eve::frac
//!     (x))`;
//!
//!     This means that x is a [floating real value](@ref eve::floating_value) representing an
//!     integer (flint is a shortcut for 'floating integer').
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_flint.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_flint[mask](x)` provides a masked version of `eve::is_flint` which is
//!     equivalent to `if_else (mask, is_flint(x), eve::false( eve::as(x)))`.
//!
//! @}
//================================================================================================
  inline constexpr auto is_flint = functor<is_flint_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<T>
    is_flint_(EVE_REQUIRES(cpu_), O const &, T const& a) noexcept
    {
      if constexpr( integral_value<T> )
        return true_(eve::as<T>());
      else
      {
        auto r = is_eqz(frac[raw](a));
        if constexpr( O::contains(pedantic2) )
          return r && (a <= eve::maxflint(eve::as<T>()));
        else
          return r;
      }
    }
  }
}
