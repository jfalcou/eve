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
  //! @addtogroup core_horizontal
  //! @{
  //!   @var any
  //!   @brief Computes a bool value which is true if and only if any elements of `x` is not zero.
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
  //!      bool any(eve::as_logical<T> x) noexcept;  //1
  //!
  //!      template< eve::top_bits M >
  //!      bool any(M m) noexcept;                   //2
  //!   }
  //!   @endcode
  //!
  //!   * 1. A bool value which is true if and only if any elements of `x` is not zero.
  //!   * 2  A bool value which is true if and only if any top bits elements of `x` is not zero.
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument(@ref eve::logical_value).
  //!
  //!    **Return value**
  //!
  //!    A bool value which is true if and only if any elements of `x` is not zero
  //!    is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/any.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::any[mask](x)` provides a masked
  //!     version of `any` which is
  //!     equivalent to : any not masked elements is not zero.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/any.cpp}
  //!
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(any_, any);
}

#include <eve/module/core/regular/impl/any.hpp>

#if defined(EVE_INCLUDE_POWERPC_HEADER)
#  include <eve/module/core/regular/impl/simd/ppc/any.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/any.hpp>
#endif
