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
  struct ellint_2_t : elementwise_callable<ellint_2_t, Options>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE
    T operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    template<eve::floating_ordered_value T0, eve::floating_ordered_value T1>
    constexpr EVE_FORCEINLINE
    eve::common_value_t<T0, T1> operator()(T0 a, T1 b) const noexcept { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(ellint_2_t, ellint_2_);
  };

//================================================================================================
//! @addtogroup elliptic
//! @{
//!   @var ellint_2
//!   @brief Computes the  elliptic integrals of the second kind :
//!   \f$ \mathbf{E}(\phi, k) = \int_0^{\phi} \scriptstyle \sqrt{1-k^2\sin^2 t}
//!   \scriptstyle\;\mathrm{d}t\f$ and
//!   \f$\mathbf{E}(k) = \int_0^{\pi/2} \scriptstyle \sqrt{1-k^2\sin^2 t}
//!   \scriptstyle\;\mathrm{d}t\f$.
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
//!      constexpr T ellint_2(T k) noexcept;                                       //1
//!
//!      template< eve::floating_ordered_value T,  eve::floating_ordered_value U >
//!      constexpr eve::common_value_t<T, U> ellint_2(T phi, U k) noexcept;        //2
//!   }
//!   @endcode
//!
//!    1. complete elliptic integrals of the second kind.
//!    2. incomplete elliptic integrals of the second kind.
//!
//!
//!   **Parameters**
//!
//!     * `phi`:   [floating real Jacobi amplitude](@ref eve::floating_ordered_value).
//!
//!     * `k`:  [floating real elliptic modulus](@ref eve::floating_ordered_value).
//!             `k` must verify \f$k^2\sin^2\phi \le 1\f$ or the result is NaN. In the complete
//!             case, this means \f$|k| \le 1\f$.
//!
//!   **Return value**
//!
//!     1. the complete ( corresponding to \f$ \phi = \pi/2 \f$ ) is returned.
//!     2. the incomplete elliptic integrals is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/elliptic/regular/ellint_2.cpp}
//! @}
//================================================================================================
  inline constexpr auto ellint_2 = functor<ellint_2_t>;

}

#include <eve/module/elliptic/regular/impl/ellint_2.hpp>
