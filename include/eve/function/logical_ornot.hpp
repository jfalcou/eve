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
  //! @addtogroup logical
  //! @{
  //! @var logical_ornot
  //!
  //! @brief Callable object computing the logical ANDNOT operation.
  //!
  //! **Required header:** `#include <eve/function/logical_ornot.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the logical ANDNOT operation   |
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
  //!Computes  logical ANDNOT of the two parameters following the
  //![logical operations semantic](@ref glossary_logical).
  //!
  //!the call `logical_andnot(x, y)` is semantically equivalent to `x && !y`
  //!if `x` or  `y` is an  [simd value](@ref eve::simd_value).
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/logical_ornot.cpp}
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct logical_ornot_; }
  template<> struct supports_conditional<tag::logical_ornot_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(logical_ornot_, logical_ornot);
}

#include <eve/module/real/core/function/regular/generic/logical_ornot.hpp>
