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
  //! @var secpi
  //!
  //! @brief Callable object computing secpi.
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
  //!      T secpi(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) secine of the input expressed in \f$\pi\f$ multiples.
  //!
  //!The call `secpi(x)` is semantically equivalent to \f$\sec(\pi x)\f$.
  //!In particular:
  //!
  //!   * If the element is \f$\pm0\f$, \f$1\f$ is returned.
  //!   * If the element is \f$\pm\infty\f$, Nan is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/secpi.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!  * eve::quarter_circle, eve::half_circle, eve::full_circle,
  //!
  //!     provide a balance between speed and range limitation.
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct secpi_; }
  template<> struct supports_conditional<tag::secpi_> : std::false_type {};

  EVE_MAKE_CALLABLE(secpi_, secpi);
}

#include <eve/module/math/regular/impl/secpi.hpp>
