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
//!  @godbolt{doc/complex/regular/erfi.cpp}
//!  @}
//================================================================================================
  EVE_MAKE_CALLABLE(erfi_, erfi);
  namespace detail
  {
    template<typename Z>
    EVE_FORCEINLINE auto complex_unary_dispatch( eve::tag::erfi_
                                               , Z z) noexcept
    {
      auto realz = is_real(z);
      if (eve::all(realz))
        return Z{erfi(real(z)), 0};
      else  if (eve::none(realz))
        return -(eve::callable_i_{}*erf(callable_i_{}*z));
      else
        return if_else(realz, Z{erfi(real(z)), 0}, -(eve::callable_i_{}*erf(i(as(z))*z)));
    }

    template<floating_ordered_value V>
    EVE_FORCEINLINE auto erfi_( EVE_SUPPORTS(cpu_)
                             , V const & v) noexcept
    {
      auto over = sqr(v) > 720;
      V r = inf(as(v))*sign(v);
      return if_else(over,  r, -imag(erf(as_complex_t<V>(0, -v))));
    }
  }
}
