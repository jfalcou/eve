//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/detail/category.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  //================================================================================================
  // Wide to Logical
  //================================================================================================
  template<typename T, typename N>
  EVE_FORCEINLINE as_logical_t<wide<T,N>> to_logical( wide<T,N> const& v ) noexcept
      requires arm_abi<abi_t<T, N>>
  {
    constexpr auto cat = categorize<wide<T, N>>();
    [[maybe_unused]] auto const nez  = [](auto x) { return logical<T>(x != 0); };
    [[maybe_unused]] auto const nope = [](auto x)
    {
            if constexpr( cat == category::float64x2 )
        return vreinterpretq_u64_u32(vmvnq_u32(vreinterpretq_u32_u64(x)));
      else  if constexpr( cat == category::float64x1)
        return vreinterpret_u64_u32(vmvn_u32(vreinterpret_u32_u64(x)));
      else  if constexpr(cat == category::int64x1)
        return vreinterpret_u64_u32(vmvn_u32(vreinterpret_u32_u64(x)));
      else  if constexpr(cat == category::uint64x1)
        return vreinterpret_u64_u32(vmvn_u32(vreinterpret_u32_u64(x)));
      else  if constexpr(cat == category::int64x2)
        return vreinterpretq_u64_u32(vmvnq_u32(vreinterpretq_u32_u64(x)));
      else  if constexpr(cat == category::uint64x2)
        return vreinterpretq_u64_u32(vmvnq_u32(vreinterpretq_u32_u64(x)));
    };

    wide<T,N> const z{0};

          if constexpr( cat == category::float32x4) return vmvnq_u32(vceqq_f32(v, z));
    else  if constexpr( cat == category::int32x4  ) return vmvnq_u32(vceqq_s32(v, z));
    else  if constexpr( cat == category::int16x8  ) return vmvnq_u16(vceqq_s16(v, z));
    else  if constexpr( cat == category::int8x16  ) return vmvnq_u8 (vceqq_s8(v, z));
    else  if constexpr( cat == category::uint32x4 ) return vmvnq_u32(vceqq_u32(v, z));
    else  if constexpr( cat == category::uint16x8 ) return vmvnq_u16(vceqq_u16(v, z));
    else  if constexpr( cat == category::uint8x16 ) return vmvnq_u8 (vceqq_u8(v, z));
    else  if constexpr( cat == category::float32x2) return vmvn_u32(vceq_f32(v, z));
    else  if constexpr( cat == category::int32x2  ) return vmvn_u32 (vceq_s32(v, z));
    else  if constexpr( cat == category::int16x4  ) return vmvn_u16 (vceq_s16(v, z));
    else  if constexpr( cat == category::int8x8   ) return vmvn_u8  (vceq_s8(v, z));
    else  if constexpr( cat == category::uint32x2 ) return vmvn_u32 (vceq_u32(v, z));
    else  if constexpr( cat == category::uint16x4 ) return vmvn_u16 (vceq_u16(v, z));
    else  if constexpr( cat == category::uint8x8  ) return vmvn_u8  (vceq_u8(v, z));
    else if constexpr( current_api >= asimd)
    {
            if constexpr( cat == category::float64x1) return nope(vceq_f64 (v, z));
      else  if constexpr( cat == category::int64x1)   return nope(vceq_s64 (v, z));
      else  if constexpr( cat == category::uint64x1)  return nope(vceq_u64 (v, z));
      else  if constexpr( cat == category::float64x2) return nope(vceqq_f64(v, z));
      else  if constexpr( cat == category::int64x2)   return nope(vceqq_s64(v, z));
      else  if constexpr( cat == category::uint64x2)  return nope(vceqq_u64(v, z));
    }
    else  if constexpr( sizeof(T) == 8 )            return map(nez, v);
  }
}
