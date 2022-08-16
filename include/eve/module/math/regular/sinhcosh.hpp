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
//! @addtogroup math_hyper
//! @{
//! @var sinhcosh
//!
//! @brief Callable object performing the simultaneous computations of
//! the hyperbolic sine and cosine.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T >
//!      kumi::tuple<T, T> sinhcosh(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) pair of values containing the
//! hyperbolic sine and the hyperbolic cosine of the input.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/sinhcosh.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(sinhcosh_, sinhcosh);
}

#include <eve/module/math/regular/impl/sinhcosh.hpp>
