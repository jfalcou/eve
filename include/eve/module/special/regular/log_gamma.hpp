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
  struct log_gamma_t : elementwise_callable<log_gamma_t, Options>
  {
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(log_gamma_t, log_gamma_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var log_gamma
//!   @brief Computes the natural logarithm of the \f$\Gamma\f$ function.
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
//!      T log_gamma(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!
//!   **Return value**
//!
//!   The value of the  logarithm of the \f$\Gamma\f$ function is returned.
//!
//!   @warning
//!       For real floating inputs this callable returns NaN if `eve::gamma(x)` is less than zero
//!
//!   @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/log_gamma.cpp}
//!
//! @}
//================================================================================================
inline constexpr auto log_gamma = functor<log_gamma_t>;
}

#include <eve/module/special/regular/impl/log_gamma.hpp>
