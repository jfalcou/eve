//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup bessel
  //! @{
  //!   @var cyl_bessel_j1
  //!   @brief Computes the Bessel function of the first kind,
  //!   \f$ J_1(x)=\frac1{\pi }\int _{0}^{\pi}\cos(\tau-x\sin \tau )\,\mathrm {d} \tau \f$.
  //!
  //!   It is the solution of \f$ x^{2}y''+xy'+(x^2-1)y=0\f$ for which \f$ y(0) = 0\f$.
  //!
  //!   **Defined in header**
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
  //!      template< eve::floating_real_value T >
  //!      T cyl_bessel_j1(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [real floating argument](@ref eve::floating_real__value).
  //!
  //!   **Return value**
  //!
  //!   The value of \f$ \displaystyle J_1(x)=\frac1{\pi }\int _{0}^{\pi}\cos(\tau-x\sin \tau )
  //!   \,\mathrm {d} \tau \f$ is returned.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/bessel/regular/cyl_bessel_j1.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(cyl_bessel_j1_, cyl_bessel_j1);
}

#include <eve/module/bessel/regular/impl/cyl_bessel_j1.hpp>
