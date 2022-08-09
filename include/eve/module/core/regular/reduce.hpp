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
//! @addtogroup core_simd
//! @{
//!   @var reduce
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
//!  @godbolt{doc/core/regular/reduce.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(reduce_, reduce);
}

#include <eve/module/core/regular/impl/reduce.hpp>
