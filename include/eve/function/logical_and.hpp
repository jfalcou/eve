//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/detail/implementation.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/false.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup logical
  //! @{
  //! @var logical_and
  //!
  //! @brief Callable object computing the logical AND operation.
  //!
  //! **Required header:** `#include <eve/function/logical_and.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the logical AND operation   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, value U > auto operator()( T x, U y ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `y`:   [values](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Computes  logical AND of the two parameters following the
  //![logical operations semantic](../../../glossary.html#Logical).
  //!
  //!the call `logical_and(x, y)` is semantically equivalent to `x && y`
  //!if `x` or  `y` is an  [simd value](../../concepts.html#value) and does not shortcut.
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/logical_and.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(logical_and_, logical_and);

  namespace detail
  {
    template<logical_value T, logical_value U>
    EVE_FORCEINLINE auto logical_and_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
    {
      if constexpr( scalar_value<T> && scalar_value<U> )  return as_logical_t<T>(a && b);
      else                                                return a && b;
    }

    template<logical_value T>
    EVE_FORCEINLINE auto logical_and_(EVE_SUPPORTS(cpu_), T a, bool b) noexcept
    {
      return b ? T{a} : false_(as<T>());
    }

    template<logical_value U>
    EVE_FORCEINLINE auto logical_and_(EVE_SUPPORTS(cpu_), bool a, U b) noexcept
    {
      return a ? U{b} : false_(as<U>());
    }

    EVE_FORCEINLINE auto logical_and_(EVE_SUPPORTS(cpu_), bool a, bool b) noexcept
    {
      return a && b;
    }
  }
}
