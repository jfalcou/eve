//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once


#include <eve/detail/implementation.hpp>
#include <eve/detail/swizzle.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/traits/element_type.hpp>

#include <cstddef>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Match any pattern of the form [N-1 ... 2 1 0]
  //------------------------------------------------------------------------------------------------
  struct reverse
  {
    enum class category { none, partial, full };

    template<typename Pattern, typename Wide>
    static constexpr auto categorize(Pattern const& p, as_<Wide> const&)  noexcept
    {
      constexpr auto max_size = cardinal_v<Wide>;
      constexpr auto size     = Pattern::size(max_size);

      if(size == 1) return 0;

      auto is_reversed = [&](auto sz, auto c)
      {
        for(int i=0;i<sz;i++)
        {
          if(p(i,sz) != c-i-1)
            return false;
        }
        return true;
      };

      // When we reverse full register
      for(int i = max_size; i != 1; i/=2)
      {
        if( is_reversed(size,i) )
          return static_cast<int>(i/size);
      }

      return 0;
    }

    template<typename Pattern, typename Wide>
    static constexpr auto check(Pattern const& p, as_<Wide> const& tgt)  noexcept
    {
      return categorize(p,tgt) != 0;
    }
  };

  //------------------------------------------------------------------------------------------------
  // Reverse data
  //------------------------------------------------------------------------------------------------
  template<typename Wide, typename Pattern>
  EVE_FORCEINLINE auto do_swizzle ( EVE_SUPPORTS(neon128_), reverse const&
                                  , Pattern const&, Wide const& //v
                                  )
  {
    //using in_t        = typename Wide::storage_type;
    constexpr auto sz = Pattern::size(cardinal_v<Wide>);
    using that_t      = wide<element_type_t<Wide>,fixed<sz>>;

    puts("REVERSE");


    constexpr auto category = reverse::categorize(Pattern(),as_<Wide>());
    std::cout << "REVERSE CATEGORY " << int(category) << std::endl;

    // if constexpr(category == reverse::category::full)
    // {
    //        if constexpr(std::is_same_v<in_t,  int32x2_t >) return that_t(vrev64_s32 (v));
    //   else if constexpr(std::is_same_v<in_t,  uint32x2_t>) return that_t(vrev64_u32 (v));
    //   else if constexpr(std::is_same_v<in_t,  int16x4_t >) return that_t(vrev32_s16 (v));
    //   else if constexpr(std::is_same_v<in_t,  uint16x4_t>) return that_t(vrev32_u16 (v));
    //   else if constexpr(std::is_same_v<in_t,  int8x8_t  >) return that_t(vrev64_s8  (v));
    //   else if constexpr(std::is_same_v<in_t,  uint8x8_t >) return that_t(vrev64_u8  (v));
    //   else if constexpr(std::is_same_v<in_t, float32x2_t>) return that_t(vrev64_f32 (v));
    //   else if constexpr(std::is_same_v<in_t,  int32x4_t >) return that_t(vrev64q_s32(v));
    //   else if constexpr(std::is_same_v<in_t,  uint32x4_t>) return that_t(vrev64q_u32(v));
    //   else if constexpr(std::is_same_v<in_t,  int16x8_t >) return that_t(vrev64q_s16(v));
    //   else if constexpr(std::is_same_v<in_t,  uint16x8_t>) return that_t(vrev64q_u16(v));
    //   else if constexpr(std::is_same_v<in_t,  int8x16_t >) return that_t(vrev64q_s8 (v));
    //   else if constexpr(std::is_same_v<in_t,  uint8x16_t>) return that_t(vrev64q_u8 (v));
    //   else if constexpr(std::is_same_v<in_t, float32x4_t>) return that_t(vrev64q_f32(v));
    //   else
    //   {
    //     return that_t{v[1],v[0]};
    //   }
    // }
    // else if constexpr( category == reverse::category::partial )
    // {
    //   auto s = v.slice(lower_);

    //         if constexpr(std::is_same_v<in_t,  int32x4_t >) return that_t(vrev64_s32(s));
    //   else  if constexpr(std::is_same_v<in_t,  uint32x4_t>) return that_t(vrev64_u32(s));
    //   else  if constexpr(std::is_same_v<in_t,  int16x8_t >) return that_t(vrev64_s16(s));
    //   else  if constexpr(std::is_same_v<in_t,  uint16x8_t>) return that_t(vrev64_u16(s));
    //   else  if constexpr(std::is_same_v<in_t,  int8x16_t >) return that_t(vrev64_s8 (s));
    //   else  if constexpr(std::is_same_v<in_t,  uint8x16_t>) return that_t(vrev64_u8 (s));
    //   else  if constexpr(std::is_same_v<in_t, float32x4_t>) return that_t(vrev64_f32(s));
    //   else
    //   {
    //     return that_t{v[1],v[0]};
    //   }
    // }
    // else
    // {
    //   std::cout << "CATEGORY FOR ERROR " << int(category) << "\n";
    return that_t();
    // }
  }
}
