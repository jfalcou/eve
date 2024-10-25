//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/module/core.hpp>

namespace eve
{

  template<typename Options>
  struct sigmoid_t : elementwise_callable<sigmoid_t, Options>
  {
    template<eve::floating_value T>
    EVE_FORCEINLINE constexpr T operator()(T v) const noexcept
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(sigmoid_t, sigmoid_);
  };

//================================================================================================
//! @addtogroup math_sigmoid
//! @{
//! @var sigmoid
//! @brief `elementwise_callable` object computing the sigmoid (logistic function).
//!
//!   @groupheader{Header file}
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
//!      // Regular overload
//!      constexpr auto sigmoid(floating_value auto x)                              noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto sigmoid[conditional_sigmoidr auto c](floating_value auto x) noexcept; // 2
//!      constexpr auto sigmoid[logical_value auto m](floating_value auto x)        noexcept; // 2
//!   }
//!   @endcode
//!
//! **Parameters**
//!
//!     * `x`: [floating value](@ref eve::floating_value).
//!     * `c`: [Conditional sigmoidression](@ref conditional_sigmoidr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//! **Return value**
//!
//!   1.  Returns the [elementwise](@ref glossary_elementwise) sigmoid
//!       of the input. In particular:
//!       * If the element is \f$1/2\f$, \f$1\f$ is returned
//!       * If the element is \f$-\infty\f$, \f$+0\f$ is returned
//!       * If the element is \f$\infty\f$, \f$1\f$ is returned
//!       * If the element is a `NaN`, `NaN` is returned
//!   2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld](https://www.wolframalpha.com/input/?i=sigmoid)
//!   *  [Wikipedia](https://en.wikipedia.org/wiki/Sigmoid_function)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/math/sigmoid.cpp}
//================================================================================================
  inline constexpr auto sigmoid = functor<sigmoid_t>;
//================================================================================================
//!  @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    sigmoid_(EVE_REQUIRES(cpu_), O const &, T x) noexcept
    {
      return rec[pedantic](inc(exp(-x)));
    }
  }
}
