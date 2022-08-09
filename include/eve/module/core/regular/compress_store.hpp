//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_simd
//! @{
//!   @var compress_store
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
//!  @godbolt{doc/core/regular/compress_store.cpp}
//! @}
//================================================================================================

EVE_MAKE_CALLABLE(compress_store_, compress_store);
}

#include <eve/module/core/regular/impl/compress_store.hpp>
