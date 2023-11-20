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
//!   @var lentz_b
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
//!   The generator type should be a function object which supports the following operations:
//!   *  Gen::result_type : The type that is the result of invoking operator().
//!     This can be either an arithmetic or complex type,
//!      or a std::tuple of two floating values
//!   *  The call to g()  returns an object of type Gen::result_type.
//!      Each time this operator is called then the next pair of a and b values is returned.
//!      Or, if result_type is not a pair type, then the next b value
//!      is returned and all the a values are assumed to be 1.
//!
//!   * In all the continued fraction evaluation functions the tolerance parameter
//!     is the precision desired in the result,
//!     evaluation of the fraction will continue until the last term evaluated leaves
//!     the relative error in the result less than tolerance.
//!
//!   **Return value**
//!
//!     The value of the continued fraction is returned.
//!     \f$\displaystyle b_0+\frac{a_1}{b_1+\frac{a_2}{b_2+\frac{a_3}{b_3+\cdots\vphantom{\frac{1}{1}} }}}\f$
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/polynomial/regular/lentz_b.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(lentz_b_, lentz_b);
}

#include <eve/module/contfrac/impl/lentz.hpp>
