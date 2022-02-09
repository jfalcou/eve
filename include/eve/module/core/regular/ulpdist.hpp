//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/is_ordered.hpp>
#include <eve/module/core/regular/nb_values.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup ieee754
  //! @{
  //! @var ulpdist
  //!
  //! @brief Callable object computing the ulpdistt operation.
  //!
  //! **Required header:** #include <eve/module/core.hpp>
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the ulpdistt operation   |
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
  //!computes [elementwise](@ref glossary_elementwise) the 'units in the last place' distance betwween `x` and `y`.
  //!This is semantically equivalent to:`
  //!
  //!* if is_ordered(x,y), nb_values(x,y)/2.0 is returned
  //!* otherwise a `Nan` is returned
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/ulpdist.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct ulpdist_; }
  template<> struct supports_conditional<tag::ulpdist_> : std::false_type {};

  EVE_MAKE_CALLABLE(ulpdist_, ulpdist);
}

#include <eve/module/core/regular/impl/ulpdist.hpp>
