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
//! @var sinpicospi
//!
//! @brief Callable object computing the simultaneous  computation of sin an cos from
//! an argument in \f$\pi\f$ multiples.
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
//!      kumi::tuple<T, T> sinpicospi(T x) noexcept;              //1
//!
//!      template< eve::floating_value T >
//!      as_complex_t<T> sinpicospi(as_complex_t<T> z) noexcept;  //2
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
//! The computation returns a pair and is semantically equivalent to `{sinpi(x), cospi(x)}`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/sinpicospi.cpp}
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
  struct sinpicospi_;
}
template<> struct supports_conditional<tag::sinpicospi_> : std::false_type
{};

EVE_MAKE_CALLABLE(sinpicospi_, sinpicospi);
}

#include <eve/module/math/regular/impl/sinpicospi.hpp>
