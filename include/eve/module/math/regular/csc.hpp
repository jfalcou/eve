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
  struct csc_t : elementwise_callable<csc_t, Options,
                                      quarter_circle_option, half_circle_option,
                                      full_circle_option, medium_option, big_option,
                                      rad_option, radpi_option, deg_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(csc_t, csc_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var csc
//!
//! @brief `elementwise_callable` object computing the cosecant of the input.
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
//!      constexpr auto csc(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto csc[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto csc[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto csc[rad](floating_value auto x)                      noexcept; // 1.a
//!      constexpr auto csc[deg](floating_value auto x)                      noexcept; // 1.b
//!      constexpr auto csc[pirad](floating_value auto x)                    noexcept; // 1.c
//!      constexpr auto csc[quarter_circle](floating_value auto x)           noexcept; // 3.a
//!      constexpr auto csc[half_circle](floating_value auto x)              noexcept; // 3.b
//!      constexpr auto csc[full_circle](floating_value auto x)              noexcept; // 3.c
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * `x`: [floating value](@ref eve::floating_value).
//!      * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!      * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!    1. Returns the [elementwise](@ref glossary_elementwise) cosecant of the input.
//!       (the inverse of the sine). In particular:
//!       1. assume a parameter in radian.
//!       2. assume a parameter in degree.
//!       3. assume a parameter in \f$\pi\f$ multiples. </br>
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!    3. These are optimized calls providing a balance between speed and range limitation.
//!        1. assumes that the inputs elements  belong to \f$[-\pi/4,\pi/4]\f$ and return NaN outside.
//!        2. assumes that the inputs elements  belong to \f$[-\pi/2,\pi/2]\f$ and return NaN outside.
//!        3. assumes that the inputs elements  belong to \f$[-\pi,\pi]\f$ and return NaN outside.
//!
//!       In particular:
//!         * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!         * If the element is \f$\pm\infty\f$, Nan is returned.
//!         * If the element is a `NaN`, `NaN` is returned.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/Cosecant.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/csc.cpp}
//================================================================================================
  inline constexpr auto csc = functor<csc_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace _
  {
    template<typename T, callable_options O>
    constexpr EVE_NOINLINE T csc_(EVE_REQUIRES(cpu_), O const& o, T const& a0)
    {
      using elt_t = element_type_t<T>;
      if constexpr(std::same_as<elt_t, eve::float16_t>)
        return eve::_::apply_fp16_as_fp32(eve::csc[o], a0);
      else if constexpr(O::contains(radpi))
      {
        if constexpr( scalar_value<T> )
        {
          if( is_eqz(a0) ) return rec[pedantic](a0);
          if( is_flint(a0) || is_not_finite(a0) ) return nan(eve::as<T>()); // nan or Inf input
        }
        T x = abs(a0);
        if constexpr( simd_value<T> )
        {
          x = if_else(is_nez(a0) && (is_not_finite(x) || is_flint(x)), eve::allbits, x);
        }
        auto [fn, xr, dxr] = rem2(x);
        return rec[pedantic](sin_finalize(bitofsign(a0), quadrant(fn), xr, dxr));
      }
      else if constexpr(O::contains(deg))
      {
        if constexpr(O::contains(quarter_circle))
          return eve::rec[pedantic](eve::sind[o](a0));
        else
        {
          auto a0_180 = div_180(a0);
          auto test   = is_nez(a0_180) && is_flint(a0_180);
          if constexpr( scalar_value<T> ) // early return for nans in scalar case
          {
            if( test ) return nan(eve::as<T>());
          }
          return if_else(test, eve::allbits, rec[pedantic](sin[deg][o](a0)));
        }
      }
      else
        return eve::rec[pedantic](sin[o](a0));
    }
  }

  constexpr auto cscd = eve::csc[eve::deg];
  constexpr auto cscpi= eve::csc[eve::radpi];
}
