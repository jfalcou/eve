//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/module/core/regular/slide_left.hpp>
#include <eve/module/core/regular/count_true.hpp>
#include <eve/module/core/regular/unalign.hpp>
#include <eve/module/core/regular/shuffle.hpp>

#include <eve/arch/top_bits.hpp>

namespace eve::detail
{
  template<relative_conditional_expr C, typename T, typename U, typename N>
  EVE_FORCEINLINE
  auto compress_using_switch_(EVE_SUPPORTS(cpu_),
                              C c,
                              wide<T, N> v,
                              logical<wide<U, N>> mask) noexcept
  {
    constexpr bool like_aggregate = has_aggregated_abi_v<wide<T, N>> || has_aggregated_abi_v<wide<U, N>> || N() > 8;

    if constexpr ( C::is_complete && !C::is_inverted )
    {
      kumi::tuple cur{ v, (std::ptrdiff_t) 0 };
      return kumi::tuple<decltype(cur)> { cur };
    }
    else if constexpr ( like_aggregate && !C::is_complete )
    {
      mask = mask && c.mask(as(mask));

      return compress_using_switch(ignore_none, v, mask);
    }
    else if constexpr ( like_aggregate )
    {
      auto [l, h] = v.slice();
      auto [ml, mh] = mask.slice();

      auto lr = compress_using_switch(ignore_none, l, ml);
      auto hr = compress_using_switch(ignore_none, h, mh);

      return kumi::cat(lr, hr);
    }
    else
    {
      using l_t = logical<wide<U, N>>;
      static_assert(top_bits<l_t>::bits_per_element == 1);

      const int mmask = top_bits{mask, c}.as_int();

      if constexpr ( N() == 1 )
      {
        kumi::tuple cur{ v, (std::ptrdiff_t) mmask & 1 };
        return kumi::tuple<decltype(cur)> { cur };
      }
      else if constexpr ( N() == 2 )
      {
        if (mmask == 2) v = eve::slide_left( v, eve::index<1> );
        std::ptrdiff_t count = mmask & 1;
        count += (mmask & 2) >> 1;
        kumi::tuple cur { v, count };
        return kumi::tuple<decltype(cur)> { cur };
      }
      else if constexpr ( N() == 4 )
      {
        const int  num       = mmask & 7;
        const bool last_set  = (bool) (mmask & 8);

        int count;

        switch (num) {
          case 0b000: { count = 0; v = shuffle(v,pattern<3, 0, 0, 0>); break; }
          case 0b001: { count = 1; v = shuffle(v,pattern<0, 3, 0, 0>); break; }
          case 0b010: { count = 1; v = shuffle(v,pattern<1, 3, 0, 0>); break; }
          case 0b011: { count = 2; v = shuffle(v,pattern<0, 1, 3, 0>); break; }
          case 0b100: { count = 1; v = shuffle(v,pattern<2, 3, 0, 0>); break; }
          case 0b101: { count = 2; v = shuffle(v,pattern<0, 2, 3, 0>); break; }
          case 0b110: { count = 2; v = shuffle(v,pattern<1, 2, 3, 0>); break; }
          case 0b111: { count = 3;                                     break; }
          #if defined(SPY_COMPILER_IS_CLANG) or defined(SPY_COMPILER_IS_GCC)
          default: __builtin_unreachable();
          #endif
        }
        count += last_set ? 1 : 0;

        kumi::tuple cur { v, count };

        return kumi::tuple<decltype(cur)> { cur };
      }
      else if constexpr ( N() == 8 )
      {
        const int  num1       = mmask & 7;
        const bool last_set1  = (bool) (mmask & 8);
        const int  num2       = (mmask & 0x70);
        const bool last_set2  = (bool) (mmask & 0x80);

        int count1, count2;

        switch (num1) {
          case 0b000: { count1 = 0; v = shuffle(v,pattern<3, 0, 0, 0, 4, 5, 6, 7>); break; }
          case 0b001: { count1 = 1; v = shuffle(v,pattern<0, 3, 0, 0, 4, 5, 6, 7>); break; }
          case 0b010: { count1 = 1; v = shuffle(v,pattern<1, 3, 0, 0, 4, 5, 6, 7>); break; }
          case 0b011: { count1 = 2; v = shuffle(v,pattern<0, 1, 3, 0, 4, 5, 6, 7>); break; }
          case 0b100: { count1 = 1; v = shuffle(v,pattern<2, 3, 0, 0, 4, 5, 6, 7>); break; }
          case 0b101: { count1 = 2; v = shuffle(v,pattern<0, 2, 3, 0, 4, 5, 6, 7>); break; }
          case 0b110: { count1 = 2; v = shuffle(v,pattern<1, 2, 3, 0, 4, 5, 6, 7>); break; }
          case 0b111: { count1 = 3;                                         break; }
          #if defined(SPY_COMPILER_IS_CLANG) or defined(SPY_COMPILER_IS_GCC)
          default: __builtin_unreachable();
          #endif
        }
        switch (num2) {
          case 0b000'0000: { count2 = 0; v = shuffle(v,pattern<0, 1, 2, 3, 7, 7, 7, 7>); break; }
          case 0b001'0000: { count2 = 1; v = shuffle(v,pattern<0, 1, 2, 3, 4, 7, 7, 7>); break; }
          case 0b010'0000: { count2 = 1; v = shuffle(v,pattern<0, 1, 2, 3, 5, 7, 7, 7>); break; }
          case 0b011'0000: { count2 = 2; v = shuffle(v,pattern<0, 1, 2, 3, 4, 5, 7, 7>); break; }
          case 0b100'0000: { count2 = 1; v = shuffle(v,pattern<0, 1, 2, 3, 6, 7, 7, 7>); break; }
          case 0b101'0000: { count2 = 2; v = shuffle(v,pattern<0, 1, 2, 3, 4, 6, 7, 7>); break; }
          case 0b110'0000: { count2 = 2; v = shuffle(v,pattern<0, 1, 2, 3, 5, 6, 7, 7>); break; }
          case 0b111'0000: { count2 = 3;                                         break; }
          #if defined(SPY_COMPILER_IS_CLANG) or defined(SPY_COMPILER_IS_GCC)
          default: __builtin_unreachable();
          #endif
        }

        auto [l, h] = v.slice();

        kumi::tuple l_half { l, count1 + last_set1 };
        kumi::tuple h_half { h, count2 + last_set2 };

        return kumi::tuple{ l_half, h_half };
      }
    }
  }
}
