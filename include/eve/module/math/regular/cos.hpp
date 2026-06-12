//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/math/detail/generic/cos_kernel.hpp>

namespace eve
{
  template<typename Options>
  struct cos_t : elementwise_callable<cos_t, Options, quarter_circle_option,
                                      half_circle_option, full_circle_option,
                                      medium_option, big_option,  raw_option, fast_option,
                                      rad_option, radpi_option, deg_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(cos_t, cos_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//!   @var cos
//!   @brief `elementwise_callable` object computing the cosine.
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
//!      constexpr auto cos(floating_value auto x)                          noexcept; // 1.a
//!
//!      // Lanes masking
//!      constexpr auto cos[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto cos[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto cos[rad](floating_value auto x)                      noexcept; // 1.a
//!      constexpr auto cos[deg](floating_value auto x)                      noexcept; // 1.b
//!      constexpr auto cos[pirad](floating_value auto x)                    noexcept; // 1.c
//!      constexpr auto cos[quarter_circle](floating_value auto x)           noexcept; // 3.a
//!      constexpr auto cos[half_circle](floating_value auto x)              noexcept; // 3.b
//!      constexpr auto cos[full_circle](floating_value auto x)              noexcept; // 3.c
//!      constexpr auto acos[raw](floating_value auto x)                     noexcept; // 4.a
//!      constexpr auto acos[fast] (floating_value auto x)                   noexcept; // 4.b
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
//!    1. Returns the [elementwise](@ref glossary_elementwise) cosine of the input.
//!       In particular:
//!       1. assume a parameter in radian.
//!       2. assume a parameter in degree.
//!       3. assume a parameter in \f$\pi\f$ multiples. </br>
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!    3. These are optimized calls providing a balance between speed and range limitation.
//!         1. assumes that the inputs elements  belong to \f$[-\pi/4,\pi/4]\f$ and return NaN outside.
//!         2. assumes that the inputs elements  belong to \f$[-\pi/2,\pi/2]\f$ and return NaN outside.
//!         3. assumes that the inputs elements  belong to \f$[-\pi,\pi]\f$ and return NaN outside.
//!       these options can be combined with the previous ones with ranges adapted to the chosen unity.
//!
//!       In particular:
//!       * If the element is \f$\pm0\f$, \f$1\f$ is returned.
//!       * If the element is \f$\pm\infty\f$, Nan is returned.
//!       * If the element is a `Nan`, `Nan` is returned.
//!    4. faster but less accurate versions that can be mixed with range limitations  quarter_circle or
//!       half_circle_option to have any effect.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/cos)
//!   *  [Wikipedia](https://fr.wikipedia.org/wiki/Cosinus)
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/Cosine.html)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/math/cos.cpp}
//================================================================================================
 inline constexpr auto cos = functor<cos_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace _
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T cos_(EVE_REQUIRES(cpu_), O const& o , T const& a0)
    {
      using elt_t = element_type_t<T>;
      if constexpr(std::same_as<eve::element_type_t<T>, eve::float16_t>)
        return eve::_::apply_fp16_as_fp32(eve::cos_kernel[o], a0);
      else if constexpr(O::contains(half_circle) ||  O::contains(quarter_circle) )
      {
        if constexpr(O::contains(deg))
          return cos[o.drop(deg)](div_180(a0));
        else if constexpr(O::contains(radpi))
          return cos[o.drop(radpi)](pi(eve::as<elt_t>())*a0);
        else if constexpr(O::contains(raw))
        {
          constexpr elt_t c0(1);
          constexpr elt_t c2(-0.4960);
          constexpr elt_t c4(0.03705);
          return reverse_horner(sqr(a0), c0, c2, c4);
        }
        else if constexpr(O::contains(fast) || std::same_as<elt_t, float>)
        {
          constexpr elt_t c0(1);
          constexpr elt_t c2(-0.4999999963);
          constexpr elt_t c4(0.0416666418);
          constexpr elt_t c6(-0.0013888397);
          constexpr elt_t c8(0.0000247609);
          constexpr elt_t c10(-0.0000002605);
          return reverse_horner(sqr(a0), c0, c2, c4, c6, c8, c10); //absolute error less than 2x1.0e-9
        }
        else
          return cos_kernel[o](a0);
      }
      else
        return cos_kernel[o](a0);
    }
  }
    constexpr auto cosd = eve::cos[eve::deg];
    constexpr auto cospi= eve::cos[eve::radpi];
}
