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
  //! @addtogroup core
  //! @{
  //! @var three_fma
  //!
  //! @brief Callable object computing the three_fma operation.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the three_fma operation                                    |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U, value V > auto operator()( T x, U y, V z ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`, `z`:   [values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!computes [elementwise](@ref glossary_elementwise) a triple of values `[a, b, c]` such that:
  //!
  //!* `a` is `x*y+z`
  //!* `b`, c`is are values such that (`a`\f$\oplus\f$`b`) \f$\oplus\f$`c`is exactly to `x`\f$\otimes\f$`y\f$\oplus\f$`y`
  //!
  //!where \f$\oplus\f$ (resp. \f$\otimes\f$) adds (resp. multiplies) its two parameters with infinite precision.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/three_fma.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct three_fma_; }
  template<> struct supports_conditional<tag::three_fma_> : std::false_type {};

  EVE_MAKE_CALLABLE(three_fma_, three_fma);
}

#include <eve/module/core/regular/impl/three_fma.hpp>
