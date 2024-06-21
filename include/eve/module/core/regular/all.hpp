//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_reduction
//! @{
//!   @var all
//!   @brief Computes a bool value which is true if and only if all elements of `x` are not zero.
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
//!      bool all(value auto x) noexcept;                //1
//!      bool all(top_bits auto M t) noexcept;           //1
//!      bool all[auto choice m](value auto x) noexcept; //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref value).
//!     * `t` :  [argument](@ref top_bits).
//!     * `m` :  choice.
//!
//!    **Return value**
//!
//!      A bool value.
//!
//!      1. A bool value which is true if and only if all elements of `x` are not zero.
//!      2. A masked version  which is true if and only if all chosen elements of `x` are not zero.
//!
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/all.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!  @}
//================================================================================================
EVE_MAKE_CALLABLE(all_, all);
}

#include <eve/module/core/regular/impl/all.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/all.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/all.hpp>
#endif

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/all.hpp>
#endif
