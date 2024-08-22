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
  struct cyl_bessel_j1_t : elementwise_callable<cyl_bessel_j1_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr
    T operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(cyl_bessel_j1_t, cyl_bessel_j1_);
  };

//================================================================================================
//! @addtogroup bessel
//! @{
//!   @var cyl_bessel_j1
//!   @brief `elementwise_callable` object computing the Bessel function of the first kind,
//!   \f$ J_1(x)=\frac1{\pi }\int _{0}^{\pi}\cos(\tau-x\sin \tau )\,\mathrm {d} \tau \f$.
//!
//!   It is the solution of \f$ x^{2}y''+xy'+(x^2-1)y=0\f$ for which \f$ y(0) = 0\f$.
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
//!      constexpr auto cyl_bessel_j1(floating_value auto x) -> decltype(x)           noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto cyl_bessel_j1[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto cyl_bessel_j1[logical_value auto m](floating_value auto x)    noexcept; // 2
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
//!     1. The value of \f$ \displaystyle J_1(x)=\frac1{\pi }\int _{0}^{\pi}\cos(\tau-x\sin \tau )
//!       \,\mathrm {d} \tau \f$ is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: cyl_bessel_j](https://en.cppreference.com/w/cpp/numeric/special_functions/cyl_bessel_j)
//!   *  [Wikipedia: Bessel Functions](https://en.wikipedia.org/wiki/Bessel_function)
//!   *  [DLMF: Bessel Functions](https://dlmf.nist.gov/10.2)
//!
//!   @groupheader{Example}
//!   @godbolt{doc/bessel/cyl_bessel_j1.cpp}
//================================================================================================
  inline constexpr auto cyl_bessel_j1 = functor<cyl_bessel_j1_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/bessel/regular/impl/cyl_bessel_j1.hpp>
