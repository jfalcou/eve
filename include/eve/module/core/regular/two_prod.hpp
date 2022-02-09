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
  //! @var two_prod
  //!
  //! @brief Callable object computing the two_prod operation.
  //!
  //! **Required header:** #include <eve/module/core.hpp>
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the two_prod operation   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T x, U y ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!computes [elementwise](@ref glossary_elementwise) a pair of values `[a,e]` such that:
  //!
  //!* `a` is `x*y`
  //!* `e` is a value such that `a`\f$\oplus\f$`e` is equal to `x`\f$\otimes\f$`y`
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
  //! @godbolt{doc/core/two_prod.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct two_prod_; }
  template<> struct supports_conditional<tag::two_prod_> : std::false_type {};

  EVE_MAKE_CALLABLE(two_prod_, two_prod);
}

#include <eve/module/core/regular/impl/two_prod.hpp>
