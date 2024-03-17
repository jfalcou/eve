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
#include <eve/module/math/regular/sinpi.hpp>

namespace eve
{
  template<typename Options>
  struct sinpic_t : elementwise_callable<sinpic_t, Options, quarter_circle_option, half_circle_option, full_circle_option, medium_option, big_option>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sinpic_t, sinpic_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var sinpic
//!
//! @brief Callable object computing the normalized cardinal sine.
//!
//!   **Defined in Header**
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
//!      template< eve::floating_value T >
//!      T sinpic(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) sine of the input times \f$\pi\f$  divided
//! by the input times \f$\pi\f$.
//!
//! In particular:
//!
//!   * If the element is \f$\pm0\f$, \f$1\f$ is returned.
//!   * If the element is \f$\pm\infty\f$, 0 is returned.
//!   * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sinpic.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  @}
//================================================================================================
 inline constexpr auto sinpic = functor<sinpic_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T sinpic_(EVE_REQUIRES(cpu_), O const& , T const& a0)
    {
      if constexpr( scalar_value<T> )
      {
        if( is_eqz(a0) ) return one(eve::as(a0));
        if constexpr( eve::platform::supports_infinites )
          if( is_infinite(a0) ) return zero(eve::as<T>());
        if constexpr( eve::platform::supports_denormals )
          return eve::abs(a0) < eps(as<T>()) ? one(eve::as<T>()) : sinpi(a0) / (pi(as<T>()) * a0);
        else return sinpi(a0) / (pi(eve::as(a0)) * a0);
      }
      else
      {
        auto r1 = sinpi(a0) / (pi(eve::as(a0)) * a0);
        if constexpr( eve::platform::supports_denormals )
        {
          r1 = if_else(eve::abs(a0) < eps(as<T>()), one(eve::as<T>()), r1);
        }
        else r1 = if_else(is_eqz(a0), one(eve::as<T>()), r1);
        if constexpr( eve::platform::supports_infinites )
          r1 = if_else(is_infinite(a0), eve::zero, r1);
        return r1;
      }
    }
  }
}
