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
//!   @var count_true
//!   @brief Computes the number of non 0 elements
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
//!      template< eve::value T >
//!      T count_true(T x) noexcept;                 //1
//!   }
//!      template< eve::top_bits M >
//!      as_wide_as<unsigned, M> any(M m) noexcept;  //2
//!   }
//!   @endcode
//!
//!   * 1. The T value  of the number of non 0 elements.
//!   * 2  The unsigned  value  of the number of non 0 elements.
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of the number of non 0 elements
//!    is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/count_true.cpp}
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::$name$[mask](x, ...)` provides a masked
//!     version of `count_true which count the non masked non zero element
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/count_true.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(count_true_, count_true);
}

#include <eve/module/core/regular/impl/count_true.hpp>

#if defined(EVE_INCLUDE_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/count_true.hpp>
#endif
