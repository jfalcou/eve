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
  struct dawson_t : elementwise_callable<dawson_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(dawson_t, dawson_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var dawson
//!   @brief Computes the Dawson function \f$\displaystyle D_+(x)=e^{-x^2}\int_0^{x}
//!   e^{t^2} \mbox{d}t\f$
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
//!      T dawson(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   the value of the Dawson function for `x` is returned.
//!
//!   @groupheader{Example}
//!
//!   @godbolt{doc/special/regular/dawson.cpp}
//! @}
//================================================================================================
inline constexpr auto dawson = functor<dawson_t>;
}

#include <eve/module/special/regular/impl/dawson.hpp>
