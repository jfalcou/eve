//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_horizontal
//! @{
//!   @var none
//!   @brief Computes a bool value which is true if and only if all elements of `x` are 0.
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
//!      bool none(T x) noexcept;   //1
//!
//!      template< eve::top_bits M >
//!      bool none(M m) noexcept;   //2
//!   }
//!   @endcode
//!
//!   * 1. A bool value which is true if and only if all elements of `x` are  zero.
//!   * 2  A bool value which is true if and only if all top bits elements of `x` are zero.
//!
//!   **Parameters**
//!
//!     * `x` :  argument(@ref eve::logical_value).
//!
//!     * `m` :  argument(@ref eve::top_bits).
//!
//!    **Return value**
//!
//!    A bool value.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/none.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::none[mask](x)` provides a masked
//!     version of `none` which is
//!     equivalent to : all not masked elements are  zero.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/none.cpp}
//!
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(none_, none);
}

#include <eve/module/core/regular/impl/none.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/none.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/none.hpp>
#endif
