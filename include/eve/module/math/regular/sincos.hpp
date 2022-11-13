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
//! @var sincos
//!
//! @brief Callable object computing the simultaneous  computation of sine an cosine.
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
//!      kumi::tuple<T, T> sincos(T x) noexcept;              //1
//!
//!      template< eve::floating_value T >
//!      as_complex_t<T> sincos(as_complex_t<T> z) noexcept;  //2
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
//! The computation returns a pair and is semantically equivalent to `{sin(x), cos(x)}`
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/sincos.cpp}
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
  struct sincos_;
}
template<> struct supports_conditional<tag::sincos_> : std::false_type
{};

EVE_MAKE_CALLABLE(sincos_, sincos);
}

#include <eve/module/math/regular/impl/sincos.hpp>
