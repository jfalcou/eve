//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/arch.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup core_arithmetic
  //! @{
  //!   @var nb_values
  //!   @brief Computes the  number of values representable in the type between the
  //!   [arguments](@ref eve::value).
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
  //!      T nb_values(T x, T y) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x`, `y`:  [arguments](@ref eve::value).
  //!
  //!    **Return value**
  //!
  //!      Returns the number of values representable in the type in the interval `[x, y[`
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/nb_values.cpp}
  //================================================================================================
 EVE_MAKE_CALLABLE(nb_values_, nb_values);
}

#include <eve/module/core/regular/impl/nb_values.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/nb_values.hpp>
#endif

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/nb_values.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/nb_values.hpp>
#endif
