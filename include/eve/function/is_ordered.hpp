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
  //! @addtogroup predicates
  //! @{
  //! @var is_ordered
  //!
  //! @brief Callable object performing the computation of the is_ordered logical value.
  //!
  //! **Required header:** `#include <eve/function/is_ordered.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the is_ordered logical value   |
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
  //!The call:
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!logical<T> r = is_ordered(x, y);
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!is semantically  equivalent to:
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!logical<T> r;
  //!if   constexpr(floating_real_value<T>) r = is_not_nan(x) && is_not_nan(y);
  //!else constexpr(integral_real_value<T>) r = True<T>();
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
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
  //! @include{lineno} doc/core/is_ordered.cpp
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(is_ordered_, is_ordered);
}

#include <eve/arch.hpp>
#include <eve/module/real/core/function/regular/generic/is_ordered.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/is_ordered.hpp>
#endif
