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
//! @addtogroup core_logical
//! @{
//!   @var logical_xor
//!   @brief Computes the logical XOR of its arguments.
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
//!      template< eve::value T, eve::value U >
//!      auto logical_xor(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!      Returns the logical XOR of the two parameters following the
//!      [logical operations semantic](@ref glossary_logical).
//!
//!      The call `logical_xor(x, y)` is semantically equivalent to `(x && !y) || (!x && y)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/logical_or.cpp}
//! @}
//================================================================================================

namespace tag
{
  struct logical_xor_;
}
template<> struct supports_conditional<tag::logical_xor_> : std::false_type
{};

EVE_MAKE_CALLABLE(logical_xor_, logical_xor);
}

#include <eve/module/core/regular/impl/logical_xor.hpp>
