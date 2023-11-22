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
//! @addtogroup contfrac
//! @{
//!   @var lentz_a
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
//!     template< typename Gen, eve::scalar_ordered_value T> auto lentz_a(Gen g, const T& tol, size_t & max_terms) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `g`   : generator function.
//!     * `tol` : tolerance value. If negative the effective tolerance will be abs(tol)*eve::eps(as(< u_t>)
//!               where u_t is the underlying floating type  associated to the return type of the invocable g.
//!     * `max_terms` : no more than max_terms calls to the generator will be made,
//!
//!   The generator type should be an invocable which supports the following operations:
//!   *  The call to g()  returns a floating value or a pair (kumi::tuple) of such.
//!      Each time this operator is called then the next pair of a and b values has to be returned, 
//!      or, if result_type is not a pair type, then the next b value
//!      has to be returned and all the a values are assumed to be equal to one.
//!
//!   *  In all the continued fraction evaluation functions the effective tol parameter
//!      is the relative precision desired in the result,
//!      The evaluation of the fraction will continue until the last term evaluated leaves
//!      the relative error in the result less than tolerance or the max_terms iteration is reached.
//!
//!   **Return value**
//!
//!     The value of the continued fraction is returned.
//!     \f$\displaystyle \frac{a_0}{b_0+\frac{a_1}{b_1+\frac{a_2}{b_2+\cdots\vphantom{\frac{1}{1}} }}}\f$
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/polynomial/regular/lentz_a.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(lentz_a_, lentz_a);
}

#include <eve/module/contfrac/impl/lentz.hpp>
