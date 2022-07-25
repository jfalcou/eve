//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/spy.hpp>
#include <eve/module/core/regular/unalign.hpp>

namespace eve::detail
{

template<real_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
EVE_FORCEINLINE wide<T, N>
                load_(EVE_SUPPORTS(sve_fixed_),
                      ignore_none_ const&,
                      safe_type const&,
                      eve::as<wide<T, N>> const&,
                      Ptr p) requires(sve_abi<abi_t<T, N>>)
{
  auto ptr = unalign(p);

  /*if constexpr( N() == expected_cardinal_v<T> )
  {
    if constexpr( std::same_as<T, double> ) return svld1_f64(svptrue_b64(), ptr);
    else if constexpr( std::same_as<T, float> ) return svld1_f32(svptrue_b64(), ptr);
    else if constexpr( std::same_as<T, std::int64_t> ) return svld1_s64(svptrue_b64(), ptr);
    else if constexpr( std::same_as<T, std::uint64_t> ) return svld1_u64(svptrue_b64(), ptr);
    else if constexpr( std::same_as<T, std::int32_t> ) return svld1_s32(svptrue_b64(), ptr);
    else if constexpr( std::same_as<T, std::uint32_t> ) return svld1_u32(svptrue_b64(), ptr);
    else if constexpr( std::same_as<T, std::int16_t> ) return svld1_s16(svptrue_b64(), ptr);
    else if constexpr( std::same_as<T, std::uint16_t> ) return svld1_u16(svptrue_b64(), ptr);
    else if constexpr( std::same_as<T, std::int8_t> ) return svld1_s8(svptrue_b64(), ptr);
    else if constexpr( std::same_as<T, std::uint8_t> ) return svld1_u8(svptrue_b64(), ptr);
  }
  else
  {*/
    typename wide<T, N>::storage_type that {};
    std::memcpy(&that, ptr, N::value * sizeof(T));
    return that;
  //}
}

}
