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
// TODO DOC
//================================================================================================
//! @addtogroup core_simd
//! @{
//!   @var gather
//!   @brief Computes the TODO
//!
//!   @groupheader{Header file}
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
EVE_MAKE_CALLABLE(gather_, gather);
}

#include <eve/module/core/regular/impl/gather.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/gather.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/gather.hpp>
#endif
