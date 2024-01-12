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
  struct erfc_inv_t : elementwise_callable<erfc_inv_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(erfc_inv_t, erfc_inv_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var erfc_inv
//!   @brief Computes the complementar error function \f$ \displaystyle
//!   \mbox{erf}(x)=1-\frac{2}{\sqrt\pi}\int_0^{x} e^{-t^2}\mbox{d}t\f$
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
//!      T erfc_inv(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!       Must be in interval  \f$[0, 2]\f$ else nan is returned.
//!
//!    **Return value**
//!
//!    The value of the inverse error function is returned. In particular:
//!
//!      * If the argument is \f$\pm0\f$, \f$1\f$ is returned.
//!      * If the argument is \f$2\f$, \f$-\infty\f$ is returned.
//!      * If the argument is \f$0\f$,\f$\infty\f$ is returned.
//!      * If the argument is NaN, NaN is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/erfc_inv.cpp}
//! @}
//================================================================================================
inline constexpr auto erfc_inv = functor<erfc_inv_t>;
}

#include <eve/module/special/regular/impl/erfc_inv.hpp>
