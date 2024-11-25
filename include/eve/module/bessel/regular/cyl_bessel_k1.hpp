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
  struct cyl_bessel_k1_t : elementwise_callable<cyl_bessel_k1_t, Options>
  {
    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(T a) const noexcept
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), a);
    }

    EVE_CALLABLE_OBJECT(cyl_bessel_k1_t, cyl_bessel_k1_);
  };

//================================================================================================
//! @addtogroup bessel
//! @{
//!   @var cyl_bessel_k1
//!   @brief `elementwise_callable` object computing the modified Bessel function of the second kind,
//!   \f$ K_1(x)=\int_{0}^{\infty} e^{-x \cosh \tau} \cosh \tau\,\mathrm{d}\tau\f$.
//!
//!   It is a solution of \f$ x^{2}y''+xy'-(1+x^2)y=0\f$ for which \f$ y(0) = \infty\f$.
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
//!      constexpr auto cyl_bessel_k1(floating_value auto x) -> decltype(x)           noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto cyl_bessel_k1[conditional_expr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto cyl_bessel_k1[logical_value auto m](floating_value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: positive [floating argument](@ref eve::floating_value).
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. The value of \f$ \displaystyle K_1(x)=\int_{0}^{\infty} e^{-x \cosh \tau}
//!         \cosh \tau\,\mathrm{d}\tau\f$ is returned.
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [C++ standard reference: cyl_bessel_k](https://en.cppreference.com/w/cpp/numeric/special_functions/cyl_bessel_k)
//!   *  [Wikipedia: Bessel Functions](https://en.wikipedia.org/wiki/Bessel_function)
//!   *  [DLMF: Modified Bessel Functions](https://dlmf.nist.gov/10.25)
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/bessel/cyl_bessel_k1.cpp}
//================================================================================================
   inline constexpr auto cyl_bessel_k1 = functor<cyl_bessel_k1_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/bessel/regular/impl/cyl_bessel_k1.hpp>
