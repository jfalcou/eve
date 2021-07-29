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
  //! @addtogroup comparisons
  //! @{
  //! @var is_eqz
  //!
  //! @brief Callable object computing the equality to zero predicate.
  //!
  //! **Required header:** `#include <eve/function/is_eqz.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the equality to zero predicate   |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T > auto operator()( T x ) const noexcept
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [values](../../concepts.html#value).
  //!
  //! **Return value**
  //!
  //!Returns the logical value containing the [element-wise](../../../glossary.html#value) equality test result
  //!between `x` and 0.
  //!
  //!The result type is `logical< T >`.
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
  //! @include{lineno} doc/core/is_eqz.cpp
  //!
  //!  @}
  //================================================================================================

  EVE_MAKE_CALLABLE(is_eqz_, is_eqz);

  namespace detail
  {
    // -----------------------------------------------------------------------------------------------
    // logical masked case
    template<conditional_expr C, real_value U, real_value V>
    EVE_FORCEINLINE auto is_eqz_(EVE_SUPPORTS(cpu_), C const &cond, U const &u) noexcept
    {
      return lmask_op(cond, is_eqz, u);
    }
  }
}

#include <eve/module/real/core/function/regular/generic/is_eqz.hpp>
