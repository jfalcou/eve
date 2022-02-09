//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/if_else.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup reduction
  //! @{
  //! @var reduce
  //!
  //! @brief Callable object computing a generalized fold operation.
  //!
  //! **Required header:** `#include <eve/module/core.hpp>`
  //!
  //! #### Member Functions
  //!
  //! | Member       | Effect                                                     |
  //! |:-------------|:-----------------------------------------------------------|
  //! | `operator()` | the computation of a generalized fold operation   |
  //! | `operator[]` | Construct a conditional version of current function object |
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  template<simd_value T> auto operator()( T v ) const noexcept;
  //!  template<simd_value T, Callable F> auto operator()( T v, F binary_op ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //! **Parameters**
  //!
  //! `v`:   [SIMD value](@ref eve::simd_value) to reduce.
  //!
  //! `binary_op`:   Binary callable object that perform a binary, associative and commutative operation.
  //!                If unspecified, the sum of all element of `v`is performed.
  //!
  //! **Return value**
  //!
  //! Generalized fold of `v.get(0)`, `v.get(1)`, ... `v.get(v.size()-1)` over `binary_op`,
  //!
  //! ---
  //!
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
  //!  auto operator[]( conditional_expression auto cond ) const noexcept;
  //!  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //!
  //!  Higher-order function generating a masked version of eve::reduce
  //!
  //!  **Parameters**
  //!
  //!  `cond` : conditional expression
  //!
  //!  **Return value**
  //!
  //!  A Callable object so that the expression `reduce[cond](x, ...)` is equivalent to `if_else(cond,reduce(x, ...),x)`
  //!
  //! ---
  //!
  //! #### Supported decorators
  //!
  //!   * eve::splat
  //!
  //!
  //!     The expression `eve::splat(eve::reduce)(v,binary_op)` computes the reduction of `v`
  //!     using `binary_op` but returns a [SIMD value](@ref eve::simd_value) containing the result
  //!     in all lanes.
  //!
  //! #### Example
  //!
  //! @godbolt{doc/core/reduce.cpp}
  //!
  //!  @}
  //================================================================================================
  EVE_MAKE_CALLABLE(reduce_, reduce);
}

#include <eve/arch.hpp>
#include <eve/module/core/regular/impl/reduce.hpp>
