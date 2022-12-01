//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
//!   \f$\mathbf{F}(\phi, k) = \int_0^{\phi} \frac{\mathrm{d}t}{\sqrt{1-k^2\sin^2 t}}\f$ and
//!   \f$\mathbf{K}(k) = \int_0^{\pi/2} \frac{\mathrm{d}t}{\sqrt{1-k^2\sin^2 t}}\f$.
//!
//!   Be aware that as \f$\pi/2\f$ is not exactly represented by floating point
//!   values the result of the incomplete function with a \f$\phi\f$ floating point value
//!   representing \f$\pi/2\f$ can differ a lot with the result of the complete call.
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
//!      T ellint_1(T k) noexcept;                                                //1
//!
//!      template< eve::floating_real_value T,  eve::floating_real_value U >
//!      eve::common_value_t<T, U> ellint_1(T phi, U k) noexcept;        //2
//!   }
//!   @endcode
//!
//!    1. complete elliptic integrals of the first kind.
//!    2. incomplete elliptic integrals of the first kind.
//!
//!   **Parameters**
//!
//!     * `phi`:   [floating real Jacobi amplitude](@ref eve::floating_real_value).
//!
//!     * `k`:  [floating real elliptic modulus](@ref eve::floating_real_value). `k` must verify
//!             \f$k^2\sin^2\phi \le 1\f$ or the result is NaN. In the complete case this means
//!             \f$|k| \le 1\f$.
//!
//!   **Return value**
//!
//!     1. the complete elliptic integral (corresponding to \f$ \phi = \pi/2 \f$) is returned.
//!     2. the incomplete elliptic integral is returned:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/elliptic/regular/ellint_1.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(ellint_1_, ellint_1);
}

#include <eve/module/elliptic/regular/impl/ellint_1.hpp>
