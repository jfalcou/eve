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
struct gamma_p_t : elementwise_callable<gamma_p_t, Options>
{
  template<eve::floating_ordered_value T0, eve::floating_ordered_value T1>
  EVE_FORCEINLINE
  eve::common_value_t<T0, T1> operator()(T0 a, T1 b) const  noexcept { return EVE_DISPATCH_CALL(a, b); }

  EVE_CALLABLE_OBJECT(gamma_p_t, gamma_p_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var gamma_p
//!   @brief Computes the normalized lower incomplete \f$\Gamma\f$ function.
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
//!      template< eve::floating_ordered_value T0,  floating_ordered_value T1>
//!      T  gamma_p(T1 x, T2 y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [real floating arguments](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   The value of the normalized lower incomplete \f$\Gamma\f$ function is returned as
//!   \f$\displaystyle \frac{1}{\Gamma(x)}\int_0^{y} t^{x-1}e^{-t}\mbox{d}t\f$
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/gamma_p.cpp}
//! @}
//================================================================================================
  inline constexpr auto gamma_p = functor<gamma_p_t>;
}

#include <eve/module/special/regular/impl/gamma_p.hpp>
