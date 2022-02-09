//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/pedantic.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup arithmetic
  //! @{
  //! @var modf
  //!
  //! @brief Callable object computing the modf operation.
  //!
  //! **Required header:** `#include <eve/function/modf.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the modf operation   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!A pair of values containing respectively the [elementwise](@ref glossary_elementwise) fractional and integral parts of `x`,
  //!each having the type and sign of `x`.
  //!
  //!In particular:
  //!  * If `x` is infinite `{Nan, x}` is returned.
  //!  * If `x` is a `Nan`  `{Nan, Nan}` is returned.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!     **Required header:** `#include <eve/function/pedantic/modf.hpp>`
  //!
  //!     The call `pedantic(modf)(x)` ensures standard conformity : if `x` is infinite, `{0, x}` is returned.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/arithmetic/modf.cpp}
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct modf_; }
  template<> struct supports_conditional<tag::modf_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(modf_, modf);
}

#include <eve/module/core/regular/impl/modf.hpp>
