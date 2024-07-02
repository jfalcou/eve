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
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math/regular/atan.hpp>
#include <eve/module/math/regular/tanh.hpp>

namespace eve
{
  template<typename Options>
  struct gd_t : elementwise_callable<gd_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(gd_t, gd_);
  };

//================================================================================================
//! @addtogroup math_hyper
//! @{
//! @var gd
//! @brief `elementwise_callable` object computing the gudermanian gd: \f$\int_0^\infty 1/\cosh x dx\f$.
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
//!      // Regular overload
//!      constexpr auto gd(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto gd[conditional_expr auto c](floating_value auto x) noexcept; // 2.1
//!      constexpr auto gd[logical_value auto m](floating_value auto x)    noexcept; // 2.2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * `x`: [floating value](@ref eve::floating_value).
//!      * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!      * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1.  Returns the [elementwise](@ref glossary_elementwise) gudermanian of the input.
//!         In particular:
//!            * If the element is \f$\pm0\f$, \f$0\f$ is returned.
//!            * If the element is \f$\pm\infty\f$, \f$\pm\pi/2\f$ is returned.
//!            * If the element is a `NaN`, `NaN` is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/regular/gd.cpp}
//!  @}
//================================================================================================
  inline constexpr auto gd = functor<gd_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T gd_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      return 2*atan(tanh(a0*half(as(a0))));
    }
  }
}
