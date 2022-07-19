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
  //!   @var countl_zero
  //!   @brief Computes the number of consecutive 0 in a value starting from left
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
  //!      template< eve::real_value T >
  //!      T countl_zero(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!    **Return value**
  //!
  //!      The value of the number of consecutive 0 ("zero") bits in the value of `x`, starting
  //!      from the most significant bit ("left"), with same type as `x`,
  //!      is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/countl_zero.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(countl_zero_, countl_zero);
}

#include <eve/module/core/regular/impl/countl_zero.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/countl_zero.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/countl_zero.hpp>
#endif
