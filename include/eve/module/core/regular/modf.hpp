//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
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
//!     * `x` :  [argument](@ref eve::value).
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
//!
//!      **Example**
//!
//!        @godbolt{doc/core/pedantic/modf.cpp}
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
