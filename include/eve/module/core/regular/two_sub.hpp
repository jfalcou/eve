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
//! @subtogroup core_accuracy
//! @{
//!   @var two_sub
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
//!      kumi::tuple<T, T> two_sub(T x, T y) noexcept;
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
//!     * `a` is `x-y`
//!     * `e` is a value such that `a`\f$\oplus\f$`e` is equal to `x`\f$\ominus\f$`y`
//!
//! where \f$\ominus\f$ subs its two parameters with infinite precision.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/two_sub.cpp}
//!
//! @}
//================================================================================================
namespace tag
{
  struct two_sub_;
}
template<> struct supports_conditional<tag::two_sub_> : std::false_type
{};

EVE_MAKE_CALLABLE(two_sub_, two_sub);
}

#include <eve/module/core/regular/impl/two_sub.hpp>
