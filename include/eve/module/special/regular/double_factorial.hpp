//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{
  template<typename Options>
  struct double_factorial_t : elementwise_callable<double_factorial_t, Options>
  {
    template<eve::unsigned_value T>
    EVE_FORCEINLINE
    as_wide_as_t<double, T >
    operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(double_factorial_t, double_factorial_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var double_factorial
//!   @brief Computes the double factorial of `n`
//!
//!   THe double factorial is defined as \f$\displaystyle (2n)!! =
//!   \prod_{i=1}^n (2i)\f$ and \f$\displaystyle (2n+1)!! = \prod_{i=0}^n (2i+1)\f$
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/special.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::unsigned_value N >
//!      eve::as_double_as<N, double> double_factorial(N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  [unsigned argument](@ref eve::unsigned_value).
//!
//!   **Return value**
//!
//!   The value of the double factorial of `n` is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/double_factorial.cpp}
//! @}
//================================================================================================
inline constexpr auto double_factorial = functor<double_factorial_t>;
}

#include <eve/module/special/regular/impl/double_factorial.hpp>
