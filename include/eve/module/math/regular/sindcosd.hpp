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
//! @var sindcosd
//!
//! @brief Callable object computing the simultaneous  computation of sine an cosine
//! from an argument in degrees.
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
//!      kumi::tuple<T, T> sindcosd(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!`x`:   [floating real value](@ref eve::floating_real_value).
//!
//! **Return value**
//!
//! The computation returns a pair and is semantically equivalent to `{sind(x), cosd(x)}`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/sindcosd.cpp}
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
  struct sindcosd_;
}
template<> struct supports_conditional<tag::sindcosd_> : std::false_type
{};

EVE_MAKE_CALLABLE(sindcosd_, sindcosd);
}

#include <eve/module/math/regular/impl/sindcosd.hpp>
