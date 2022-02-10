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
  //! @var logical_xor
  //!
  //! @brief Callable object computing the logical XOR operation.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the logical XOR operation   |
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
  //!Computes  logical XOR of the two parameters following the
  //![logical operations semantic](@ref glossary_logical).
  //!
  //!the call `logical_xor(x, y)` is semantically equivalent to `(x && !y) || (!x && y)`.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/logical_xor.cpp}
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct logical_xor_; }
  template<> struct supports_conditional<tag::logical_xor_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(logical_xor_, logical_xor);
}

#include <eve/module/core/regular/impl/logical_xor.hpp>
