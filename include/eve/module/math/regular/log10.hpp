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
  struct log10_t : elementwise_callable<log10_t, Options>
  {
    template<eve::floating_ordered_value T>
    EVE_FORCEINLINE  constexpr T operator()(T v) const noexcept { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(log10_t, log10_);
  };

//================================================================================================
//! @addtogroup math_log
//! @{
//! @var log10
//!
//! @brief Callable object computing the base 10  logarithm: \f$\log_{10} x\f$.
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
//!      T log10(T x) noexcept;
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!   *  `x`:   [floating value](@ref eve::floating_value).
//!
//! **Return value**
//!
//!   *  Returns the [elementwise](@ref glossary_elementwise) the base 10 logarithm  of `x`
//!      In particular, for floating inputs:
//!
//!      * If the element is \f$\pm0\f$, \f$-\infty\f$ is returned.
//!      * If the element is \f$1\f$, \f$+0\f$ is returned.
//!      * If the element is \f$\infty\f$, \f$\infty\f$ is returned.
//!      * If the element is less than 0, `NaN` is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/log10.cpp}
//!
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::log10[mask](x)` provides a masked version of `eve::log10` which is
//!     equivalent to `if_else (mask, log10(x), x)`.
//!
//!      **Example**
//!
//!        @godbolt{doc/math/masked/log10.cpp}
//!  @}
//================================================================================================
inline constexpr auto log10 = functor<log10_t>;
}


#include <eve/module/math/regular/impl/log10.hpp>
