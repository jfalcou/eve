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
#include <eve/module/core/bit_and.hpp>
#include <eve/module/core/bit_andnot.hpp>
#include <eve/module/core/byte_reverse.hpp>
#include <eve/module/core/bit_swap_adjacent.hpp>
#include <eve/module/core/bit_swap_pairs.hpp>
#include <eve/module/core/bit_shl.hpp>
#include <eve/module/core/bit_shr.hpp>


namespace eve
{
  template<typename Options>
  struct bit_reverse_t : elementwise_callable<bit_reverse_t, Options>
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
//!   @brief  elementwise reverse the bit order.
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
//!      template< eve::value T >
//!      T bit_reverse(T x) noexcept;          //1
//!
//!      template< unsignedvalue T,  integral_scalar_value N>
//!      T bit_reverse(T x , N n) noexcept;    //2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [argument](@ref eve::value).
//!     * `n` :  n delimit the band to be reversed at both ends of x.
//!
//!    **Return value**
//!
//!    The values of the of the parameter are returned with bits in reversed order.
//!    if n is present :
//!      - if n == 0 the call returns x
//!      - if 2*n >= sizeof(element_type_t<T>)   the call is identical to reverse(x)
//!      - otherwise the first n bits and the last n bits of each element of x are swapped in
//!        reverse order and the central remaining bits are unchanged.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/bit_reverse.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::bit_reverse[mask](x, ...)` provides a masked
//!     version of `bit_reverse` which is
//!     equivalent to `if_else(mask, bit_reverse(x, ...), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto bit_reverse = functor<bit_reverse_t>;

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
