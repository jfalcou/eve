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
  struct airy_t : elementwise_callable<airy_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr eve::result_t<zip,T,T> operator()(T a) const noexcept { return EVE_DISPATCH_CALL(a); }

    EVE_CALLABLE_OBJECT(airy_t, airy_);
  };

//================================================================================================
//! @addtogroup bessel
//! @{
//!   @var airy
//!   @brief Computes the airy functions values \f$ Ai(x)\f$ and \f$ Bi(x)\f$.
//!
//!   This function is designed to be faster than two separate calls to
//!   eve::airy_ai and eve::airy_bi.
//!
//!   **Defined in header**
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
//!      template< eve::floating_ordered_value T >
//!      kumi::tuple<T, T> airy(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [ordered floating argument](@ref eve::floating_ordered_value).
//!
//!    **Return value**
//!
//!    The tuple `{eve::airy_ai (x), eve::airy_bi (x)}` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/bessel/regular/airy.cpp}
//! @}
//================================================================================================
  inline constexpr auto airy = functor<airy_t>;
}

#include <eve/module/bessel/regular/impl/airy.hpp>
