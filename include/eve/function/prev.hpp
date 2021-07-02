//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/assert.hpp>
#include <eve/function/saturated.hpp>
#include <type_traits>

namespace eve
{
  //================================================================================================
  //! @addtogroup bits
  //! @{
  //! @var prev
  //!
  //! **Required header:**
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  #include <eve/function/prev.hpp>
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! <br/>Callable object performing the computation of the prevt operation.
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the prevt operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template< value T, integral_value U > auto operator()( T x, U n = 1 ) const noexcept requires compatible< T, U >;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`, `n`:   [values](../../concepts.html#value).
  //!
  //!
  //!
  //! **Return value**
  //!
  //!computes [`element-wise`](../../../glossary.html#element-wise), the `n`th  representable value less than `x`.
  //!If `n` is zero returns `x`.
  //!
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::prev
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `prev[cond](x, ...)` is equivalent to `if_else(cond,prev(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  ====================================================================================================
  //!  * `pedantic`
  //!     **Required header: 
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!       #include <eve/function/pedantic/prev.hpp>`
  //!      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!  
  //!     The call `pedantic(prev)(x)` distinguish -0.0 and +0.0 for floating point point inputs and so `pedantic(prev)(0.0)` is -0.0.
  //!  
  //!
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/TODO)
  //!
  //! @include{lineno} doc/core/prev.cpp
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct prev_; }

  namespace detail
  {

    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::prev_), T const&, [[ maybe_unused ]] U const & n)
    {
      EVE_ASSERT(eve::all(is_gez(n)), "[eve::prev] : second parameter must be positive");
    }

    template<typename T, typename U>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(saturated_type, eve::tag::prev_), T const&,[[ maybe_unused ]]  U const & n)
    {
      EVE_ASSERT(eve::all(is_gez(n)), "[[eve::saturated([eve::prev)] : second parameter must be positive");
    }
  }

  EVE_MAKE_CALLABLE(prev_, prev);
}

#include <eve/module/real/core/function/regular/generic/prev.hpp>
