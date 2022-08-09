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
//! @addtogroup core_logical
//! @{
//!   @var logical_notor
//!   @brief Computes the logical NOTOR of its arguments.
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
//!      auto logical_notor(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!     Returns the logical NOTOR of the two parameters following the
//!     [logical operations semantic](@ref glossary_logical).
//!
//!     The call `logical_notor(x, y)` is semantically equivalent to `!x || y`
//!     if `x` or  `y` is an  [simd value](@ref eve::simd_value) and  does not shortcut.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/logical_notor.cpp}
//! @}
//================================================================================================

namespace tag
{
  struct logical_notor_;
}
template<> struct supports_conditional<tag::logical_notor_> : std::false_type
{};

EVE_MAKE_CALLABLE(logical_notor_, logical_notor);
}

#include <eve/module/core/regular/impl/logical_notor.hpp>
