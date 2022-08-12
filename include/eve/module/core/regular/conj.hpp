//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

namespace eve
{
//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var conj
//!   @brief Computes the the conjugate value.
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
//!      T conj(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!     for real inputs the call deduce to identity.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/conj.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::conj[mask](x)` provides a masked version of `eve::conj` which is
//!     equivalent to `if_else (mask, conj(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/conj.cpp}
//!
//! @}
//================================================================================================

//================================================================================================
  //! @addtogroup math
  //! @{
  //! @var conj
  //!
  //! @brief Callable object computing the conjugate value.
  //!
  //! **Required header:** `#include <eve/module/math.hpp>`
  //!
  //! #### Members Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of the conjugate value   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator()(floating_value auto x ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //!`x`:  the [floating value](@ref eve::value) to conjugate
  //!
  //! **Return value**
  //!
  //!This function acts as identity on real entries
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::conj
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `conj[cond](x, ...)` is equivalent to `if_else(cond,conj(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Example
  //!
  //! @godbolt{doc/math/conj.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(conj_, conj);
}

#include <eve/module/core/regular/impl/conj.hpp>
