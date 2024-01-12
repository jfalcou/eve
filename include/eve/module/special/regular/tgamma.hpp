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
  struct tgamma_t : elementwise_callable<tgamma_t, Options>
  {
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(tgamma_t, tgamma_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var tgamma
//!   @brief Computes \f$\displaystyle \Gamma(x)=\int_0^\infty t^{x-1}e^{-t}\mbox{d}t\f$.
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
//!      template< eve::floating_value T >
//!      T tgamma(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!   *  `x`:   [floating real value](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   The value of \f$\Gamma\f$ is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/tgamma.cpp}
//!
//!
//! @}
//================================================================================================
inline constexpr auto tgamma = functor<tgamma_t>;
}

#include <eve/module/special/regular/impl/tgamma.hpp>
