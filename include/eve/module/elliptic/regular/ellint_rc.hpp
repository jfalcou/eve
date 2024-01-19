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
  struct ellint_rc_t : elementwise_callable<ellint_rc_t, Options>
  {
    template<eve::floating_ordered_value T0, eve::floating_ordered_value T1>
    constexpr EVE_FORCEINLINE
    eve::common_value_t<T0, T1> operator()(T0 a, T1 b) const noexcept { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(ellint_rc_t, ellint_rc_);
  };

//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var ellint_rc
//!   @brief computes the degenerate Carlson's elliptic integral
//!   \f$  \mathbf{R}_\mathbf{C}(x, y) = \frac12 \int_{0}^{\infty}
//!   \scriptstyle(t+x)^{-1/2}(t+y)^{-1}\scriptstyle\;\mathrm{d}t\f$.
//!
//!   **Defined in header**
//!
//!   @code
//!   #include <eve/module/elliptic.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      constexpr template< eve::floating_ordered_value T,  eve::floating_ordered_value U >
//!      eve::common_value_t<T, U> ellint_rc(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [floating real arguments](@ref eve::floating_ordered_value). `x` and `y` must be
//!                 strictly positive and `y` non zero or the result is NaN.
//!
//!   **Return value**
//!
//!    the value of the \f$\mathbf{R}_\mathbf{C}\f$ elliptic integral is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/elliptic/regular/ellint_rc.cpp}
//! @}
//================================================================================================
  inline constexpr auto ellint_rc = functor<ellint_rc_t>;
}

#include <eve/module/elliptic/regular/impl/ellint_rc.hpp>
