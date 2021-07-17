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
  //! @var is_flint
  //!
  //! @brief Callable object computing the is_flint logical value.
  //!
  //! **Required header:** `#include <eve/function/is_flint.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the is_flint logical value   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< real_value T> auto operator()( T x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [value](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!The call:
  //!
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!logical<T> r = is_flint(x);
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!is semantically  equivalent to:
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ c++
  //!logical<T> r;
  //!if   constexpr(floating_real_value<T>) r = is_eqz(frac(x));
  //!else constexpr(integral_real_value<T>) r = True<T>());
  //!~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  * `pedantic`
  //!     Pedantically speaking flint stands for floating integer. The call `pedantic(is_flint)(x)` considers
  //!      that integral typed values are not floating and so `pedantic(is_flint)(x)` returns false for all elements of this types. Moreover a
  //!      floating point value is pedantically deemed as flint only is the next representable value is not flint, so
  //!      great floating values are not pedantically flint.
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/is_flint.cpp
  //!
  //!  @}
  //================================================================================================
     
  namespace tag { struct is_flint_; }
  template<> struct supports_conditional<tag::is_flint_> : std::false_type {};
  
  EVE_MAKE_CALLABLE(is_flint_, is_flint);
}

#include <eve/module/real/core/function/regular/generic/is_flint.hpp>
