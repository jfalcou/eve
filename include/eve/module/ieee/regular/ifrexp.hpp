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
  //! @addtogroup ieee754
  //! @{
  //! @var ifrexp
  //!
  //! @brief Callable object computing the ifrexp pair of values.
  //!
  //! **Required header:** `#include <eve/function/ifrexp.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the ifrexp pair of values   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(floating_value auto x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [floating_real_value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!    Computes the [elementwise](@ref glossary_elementwise) ieee ifrexp of the floating value,
  //!    returning a pair `{m,e}`  of values `m` being of the same type as `x` and `e` of the asscociated integral type,
  //!    which are related by
  //!    \f$x =  m\times 2^e\f$, with  \f$|m| \in [0.5, 1.5[\f$.
  //!
  //!    However, the cases \f$x = \pm\infty\f$ or is a Nan or a denormal are undefined.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::ifrexp
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `ifrexp[cond](x, ...)` is equivalent to `if_else(cond,ifrexp(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!     **Required header:** `#include <eve/function/pedantic/ifrexp.hpp>`
  //!
  //!     The call `pedantic(ifrexp)(x)` takes also properly care of the cases where \f$x = \pm0, \pm\infty\f$ or is a Nan,
  //!      where \f$m=x\f$ and \f$e=0\f$ and of the denormal cases.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/ifrexp.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct ifrexp_; }
  template<> struct supports_conditional<tag::ifrexp_> : std::false_type {};

  EVE_MAKE_CALLABLE(ifrexp_, ifrexp);
}

#include <eve/module/ieee/regular/impl/ifrexp.hpp>
