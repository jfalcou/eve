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
struct betainc_t : elementwise_callable<betainc_t, Options>
{
  template<eve::floating_ordered_value T0, eve::floating_ordered_value T1, eve::floating_ordered_value T2>
  EVE_FORCEINLINE eve::common_value_t<T0, T1, T2> operator()(T0 a, T1 b, T2 c) const  { return EVE_DISPATCH_CALL(a, b, c); }

  EVE_CALLABLE_OBJECT(betainc_t, betainc_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var betaincinc
//!   @brief Computes the betainc incomplete function. \f$\displaystyle \mbox{I}_s(x,y) =
//!   \frac{1}{\mbox{B}(x,y)}\int_0^s t^{x-1}(1-t)^{y-1}\mbox{d}t\f$
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
//!      template< eve::floating_ordered_value S
//!              , eve::floating_ordered_value T
//!              , eve::floating_ordered_value U>
//!      eve:common_value_t<S, T, U>  $name$(S s, T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `s` :  [real floating argument](@ref eve::floating_ordered_value). \f$ s \in [0, 1]\f$
//!
//!     * `x`, `y`:  [strictly positive real floating arguments](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   The value of the incomplete betainc function is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/betaincinc.cpp}
//! @}
//================================================================================================
 inline constexpr auto betainc = functor<betainc_t>;
}

#include <eve/module/special/regular/impl/betainc.hpp>
