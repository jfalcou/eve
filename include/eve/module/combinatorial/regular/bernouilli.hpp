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
  struct bernouilli_t : elementwise_callable<bernouilli_t, Options, saturated_option>
  {
    template<eve::unsigned_value T>
    EVE_FORCEINLINE
    as_wide_as_t<double, T> operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(bernouilli_t, bernouilli_);
  };

//================================================================================================
//! @addtogroup combinatorial
//! @{
//!   @var bernouilli
//!   @brief Computes the nth Bernouilli number \f$b_n\f$ as a double.
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
//!      template< eve::unsigned_value N >
//!      eve::as_wide_as<double, N> bernouilli(N n) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n` :  unsigned argument.
//!
//!    **Return value**
//!
//!    The value of the nth Bernouilli number is returned.
//!    The result's element type is double to avoid overflow and its cardinal is the same as 'n'.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/combinatorial/regular/bernouilli.cpp}
//! @}
//================================================================================================
inline constexpr auto bernouilli = functor<bernouilli_t>;
}

#include <eve/module/combinatorial/regular/impl/bernouilli.hpp>
