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
//! @addtogroup polynomial
//! @{
//!   @var horner
//!   @brief Implement the lentz scheme to evaluate continued fractions
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/contfrac.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!     template< typename Gen, eve::floating_value T>
//!     T lentz_b(Gen g, const T& eps, size_t & max_terms) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `g`   : generator function.
//!     * `eps` : tolerance value.
//!     * `max_terms` : no more than max_terms calls to the generator will be made,
//!
//!   **Return value**
//!
//!     The value of the continued fraction is returned.
//!     \f$\displaystyle b0+\cfrac{a1}{b1+\cfrac{a2}{b2+\cfrac{a3}{b3+\cdots\vphantom{\cfrac{1}{1}} }}}\f$
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/polynomial/regular/lentz_b.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(lentz_b_, lentz_b);
}

#include <eve/module/polynomial/regular/impl/lentz.hpp>
