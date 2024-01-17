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
  struct ellint_1_t : elementwise_callable<ellint_1_t, Options>
  {
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE
    T operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    template<eve::floating_ordered_value T0, eve::floating_ordered_value T1>
    EVE_FORCEINLINE
    eve::common_value_t<T0, T1> operator()(T0 a, T1 b) const noexcept { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(ellint_1_t, ellint_1_);
  };


//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var ellint_1
//!   @brief Computes the  elliptic integrals of the first kind :
//!   \f$\mathbf{F}(\phi, k) = \int_0^{\phi} \frac{\mathrm{d}t}{\sqrt{1-k^2\sin^2 t}}\f$ and
//!   \f$\mathbf{K}(k) = \int_0^{\pi/2} \frac{\mathrm{d}t}{\sqrt{1-k^2\sin^2 t}}\f$.
//!
//!   Be aware that as \f$\pi/2\f$ is not exactly represented by floating point
//!   values the result of the incomplete function with a \f$\phi\f$ floating point value
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
//!      T ellint_1(T k) noexcept;                                                //1
//!
//!      template< eve::floating_ordered_value T,  eve::floating_ordered_value U >
//!      eve::common_value_t<T, U> ellint_1(T phi, U k) noexcept;        //2
//!   }
//!   @endcode
//!
//!    1. complete elliptic integrals of the first kind.
//!    2. incomplete elliptic integrals of the first kind.
//!
//!   **Parameters**
//!
//!     * `phi`:   [floating real Jacobi amplitude](@ref eve::floating_ordered_value).
//!
//!     * `k`:  [floating real elliptic modulus](@ref eve::floating_ordered_value). `k` must verify
//!             \f$k^2\sin^2\phi \le 1\f$ or the result is NaN. In the complete case this means
//!             \f$|k| \le 1\f$.
//!
//!   **Return value**
//!
//!     1. the complete elliptic integral (corresponding to \f$ \phi = \pi/2 \f$) is returned.
//!     2. the incomplete elliptic integral is returned:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/elliptic/regular/ellint_1.cpp}
//! @}
//================================================================================================
  inline constexpr auto ellint_1 = functor<ellint_1_t>;
}

#include <eve/module/elliptic/regular/impl/ellint_1.hpp>
