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
  //! @addtogroup invtrigonometric
  //! @{
  //! @var acos
  //!
  //! @brief Callable object computing acos.
  //!
  //! **Required header:** `#include <eve/function/acos.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the  computation of acos   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(floating_value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!Returns the [element-wise](@ref glossary_elementwise) arc cosine of the
  //!input in the range \f$[0 , \pi]\f$.
  //!
  //!In particular:
  //!
  //!   * If the element is \f$1\f$, \f$+0\f$ is returned.
  //!   * If the element \f$|x| > 1\f$, `NaN` is returned.
  //!   * If the element is a `Nan`, `NaN` is returned.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::raw
  //!     The call `raw(acos)(x)`, call a faster implementation which can be slightly less accurate near 1.
  //!
  //!  * eve::diff
  //!
  //!     **Required header:** `#include <eve/function/diff/acos.hpp>`
  //!
  //!     The expression `diff(acos)(x)` computes the derivative of the function at `x`.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/acos.cpp
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct acos_; }
  template<> struct supports_conditional<tag::acos_> : std::false_type {};

  EVE_MAKE_CALLABLE(acos_, acos);
}

#include <eve/module/real/math/function/regular/generic/acos.hpp>
