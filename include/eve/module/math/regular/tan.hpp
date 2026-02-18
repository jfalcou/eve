//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/math/detail/generic/tan_kernel.hpp>

namespace eve
{
  template<typename Options>
  struct tan_t : elementwise_callable<tan_t, Options, quarter_circle_option, half_circle_option,
                                      full_circle_option, medium_option, big_option,
                                      rad_option, radpi_option, deg_option>
  {
    template<eve::floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(tan_t, tan_);
  };

//================================================================================================
//! @addtogroup math_trig
//! @{
//! @var tan
//!
//! @brief `elementwise_callable` object computing the tangent.
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
//!      constexpr auto tan(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto tan[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto tan[logical_value auto m](floating_value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto tan[quarter_circle](floating_value auto x)          noexcept; // 3.a
//!      constexpr auto tan[half_circle](floating_value auto x)             noexcept; // 3.b
//!      constexpr auto tan[full_circle](floating_value auto x)             noexcept; // 3.c
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
//!    1.  Returns the [elementwise](@ref glossary_elementwise) tangent of the input. In particular:
//!         * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!         * If the element is \f$\pm\infty\f$, Nan is returned.
//!         * If the element is a `Nan`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!    3. These are optimized calls providing a balance between speed and range limitation.
//!        1. assumes that the inputs elements  belong to \f$[-\pi/4,\pi/4]\f$ and return NaN outside.
//!        2. assumes that the inputs elements  belong to \f$[-\pi/2,\pi/2]\f$ and return NaN outside.
//!        3. assumes that the inputs elements  belong to \f$[-\pi,\pi]\f$ and return NaN outside.
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/math/tan)
//!   *  [Wikipedia](https://fr.wikipedia.org/wiki/Tangent)
//!   *  [Wolfram MathWorld](https://mathworld.wolfram.com/Tangent.html)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/tan.cpp}
//================================================================================================
  inline constexpr auto tan = functor<tan_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T tan_(EVE_REQUIRES(cpu_), O const& o , T const& a0)
    {
    if constexpr(std::same_as<eve::element_type_t<T>, eve::float16_t>)
      return eve::detail::apply_fp16_as_fp32(eve::tan_kernel[o], a0);
    else
      return tan_kernel[o](a0);
    }
  }
  constexpr auto tand = eve::tan[eve::deg];
  constexpr auto tanpi= eve::tan[eve::radpi];

}
