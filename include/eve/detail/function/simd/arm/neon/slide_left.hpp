//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/conditional.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, arm_abi ABI, std::ptrdiff_t Shift>
  EVE_FORCEINLINE wide<T,N,ABI> slide_left_ ( EVE_SUPPORTS(neon128_)
                                            , wide<T,N,ABI> v, index_t<Shift>
                                            ) noexcept
  requires(Shift<=N::value)
  {
    using that_t  = wide<T,N,ABI>;

    if constexpr(Shift == N::value)
    {
      return that_t{0};
    }
    else if constexpr(Shift == 0)
    {
      return v;
    }
    else
    {
      constexpr auto c = categorize<that_t>();
      that_t z{0};

      // Mask noises from smaller sized registers
      if constexpr(N::value < expected_cardinal_v<T,arm_64_>)
      {
        wide<T,expected_cardinal_t<T,arm_64_>> w = v.storage();
        w &= keep_first(N::value).mask(as(w)).bits();
        v = w.storage();
      }
            if constexpr( c == category::int64x2    ) return vextq_s64(v,z,Shift);
      else  if constexpr( c == category::uint64x2   ) return vextq_u64(v,z,Shift);
      else  if constexpr( c == category::int64x1    ) return vext_s64 (v,z,Shift);
      else  if constexpr( c == category::uint64x1   ) return vext_u64 (v,z,Shift);
      else  if constexpr( c == category::int32x4    ) return vextq_s32(v,z,Shift);
      else  if constexpr( c == category::uint32x4   ) return vextq_u32(v,z,Shift);
      else  if constexpr( c == category::int32x2    ) return vext_s32 (v,z,Shift);
      else  if constexpr( c == category::uint32x2   ) return vext_u32 (v,z,Shift);
      else  if constexpr( c == category::int16x8    ) return vextq_s16(v,z,Shift);
      else  if constexpr( c == category::uint16x8   ) return vextq_u16(v,z,Shift);
      else  if constexpr( c == category::int16x4    ) return vext_s16 (v,z,Shift);
      else  if constexpr( c == category::uint16x4   ) return vext_u16 (v,z,Shift);
      else  if constexpr( c == category::int8x16    ) return vextq_s8 (v,z,Shift);
      else  if constexpr( c == category::uint8x16   ) return vextq_u8 (v,z,Shift);
      else  if constexpr( c == category::int8x8     ) return vext_s8  (v,z,Shift);
      else  if constexpr( c == category::uint8x8    ) return vext_u8  (v,z,Shift);
      else
      {
        using f_t = as_integer_t<wide<T,N,ABI>>;
        return bit_cast( slide_left(bit_cast(v,as_<f_t>{}), index<Shift>), as(v) );
      }
    }
  }
}
