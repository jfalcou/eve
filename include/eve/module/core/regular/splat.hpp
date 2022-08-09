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
// Function decorator - splat mode
struct splat_
{
  template<typename D> static constexpr auto combine(D const&) noexcept = delete;
};

using splat_type = decorated<splat_()>;

//================================================================================================
//! @addtogroup core_simd
//! @{
//!   @var splat
//!   @brief Computes the TODO
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
//!      TODO
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!      * `x`:  An instance of an [scalar value](@ref eve::scalar__value)
//!
//!    **Return value**
//!
//!      *A @callable performing the same kind of operation but returning its result as a
//!       [SIMD value](@ref eve::simd_value).
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/splat.cpp}
//! @}
//================================================================================================

[[maybe_unused]] inline constexpr splat_type const splat = {};
}
