//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/complex/regular/detail/special.hpp>
#include <eve/algo.hpp>
#include <iostream>
#include <array>

namespace eve
{
//================================================================================================
//! @addtogroup complex
//! @{
//! @var lambda
//!
//! @brief Callable object computing The Dirichlet \f$ \lambda(z) = \sum_0^\infty \frac{1}{(2n+1)^z}\f$
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
//!   *  `z`:   [floatingl](@ref eve::floating_real_value) or [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   Returns the Dirichlet sum \f$ \sum_0^\infty \frac{1}{(2n+1)^z}\f$
//!
//!  @groupheader{Example}
//!
//!   **Real version**
//!
//!  @godbolt{doc/math/lambda.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/lambda.cpp}
//!  @}
//================================================================================================
  EVE_MAKE_CALLABLE(lambda_, lambda);
  namespace detail
  {
    template<floating_real_value V>
    EVE_FORCEINLINE auto lambda_( EVE_SUPPORTS(cpu_)
                              , V const & v) noexcept
    {
      return real(lambda(as_complex_t<V>(v, 0)));
    }

    template<typename Z>
    EVE_FORCEINLINE auto complex_binary_dispatch( eve::tag::lambda_
                                                , Z zz) noexcept
    {
      auto z=exp2(zz);
      auto k = (z-1)/(z-2);
      return if_else(z == one(as(z)), inf(as(z)), k*dlambda(1u, z));
    }
  }
}
