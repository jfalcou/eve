//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/callable.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup operators
  //! @{
  //! @var add
  //!
  //! @brief Callable object performing the sum of multiple values.
  //!
  //! **Required header:** `#include <eve/function/add.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | Computes the sum of its parameter                          |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(eve::value auto const&... xs) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //! `xs`:  Instances of eve::value
  //!
  //! **Return value**
  //!
  //! A value of the [common compatible type](@ref common_compatible) of all `xs` containing the
  //! [elementwise](@ref glossary_elementwise) sum of all `xs`.
  //!
  //!@warning
  //!   Although the infix notation with `+` is supported for two parameters, the `+` operator on
  //!   standard scalar types is the original one and so can lead to automatic promotion.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::add
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `add[cond](x0,xs...)` is equivalent
  //!  to `if_else(cond,add(x0,xs...),x0)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::saturated
  //!
  //!     **Required header:** `#include <eve/function/saturated/abs.hpp>`
  //!
  //!     The expression `eve::saturated(eve::add)(xs...)` computes the saturated sum of all `xs`.
  //!
  //!   * eve::diff, eve::diff_1st, eve::diff_2nd, eve::diff_3rd, eve::diff_nth
  //!
  //!     **Required header:** `#include <eve/function/diff/add.hpp>`
  //!
  //!     The expression `eve::diff_nth<N>(eve::add)(xs...)` computes the derivative of the sum
  //!     of `xs...` over the Nth parameters.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/add.cpp}
  //!
  //!  @}
  //================================================================================================
  namespace tag { struct add_ {}; }

  namespace detail
  {
    struct callable_add_  : callable<tag::add_, callable_add_>
    {
      // Proceed to the actual computation
      EVE_BIND_TO_CALLABLE(add_)

      // Provide the concept-based interface
      template<value T0, value... Tn>
      requires(compatible_values<T0, Tn> && ...)
      EVE_FORCEINLINE constexpr auto operator()(T0 a0, Tn... an) const noexcept
      {
        return callable<tag::add_, callable_add_>::dispatch(a0, an...);
      }
    };
  }

  EVE_BUILD_CALLABLE(add_, add);
}

#include <eve/module/real/core/function/regular/generic/add.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/real/core/function/regular/simd/x86/add.hpp>
#endif
