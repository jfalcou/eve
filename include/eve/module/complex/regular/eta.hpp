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
#include <array>

namespace eve
{
//================================================================================================
//! @addtogroup special
//! @{
//! @var eta
//!
//! @brief Callable object computing The Dirichlet \f$ \displaystyle \eta(z) = \sum_0^\infty \frac{(-1)^n}{(n+1)^z}\f$
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
//!      T eta(T z) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `z`:   [floatingl](@ref eve::floating_value) or [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   Returns the Dirichlet sum \f$ \sum_0^\infty \frac{(-1)^n}{(n+1)^z}\f$
//!
//!  @groupheader{Example}
//!
//!   **Real version**
//!
//!  @godbolt{doc/special/regular/eta.cpp}
//!
//!   **Complex version**
//!
//!  @godbolt{doc/complex/eta.cpp}
//!  @}
//================================================================================================
  EVE_MAKE_CALLABLE(eta_, eta);
  namespace detail
  {
    template<floating_ordered_value V>
    EVE_FORCEINLINE auto eta_( EVE_SUPPORTS(cpu_)
                              , V const & v) noexcept
    {
      return real(deta(1u, as_complex_t<V>(v, 0)));
    }

    template<typename Z>
    EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::eta_
                                                , Z z) noexcept
    {
      return deta(1u, z);
    }
  }
}
