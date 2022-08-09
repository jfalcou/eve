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
//!   @var lfactorial
//!   @brief Computes the natural logarithm of the factorial of unsigned integer values
//!   \f$\displaystyle \log n! = \sum_{i=1}^n \log i\f$.
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
//!      template< eve::value N >
//!      auto lfactorial(N x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [integer or flint argument](@ref eve::value).
//!
//!   **Return value**
//!
//!   The value of \f$ \log n!\f$ is returned with the following considerations:
//!     * If the entry is an [integral value](eve::integral_value), the result
//!       [element type](eve::element_type) is always double to try to avoid overflow.
//!     * If the entry is a [floating point value](eve::floating_point_value)
//!       which must be a flint,  the result is of the same type as the entry.
//!     * If `n` elements are not integer or flint the result is undefined.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/lfactorial.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(lfactorial_, lfactorial);
}

#include <eve/module/special/regular/impl/lfactorial.hpp>
