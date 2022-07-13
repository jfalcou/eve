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
//!   @var erf
//!   @brief Computes the error function \f$ \displaystyle
//!   \mbox{erf}(x)=\frac{2}{\sqrt\pi}\int_0^{x} e^{-t^2}\mbox{d}t\f$
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
//!      T erf(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_real_value).
//!
//!    **Return value**
//!
//!    the value of the error function is returned. In particular:
//!
//!      - If the argument is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      - If the argument is \f$\pm\infty\f$, \f$\pm1\f$ is returned.
//!      - If the argument is Nan, nan returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/erf.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(erf_, erf);
}

#include <eve/module/special/regular/impl/erf.hpp>
