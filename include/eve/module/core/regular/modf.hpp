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
//! @addtogroup core_arithmetic
//! @{
//!   @var modf
//!   @brief Computes the [elementwise](@ref glossary_elementwise)
//!   pair of  fractional and integral parts of the value,
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::value T >
//!      kumi::tuple<T, T> modf(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :   [real](@ref eve::value) or [complex](@ref eve::complex) argument.
//!
//!   **Return value**
//!
//!     A pair of values containing respectively the [elementwise](@ref glossary_elementwise)
//!     fractional and integral parts of `x`, each having the type and sign of `x`.
//!
//!     In particular:
//!       * If `x` is infinite `{Nan, x}` is returned.
//!       * If `x` is a `Nan`  `{Nan, Nan}` is returned.
//!
//!     For complex inputs the operation is applied to both real and imaginary parts.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/modf.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * eve::pedantic
//!
//!     The call `pedantic(modf)(x)` ensures standard conformity : if `x` is infinite,
//!     `{0, x}` is returned.
//! @}
//================================================================================================

namespace tag
{
  struct modf_;
}
template<> struct supports_conditional<tag::modf_> : std::false_type
{};

EVE_MAKE_CALLABLE(modf_, modf);
}

#include <eve/module/core/regular/impl/modf.hpp>
