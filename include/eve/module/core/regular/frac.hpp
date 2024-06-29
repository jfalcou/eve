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
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/trunc.hpp>

namespace eve
{

  template<typename Options>
  struct frac_t : elementwise_callable<frac_t, Options, raw_option, almost_option, pedantic_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(frac_t, frac_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var frac
//!   @brief `elementwise_callable` computing the fractional part of the input.
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
//!      constexpr auto frac(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto frac[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto frac[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto frac[raw](floating_value auto x)            noexcept; // 3
//!      constexpr auto frac[pedantic](floating_value auto x)       noexcept  // 4
//!      constexpr auto frac[almost = tol](floating_value auto x)   noexcept; // 5
//!      constexpr auto frac[almostl](floating_value auto x)        noexcept; // 6
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :[value](@ref value) argument.
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!     * `tol` [scalar_value](@ref value) tolerance.
//!
//!   **Return value**
//!
//!     1. The fractional part of `x` with the same sign as `x`: `x-trunc(x)`. In particular:
//!        * If an [element](@ref glossary_elementwise) of `x` is \f$\pm0\f$,  \f$\pm0\f$ is
//!          returned.
//!        * If an [element](@ref glossary_elementwise) of `x` is \f$\pm\infty\f$ or `Nan`, a
//!          `Nan` is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!     5. `almost` allows a fuzzy interpretation of `frac` using internally the `almost` version of `trunc`.
//!     6. with no tolerance value, the call is equivalent to `frac[tolerance = 3*eps(as(x))(x)`
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/modf)
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Fractional_part)
//!
//! @}
//================================================================================================
  inline constexpr auto frac = functor<frac_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    frac_(EVE_REQUIRES(cpu_), O const& o, T const& a) noexcept
    {
      if constexpr( floating_value<T> )
      {
        if constexpr(O::contains(raw2))      return a-trunc[o](a);
        else
        {
          auto f = if_else(is_eqz(a), a, a - trunc[o](a));
          if constexpr(platform::supports_infinites && O::contains(pedantic2))
            return if_else(is_infinite(a), bit_and(a, signmask(as(a))), f);
          else
            return f;
        }
      }
      else
        return zero(eve::as(a));
    }
  }
}
