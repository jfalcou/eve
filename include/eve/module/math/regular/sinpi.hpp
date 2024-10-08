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
#include <eve/module/core.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/math/regular/sin.hpp>

namespace eve
{
  template<typename Options>
  struct sinpi_t : elementwise_callable<sinpi_t, Options, quarter_circle_option>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(sinpi_t, sinpi_);
  };

  //================================================================================================
  //! @addtogroup math_trig
  //! @{
  //! @var sinpi
  //!
  //! @brief `elementwise_callable` object computing the sine from an input in \f$\pi\f$ multiples.
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
  //!      constexpr auto sinpi(floating_value auto x)                          noexcept; // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto sinpi[conditional_expr auto c](floating_value auto x) noexcept; // 2
  //!      constexpr auto sinpi[logical_value auto m](floating_value auto x)    noexcept; // 2
  //!
  //!      // Semantic options
  //!      constexpr auto sinpi[quarter_circle](floating_value auto x)          noexcept; // 3
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!      * `x`: [floating value](@ref floating_value).
  //!      * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
  //!      * `m`: [Logical value](@ref logical) masking the operation.
  //!
  //! **Return value**
  //!
  //!    1.   Returns the [elementwise](@ref glossary_elementwise) cosine of the input in \f$\pi\f$ multiples.
  //!       The call `sinpi(x)` is  equivalent to \f$\cos(\pi x)\f$.
  //!       In particular:
  //!        * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
  //!        * If the element is \f$\pm1/2\f$, \f$1\f$ is returned.
  //!        * If the element is \f$\pm\infty\f$, Nan is returned.
  //!        * If the element is a `Nan`, `Nan` is returned.
  //!    2. [The operation is performed conditionnaly](@ref conditional).
  //!    3. Assumes that the inputs elements  belong to \f$[-1/4,1/4]\f$ and return NaN outside.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/math/sinpi.cpp}
  //================================================================================================
  inline constexpr auto sinpi = functor<sinpi_t>;
  //================================================================================================
  //!  @}
  //================================================================================================

  namespace detail
  {
    template<callable_options O, typename T>
    constexpr EVE_FORCEINLINE T sinpi_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      if constexpr(O::contains(quarter_circle))
      {
        return sin[eve::quarter_circle](a0 * pi(eve::as<T>()));
      }
      else
      {
        if constexpr( scalar_value<T> )
          if( is_not_finite(a0) ) return nan(eve::as<T>());
        auto x = eve::abs(a0);
        if( eve::all(x <= T(0.25)) )
          return sinpi[quarter_circle](a0);
        if constexpr( scalar_value<T> )
        {
          if( x > maxflint(eve::as<T>()) ) return T(0);
        }
        else
        {
          x = if_else(is_not_finite(x), eve::allbits, x); // nan or Inf input
          x = if_else(is_greater(x, maxflint(eve::as(x))), eve::zero, x);
        }
        auto [fn, xr, dxr] = rem2(x);
        return sin_finalize(bitofsign(a0), fn, xr, dxr);
      }
    }
  }
}
