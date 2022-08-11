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
//!   pair of  sum and error,
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
//!      kumi::tuple<T, T> two_add(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     Computes [elementwise](@ref glossary_elementwise) a pair of values `[a,e]` such that:
//!
//!     * `a` is `x+y`
//!     * `e` is a value such that `a`\f$\oplus\f$`e` is equal to `x`\f$\oplus\f$`y`
//!
//! where \f$\oplus\f$ adds its two parameters with infinite precision.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/two_add.cpp}
//!
//! @}
//================================================================================================
namespace tag
{
  struct two_add_;
}
template<> struct supports_conditional<tag::two_add_> : std::false_type
{};

EVE_MAKE_CALLABLE(two_add_, two_add);
}

#include <eve/module/core/regular/impl/two_add.hpp>
