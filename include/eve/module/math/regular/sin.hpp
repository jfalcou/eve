//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/math/detail/generic/sin_kernel.hpp>

namespace eve
{
  template<typename Options>
  struct sin_t : elementwise_callable<sin_t, Options, quarter_circle_option,
                                      half_circle_option, full_circle_option,
                                      medium_option, big_option,
                                      rad_option, radpi_option, deg_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sin_t, sin_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var sin
//!
//! @brief `elementwise_callable` object computing the sine.
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
//!      constexpr auto sin(floating_value auto x)                          noexcept; // 1.a
//!
//!      // Lanes masking
//!      constexpr auto sin[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto sin[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto sin[rad](floating_value auto x)                     noexcept; // 1.a
//!      constexpr auto sin[deg](floating_value auto x)                     noexcept; // 1.b
//!      constexpr auto sin[pirad](floating_value auto x)                   noexcept; // 1.c
//!      constexpr auto sin[quarter_circle](floating_value auto x)          noexcept; // 3.a
//!      constexpr auto sin[half_circle](floating_value auto x)             noexcept; // 3.b
//!      constexpr auto sin[full_circle](floating_value auto x)             noexcept; // 3.c
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
//!    1. Returns the [elementwise](@ref glossary_elementwise) sine of the input. In particular:
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
//!       * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!       * If the element is \f$\pm\infty\f$, Nan is returned.
//!       * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/sin)
//!   *  [Wikipedia](https://fr.wikipedia.org/wiki/Sinus)
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/Sine.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/sin.cpp}
//================================================================================================
  inline constexpr auto sin = functor<sin_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace _
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T sin_(EVE_REQUIRES(cpu_), O const& o , T const& a0)
    {
    if constexpr(std::same_as<eve::element_type_t<T>, eve::float16_t>)
      return eve::_::apply_fp16_as_fp32(eve::sin_kernel[o], a0);
    else
      return sin_kernel[o](a0);
    }
  }
  constexpr auto sind = eve::sin[eve::deg];
  constexpr auto sinpi= eve::sin[eve::radpi];

}
