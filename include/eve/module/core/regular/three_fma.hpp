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
//! @addtogroup core_accuracy
//! @{
//!   @var two_add
//!   @brief Computes the [elementwise](@ref glossary_elementwise)
//!   triple  of  fma  and errors,
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
//!      template< eve::floating_value T, eve::floating_value U , eve::floating_value V >
//!      auto three_fma(T x, U y, V z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      `x`, `y`, `z`:   [floating values](@ref eve::floating_value).
//!
//!   **Return value**
//!
//!     Computes [elementwise](@ref glossary_elementwise) a pair of values `[a,e]` such that:
//!
//!     * `a` is `x*y+z`
//!     * `b`, c`is are values such that (`a`\f$\oplus\f$`b`) \f$\oplus\f$`c`is exactly to
//!              `x`\f$\otimes\f$`y\f$\oplus\f$`y`
//!
//!     where \f$\oplus\f$ (resp. \f$\otimes\f$) adds (resp. multiplies) its two parameters with
//!     infinite precision.
//!
//!     where \f$\oplus\f$ adds its two parameters with infinite precision.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/three_fma.cpp}
//!
//! @}
//================================================================================================
namespace tag
{
  struct three_fma_;
}
template<> struct supports_conditional<tag::three_fma_> : std::false_type
{};

EVE_MAKE_CALLABLE(three_fma_, three_fma);
}

#include <eve/module/core/regular/impl/three_fma.hpp>
