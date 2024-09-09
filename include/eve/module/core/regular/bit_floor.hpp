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
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/bit_width.hpp>
#include <eve/module/core/regular/dec.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/ifrexp.hpp>
#include <eve/module/core/regular/is_eqz.hpp>
#include <eve/module/core/regular/is_ltz.hpp>
#include <eve/module/core/regular/ldexp.hpp>

namespace eve
{
  template<typename Options>
  struct bit_floor_t : elementwise_callable<bit_floor_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    { return EVE_DISPATCH_CALL(v); }

    EVE_CALLABLE_OBJECT(bit_floor_t, bit_floor_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_floor
//!   @brief  `elementwise_callable` object computing, if `x` is not zero,
//!   the largest integral power of two that is not greater than `x`.
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
//!      // Regular overload
//!      constexpr auto bit_floor(value auto x)                          noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto bit_floor[conditional_expr auto c](value auto x) noexcept; // 2
//!      constexpr auto bit_floor[logical_value auto m](value auto x)    noexcept; // 2
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
//!      1. The value of the largest integral power of two that is not greater than `x` is returned.
//!         If `x` is zero returns zero.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_floor.cpp}
//================================================================================================
  inline constexpr auto bit_floor = functor<bit_floor_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    bit_floor_(EVE_REQUIRES(cpu_), O const&, T const& v) noexcept
    {
      if constexpr( floating_value<T> )
      {
        auto vlt1 = v < one(eve::as(v));
        auto e = exponent(v);
        auto r = eve::ldexp(one(eve::as(v)), e);
        return if_else(vlt1, eve::zero, r);
      }
      else if constexpr( signed_integral_value<T> )
      {
        auto uz = bit_floor(convert(v, uint_from<T>()));
        return if_else(is_ltz(v), zero, convert(uz, as<element_type_t<T>>()));
      }
      else
      {
        return if_else(is_eqz(v), zero, T{1} << dec[saturated](bit_width(v)));
      }
    }
  }
}
