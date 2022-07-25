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
  //! @addtogroup core_internal
  //! @{
  //!   @var exponent
  //!   @brief Computes the IEEE exponent of the floating value.
  //!
  //!    The exponent \f$e\f$ and mantissa \f$m\f$ of a floating point entry \f$x\f$ are related by
  //!    \f$x =  m\times 2^e\f$, with  \f$|m| \in [1, 2[\f$.
  //!
  //!    The exception is when \f$x = \pm0, \pm\infty\f$ or is a Nan, where \f$m=x\f$ and \f$e=0\f$).
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
  //!      eve::as_integer_t<T> exponent(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  argument.
  //!
  //!    **Return value**
  //!
  //!    The value of the IEEE exponent.
  //!    is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core//regular/exponent.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(exponent_, exponent);
}

#include <eve/module/core/regular/impl/exponent.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/exponent.hpp>
#endif
