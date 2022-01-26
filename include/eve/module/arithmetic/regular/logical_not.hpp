//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup logical
  //! @{
  //! @var logical_not
  //!
  //! @brief Callable object computing the logical NOT operation.
  //!
  //! **Required header:** `#include <eve/function/logical_not.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the logical NOT operation   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()( value auto x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Computes  the logical NOT of the parameter.
  //!
  //!the call `logical_not(x)` is semantically equivalent to `is_eqz(x)`. Infix notation can be used with `!x`
  //!
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/logical_not.cpp}
  //!
  //!  @}
  //================================================================================================

  namespace tag { struct logical_not_; }
  template<> struct supports_conditional<tag::logical_not_> : std::false_type {};

  EVE_MAKE_CALLABLE(logical_not_, logical_not);
}

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE auto logical_not_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return as_logical_t<T>(!a);
  }

  EVE_FORCEINLINE auto logical_not_(EVE_SUPPORTS(cpu_), bool a) noexcept
  {
    return !a;
  }
}
