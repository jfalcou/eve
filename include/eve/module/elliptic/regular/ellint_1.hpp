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
  //! @addtogroup elliptic
  //! @{
  //!   @var ellint_1
  //!   @brief Computes the  elliptic integrals of the first kind :
  //!   \f$\int_0^{\phi} \frac{\mathrm{d}t}{\sqrt{1-k^2\sin^2 t}}\f$.
  //!
  //!   $details$
  //!
  //!   **Defined in Header**
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
  //!      template< eve::floating_real_value T >
  //!      T ellint_1(T phi) noexcept;                                                //1
  //!
  //!      template< eve::floating_real_value T  eve::loating_real_value U >
  //!      eve::common_compatible_value<T, U> ellint_1(T phi; U k) noexcept;          //2
  //!   }
  //!
  //!   1. complete elliptic integrals of the first kind ( corresponds to \f$\phi = \pi/2\f$ ).
  //!   2. incomplete elliptic integrals of the first kind.
  //!
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   `phi`, `k`:   [floating real arguments](@ref eve::floating_real_value).
  //!
  //!   **Return value**
  //!
  //!     the complete and incomplete elliptic integrals of the first kind are returned:
  //!
  //!   **Notes**
  //!
  //!     - `k` must verify \f$k^2\sin^2\phi \le 1\f$ or the result is nan.
  //!
  //!     - In the complete case this means \f$|k| \le 1\f$.
  //!
  //!  @warning
  //!    Be aware that as \f$\pi/2\f$ is not exactly represented by floating point
  //!    values the result of the incomplete  function with a \f$\phi\f$ value
  //!    "representing" \f$\pi/2\f$ can differ a lot with the result of the complete call.
  //!
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/elliptic/regular/ellint_1.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(ellint_1_, ellint_1);
}

#include <eve/module/elliptic/regular/impl/ellint_1.hpp>
