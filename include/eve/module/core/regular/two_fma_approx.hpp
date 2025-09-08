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
#include <eve/module/core/regular/two_add.hpp>

namespace eve
{
  template<typename Options>
  struct two_fma_approx_t : elementwise_callable<two_fma_approx_t, Options>
  {
    template<eve::floating_value T, eve::floating_value U, eve::floating_value V>
    requires(eve::same_lanes_or_scalar<T, U, V>)
      constexpr EVE_FORCEINLINE zipped<common_value_t<T, U, V>, common_value_t<T, U, V>>
    operator()(T t, U u, V v) const noexcept
    { return EVE_DISPATCH_CALL(t, u, v); }

    EVE_CALLABLE_OBJECT(two_fma_approx_t, two_fma_approx_);
  };

//================================================================================================
//! @addtogroup core_accuracy
//! @{
//!   @var two_fma_approx
//!   @brief Computes the [elementwise](@ref glossary_elementwise)
//!   triplet  of an fma value f and two errors e1 and e2 such that \f$ax+y = f+r_1+r_2\f$
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!     constexpr auto two_fma_approx(floating_value auto a, floating_value auto b, floating_value auto c) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `a`, `b`, 'c':  [floating arguments](@ref eve::floating_value).
//!
//!   **Return value**
//!
//!     Computes [elementwise](@ref glossary_elementwise) a pair of values `[f, e1]` such that:
//!
//!     * `f` is `fma(a, x, y)`
//!     * `\f$ a\otimes x\oplus y = r1\oplus e1 with a very small error (less than 14*eps
//!
//!    where \f$\oplus\f$ (resp. \f$\otimes\f$) adds (resp. multiplies) its two parameters with
//!    infinite precision.
//!
//!  @groupheader{External references}
//!   *  [Exact and Approximated error of the FMA](https://inria.hal.science/inria-00429617/document)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/two_fma_approx.cpp}
//================================================================================================
  inline constexpr auto two_fma_approx = functor<two_fma_approx_t>;
//================================================================================================
//! @}
//================================================================================================
}

#include <eve/module/core/regular/two_prod.hpp>

namespace eve
{
  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE auto two_fma_approx_(EVE_REQUIRES(cpu_), O const&, T a, T b, T c) noexcept
    {
      T d = fma(a, b, c);
      auto [v1, v2] = two_prod(a, b);
      auto [w1, w2] = two_add(c, v1);
      auto t = w1-d;
      return eve::zip(d, t+(v2+w2));
    }
  }
}
