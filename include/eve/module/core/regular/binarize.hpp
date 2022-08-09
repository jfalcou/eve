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
//! @addtogroup core_conversions
//! @{
//!   @var binarize
//!   @brief transform logical values to numerical values
//!
//!   binarize(c, v) is semantically  equivalent to: if_else(c, v, T(0));
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
//!      template< eve::value C  >
//!      C binarize(eve::as_logical<C> c) noexcept;            //1
//!      template< eve::value V,  eve::logical_value C >
//!      T binarize(C, c, T v = T(1)) noexcept;                //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `c` :  [condition](@ref eve::logical_value).
//!
//!     * `x` :  [value](@ref eve::value) to return if the condition is met (C(1) if omitted).
//!
//!    **Return value**
//!
//!     1. The value of `if_else(c, v, T(0))` is returned.
//!     2. The value of `if_else(c, C(1), C(0))` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/binarize.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(binarize_, binarize);
}

#include <eve/module/core/regular/impl/binarize.hpp>
