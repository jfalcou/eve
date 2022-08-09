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
//! @addtogroup core_simd
//! @{
//!   @var scan
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
//!  @godbolt{doc/core/regular/scan.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(scan_, scan);
}

#include <eve/arch.hpp>
#include <eve/module/core/regular/impl/scan.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/scan.hpp>
#endif
