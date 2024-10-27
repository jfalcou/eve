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
#include <eve/module/core/regular/is_pow2.hpp>

namespace eve
{

  template<typename Options>
  struct bit_swap_adjacent_t : strict_elementwise_callable<bit_swap_adjacent_t, Options>
  {
    template<eve::unsigned_value T, integral_scalar_value I>
    constexpr EVE_FORCEINLINE T operator()(T v,  I i) const
    { return EVE_DISPATCH_CALL(v, i); }

    EVE_CALLABLE_OBJECT(bit_swap_adjacent_t, bit_swap_adjacent_);
  };

//================================================================================================
//! @addtogroup core_bitops
//! @{
//!   @var bit_swap_adjacent
//!   @brief `strict_elementwise_callable` object  swapping adjacent groups of n bits.
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
//!      constexpr auto bit_swap_adjacent(unsigned_value auto x, integral_scalar_value auto n) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto bit_swap_adjacent[conditional_expr auto c](unsigned_value auto x, integral_scalar_value auto n) noexcept; // 2
//!      constexpr auto bit_swap_adjacent[logical_value auto m](unsigned_value auto x, integral_scalar_value auto n)    noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`: [argument](@ref eve::integral_value).
//!     * `n`: size of the groups of bits to be swapped. n MUST be a power of 2 else the call will assert.
//!     * `c`: [Conditional expression](@ref eve::conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!    **Return value**
//!      1. Return `x` with pairs of contiguous groups of N bits swapped in each element.
//!         - If n is greater or equal to sizeof(x)*8 0 is returned.
//!         - If n is equal            to 0           x is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/bit_swap_adjacent.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//================================================================================================
  inline constexpr auto bit_swap_adjacent = functor<bit_swap_adjacent_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<typename T, integral_scalar_value N, callable_options O>
    EVE_FORCEINLINE constexpr T
    bit_swap_adjacent_(EVE_REQUIRES(cpu_), O const&, T const& x, N const & n) noexcept
    {
      EVE_ASSERT(eve::is_pow2(n) || (n == 0),  "n is not a power of 2");
      using e_t =  element_type_t<T>;
      constexpr auto S = sizeof(e_t);
      auto  mk_ct = [](uint8_t C){
        e_t r = C;
        size_t shift = 4;
        constexpr size_t ls = S/2-(S == 8); //logarithm
        for(size_t i = 1; i <= ls; ++i)
        {
          shift *= 2;
          r += r << shift;
        }
        return r;
      };
      auto swp = [](auto vx, auto vm, auto vn)->T
      {
        return bit_or(bit_shl(bit_and(vx, T(vm)), vn), bit_shr(bit_andnot(vx, T(vm)), vn));
      };

      if (n > N(S*4)) return zero(as(x));
      else if (n == 0) return x;
      else if (n == 1) //Return x with neighbor bits swapped.
        return swp(x, mk_ct(0x55), n);
      else if (n == 2) //Return x with group of 2 bits swapped.
        return swp(x, mk_ct(0x33), n);
      else if (n == 4) //Return x with group of 4 bits swapped.
        return swp(x, mk_ct(0x0f), n);
      else if (n == 8) //Return x with group of 8 bits swapped.
      {
        if      constexpr(S == 2) return (x << n) | (x >> n);
        else if constexpr(S == 4) return swp(x, 0x00ff00ffU, n);
        else if constexpr(S == 8) return swp(x, 0x00ff00ff00ff00ffUL, n);
        else return  zero(as(x));
      }
      else if (n == 16) //Return x with group of 16 bits swapped.
      {
        if      constexpr(S == 4) return (x << n) | (x >> n);
        else if constexpr(S == 8) return swp(x, 0x0000ffff0000ffffUL, n);
        else return  zero(as(x));
      }
      else if (n == 32) //Return x with group of 32 bits swapped. (S = 8)
        return (x << n) | (x >> n);
      else return zero(as(x));
    }
  }
}
