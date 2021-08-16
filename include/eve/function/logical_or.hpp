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
#include <eve/constant/true.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup logical
  //! @{
  //! @var logical_or
  //!
  //! @brief Callable object computing the logical OR operation.
  //!
  //! **Required header:** `#include <eve/function/logical_or.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the logical OR operation   |
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
  //!Computes  logical OR of the two parameters following the
  //![logical operations semantic](@ref glossary_logical).
  //!
  //!the call `logical_or(x, y)` is semantically equivalent to `x || y`
  //!if `x` or  `y` is an  [simd value](@ref eve::simd_value) and does not shortcut.
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
  //! @include{lineno} doc/core/logical_or.cpp
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct logical_or_; }
  template<> struct supports_conditional<tag::logical_or_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(logical_or_, logical_or);

  namespace detail
  {
    template<logical_value T, logical_value U>
    EVE_FORCEINLINE auto logical_or_(EVE_SUPPORTS(cpu_), T a, U b) noexcept
    {
      if constexpr( scalar_value<T> && scalar_value<U> )  return as_logical_t<T>(a || b);
      else                                                return a || b;
    }

    template<logical_value T>
    EVE_FORCEINLINE auto logical_or_(EVE_SUPPORTS(cpu_), T a, bool b) noexcept
    {
      return b ? true_(as<T>()) : T{a};
    }

    template<logical_value U>
    EVE_FORCEINLINE auto logical_or_(EVE_SUPPORTS(cpu_), bool a, U b) noexcept
    {
      return a ? true_(as<U>()) : U{b};
    }

    EVE_FORCEINLINE auto logical_or_(EVE_SUPPORTS(cpu_), bool a, bool b) noexcept
    {
      return a || b;
    }
  }
}
