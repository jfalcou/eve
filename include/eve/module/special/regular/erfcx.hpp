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
//! @addtogroup special
//! @{
//!   @var erfcx
//!   @brief Computes the normalized complementary error function
//!   \f$ \displaystyle \mbox{erfcx}(x) = e^{x^2} \mbox{erfc}(x)\f$.
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_real_value T >
//!      T erfcx(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_real_value).
//!
//!   **Return value**
//!
//!   The value of the normalized complementary error function is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/erfcx.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(erfcx_, erfcx);
}

#include <eve/module/special/regular/impl/erfcx.hpp>
