//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/traits/common_value.hpp>
#include <eve/module/elliptic/am.hpp>

namespace eve
{
  template<typename Options>
  struct jacobi_elliptic_t : elementwise_callable<jacobi_elliptic_t, Options, threshold_option, modular_option, eccentric_option>
  {

    template<eve::floating_value T0, eve::floating_value T1>
    requires (same_lanes_or_scalar<T0, T1>)
      constexpr EVE_FORCEINLINE
    auto operator()(T0 a, T1 b) const noexcept -> decltype(zip(common_value_t<T0, T1>(), common_value_t<T0, T1>(), common_value_t<T0, T1>()))
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(jacobi_elliptic_t, jacobi_elliptic_);
  };

//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var jacobi_elliptic
//!   @brief `elementwise_callable` object computing the  Jacobi's sn, cn and dn function simultaneously.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/elliptic.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto jacobi_elliptic(floating_value auto u, floating_value auto x)                  noexcept; // 1
//!
//!      //Semantic modifiers
//!      constexpr auto jacobi_elliptic[modular](floating_value auto u, floating_value auto alpha)     noexcept; // 1
//!      constexpr auto jacobi_elliptic[eccentric(floating_value auto u, floating_value auto k)        noexcept; // 1
//!      constexpr auto jacobi_elliptic[threshold = tol](floating_value auto u, floating_value auto x) noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto jacobi_elliptic[conditional_expr auto c](/*any of the above overloads*/)       noexcept; // 2
//!      constexpr auto jacobi_elliptic[logical_value autolm](/*any of the above overloads*/)          noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `u`: argument.
//!     * `m`: amplitude parameter (\f$0\le m\le 1\f$).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `l`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!      1. return a `kumi::tuple` containing `sn``cn` and `dn` values. Take care that the meaning of the second parameters
//!         depends on the option used (see note below).
//!      2. [The operation is performed conditionally](@ref conditional)
//!
//!  @groupheader{External references}
//!   *  [DLMF: Jacobian Elliptic](https://dlmf.nist.gov/22.2)
//!   *  [Wolfram MathWorld: Jacobi Elliptic Functions](https://mathworld.wolfram.com/JacobiEllipticFunctions.html)
//!   *  [Wikipedia: Jacobi elliptic functions](https://en.wikipedia.org/wiki/Jacobi_elliptic_functions)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/elliptic/jacobi_elliptic.cpp}
//================================================================================================
  inline constexpr auto jacobi_elliptic = functor<jacobi_elliptic_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<floating_value T, callable_options O>
    auto jacobi_elliptic_(EVE_REQUIRES(cpu_), O const& o, T u, T x) noexcept
    {
      auto tol = [&](){
        if constexpr (O::contains(threshold)) return o[threshold].value(x);
        else                                  return eps(as(element_type_t<T>()));
      }();
      x =  abs(x);
      if constexpr(O::contains(modular)) x = sin(x);
      else if constexpr(O::contains(eccentric)) x = sqrt(x);
      auto phi = am[eve::threshold = tol](u, x);
      auto [sn, cn] = sincos(phi);
      return zip(sn, cn, sqrt(oneminus(sqr(x*sn))));
    }
  }
}
