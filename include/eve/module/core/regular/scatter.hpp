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
//! @addtogroup core_simd
//! @{
//!   @var scatter
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
//!      * `x`:  An instance of an [SIMD value](@ref eve::simd_value)
//!
//!    **Return value**
//!
//!      * TODO
//!
//!  @groupheader{Example}
//!
//!  TODO
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(scatter_, scatter);
}

#include <eve/module/core/regular/impl/scatter.hpp>

// #if defined(EVE_INCLUDE_X86_HEADER)
// #  include <eve/module/core/regular/impl/simd/x86/scatter.hpp>
// #endif

// #if defined(EVE_INCLUDE_SVE_HEADER)
// #  include <eve/module/core/regular/impl/simd/arm/sve/scatter.hpp>
// #endif
