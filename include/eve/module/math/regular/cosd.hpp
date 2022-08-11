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
  //! @addtogroup math_trig
  //! @{
  //! @var cosd
  //!
  //! @brief Callable object computing cosd.
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
  //!      T cosd(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) cosine of the input expressed in degrees.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$1\f$ is returned.
  //!   * If the element is \f$\pm\infty\f$, Nan is returned.
  //!   * If the element is a `NaN`, `NaN` is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/cosd.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
  //!
  //!     provide a balance between speed and range limitation.
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct cosd_; }
  template<> struct supports_conditional<tag::cosd_> : std::false_type {};

  EVE_MAKE_CALLABLE(cosd_, cosd);
}

#include <eve/module/math/regular/impl/cosd.hpp>
