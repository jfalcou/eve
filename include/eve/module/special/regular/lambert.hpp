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
//!   @var lambert
//!   @brief Computes the
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
//!      kumi::tuple<T, T> lambert(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_real_value).
//!
//!    **Return value**
//!
//!    The result is the kumi pair of the two branches values. The branches are not defined for
//!    input less than \f$e^{-1}\f$ in that case they return nan.
//!
//!    As for input positive only one branch exist the two values returned are equal.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/lambert.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(lambert_, lambert);
}

#include <eve/module/special/regular/impl/lambert.hpp>
