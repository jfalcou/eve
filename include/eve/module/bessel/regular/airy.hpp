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

namespace eve
{
  template<typename Options>
  struct airy_t : elementwise_callable<airy_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr zipped<T,T> operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(airy_t, airy_);
  };

//================================================================================================
//! @addtogroup bessel
//! @{
//!   @var airy
//!   @brief `elementwise_callable` object computing simutaneously the airy functions values \f$ Ai(x)\f$
//!   and \f$ Bi(x)\f$.
//!
//!   This function is designed to be faster than two separate calls to
//!   eve::airy_ai and eve::airy_bi.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/bessel.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      constexpr auto airy(eve::floating_value auto x) -> decltype(eve::zip(x,x)) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [floating value](@ref eve::floating_value).
//!
//!    **Return value**
//!
//!    The tuple `{airy_ai (x), airy_bi (x)}` is returned.
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Airy Functions](https://mathworld.wolfram.com/AiryFunctions.html)
//!   *  [Wikipedia: Airy function](https://en.wikipedia.org/wiki/Airy_function)
//!   *  [DLMF: Airy and Related Functions](https://dlmf.nist.gov/9)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/bessel/airy.cpp}
//================================================================================================
  inline constexpr auto airy = functor<airy_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/bessel/regular/impl/airy.hpp>
