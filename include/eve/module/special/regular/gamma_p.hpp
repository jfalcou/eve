//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup special
  //! @{
  //!   @var gamma_p
  //!   @brief Computes the normalized lower incomplete \f$\Gamma\f$ function :
  //!        \f$\displaystyle \frac{1}{\Gamma(x)}\int_0^{y} t^{x-1}e^{-t}\mbox{d}t\f$
  //!
  //!   **Defined in header**
  //!
  //!   @code
  //!   #include <eve/module/special.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::floating_real_value T >
  //!      T  gamma_p(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y`:  [real floating arguments](@ref eve::floating_real_value).
  //!
  //!    **Return value**
  //!
  //!    the value of the normalized lower incomplete \f$\Gamma\f$ function
  //!    is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/special/regular/gamma_p.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(gamma_p_, gamma_p);
}

#include <eve/module/special/regular/impl/gamma_p.hpp>
