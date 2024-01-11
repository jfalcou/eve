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
struct digamma_t : elementwise_callable<digamma_t, Options>
{
  template<eve::value T>
  EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(digamma_t, digamma_);
};

//================================================================================================
//! @addtogroup special
//! @{
//!   @var digamma
//!   @brief Computes the Digamma function i.e. the logarithmic derivative of the \f$\Gamma\f$
//!   function.
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
//!      T digamma(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!
//!   **Return value**
//!
//!   The value of the Digamma function: \f$\frac{\Gamma'(x)}{\Gamma(x)}\f$ is returned.
//!
//!   @groupheader{Example}
//!   @godbolt{doc/special/regular/digamma.cpp}
//!
//!
//! @}
//================================================================================================
inline constexpr auto digamma = functor<digamma_t>;
}


#include <eve/module/special/regular/impl/digamma.hpp>
