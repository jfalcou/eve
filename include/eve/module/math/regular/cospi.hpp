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
#include <eve/module/core.hpp>
#include <eve/module/math/constant/pi.hpp>

#include <eve/module/math/regular/cos.hpp>
#include <eve/module/math/detail/generic/rem2.hpp>

namespace eve
{
  template<typename Options>
  struct cospi_t : elementwise_callable<cospi_t, Options, quarter_circle_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(cospi_t, cospi_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var cospi
//!
//! @brief  `elementwise_callable` object computing the cosine from an input in \f$\pi\f$ multiples.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto cospi(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto cospi[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto cospi[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto cospi[quarter_circle](floating_value auto x)          noexcept; // 3
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!     * `x`: [floating value](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!    1.   Returns the [elementwise](@ref glossary_elementwise) cosine of the input in \f$\pi\f$ multiples.
//!       The call `cospi(x)` is semantically equivalent to \f$\cos(\pi x)\f$.
//!       In particular:
//!        * If the element is \f$\pm0\f$, \f$1\f$ is returned.
//!        * If the element is \f$\pm1/2\f$, \f$0\f$ is returned.
//!        * If the element is \f$\pm\infty\f$, Nan is returned.
//!        * If the element is a `Nan`, `Nan` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!    3. Assumes that the inputs elements  belong to \f$[-1/4,1/4]\f$ and return NaN outside.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/cospi.cpp}
//================================================================================================
 inline constexpr auto cospi = functor<cospi_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T cospi_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(O::contains(quarter_circle))
      {
        return eve::cos[quarter_circle](a0*pi(eve::as<T>()));
      }
      else
      {
        if constexpr( scalar_value<T> )
          if( is_not_finite(a0) ) return nan(eve::as<T>());
        auto x = eve::abs(a0);
        if constexpr( scalar_value<T> )
        {
          if( x > maxflint(eve::as<T>()) ) return T(1);
        }
        else
        {
          x = if_else(is_not_finite(x), eve::allbits, x); // nan or Inf input
          x = if_else(is_greater(x, maxflint(eve::as(x))), eve::zero, x);
        }
        auto [fn, xr, dxr] = rem2(x);
        return cos_finalize(fn, xr, dxr);
      }
    }
  }
}
