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
//! @addtogroup special
//! @{
//!   @var erfc
//!   @brief Computes the complementar error function \f$ \displaystyle
//!   \mbox{erf}(x)=1-\frac{2}{\sqrt\pi}\int_0^{x} e^{-t^2}\mbox{d}t\f$
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
//!      T erfc(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_real_value).
//!
//!   **Return value**
//!
//!   The value of the complementary error function is returned. In particular:
//!
//!     * If the argument is \f$\pm0\f$, \f$1\f$ is returned.
//!     * If the argument is \f$\infty\f$, \f$1\f$ is returned.
//!     * If the argument is \f$-\infty\f$,\f$2\f$ is returned.
//!     * If the argument is Nan, nan is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/erf.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(erfc_, erfc);
}

#include <eve/module/special/regular/impl/erfc.hpp>
