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
#include <eve/module/math/regular/cos.hpp>

namespace eve
{
  template<typename Options>
  struct sec_t : elementwise_callable<sec_t, Options,
                                      quarter_circle_option, half_circle_option,
                                      full_circle_option, medium_option, big_option,
                                      rad_option, radpi_option, deg_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sec_t, sec_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var sec
//!
//! @brief `elementwise_callable` object computing the secant of the input.
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
//!      constexpr auto sec(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sec[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto sec[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto csc[rad](floating_value auto x)                     noexcept; // 1.a
//!      constexpr auto csc[deg](floating_value auto x)                     noexcept; // 1.b
//!      constexpr auto csc[pirad](floating_value auto x)                   noexcept; // 1.c
//!      constexpr auto sec[quarter_circle](floating_value auto x)          noexcept; // 3.a
//!      constexpr auto sec[half_circle](floating_value auto x)             noexcept; // 3.b
//!      constexpr auto sec[full_circle](floating_value auto x)             noexcept; // 3.c
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!      * `x`: [floating value](@ref eve::floating_value).
//!      * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!      * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//! **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) secant of
//!       (the inverse of the cosine). In particular:
//!       1. assume a parameter in radian.
//!       2. assume a parameter in degree.
//!       3. assume a parameter in \f$\pi\f$ multiples. </br>
//!       the input (inverse of the cosine).
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!    3. These are optimized calls providing a balance between speed and range limitation.
//!        1. assumes that the inputs elements  belong to \f$[-\pi/4,\pi/4]\f$ and return NaN outside.
//!        2. assumes that the inputs elements  belong to \f$[-\pi/2,\pi/2]\f$ and return NaN outside.
//!        3. assumes that the inputs elements  belong to \f$[-\pi,\pi]\f$ and return NaN outside.
//!
//!       In particular:
//!        * If the element is \f$\pm0\f$, \f$1\f$ is returned.
//!        * If the element is \f$\pm\infty\f$, Nan is returned.
//!        * If the element is a `NaN`, `NaN` is returned.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/Secant.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/sec.cpp}
//================================================================================================
  inline constexpr auto sec = functor<sec_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_NOINLINE T sec_(EVE_REQUIRES(cpu_), O const& o, T a0)
    {
      using elt_t = element_type_t<T>;
      if constexpr(std::same_as<elt_t, eve::float16_t>)
        return eve::detail::apply_fp16_as_fp32(eve::sec[o], a0);
      else if constexpr(O::contains(radpi))
      {
        if constexpr(O::contains(quarter_circle))
        {
          auto x    = abs(a0);
          auto test = is_not_less_equal(x, T(0.25));
          if constexpr( scalar_value<T> )
          {
            if( test ) return nan(eve::as<T>());
          }
          else { a0 = if_else(test, eve::allbits, a0); }

          a0 *= pi(eve::as<T>());
          auto x2 = sqr(a0);
          return rec[pedantic](cos_eval(x2));
        }
        else
        {
          const T x = eve::abs(a0);
          if constexpr( scalar_value<T> )
          {
            if( is_not_finite(x) ) return nan(eve::as<T>());
            if( x > maxflint(eve::as<T>()) ) return T(1);
          }

          T z = cospi[o](x);
          if constexpr( scalar_value<T> ) { return (z) ? rec[pedantic](z) : nan(eve::as<T>()); }
          else { return if_else(is_nez(z) && is_finite(a0), rec[pedantic](z), eve::allbits); }
        }
      }
      else if constexpr(O::contains(deg))
      {
        if constexpr( O::contains(quarter_circle) )
          return eve::rec[pedantic](eve::cos[deg][o](a0));
        else
        {
          auto a0_180 = div_180(a0);
          auto test   = is_not_flint(a0_180) && is_flint(a0_180 + mhalf(eve::as(a0_180)));
          if constexpr( scalar_value<T> ) // early return for nans in scalar case
          {
            if( test ) return nan(eve::as<T>());
          }
          return if_else(test, eve::allbits, rec[pedantic](cos[deg][o](a0)));
        }
      }
      else
        return eve::rec[pedantic](cos[o](a0));
    }
  }
  constexpr auto secd = eve::sec[eve::deg];
  constexpr auto secpi= eve::sec[eve::radpi];
}
