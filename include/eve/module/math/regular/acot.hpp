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
  //! @addtogroup math_invtrig
  //! @{
  //! @var acot
  //!
  //! @brief Callable object computing acot.
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/math.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::floating_value T >
  //!      T acot(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) arc cotangent of the
  //!input in the range \f$[-\frac\pi2, \frac\pi2]\f$.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$\pm\frac\pi2\f$ is returned.
  //!   * If the element is \f$\pm\infty\f$, \f$\pm0\f$ is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/acot.cpp}
  //!  @}
  //================================================================================================

  namespace tag { struct acot_; }
  template<> struct supports_conditional<tag::acot_> : std::false_type {};

  EVE_MAKE_CALLABLE(acot_, acot);
}

#include <eve/module/math/regular/impl/acot.hpp>
