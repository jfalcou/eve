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
  struct erfcx_t : elementwise_callable<erfcx_t, Options>
  {
    template<eve::value T>
    EVE_FORCEINLINE T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(erfcx_t, erfcx_);
  };

//================================================================================================
//! @addtogroup special
//! @{
//!   @var erfcx
//!   @brief Computes the normalized complementary error function
//!   \f$ \displaystyle \mbox{erfcx}(x) = e^{x^2} \mbox{erfc}(x)\f$.
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
//!      T erfcx(T x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [real floating argument](@ref eve::floating_ordered_value).
//!
//!   **Return value**
//!
//!   The value of the normalized complementary error function is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/special/regular/erfcx.cpp}
//! @}
//================================================================================================
inline constexpr auto erfcx = functor<erfcx_t>;
}

#include <eve/module/special/regular/impl/erfcx.hpp>
