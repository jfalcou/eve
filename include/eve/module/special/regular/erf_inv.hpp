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
  struct erf_inv_t : elementwise_callable<erf_inv_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE T operator()(T v) const  noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(erf_inv_t, erf_inv_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var erf_inv
//!   @brief Computes the inverse of the error function.
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
//!      T erf_inv(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   The value `y` such that `erf(y)==x` is returned. For `x` outside of \f$[-1,1]\f$, the result
//!   is NaN.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/erf_inv.cpp}
//! @}
//================================================================================================
inline constexpr auto erf_inv = functor<erf_inv_t>;
}

#include <eve/module/special/regular/impl/erf_inv.hpp>
