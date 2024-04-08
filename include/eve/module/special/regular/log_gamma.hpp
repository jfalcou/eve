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
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

namespace eve
{
  template<typename Options>
  struct log_gamma_t : elementwise_callable<log_gamma_t, Options>
  {
    template<eve::floating_ordered_value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const  noexcept
    { return EVE_DISPATCH_CALL(v); }

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

  namespace detail
  {

    template<typename T, callable_options O>
    constexpr T
    log_gamma_(EVE_REQUIRES(cpu_), O const&, T a0) noexcept
    {
      auto aa0 = if_else(a0 == minf(as(a0)) || is_lez(signgam(a0)), allbits, a0);
      return log_abs_gamma(aa0);
    }
  }
}
