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
  //! @addtogroup core_predicates
  //! @{
  //!   @var is_nlez
  //!   @brief Returns a logical true  if and only if the element value is not less or equal to 0.
  //!
  //!   $details$
  //!
  //!   **Defined in Header**
  //!
  //!   @code
  //!   #include <eve/module/core.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace eve
  //!   {
  //!      template< eve::value T >
  //!      eve::as_logical<T> is_nlez(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [argument](@ref eve::value).
  //!
  //!   **Return value**
  //!
  //!    Returns [elementwise](@ref glossary_elementwise) `!(x <= 0)`.
  //!
  //!   **Note**
  //!
  //!    This is not equivalent to `(x >=   0)` for floating values.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/core/regular/is_nlez.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve;::is_nlez[mask](x)` provides a masked version of `eve::is_nlez` which is
  //!     equivalent to `if_else (mask, is_nlez(x), eve::false( eve::as(x)))`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/core/masked/is_nlez.cpp}
  //! @}
  //================================================================================================

  //================================================================================================
  //! @addtogroup core
  //! @{
  //! @var is_nlez
  //!
  //! @brief Callable object computing the "not less or equal to zero" predicate.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the "not less or equal to zero" predicate   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(value x) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:   [values](@ref eve::value).
  //!
  //! **Return value**
  //!
  //!Returns the [elementwise](@ref glossary_elementwise) `!(x <= 0)`.
  //!
  //!The result type is `logical< T >`.
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::is_nlez
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `is_nlez[cond](x)` is equivalent to
  //! `if_else(cond,is_nlez(x),false(as(is_nlez(x))))`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!  no decorators are supported
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/is_nlez.cpp}
  //!
  //!  @}
  //================================================================================================

  EVE_MAKE_CALLABLE(is_nlez_, is_nlez);
}

#include <eve/module/core/regular/impl/is_nlez.hpp>
