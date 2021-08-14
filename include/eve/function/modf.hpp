//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

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
  //!`x`:   [value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!A pair of values containing respectively the [element-wise](../../../glossary.html#value) fractional and integral parts of `x`,
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
  //!  * `pedantic`
  //!
  //!     **Required header:** `#include <eve/function/pedantic/modf.hpp>`
  //!
  //!     The call `pedantic(modf)(x)` ensures standard conformity : if `x` is infinite, `{0, x}` is returned.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/modf.cpp
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct modf_; }
  template<> struct supports_conditional<tag::modf_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(modf_, modf);
}

#include <eve/module/real/core/function/regular/generic/modf.hpp>
