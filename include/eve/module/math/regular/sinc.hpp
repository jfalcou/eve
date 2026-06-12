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
#include <eve/module/math/detail/generic/sinc_kernel.hpp>
#include <eve/module/math/regular/sin.hpp>
//#include <eve/module/math/regular/sinpic.hpp>

namespace eve
{
  template<typename Options>
  struct sinc_t : elementwise_callable<sinc_t, Options, raw_option, fast_option,
                                       quarter_circle_option, half_circle_option,
                                       full_circle_option, medium_option, big_option,
                                       rad_option, radpi_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sinc_t, sinc_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var sinc
//!
//! @brief `elementwise_callable` object computing the sine cardinal.
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
//!      constexpr auto sinc(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sinc[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto sinc[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto sinc[radpi](floating_value auto x)                    noexcept; // 1.c
//!      constexpr auto sinc[quarter_circle](floating_value auto x)           noexcept; // 3.a
//!      constexpr auto sinc[half_circle](floating_value auto x)              noexcept; // 3.b
//!      constexpr auto sinc[full_circle](floating_value auto x)              noexcept; // 3.c
//!      constexpr auto sinc[raw](floating_value auto x)                      noexcept; // 4.a
//!      constexpr auto sinc[fast] (floating_value auto x)                    noexcept; // 4.b
//!      constexpr auto sinc[radpi](floating_value auto x)                      noexcept; // 5
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!    * `x`: [floating value](@ref eve::floating_value).
//!    * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!    * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) sine of the input divided by the input.
//!       In particular:
//!       * If the element is \f$\pm0\f$, \f$1\f$ is returned.
//!       * If the element is \f$\pm\infty\f$, 0 is returned.
//!       * If the element is a `Nan`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!    3. These are optimized calls providing a balance between speed and range limitation.
//!         1. assumes that the inputs elements  belong to \f$[-\pi/4,\pi/4]\f$ and return NaN outside.
//!         2. assumes that the inputs elements  belong to \f$[-\pi/2,\pi/2]\f$ and return NaN outside.
//!         3. assumes that the inputs elements  belong to \f$[-\pi,\pi]\f$ and return NaN outside.
//!       these options can be combined with the previous ones with ranges adapted to the chosen unity.
//!    5. returns \f$\sin \frac{\pi x}{\pi x}
//!  @groupheader{External references}
//!   *  [Wikipedia](https://fr.wikipedia.org/wiki/Sinus_cardinal)
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/SineCardinalFunction.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/sinc.cpp}
//================================================================================================
  inline constexpr auto sinc = functor<sinc_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace _
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T sinc_(EVE_REQUIRES(cpu_), O const& o , T const& a0)
    {
      using elt_t = element_type_t<T>;
      if constexpr(std::same_as<eve::element_type_t<T>, eve::float16_t>)
        return eve::_::apply_fp16_as_fp32(eve::sinc[o], a0);
      else if constexpr(std::same_as<elt_t, double> ||
                        (std::same_as<elt_t, float> && !(O::contains(fast) ||  O::contains(raw))))
      {
        auto r = sin[o](a0)/a0;
        if constexpr( O::contains(radpi) ) r *= inv_pi(as<elt_t>());
        r = if_else(is_infinite(a0), zero, r);
        return if_else(eve::abs(a0) < eps(as<elt_t>()), one, r);
      }                                                
      else if constexpr(O::contains(half_circle) ||  O::contains(quarter_circle))
      {
        if constexpr(O::contains(radpi))    return sinc[o.drop(radpi)](pi(eve::as<elt_t>())*a0);
        else if constexpr(O::contains(raw)) return ab_st::raw_sinc(a0);
        else if constexpr(O::contains(fast))return ab_st::fast_sinc(a0);
        else if constexpr(std::same_as<elt_t, float>)
        {
          auto bound = O::contains(fast) ? pio_2[lower](as<elt_t>()) :pio_4[lower](as<elt_t>());
          return if_else(eve::abs(a0) <= bound, sinc[fast](a0), allbits);
        }
        else return sinc(a0); 
      }
      else return sinc(a0);
    }
  }
   constexpr auto sinpic = eve::sinc[eve::radpi];
}
