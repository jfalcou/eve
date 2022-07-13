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
  //!   @var tgamma
  //!   @brief Computes \f$\displaystyle \Gamma(x)=\int_0^\infty t^{x-1}e^{-t}\mbox{d}t\f$
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
  //!      T tgamma(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [real floating argument](@ref eve::floating_real_value).
  //!
  //!    **Return value**
  //!
  //!    the value of \f$\Gamma\f$ is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/special/regular/tgamma.cpp}
  //! @}
  //================================================================================================

EVE_MAKE_CALLABLE(tgamma_, tgamma);
}

#include <eve/module/special/regular/impl/tgamma.hpp>
