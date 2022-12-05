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
  //!   @var ellint_rf
  //!   @brief Computes the Carlson's elliptic integral
  //!   \f$  \mathbf{R}_\mathbf{F}(x, y) = \mathbf{R}_\mathbf{D}(x, y) =
  //!   \frac32 \int_{0}^{\infty} \scriptstyle[(t+x)(t+y)]^{-1/2}
  //!   (t+z)^{-3/2}\scriptstyle\;\mathrm{d}t\f$.
  //!
  //!   **Defined in header**
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
  //!      template< eve::floating_ordered_value T
  //!              , eve::floating_ordered_value U
  //!              , eve::floating_ordered_value V >
  //!      eve::common_value_t<T, U, V> ellint_rf(T x, U y, V z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y`, `z`:  [floating real arguments](@ref eve::floating_ordered_value).
  //!                       All those arguments must be non-negative and at most one zero or the
  //!                       the result is NaN.
  //!
  //!   **Return value**
  //!
  //!   the value of the \f$\mathbf{R}_\mathbf{F}\f$ Carlson elliptic integral is returned:
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/elliptic/regular/ellint_rc.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(ellint_rf_, ellint_rf);
}

#include <eve/module/elliptic/regular/impl/ellint_rf.hpp>
