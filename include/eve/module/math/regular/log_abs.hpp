//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup math_log
//! @{
//! @var log_abs
//!
//! @brief Callable object computing the natural logarithm of the absolute value of the input.
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
//!      template< eve::floating_value T >           //1
//!      T log_abs(T x) noexcept;
//!
//!      template< eve::floating_value T >
//!      T log_abs(eve::complex<T> z) noexcept;      //2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!   *  `z`:   [complex ](@ref eve::complex) value.
//!
//! **Return value**
//!
//!   Returns [elementwise](@ref glossary_elementwise) the natural logarithm  of
//!   the absolute value of the input.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/log_abs.cpp}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(log_abs_, log_abs);
}

#include <eve/module/math/regular/impl/log_abs.hpp>
