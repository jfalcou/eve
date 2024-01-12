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
  struct omega_t : elementwise_callable<omega_t, Options>
  {
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(omega_t, omega_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var omega
//!   @brief Computes the the Wright \f$\omega\f$ the inverse function of \f$ x \rightarrow \log
//!   x+x\f$
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
//!      T omega(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   The value of the Wright \f$\omega\f$ function is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/omega.cpp}
//! @}
//================================================================================================
inline constexpr auto omega = functor<omega_t>;
}


#include <eve/module/special/regular/impl/omega.hpp>
