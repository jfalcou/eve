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
//!   @var logical_andnot
//!   @brief Computes the logical ANDNOT of its arguments.
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
//!      auto logical_andnot(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!     Returns the logical ANDNOT of the two parameters following the
//!     [logical operations semantic](@ref glossary_logical).
//!
//!     The call `logical_andnot(x, y)` is semantically equivalent to `x && !y`
//!     if `x` or  `y` is an  [simd value](@ref eve::simd_value) and  does not shortcut.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/logical_andnot.cpp}
//! @}
//================================================================================================
namespace tag
{
  struct logical_andnot_;
}
template<> struct supports_conditional<tag::logical_andnot_> : std::false_type
{};

EVE_MAKE_CALLABLE(logical_andnot_, logical_andnot);
}

#include <eve/module/core/regular/impl/logical_andnot.hpp>
