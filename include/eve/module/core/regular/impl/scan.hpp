//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/plus.hpp>
#include <eve/module/core/regular/slide_right.hpp>

namespace eve::detail
{
template<int group_size, simd_value Wide, typename Op>
EVE_FORCEINLINE Wide
scan_common_impl(Wide x, Op op)
{
  if constexpr( group_size == 1 ) return x;
  else
  {
    x = scan_common_impl<group_size / 2>(x, op);
    return op(x, slide_right(x, eve::index<group_size / 2>));
  }
}

template<int group_size, simd_value Wide, typename Op>
EVE_FORCEINLINE Wide
scan_common_impl(Wide x, Op op, Wide z)
{
  if constexpr( group_size == 1 ) return x;
  else
  {
    x = scan_common_impl<group_size / 2>(x, op, z);
    return op(x, slide_right(z, x, eve::index<group_size / 2>));
  }
}

template<simd_value Wide, typename Op, typename Zero>
EVE_FORCEINLINE Wide
scan_(EVE_SUPPORTS(cpu_), Wide v, Op op, Zero z) noexcept
{
  if constexpr( Wide::size() == 1 ) return v;
  else if constexpr( has_emulated_abi_v<Wide> )
  {
    auto sum = v.get(0);

    for( int i = 1; i != Wide::size(); ++i )
    {
      sum = op(sum, v.get(i));
      v.set(i, sum);
    }

    return v;
  }
  else if constexpr( std::same_as<Zero, callable_zero_> )
  {
    return scan_common_impl<Wide::size()>(v, op);
  }
  else { return scan_common_impl<Wide::size()>(v, op, Wide {z}); }
}

template<simd_value Wide>
EVE_FORCEINLINE Wide
scan_(EVE_SUPPORTS(cpu_), Wide v) noexcept
{
  return scan(v, plus, eve::zero);
}

}
