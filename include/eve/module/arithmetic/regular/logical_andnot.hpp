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
  //! @addtogroup logical
  //! @{
  //! @var logical_andnot
  //!
  //! @brief Callable object computing the logical ANDNOT operation.
  //!
  //! **Required header:** `#include <eve/function/logical_andnot.hpp>`
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
  //! @godbolt{doc/arithmetic/logical_andnot.cpp}
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct logical_andnot_; }
  template<> struct supports_conditional<tag::logical_andnot_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(logical_andnot_, logical_andnot);
}

#include <eve/module/arithmetic/regular/impl/logical_andnot.hpp>
