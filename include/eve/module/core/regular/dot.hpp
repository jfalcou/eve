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
//! @addtogroup core_arithmetic
//! @{
//!   @var dot
//!   @brief Computes elementwise the dot product of the two parameters.
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
//!      template< value T1, value T2>
//!      auto dot(T1 x, T2 y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`  :  [real or complex arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!    dot product: real(x)*real(y)+imag(x)*imag(y). For real numbers it is just the product.
//!
//!  @groupheader{Example}
//!
//!    **Real version**
//!
//!  @godbolt{doc/core/regular/dot.cpp}
//!
//!    **Complex version**
//!
//!  @godbolt{doc/complex/regular/dot.cpp}
//!
//! @}
//================================================================================================
//   namespace tag { struct dot_; }
//   template<> struct supports_conditional<tag::dot_> : std::false_type {};

  EVE_MAKE_CALLABLE(dot_, dot);

}

#include <eve/module/core/regular/impl/dot.hpp>
