//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_accuracy
//! @{
//!   @var two_prod
//!   @brief Computes the [elementwise](@ref glossary_elementwise)
//!   pair of  product and error,
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
//!      template< eve::floating_value T, eve::floating_value U  >
//!      auto two_prod(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     Computes [elementwise](@ref glossary_elementwise) a pair of values `[a,e]` such that:
//!
//!     * `a` is `x*y`
//!     * `e` is a value such that `a`\f$\oplus\f$`e` is equal to `x`\f$\otimes\f$`y`
//!
//!    where \f$\oplus\f$ (resp. \f$\otimes\f$) adds (resp. multiplies) its two parameters with
//!    infinite precision.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/two_prod.cpp}
//!
//! @}
//================================================================================================
namespace tag
{
  struct two_prod_;
}
template<> struct supports_conditional<tag::two_prod_> : std::false_type
{};

EVE_MAKE_CALLABLE(two_prod_, two_prod);
}

#include <eve/module/core/regular/impl/two_prod.hpp>
