//==================================================================================================
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
  //! @addtogroup combinatorial
  //! @{
  //!   @var fibonacci
  //!   @brief Computes the  nth element of a fibonacci sequence \f$(f_i)_{i\in \mathbb{N}}\f$.
  //!
  //!     The sequence is defined by the recurrence relations :
  //!
  //!     * \f$f_0 = x\f$
  //!     * \f$f_1 = y\f$
  //!     * \f$f_{n+2} = f_{n+1} + f_{n},  n > 0\f$
  //!
  //!     but is computed using the Binet formula.
  //!
  //!   **Alternative Header**
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
  //!      template< eve::floating_real_value T,  eve::floating_real_value,  unsigned_value N>
  //!      auto fibonacci(T x, U y, N n) noexcept requires eve::compatible< T, U >;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   `x`, `y`:   [floating arguments](@ref eve::floating_real_value) : \f$f_0\f$ and \f$f_1\f$.
  //!
  //!   `n`:   [index](@ref eve::unsigned_value) of the value to be returned
  //!
  //!    **Return value**
  //!
  //!    the value of the  nth element of a fibonacci sequence beginning by `x` and  `y`
  //!    is returned.
  //!
  //!    The return type is the [common compatible type of `T`, and `U`](@ref eve::compatible).
  //!
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/combinatorial/fibonacci.cpp}
  //! @}
  //================================================================================================
  EVE_MAKE_CALLABLE(fibonacci_, fibonacci);
}

#include <eve/module/combinatorial/regular/impl/fibonacci.hpp>
