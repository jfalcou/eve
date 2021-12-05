//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/function/slide_left.hpp>
#include <eve/function/count_true.hpp>

#include <eve/detail/top_bits.hpp>

namespace eve::detail
{
  template<relative_conditional_expr C, typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_switch_(EVE_SUPPORTS(cpu_),
                                 C c,
                                 wide<T, N> v,
                                 logical<wide<U, N>> mask,
                                 Ptr ptr) noexcept
  {
    constexpr bool has_aggregation = has_aggregated_abi_v<wide<T, N>> || has_aggregated_abi_v<wide<U, N>> || N() > 4;

         if constexpr ( C::is_complete  && !C::is_inverted ) return as_raw_pointer(ptr);
    else if constexpr ( has_aggregation && !C::is_complete )
    {
      return compress_store_impl_switch(ignore_none, v, mask && c.mask(as(mask)), ptr);
    }
    else if constexpr ( has_aggregation )
    {
      auto [l, h] = v.slice();
      auto [ml, mh] = mask.slice();

      T* ptr1 = compress_store_impl_switch(ignore_none, l, ml, ptr);
      return compress_store_impl_switch(ignore_none, h, mh, ptr1);
    }
    else
    {
      using l_t = logical<wide<U, N>>;
      static_assert(top_bits<l_t>::bits_per_element == 1);

      const int mmask = top_bits{mask, c}.as_int();

      if constexpr ( N() == 1 )
      {
        eve::store(v, ptr);
        return as_raw_pointer(ptr) + mmask;
      }
      else if constexpr ( N() == 2 )
      {
        if (mmask == 2) v = eve::slide_left( v, eve::index<1> );
        eve::store(v, ptr);
        T* res = as_raw_pointer(ptr);
        res += mmask & 1;
        res += (mmask & 2) >> 1;
        return res;
      }
      else if constexpr ( N() == 4 )
      {
        const int  num       = mmask & 7;
        const bool last_set  = (bool) (mmask & 8);

        int count;

        switch (num) {
          case 0b000: { count = 0; v = v[pattern<3, 0, 0, 0>]; break; }
          case 0b001: { count = 1; v = v[pattern<0, 3, 0, 0>]; break; }
          case 0b010: { count = 1; v = v[pattern<1, 3, 0, 0>]; break; }
          case 0b011: { count = 2; v = v[pattern<0, 1, 3, 0>]; break; }
          case 0b100: { count = 1; v = v[pattern<2, 3, 0, 0>]; break; }
          case 0b101: { count = 2; v = v[pattern<0, 2, 3, 0>]; break; }
          case 0b110: { count = 2; v = v[pattern<1, 2, 3, 0>]; break; }
          case 0b111: { count = 3;                             break; }
          #if defined(SPY_COMPILER_IS_CLANG) or defined(SPY_COMPILER_IS_GCC)
          default: __builtin_unreachable();
          #endif
        }
        count += last_set ? 1 : 0;
        store(v, ptr);
        return as_raw_pointer(ptr) + count;
      }
    }
  }
}
