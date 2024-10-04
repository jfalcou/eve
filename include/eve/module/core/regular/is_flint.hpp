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
    EVE_FORCEINLINE constexpr as_logical_t<T> operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL_PT((as_logical_t<T>), t);
    }

    EVE_CALLABLE_OBJECT(is_flint_t, is_flint_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_flint
//!   @brief `elementwise callable` returning a logical true  if and only if the element value is a floating value
//!   representing an integer
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
//!      // Regular overloads
//!      constexpr auto is_flint(floating_value auto x)                 noexcept; // 1
//!      constexpr auto is_flint(integer_value auto x)                  noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto is_flint[conditional_expr auto c](value auto x) noexcept; // 3
//!      constexpr auto is_flint[logical_value auto m](value auto x)    noexcept; // 3
//!
//!      // Semantic options
//!      constexpr auto is_flint[pedantic](floating_value auto x)       noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. The call `is_flint(x)` is semantically  equivalent to `is_eqz (eve::frac(x))`;
//!        This means that x represents an integral value.
//!     2. Always returns `true`
//!     3. [The operation is performed conditionnaly](@ref conditional).
//!     4. The call `is_flint[pedantic](x)` also check that the input is not greater or equal to the
//!        largest consecutive integer in the element type of `x` (`maxflint(as(x))`).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_flint.cpp}
//================================================================================================
  inline constexpr auto is_flint = functor<is_flint_t>;
//================================================================================================
//! @}
//================================================================================================

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
        if constexpr( O::contains(pedantic) )
          return r && (a <= eve::maxflint(eve::as<T>()));
        else
          return r;
      }
    }
  }
}
