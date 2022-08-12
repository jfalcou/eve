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
//! @addtogroup math_invtrig
//! @{
//! @var asecd
//!
//! @brief Callable object computing asecd.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T >
//!      T asecd(T x) noexcept;
//!   }
//!   @endcode
//!
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_real_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) arc secant of the
//! input in the range \f$[0, 180]\f$.
//!
//! In particular:
//!
//!   * If the element is \f$1\f$, \f$+0\f$ is returned.
//!   * If the element is \f$0\f$, \f$180\f$ is returned.
//!   * If the element \f$|x| < 1\f$, `NaN` is returned.
//!   * If the element is a `Nan`, `NaN` is returned.
//!
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/asecd.cpp}
//!  @}
//================================================================================================

namespace tag
{
  struct asecd_;
}
template<> struct supports_conditional<tag::asecd_> : std::false_type
{};

EVE_MAKE_CALLABLE(asecd_, asecd);
}

#include <eve/module/math/regular/impl/asecd.hpp>
