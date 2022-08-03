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
  //!   @var countr_zero
  //!   @brief Computes the number of consecutive 0 in a value starting from right
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
  //!      T countr_zero(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [argument](@ref eve::value).
  //!
  //!    **Return value**
  //!
  //!      The value of the number of consecutive 0 ("zero") bits in the value of `x`, starting
  //!      from the least significant bit ("right"), with same type as `x`,
  //!      is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/countr_zero.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(countr_zero_, countr_zero);
}

#include <eve/module/core/regular/impl/countr_zero.hpp>
