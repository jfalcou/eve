//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, std::ptrdiff_t Shift>
  EVE_FORCEINLINE wide<T,N> slide_right_( EVE_SUPPORTS(neon128_)
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
      constexpr auto c    = categorize<that_t>();
      that_t z{0};

      // The actual shift uses the expected cardinal so it has enough
      // to push through the unused space.
      constexpr auto shf  = expected_cardinal_v<T,abi_t<T, N>> - Shift;

            if constexpr( c == category::int64x2    ) return vextq_s64(z,v,shf);
      else  if constexpr( c == category::uint64x2   ) return vextq_u64(z,v,shf);
      else  if constexpr( c == category::int64x1    ) return vext_s64 (z,v,shf);
      else  if constexpr( c == category::uint64x1   ) return vext_u64 (z,v,shf);
      else  if constexpr( c == category::int32x4    ) return vextq_s32(z,v,shf);
      else  if constexpr( c == category::uint32x4   ) return vextq_u32(z,v,shf);
      else  if constexpr( c == category::int32x2    ) return vext_s32 (z,v,shf);
      else  if constexpr( c == category::uint32x2   ) return vext_u32 (z,v,shf);
      else  if constexpr( c == category::int16x8    ) return vextq_s16(z,v,shf);
      else  if constexpr( c == category::uint16x8   ) return vextq_u16(z,v,shf);
      else  if constexpr( c == category::int16x4    ) return vext_s16 (z,v,shf);
      else  if constexpr( c == category::uint16x4   ) return vext_u16 (z,v,shf);
      else  if constexpr( c == category::int8x16    ) return vextq_s8 (z,v,shf);
      else  if constexpr( c == category::uint8x16   ) return vextq_u8 (z,v,shf);
      else  if constexpr( c == category::int8x8     ) return vext_s8  (z,v,shf);
      else  if constexpr( c == category::uint8x8    ) return vext_u8  (z,v,shf);
      else
      {
        using f_t = as_integer_t<wide<T,N>>;
        return bit_cast( slide_right(bit_cast(v,as<f_t>{}), index<Shift>), as(v) );
      }
    }
  }
}
