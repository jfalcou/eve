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
  struct betainc_inv_t : elementwise_callable<betainc_inv_t, Options>
  {
    template<eve::floating_ordered_value T0, eve::floating_ordered_value T1, eve::floating_ordered_value T2>
    EVE_FORCEINLINE constexpr
    eve::common_value_t<T0, T1, T2> operator()(T0 a, T1 b, T2 c) const noexcept { return EVE_DISPATCH_CALL(a, b, c); }

    EVE_CALLABLE_OBJECT(betainc_inv_t, betainc_inv_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var betainc_inv
//!   @brief Computes the inverse relative to the first parameter of the beta incomplete function.
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
//!      template < eve::floating_ordered_value S
//!               , eve::floating_ordered_value T
//!               , eve::floating_ordered_value U>
//!      eve:common_value_t<S, T, U>  betainc_inv(S s, T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `s` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!     * `x`, `y`:  [strictly positive real floating arguments](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   The value of inverse of incomplete beta function relative to the first parameter
//!   is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/betainc_inv.cpp}
//! @}
//================================================================================================
  inline constexpr auto betainc_inv = functor<betainc_inv_t>;
}


#include <eve/module/special/regular/impl/betainc_inv.hpp>
