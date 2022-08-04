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
//! @addtogroup core_internal
//! @{
//!   @var bitofsign
//!   @brief Computes the value in the input type of the bit of sign.
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
//!      T bitofsign(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!    **Return value**
//!
//!    The value of the bit of sign is returned.
//!
//!    **Notes**
//!
//!      * bitofsign does NOT return  a [logical value](@ref eve::value)
//!
//!      * In particular,  take care that for  [floating real values](@ref eve::value) bitofsign
//!      does NOT return
//!        a [logical value](@ref eve::value) that can be tested, but `mzero(as(x))` if `x` is
//!        negative and  `zero(as(x))` if `x` is positive, which both satisfy the eve::is_eqz
//!        predicate.
//!
//!      * If you want to test if the bit of sign is set eve::is_negative is the right function to
//!      call.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/bitofsign.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(bitofsign_, bitofsign);
}

#include <eve/module/core/regular/impl/bitofsign.hpp>
