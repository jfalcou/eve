//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/all.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var clamp
//!   @brief Computes the largest integer not greater than the input.
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
//!      template< eve::value T, eve::value U,  eve::value V>
//!      auto clamp(T x, U lo, V hi) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` : value to clamp.
//!
//!     * `lo`, `hi`: [the boundary values](@ref eve::value) to clamp `x` to.
//!
//!    **Return value**
//!
//!       Each [element](@ref glossary_elementwise)  of the result contains:
//!          *  `lo`, if `x` is less than `lo`.
//!          *  `hi`, if `hi` is less than `x`.
//!          *  otherwise `x`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/clamp.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::clamp[mask](x, ...)` provides a masked version of `eve::clamp` which is
//!     equivalent to `if_else (mask, clamp(x, ...), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/clamp.cpp}
//!
//! @}
//================================================================================================
namespace tag
{
  struct clamp_;
}

namespace detail
{
  template<typename X, typename L, typename H>
  EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::clamp_),
                             X const&,
                             [[maybe_unused]] L const& lo,
                             [[maybe_unused]] H const& hi)
  {
    EVE_ASSERT(eve::all(lo <= hi), "[eve::clamp] Unordered clamp boundaries");
  }
}
EVE_MAKE_CALLABLE(clamp_, clamp);

}

#include <eve/module/core/regular/impl/clamp.hpp>
