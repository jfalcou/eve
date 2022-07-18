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
  //!   @var all
  //!   @brief Computes a bool value which is true if and only if all elements of `x` are not zero_
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T >
  //!      bool all(T x) noexcept;
  //!   }
  //!   @endcode
  //! **Return value**
  //!    A bool value which is true if and only if all elements of `x` are not zero_
  //!    is returned.
  //!  **Parameters**
  //!     The call `eve::all[mask](x)` provides a masked
  //!     version of `all` which is
  //!     equivalent to : all not masked elements are not zero.
  //! @godbolt{doc/core/all.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(all_, all);
}

#include <eve/module/core/regular/impl/all.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/all.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/all.hpp>
#endif
