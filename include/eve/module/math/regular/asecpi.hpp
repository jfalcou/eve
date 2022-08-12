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
//! @var asecpi
//!
//! @brief Callable object computing asecpi.
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
//!      T asecpi(T x) noexcept;
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
//! input in \f$\pi\f$ multiples in the range \f$[0, 1]\f$.
//!
//! In particular:
//!
//!   * If the element is \f$1\f$, \f$+0\f$ is returned.
//!   * If the element is \f$0\f$, \f$1\f$ is returned.
//!   * If the element \f$|x| < 1\f$, `NaN` is returned.
//!   * If the element is a `Nan`, `NaN` is returned.
//!
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/asecpi.cpp}
//!
//!  @}
//================================================================================================

namespace tag
{
  struct asecpi_;
}
template<> struct supports_conditional<tag::asecpi_> : std::false_type
{};

EVE_MAKE_CALLABLE(asecpi_, asecpi);
}

#include <eve/module/math/regular/impl/asecpi.hpp>
