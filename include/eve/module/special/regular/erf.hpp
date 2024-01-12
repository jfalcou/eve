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
  struct erf_t : elementwise_callable<erf_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE T operator()(T v) const  { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(erf_t, erf_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var erf
//!   @brief Computes the error function: \f$ \displaystyle
//!   \mbox{erf}(x)=\frac{2}{\sqrt\pi}\int_0^{x} e^{-t^2}\mbox{d}t\f$.
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
//!      T erf(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!    **Return value**
//!
//!    The value of the error function is returned. In particular:
//!
//!      * If the argument is \f$\pm0\f$, \f$\pm0\f$ is returned.
//!      * If the argument is \f$\pm\infty\f$, \f$\pm1\f$ is returned.
//!      * If the argument is Nan, nan returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/erf.cpp}
//!
//! @}
//================================================================================================
inline constexpr auto erf = functor<erf_t>;
}

#include <eve/module/special/regular/impl/erf.hpp>
