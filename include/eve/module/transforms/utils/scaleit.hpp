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
//! @addtogroup transforms
//! @{
//!   @var scaleit
//!   @brief take one (resp. two) range and scale it (resp. them) by a factor
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/transforms.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!     template<range R, value T>
//!     auto scaleit(R & f, T fac) noexcept;
//!
//!     template<range R, value T>
//!     auto scaleit(R & fr, R &fi, T fac) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!     * `f`   : range of complex or scalar ordered arguments.
//!     * `fr   : range of scalar ordered arguments
//!     * `fi   : range of scalar ordered  arguments (of same size as fr)
//!     * `fac` : scalar ordered normalization factor. (converted to the underlying type of R
//!               elements before the  scaling is done)
//!
//!   **Return value**
//!
//!     all elements of f or (rf, if) are scaled by fac.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/transforms/utils/scaleit.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(scaleit_, scaleit);

}

#include <eve/module/transforms/utils/impl/scaleit.hpp>
