//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/math/detail/generic/sincos_kernel.hpp>

namespace eve
{
  template<typename Options>
  struct sincos_t : elementwise_callable<sincos_t, Options , quarter_circle_option,
                                         half_circle_option, full_circle_option,
                                         medium_option, big_option,
                                         rad_option, radpi_option, deg_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE zipped<T,T> operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sincos_t, sincos_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var sincos
//!
//! @brief `elementwise_callable` object computing the simultaneous  computation of sine an cosine.
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
//!      constexpr auto sincos(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sincos[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto sincos[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto sincos[rad](floating_value auto x)                     noexcept; // 1.a
//!      constexpr auto sincos[deg](floating_value auto x)                     noexcept; // 1.b
//!      constexpr auto sincos[pirad](floating_value auto x)                   noexcept; // 1.c
//!      constexpr auto sincos[quarter_circle](floating_value auto x)          noexcept; // 3.a
//!      constexpr auto sincos[half_circle](floating_value auto x)             noexcept; // 3.b
//!      constexpr auto sincos[full_circle](floating_value auto x)             noexcept; // 3.c
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
//!   1 .The computation returns a tuple-like whose elements are `sin(x)` and `cos(x)`
//!       In particular:
//!       1. assume a parameter in radian.
//!       2. assume a parameter in degree.
//!       3. assume a parameter in \f$\pi\f$ multiples. </br>
//!   2. [The operation is performed conditionnaly](@ref conditional).
//!   3. These are optimized calls providing a balance between speed and range limitation.
//!        1. assumes that the inputs elements  belong to \f$[-\pi/4,\pi/4]\f$ and return NaN outside.
//!        2. assumes that the inputs elements  belong to \f$[-\pi/2,\pi/2]\f$ and return NaN outside.
//!        3. assumes that the inputs elements  belong to \f$[-\pi,\pi]\f$ and return NaN outside.
//!       these options can be combined with the previous ones with ranges adapted to the chosen unity.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/sincos.cpp}
//================================================================================================
 inline constexpr auto sincos = functor<sincos_t>;
//================================================================================================
//!  @}
//================================================================================================
 namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE eve::zipped<T, T> sincos_(EVE_REQUIRES(cpu_), O const& o , T const& a0)
    {
      if constexpr(std::same_as<eve::element_type_t<T>, eve::float16_t>)
        return eve::detail::apply_fp16_as_fp32(eve::sincos_kernel[o], a0);
      else
        return sincos_kernel[o](a0);
    }
 }
  constexpr auto sindcosd = eve::sincos[eve::deg];
  constexpr auto sinpicospi= eve::sincos[eve::radpi];
}
