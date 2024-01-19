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
  struct ellint_rg_t : elementwise_callable<ellint_rg_t, Options, raw_option>
  {
     template<eve::floating_ordered_value T0, eve::floating_ordered_value T1, eve::floating_ordered_value T2>
    constexpr EVE_FORCEINLINE
    eve::common_value_t<T0, T1, T2> operator()(T0 a, T1 b, T2 c) const noexcept { return EVE_DISPATCH_CALL(a, b, c); }

    EVE_CALLABLE_OBJECT(ellint_rg_t, ellint_rg_);
  };

//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var ellint_rg
//!   @brief Computes the Carlson's elliptic integral
//!   \f$ \mathbf{R}_\mathbf{G}(x, y) = \frac1{4\pi} \int_{0}^{2\pi}\int_{0}^{\pi}
//!   \scriptstyle\sqrt{x\sin^2\theta\cos^2\phi
//!   +y\sin^2\theta\sin^2\phi
//!   +z\cos^2\theta} \scriptstyle\;\mathrm{d}\theta\;\mathrm{d}\phi\f$
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
//!      template< eve::floating_ordered_value T
//!              , eve::floating_ordered_value U
//!              , eve::floating_ordered_value V >
//!      constexpr eve::common_value_t<T, U, V> ellint_rg(T x, U y, V z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z`:  [floating real arguments](@ref eve::floating_ordered_value).
//!                       All arguments must be non-negative or the result is nan.
//!
//!   **Return value**
//!
//!   the value of the \f$\mathbf{R}_\mathbf{G}\f$ Carlson elliptic integral is returned:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/elliptic/regular/ellint_rc.cpp}
//! @}
//================================================================================================
  inline constexpr auto ellint_rg = functor<ellint_rg_t>;
}

#include <eve/module/elliptic/regular/impl/ellint_rg.hpp>
