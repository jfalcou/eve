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
#include <array>

namespace eve
{
//================================================================================================
//! @addtogroup special
//! @{
//! @var eta
//!
//! @brief Callable object computing The imaginary error function \f$ \displaystyle \mathrm{erfi}(z) = -i/erf(iz)\f$
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
//!      T erfi(T z) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `z`:   [floatingl](@ref eve::floating_real_value) or [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   Returns the imaginary error function \f$ \displaystyle \mathrm{erfi}(z) = -i/erf(iz)\f$
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/complex/erfi.cpp}
//!  @}
//================================================================================================
  EVE_MAKE_CALLABLE(eta_, eta);
  namespace detail
  {
    template<floating_real_value V>
    EVE_FORCEINLINE auto erfi_( EVE_SUPPORTS(cpu_)
                              , V const & v) noexcept
    {
      auto over = sqr(x) > 720;
      V r = inf(as(x))*sign(x);
      return if_else(over,  r, real(erfi(to_complex(v)));
    }

    template<typename Z>
    EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::eta_
                                                , Z z) noexcept
    {
      return -i(as(z)*erf(i(as(z)*z);
    }
  }
}
