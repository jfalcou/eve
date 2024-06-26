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
#include <eve/module/math/regular/sinh.hpp>

namespace eve
{
  template<typename Options>
  struct csch_t : elementwise_callable<csch_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(csch_t, csch_);
  };

//================================================================================================
//! @addtogroup math_hyper
//! @{
//! @var csch
//! @brief `elementwise_callable` object computing  \f$\frac2{e^x+e^{-x}}\f$.
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
//!      constexpr auto csch(floating_value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto csch[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto csch[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * `x`: [floating value](@ref floating_value).
//!      * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!      * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!    1.  Returns the [elementwise](@ref glossary_elementwise) hyperbolic secant of the input.
//!       In particular:
//!          * If the element is \f$\pm0\f$, \f$\pm\infty\f$ is returned.
//!          * If the element is \f$\pm\infty\f$, \f$\pm0\f$ is returned.
//!          * If the element is a `NaN`, `NaN` is returned.
//!    2. [The operation is performed conditionnaly](@ref conditional).
//!
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/regular/csch.cpp}
//!  @}
//================================================================================================
  inline constexpr auto csch = functor<csch_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    constexpr EVE_FORCEINLINE T csch_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      return rec[pedantic2](sinh(a0));
    }
  }
}
