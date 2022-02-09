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
  //! @var logical_notor
  //!
  //! @brief Callable object computing the logical NOTOR operation.
  //!
  //! **Required header:** `#include <eve/function/logical_notor.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the logical NOTOR operation   |
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
  //!Computes  logical NOTOR of the two parameters following the
  //![logical operations semantic](@ref glossary_logical).
  //!
  //!the call `logical_notor(x, y)` is semantically equivalent to `!x || y`
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
  //! @godbolt{doc/arithmetic/logical_notor.cpp}
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct logical_notor_; }
  template<> struct supports_conditional<tag::logical_notor_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(logical_notor_, logical_notor);
}

#include <eve/module/core/regular/impl/logical_notor.hpp>
