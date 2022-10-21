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
//! @addtogroup math_trig
//! @{
//! @var arg
//!
//! @brief Callable object computing the phase angle (in radians).
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
//!      T arg(T x) noexcept;                  //1
//!
//!      template< eve::floating_value T >
//!      T arg(eve::as_complex<T> z) noexcept; //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!    `x`:   [real](@ref eve::value) or [complex](@ref eve::complex) argument.
//!
//! **Return value**
//!
//!   Returns the [elementwise](@ref glossary_elementwise)
//!   the phase angle (in radians) of the input.
//!
//!  @groupheader{Example}
//!
//!    **Real version**
//!
//!  @godbolt{doc/math/arg.cpp}
//!
//!    **Complex version**
//!
//!  @godbolt{doc/complex/arg.cpp}
//!
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(arg_, arg);
}

#include <eve/module/math/regular/impl/arg.hpp>
