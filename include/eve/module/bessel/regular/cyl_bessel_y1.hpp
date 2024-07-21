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

namespace eve
{
  template<typename Options>
  struct cyl_bessel_y1_t : elementwise_callable<cyl_bessel_y1_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr
    T operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(cyl_bessel_y1_t, cyl_bessel_y1_);
  };

//================================================================================================
//! @addtogroup bessel
//! @{
//!   @var cyl_bessel_y1
//!   @brief `elementwise_callable` object computing the Bessel function of the second kind,
//!    \f$ Y_1(x)=\frac2{\pi}\int_{1}^{\infty}\frac{\cos x\tau}
//!   {(\tau^2-1)^{3/2}}\,\mathrm{d}\tau\f$.
//!
//!   It is a solution of \f$ x^{2}y''+xy'+(x^2-1)y=0\f$ for which \f$ y(0) = \infty\f$.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/bessel.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      constexpr auto cyl_bessel_y1(floating_value auto x) -> decltype(x)           noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto cyl_bessel_y1[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto cyl_bessel_y1[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: positive [floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of \f$\displaystyle Y_1(x)=\frac2{\pi}\int_{1}^{\infty}\frac{\cos x\tau}
//!         {(\tau^2-1)^{3/2}}\,\mathrm{d}\tau\f$ is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference](https://en.cppreference.com/w/cpp/numeric/special_functions/cyl_bessel_i)
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Bessel_function)
//!   *  [DLMF](https://dlmf.nist.gov/10.2)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/bessel/cyl_bessel_y1.cpp}
//================================================================================================
  inline constexpr auto cyl_bessel_y1 = functor<cyl_bessel_y1_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/bessel/regular/impl/cyl_bessel_y1.hpp>
