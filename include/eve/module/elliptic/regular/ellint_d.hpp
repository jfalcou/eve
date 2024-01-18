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
  struct ellint_d_t : elementwise_callable<ellint_d_t, Options>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE
    T operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    template<eve::floating_ordered_value T0, eve::floating_ordered_value T1>
    constexpr EVE_FORCEINLINE
    eve::common_value_t<T0, T1> operator()(T0 a, T1 b) const noexcept { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(ellint_d_t, ellint_d_);
  };


//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var ellint_d
//!   @brief Computes the \f$\mbox{D}\f$ elliptic integrals  :
//!        \f$ \mathbf{D}(\phi, k) = \int_0^{\phi} \frac{\sin^2 t}{\sqrt{1-k^2\sin^2 t}}
//!        \scriptstyle\;\mathrm{d}t\f$ and
//!        \f$ \mathbf{D}(k) = \int_0^{\pi/2} \frac{\sin^2 t}{\sqrt{1-k^2\sin^2 t}}
//!        \scriptstyle\;\mathrm{d}t\f$.
//!
//!   Be aware that as \f$\pi/2\f$ is not exactly represented by floating point
//!   values the result of the incomplete  function with a \f$\phi\f$ floating point value
//!   representing \f$\pi/2\f$ can differ a lot with the result of the complete call.
//!
//!   **Defined in Header**
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
//!      template< eve::floating_ordered_value T >
//!      T ellint_d(T k) noexcept;                                                //1
//!
//!      template< eve::floating_ordered_value T, eve::floating_ordered_value U >
//!      eve::common_value_t<T, U> ellint_d(T phi, U k) noexcept;        //2
//!   }
//!   @endcode
//!
//!    1. complete \f$\mbox{D}\f$  elliptic integrals.
//!    2. incomplete\f$\mbox{D}\f$ elliptic integrals.
//!
//!
//!   **Parameters**
//!
//!     * `phi`: [floating real Jacobi amplitude](@ref eve::floating_ordered_value).
//!
//!     * `k`:  [floating real elliptic modulus](@ref eve::floating_ordered_value).
//!             `k` must verify \f$k^2\sin^2\phi \le 1\f$ or the result is NaN. In the complete case,
//!             this means \f$|k| \le 1\f$.
//!
//!   **Return value**
//!
//!     1. the complete elliptic integral ( corresponding to \f$ \phi = \pi/2 \f$ ) is returned.
//!     2. the incomplete elliptic integral of the first kind is returned:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/elliptic/regular/ellint_d.cpp}
//! @}
//================================================================================================
  inline constexpr auto ellint_d = functor<ellint_d_t>;
}

#include <eve/module/elliptic/regular/impl/ellint_d.hpp>
