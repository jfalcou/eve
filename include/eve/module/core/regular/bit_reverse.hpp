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
#include <eve/module/core/regular/bit_and.hpp>
#include <eve/module/core/regular/bit_andnot.hpp>
#include <eve/module/core/regular/byte_reverse.hpp>
#include <eve/module/core/regular/bit_swap_adjacent.hpp>
#include <eve/module/core/regular/bit_swap_pairs.hpp>
#include <eve/module/core/regular/bit_shl.hpp>
#include <eve/module/core/regular/bit_shr.hpp>

namespace eve
{
  template<typename Options>
  struct bit_reverse_t : strict_elementwise_callable<bit_reverse_t, Options>
  {
    template<eve::value T>
    constexpr EVE_FORCEINLINE T operator()(T v) const
    { return EVE_DISPATCH_CALL(v); }

    template<eve::value T, integral_scalar_value I >
    constexpr EVE_FORCEINLINE T operator()(T v, I i) const
    { return EVE_DISPATCH_CALL(v, i); }

    EVE_CALLABLE_OBJECT(bit_reverse_t, bit_reverse_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_reverse
//!   @brief `strict_elementwise_callable` object reversing the bit order.
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
//!      constexpr auto bit_reverse(unsigned_value auto x)                                   noexcept; // 1
//!      constexpr auto bit_reverse(unsigned_value auto x integral_scalar_value n)           noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto bit_reverse[conditional_expr auto c](/*any of the above overloads*/) noexcept; // 3
//!      constexpr auto bit_reverse[logical_value auto m](/*any of the above overloads*/)    noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::value).
//!     * `n`: n scalar delimiting the band to be reversed at both ends of x.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!      1. The values of the of the parameter are returned with bits in reversed order.
//!      2. if n is present :
//!           - if n == 0 the call returns x
//!           - if 2*n is greater or equal to the size of the element type of `x`,
//!             the call is identical to `reverse(x)`.
//!           - otherwise the first n bits and the last n bits of each element of x are swapped in
//!           reverse order and the central remaining bits are unchanged.
//!      3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_reverse.cpp}
//================================================================================================
  inline constexpr auto bit_reverse = functor<bit_reverse_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr T
    bit_reverse_(EVE_REQUIRES(cpu_), O const&, T x) noexcept
    {
      using e_t =  element_type_t<T>;
      constexpr auto S = sizeof(e_t);
      if constexpr(scalar_value<T>)
      {
        x = bit_swap_adjacent(x, 1);
        x = bit_swap_adjacent(x, 2);
        x = bit_swap_adjacent(x, 4);
        if constexpr(sizeof(T) >= 2)
          x = bit_swap_adjacent(x, 8);
        else
          return x;
        if constexpr(sizeof(T) >= 4)
          x = bit_swap_adjacent(x, 16);
        else
          return x;
        if constexpr(sizeof(T) ==  8)
          x = bit_swap_adjacent(x, 32);
        return x;
      }
      else
      {
        if constexpr(S == 1)
        {
          x =  bit_shl((x & uint8_t(0x55)), 1) | bit_shr((x & uint8_t(0xaa)), 1);
          x =  bit_shl((x & uint8_t(0x33)), 2) | bit_shr((x & uint8_t(0xcc)), 2);
          x =  (bit_shl(x, 4) | bit_shr(x, 4));
          return x;
        }
        else
        {
          using u8_t = wide<uint8_t, fixed<S*cardinal_v<T>>>;
          auto z = eve::bit_cast(x, as<u8_t>());
          return byte_reverse( bit_cast(bit_reverse(z), as<T>()));
        }
      }
    }

    template<typename T, typename I, callable_options O>
    EVE_FORCEINLINE constexpr T
    bit_reverse_(EVE_REQUIRES(cpu_), O const&, T x, I n) noexcept
    {
      using e_t =  element_type_t<T>;
      constexpr auto S = sizeof(e_t)*8;
      if (n == 0)         return x;
      else
      {
        auto y =  bit_reverse(x);
        if (n >= I(S/2))
          return y;
        else if (n == 1u)
          return bit_swap_pairs(x, 0u, S-1u);
        else
        {
          constexpr auto o = e_t(1);
          e_t mask0 = (e_t(e_t(o << n)-o) << (S-n));
          auto mask =  bit_or(mask0, bit_reverse(mask0));
          return bit_or( bit_and(y, mask), bit_andnot(x, mask));
        }
      }
    }
  }
}

#if defined(EVE_INCLUDE_ARM_NEON_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/neon/bit_reverse.hpp>
#endif

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/bit_reverse.hpp>
#endif
