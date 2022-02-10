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
  //! @addtogroup core
  //! @{
  //! @var frexp
  //!
  //! @brief Callable object computing the frexp pair of values.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the frexp pair of values   |
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
  //!    Computes the [elementwise](@ref glossary_elementwise) ieee frexp of the floating value,
  //!    returning a pair {m,e} of values of the same type of `x` which are related by
  //!    \f$x =  m\times 2^e\f$, with  \f$|m| \in [0.5, 1.5[\f$.
  //!
  //!    However, the cases \f$x = \pm\infty\f$ or is a Nan or a denormal are undefined.
  //!
  //! #### Supported decorators
  //!
  //!  * eve::pedantic
  //!
  //!
  //!     The call `pedantic(frexp)(x)` takes also properly care of the cases where \f$x = \pm0, \pm\infty\f$ or is a Nan,
  //!      where \f$m=x\f$ and \f$e=0\f$ and of the denormal cases.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/frexp.cpp}
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct frexp_; }
  template<> struct supports_conditional<tag::frexp_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(frexp_, frexp);
}

#include <eve/module/core/regular/impl/frexp.hpp>
