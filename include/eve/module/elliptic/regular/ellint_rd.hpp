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
  struct ellint_rd_t : elementwise_callable<ellint_rd_t, Options, raw_option>
  {
    template<eve::floating_ordered_value T0, eve::floating_ordered_value T1, eve::floating_ordered_value T2>
    constexpr EVE_FORCEINLINE
    eve::common_value_t<T0, T1, T2> operator()(T0 a, T1 b, T2 c) const noexcept { return EVE_DISPATCH_CALL(a, b, c); }

    EVE_CALLABLE_OBJECT(ellint_rd_t, ellint_rd_);
  };

//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var ellint_rd
//!   @brief Computes the Carlson's elliptic integral
//!
//!   \f$  \mathbf{R}_\mathbf{D}(x, y) = \frac32 \int_{0}^{\infty} \scriptstyle[(t+x)(t+y)]^{-1/2}
//!   (t+z)^{-3/2}\scriptstyle\;\mathrm{d}t\f$.
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
//!      constexpr eve::common_value_t<T, U, V> ellint_rd(T x, U y, V z) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`: [floating real arguments](@ref eve::floating_ordered_value). `x` and `y` must be
//!       strictly positive and `y` non zero. In any other case, the result is NaN.
//!     * `z`: strictly positive [floating real arguments](@ref eve::floating_ordered_value). In any other
//!       case, the result is NaN.
//!
//!   **Return value**
//!
//!   the value of the \f$\mathbf{R}_\mathbf{D}\f$ Carlson elliptic integral is returned:
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/elliptic/regular/ellint_rc.cpp}
//! @}
//================================================================================================
inline constexpr auto ellint_rd = functor<ellint_rd_t>;
}

#include <eve/module/elliptic/regular/impl/ellint_rd.hpp>
