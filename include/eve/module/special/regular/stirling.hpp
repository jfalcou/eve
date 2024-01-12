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
  struct stirling_t : elementwise_callable<stirling_t, Options>
  {
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(stirling_t, stirling_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var stirling
//!   @brief Computes the Stirling approximation of the \f$\Gamma\f$ function.
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
//!      T stirling(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!     * `y` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   The value of an approximation of the
//!   \f$\Gamma\f$ function by \f$\displaystyle \Gamma(x) \approx \sqrt{2 \pi} x^{x-\frac12}
//!   e^{-x} \left( 1 + \frac1{x} P(\frac1{x})\right)\f$, where \f$P\f$ is a polynomial,
//!   is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/stirling.cpp}
//! @}
//================================================================================================
inline constexpr auto stirling = functor<stirling_t>;
}

#include <eve/module/special/regular/impl/stirling.hpp>
