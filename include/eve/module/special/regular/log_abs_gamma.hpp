//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve
{
  template<typename Options>
  struct log_abs_gamma_t : elementwise_callable<log_abs_gamma_t, Options>
  {
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE
    T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(log_abs_gamma_t, log_abs_gamma_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var log_abs_gamma
//!   @brief Computes the natural logarithm of the absolute value of the \f$\Gamma\f$ function.
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
//!      T log_abs_gamma(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real argument](@ref eve::value).
//!
//!   **Return value**
//!
//!   In the two cases, the value of the  logarithm of the absolute value of the \f$\Gamma\f$ function is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/log_abs_gamma.cpp}
//! @}
//================================================================================================
inline constexpr auto log_abs_gamma = functor<log_abs_gamma_t>;
}

#include <eve/module/special/regular/impl/log_abs_gamma.hpp>
