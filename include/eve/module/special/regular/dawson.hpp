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
  //! @addtogroup special
  //! @{
  //!   @var dawson
  //!   @brief Computes the Dawson function \f$\displaystyle D_+(x)=e^{-x^2}\int_0^{x}
  //!   e^{t^2} \mbox{d}t\f$
  //!
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
  //!      T dawson(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [real floating argument](@ref eve::floating_real_value).
  //!
  //!    **Return value**
  //!
  //!    the value of the Dawson is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/special/regular/dawson.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(dawson_, dawson);
}

#include <eve/module/special/regular/impl/dawson.hpp>
