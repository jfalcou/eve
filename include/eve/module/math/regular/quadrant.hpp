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
//! @var quadrant
//!
//! @brief Callable object computing the quadrant value.
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
//!      T quadrant(T n) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`n`:   [ordered integral value](@ref eve::ordered_value). Must be of  integral type or a [flint](@ref
//!eve::is_flint) value
//!
//! **Return value**
//!
//!    return a value of the same type as `n` containing the quadrant number where `n` (supposed an
//!    integer) lies.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/quadrant.cpp}
//!  @}
//================================================================================================

namespace tag
{
  struct quadrant_;
}
template<> struct supports_conditional<tag::quadrant_> : std::false_type
{};

EVE_MAKE_CALLABLE(quadrant_, quadrant);
}

#include <eve/module/math/regular/impl/quadrant.hpp>
