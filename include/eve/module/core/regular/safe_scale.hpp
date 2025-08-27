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
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/dist.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/next.hpp>

namespace eve
{
  template<typename Options>
  struct safe_scale_t : elementwise_callable<safe_scale_t, Options, pedantic_option>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T a) const noexcept
    { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(safe_scale_t, safe_scale_);
  };

//================================================================================================
//! @addtogroup core_accuracy
//! @{
//!   @var safe_scale
//!   @brief `elementwise_callable` object computing underflow-safe and almost overflow-free
//!      scaling factor for the input.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto safe_scale(floating_value auto x)                 noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto safe_scale[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto safe_scale[logical_value auto m](value auto x)    noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto safe_scale[pedantic](value auto x)                noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [value](@ref eve::value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!     1. provide a value s such that |x|/s, is much above the underflow threshold and much
//!        below the overflow threshold (so that, for example, we can safely square it); (return maxflint for 0);
//!        moreover it is an integer power of 2 (in order to avoid rounding errors when multiplying or dividing by it).
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!     3. same as 1. but return 1 for 0
//!
//!  @groupheader{External references}
//!   *  [HAL: On various ways to split a floating-point number]( https://members.loria.fr/PZimmermann/papers/split.pdf)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/safe_scale.cpp}
//================================================================================================
  inline constexpr auto safe_scale = functor<safe_scale_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto safe_scale_(EVE_REQUIRES(cpu_), O const&, T const& a0)
    {
      using e_t = eve::element_type_t<T>;
      constexpr e_t eps = eve::eps(eve::as<e_t>());
      constexpr e_t phi = (eps/2)*(1+eps);
      constexpr e_t eta = eve::smallestposval(eve::as<e_t>())+2/eps;
      auto y = eve::abs(a0);
      auto e = eve::fma(phi, y, eta);
      auto ysup = y+e;
      if constexpr(O::contains(pedantic))
        return inc[eve::is_eqz(a0)](ysup-y);
      else
        return ysup-y;
    }
  }
}
