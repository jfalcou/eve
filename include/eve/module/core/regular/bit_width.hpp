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
//! @addtogroup core_bitops
//! @{
//!   @var bit_width
//!   @brief Computes elementwise the number of bits needed to store the parameter.
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
//!      template< eve::unsigned_value T >
//!      T bit_width(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [unsigned argument](@ref eve::unsigned_value).
//!
//!    **Return value**
//!
//!    The value of  number of bits needed to store the value `x`,  i.e.
//!    \f$1+\lfloor\log2(x)\rfloor\f$
//!    is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bit_width.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(bit_width_, bit_width);
}

#include <eve/module/core/regular/impl/bit_width.hpp>
