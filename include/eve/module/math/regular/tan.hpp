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
//! @var tan
//!
//! @brief Callable object computing tan.
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
//!      T tan(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//! Returns the [elementwise](@ref glossary_elementwise) tangent of the input.
//!
//! In particular:
//!
//!   * If the element is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!   * If the element is \f$\pm\infty\f$, Nan is returned.
//!   * If the element is a `Nan`, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/tan.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
//!
//!     provide a balance between speed and range limitation.
//!
//!  @}
//================================================================================================

namespace tag
{
  struct tan_;
}
template<> struct supports_conditional<tag::tan_> : std::false_type
{};

EVE_MAKE_CALLABLE(tan_, tan);
}

#include <eve/module/math/regular/impl/tan.hpp>
