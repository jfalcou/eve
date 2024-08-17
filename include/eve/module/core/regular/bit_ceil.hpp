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
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/regular/bit_floor.hpp>
#include <eve/module/core/regular/dec.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/ifrexp.hpp>
#include <eve/module/core/regular/is_less.hpp>
#include <eve/module/core/regular/is_less_equal.hpp>
#include <eve/module/core/regular/ldexp.hpp>

namespace eve
{
  template<typename Options>
  struct bit_ceil_t : elementwise_callable<bit_ceil_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(bit_ceil_t, bit_ceil_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_ceil
//!   @brief `elementwise_callable` object computing the smallest integral power
//!   of two that is not smaller than `x`.
//!
//!   @groupheader{Header file}
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
//!      // Regular overloads
//!      constexpr auto bit_ceil(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto bit_ceil[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto bit_ceil[logical_value auto m](value auto x)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!
//!    **Return value**
//!
//!      1. The value of the smallest integral power of two that is not smaller than `x`
//!         is returned. If that value is not representable in the input type,
//!         the behavior is undefined.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_ceil.cpp}
//================================================================================================
  inline constexpr auto bit_ceil = functor<bit_ceil_t>;
//================================================================================================
//! @}
//================================================================================================


  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    bit_ceil_(EVE_REQUIRES(cpu_), O const&, T v) noexcept
    {
      auto vle1 = v <= one(eve::as(v));
      if constexpr( floating_value<T> )
      {
        auto e      = exponent(v);
        auto tmp    = ldexp(one(eve::as(v)), e);
        auto tmpltv = tmp < v;
        return if_else(vle1, one(eve::as(v)), add[tmpltv](tmp, tmp));
      }
      else
      {
        auto tmp    = bit_floor(v);
        auto tmpltv = tmp < v;
        return if_else(vle1, one, add[tmpltv](tmp, tmp));
      }
    }
  }
}
