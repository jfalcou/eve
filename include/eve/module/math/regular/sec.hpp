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
  struct sec_t : elementwise_callable<sec_t, Options, quarter_circle_option, half_circle_option,
             full_circle_option, medium_option, big_option>
  {
    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

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
  //!      constexpr auto sec[quarter_circle](floating_value auto x)          noexcept; // 3.a
  //!      constexpr auto sec[half_circle](floating_value auto x)             noexcept; // 3.b
  //!      constexpr auto sec[full_circle](floating_value auto x)             noexcept; // 3.c
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
  //!    1. Returns the [elementwise](@ref glossary_elementwise) secant of
  //!       the input (inverse of the cosine). In particular:
  //!        * If the element is \f$\pm0\f$, \f$1\f$ is returned.
  //!        * If the element is \f$\pm\infty\f$, Nan is returned.
  //!        * If the element is a `NaN`, `NaN` is returned.
  //!    2. [The operation is performed conditionnaly](@ref conditional).
  //!    3. These are optimized calls providing a balance between speed and range limitation.
  //!        1. assumes that the inputs elements  belong to \f$[-\pi/4,\pi/4]\f$ and return NaN outside.
  //!        2. assumes that the inputs elements  belong to \f$[-\pi/2,\pi/2]\f$ and return NaN outside.
  //!        3. assumes that the inputs elements  belong to \f$[-\pi,\pi]\f$ and return NaN outside.
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
    constexpr EVE_FORCEINLINE T sec_(EVE_REQUIRES(cpu_), O const& o, T const& a0)
    {
      return eve::rec[pedantic](cos[o](a0));
    }
  }
}
