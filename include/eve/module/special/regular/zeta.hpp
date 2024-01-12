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
  struct zeta_t : elementwise_callable<zeta_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(zeta_t, zeta_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var zeta
//!   @brief Computes the Riemann \f$\zeta\f$ function.
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
//!      template< eve::floating_ordered_value T >
//!      T zeta(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   The value of the Riemann function defined as
//!   \f$\displaystyle \zeta(s)=\sum_{n=0}^\infty \frac1{n^s}\f$ is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/zeta.cpp}
//! @}
//================================================================================================
inline constexpr auto zeta = functor<zeta_t>;
}

#include <eve/module/special/regular/impl/zeta.hpp>
