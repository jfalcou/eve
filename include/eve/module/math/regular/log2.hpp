//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>

namespace eve
{

  template<typename Options>
  struct log2_t : elementwise_callable<log2_t, Options>
  {
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(log2_t, log2_);
  };

//================================================================================================
//! @addtogroup math_log
//! @{
//! @var log2
//!
//! @brief Callable object computing the base 2 logarithm: \f$\log_2 x\f$.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T >
//!      T log2(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) the base 2 logarithm  of `x`
//!      In particular, for floating inputs:
//!
//!      * If the element is \f$\pm0\f$, \f$-\infty\f$ is returned.
//!      * If the element is \f$1\f$, \f$+0\f$ is returned.
//!      * If the element is \f$\infty\f$, \f$\infty\f$ is returned.
//!      * If the element is less than 0, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/log2.cpp}
//!
//!
//!   * Masked Call
//!
//!     The call `eve::log2[mask](x)` provides a masked version of `eve::log2` which is
//!     equivalent to `if_else (mask, log2(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/log2.cpp}
//!  @}
//================================================================================================
inline constexpr auto log2 = functor<log2_t>;
}

#include <eve/module/math/regular/impl/log2.hpp>
