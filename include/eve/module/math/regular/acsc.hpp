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
  //! @var acsc
  //!
  //! @brief Callable object computing acsc.
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
  //!      T acsc(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) arc cosecant of the
  //!input in the range \f$[-\pi/2 , \pi/2]\f$.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm1\f$, \f$\pm\frac\pi2\f$ is returned.
  //!   * If the element \f$|x| < 1\f$, `NaN` is returned.
  //!   * If the element is \f$\pm\infty\f$, \f$\pm0\f$ is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/acsc.cpp}
  //!  @}
  //================================================================================================

  namespace tag { struct acsc_; }
  template<> struct supports_conditional<tag::acsc_> : std::false_type {};

  EVE_MAKE_CALLABLE(acsc_, acsc);
}

#include <eve/module/math/regular/impl/acsc.hpp>
