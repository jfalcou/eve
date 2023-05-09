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
//! @addtogroup fht
//! @{
//!   @var naive_fft
//!   @brief Implement the raw ht discrete transform
//!
//!   If \f$(a_i)_{0\le i\le n-1}\f$ denotes the input coefficients,  the zt naive scheme
//!   evaluates the zt-transform coefficients  \f$zt(f)\f$ by \f$(c_i)_{0\le i\le n-1}\f$:
//!   \f$\displaystyle c_i = f\sum_{k = 0}^{k = n-1} a_k z^k}\f$.
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/fht.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!     template< eve::Range R, floating_ordered_value T>
//!     void naive_fft(R a) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `a`   :  soa range of complex or real.
//!
//!   **Return value**
//!
//!   void. the inputs are modified to contain the ht values.
//!
//!   @note Never uses this algorithm it is completely inefficient.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/fft/regular/naive_zt.cpp}
//!
//! @}
//================================================================================================
  EVE_MAKE_CALLABLE(naive_zt_, naive_zt);

}

#include <eve/module/transforms/fzt/impl/naive_zt.hpp>
