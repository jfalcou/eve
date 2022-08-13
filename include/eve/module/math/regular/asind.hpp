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
//! @var asind
//!
//! @brief Callable object computing the arc sine in degrees.
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
//!      T asind(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_real_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) arc sine of the
//! input in the range \f$[-90, 90]\f$.
//!
//! In particular:
//!
//!   * If the element is \f$1\f$, \f$+0\f$ is returned.
//!   * If the element \f$|x| > 1\f$, `NaN` is returned.
//!   * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/asind.cpp}
//!  @}
//================================================================================================

namespace tag
{
  struct asind_;
}
template<> struct supports_conditional<tag::asind_> : std::false_type
{};

EVE_MAKE_CALLABLE(asind_, asind);
}

#include <eve/module/math/regular/impl/asind.hpp>
