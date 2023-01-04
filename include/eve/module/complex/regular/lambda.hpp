//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/complex/detail/special.hpp>
#include <eve/module/complex/regular/eta.hpp>
#include <array>

namespace eve
{
//================================================================================================
//! @addtogroup special
//! @{
//! @var lambda
//!
//! @brief Callable object computing The Dirichlet \f$ \displaystyle \lambda(z) = \sum_0^\infty \frac{1}{(2n+1)^z}\f$
//!
//! This function can be extended to the whole complex plane as \f$\lambda(z) = \zeta(z)(1-2^{-x})\f$
//! (where \f$\zeta\f$ is the Riemann zeta function). It coincides with the serie where the serie converges.
//! However for `z = 1` the result is \f$\infty\f$.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/complex.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< like<complex> T >
//!      T lambda(T z) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `z`:   [floating](@ref eve::floating_value) or [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   Returns the Dirichlet sum \f$  \displaystyle \sum_0^\infty \frac{1}{(2n+1)^z}\f$
//!
//!  @groupheader{Example}
//!
//!   **Real version**
//!
//!  @godbolt{doc/special/regular/lambda.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/regular/lambda.cpp}
//!  @}
//================================================================================================
  EVE_MAKE_CALLABLE(lambda_, lambda);
  namespace detail
  {
    template<typename Z>
    EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::lambda_
                                               , Z zz) noexcept
    {
      auto z=exp2(zz);
      auto k = (z-1)/(z-2);
      return if_else(z == one(as(z)), inf(as(z)), k*deta(1u, zz));
    }

    template<floating_ordered_value V>
    EVE_FORCEINLINE auto lambda_( EVE_SUPPORTS(cpu_)
                                , V const & v) noexcept
    {
      auto z=exp2(v);
      auto k = (z-1)/(z-2);
      return if_else(z == one(as(z)), inf(as(z)), k*deta(1u, v));
    }
  }
}
