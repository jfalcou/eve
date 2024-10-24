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
  struct three_fma_t : elementwise_callable<three_fma_t, Options>
  {
    template<eve::floating_value T, eve::floating_value U, eve::floating_value V>
    requires(eve::same_lanes_or_scalar<T, U, V>)
      constexpr EVE_FORCEINLINE zipped<common_value_t<T, U, V>, common_value_t<T, U, V>, common_value_t<T, U, V>>
    operator()(T t, U u, V v) const noexcept
    { return EVE_DISPATCH_CALL(t, u, v); }

    EVE_CALLABLE_OBJECT(three_fma_t, three_fma_);
  };

//================================================================================================
//! @addtogroup core_accuracy
//! @{
//!   @var three_fma
//!   @brief Computes the [elementwise](@ref glossary_elementwise)
//!   triplet  of an fma value f and two errors e1 and e2 such that \f$ax+y = f+r_1+r_2/f$
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
//!     constexpr auto three_fma(floating_value auto a, floating_value auto b, floating_value auto c) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `a`, `b`, 'c':  [floating arguments](@ref eve::floating_value).
//!
//!   **Return value**
//!
//!     Computes [elementwise](@ref glossary_elementwise) a triplet of values `[f, r1, r2]` such that:
//!
//!     * `f` is `fma(a, x, y)`
//!     * `\f$ a\otimes x\oplus y = r1\oplus r2\oplus r3\f$ exactly
//!     * `\f$ |r1 \oplus r2| \le ulp(r1)/2\f$
//!     * `\f$ |r2| \le ulp(r2)/2\f$  `
//!
//!    where \f$\oplus\f$ (resp. \f$\otimes\f$) adds (resp. multiplies) its two parameters with
//!    infinite precision.
//!
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/regular/three_fma.cpp}
//================================================================================================
  inline constexpr auto three_fma = functor<three_fma_t>;
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
    EVE_FORCEINLINE auto three_fma_(EVE_REQUIRES(cpu_), O const&, T a, T x, T y) noexcept
    {
      T r1 = fma(a, x, y);
      auto [u1, u2] = two_prod(a, x);
      auto [a1, a2] = two_add(y, u2);
      auto [b1, b2] = two_add(u1, a1);
      auto c =  (b1-r1)+b2;
      auto [r2, r3] = two_add(c, a2);
      return eve::zip(r1, r2, r3);
    }
  }
}
