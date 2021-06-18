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
  template<real_scalar_value T, typename N, std::ptrdiff_t Shift>
  EVE_FORCEINLINE wide<T,N> slide_left_ ( EVE_SUPPORTS(neon128_)
                                            , wide<T,N> v, index_t<Shift>
                                            ) noexcept
  requires(Shift<=N::value) && arm_abi<abi_t<T, N>>
  {
    using that_t  = wide<T,N>;

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
      that_t z{0}, result;

            if constexpr( c == category::int64x2    ) result = vextq_s64(v,z,Shift);
      else  if constexpr( c == category::uint64x2   ) result = vextq_u64(v,z,Shift);
      else  if constexpr( c == category::int64x1    ) result = vext_s64 (v,z,Shift);
      else  if constexpr( c == category::uint64x1   ) result = vext_u64 (v,z,Shift);
      else  if constexpr( c == category::int32x4    ) result = vextq_s32(v,z,Shift);
      else  if constexpr( c == category::uint32x4   ) result = vextq_u32(v,z,Shift);
      else  if constexpr( c == category::int32x2    ) result = vext_s32 (v,z,Shift);
      else  if constexpr( c == category::uint32x2   ) result = vext_u32 (v,z,Shift);
      else  if constexpr( c == category::int16x8    ) result = vextq_s16(v,z,Shift);
      else  if constexpr( c == category::uint16x8   ) result = vextq_u16(v,z,Shift);
      else  if constexpr( c == category::int16x4    ) result = vext_s16 (v,z,Shift);
      else  if constexpr( c == category::uint16x4   ) result = vext_u16 (v,z,Shift);
      else  if constexpr( c == category::int8x16    ) result = vextq_s8 (v,z,Shift);
      else  if constexpr( c == category::uint8x16   ) result = vextq_u8 (v,z,Shift);
      else  if constexpr( c == category::int8x8     ) result = vext_s8  (v,z,Shift);
      else  if constexpr( c == category::uint8x8    ) result = vext_u8  (v,z,Shift);
      else
      {
        using f_t = as_integer_t<wide<T,N>>;
        result = bit_cast( slide_left(bit_cast(v,as<f_t>{}), index<Shift>), as(v) );
      }

      return result;
    }
  }
}
