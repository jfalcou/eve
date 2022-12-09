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
//! @addtogroup combinatorial
//! @{
//!   @var fibonacci
//!   @brief Computes the nth element of the Fibonacci sequence \f$(f_i)_{i\in \mathbb{N}}\f$.
//!
//!   The sequence is defined by the recurrence relations :
//!
//!     * \f$f_0 = x\f$
//!     * \f$f_1 = y\f$
//!     * \f$f_{n+2} = f_{n+1} + f_{n},  n > 0\f$
//!
//!   but is computed using the
//!   [Binet formula](https://mathworld.wolfram.com/BinetsFibonacciNumberFormula.html).
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/combinatorial.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::unsigned_value N, eve::floating_ordered_value T, eve::floating_ordered_value U>
//!      eve::common_value_t<T, U> fibonacci(N n, T x, U y) noexcept
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   `n`: [index](@ref eve::unsigned_value) of the value to be returned
//!
//!   `x`, `y`: [floating point arguments](@ref eve::floating_ordered_value) : \f$f_0\f$ and \f$f_1\f$.
//!
//!    **Return value**
//!
//!    The value of the  nth element of the Fibonacci sequence beginning by `x` and `y` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/combinatorial/regular/fibonacci.cpp}
//! @}
//================================================================================================
EVE_MAKE_CALLABLE(fibonacci_, fibonacci);
}

#include <eve/module/combinatorial/regular/impl/fibonacci.hpp>
