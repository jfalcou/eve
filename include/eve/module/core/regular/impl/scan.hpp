//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/regular/slide_right.hpp>

namespace eve::detail
{
  template<int group_size, simd_value Wide, typename Op>
  EVE_FORCEINLINE Wide scan_common_impl(Wide x, Op op)
  {
    if constexpr( group_size == 1 ) return x;
    else
    {
      x = scan_common_impl<group_size / 2>(x, op);
      return op(x, slide_right(x, eve::index<group_size / 2>));
    }
  }

  template<int group_size, simd_value Wide, typename Op>
  EVE_FORCEINLINE Wide scan_common_impl(Wide x, Op op, Wide z)
  {
    if constexpr( group_size == 1 ) return x;
    else
    {
      x = scan_common_impl<group_size / 2>(x, op, z);
      return op(x, slide_right(z, x, eve::index<group_size / 2>));
    }
  }

  template<callable_options O, simd_value Wide, typename Op, typename Zero>
  EVE_FORCEINLINE Wide scan_(EVE_REQUIRES(cpu_), O const&, Wide v, Op op, Zero z) noexcept
  {
    if constexpr( Wide::size() == 1 ) return v;
    else if constexpr( has_emulated_abi_v<Wide> )
    {
      auto sum_value = v.get(0);

      for( int i = 1; i != Wide::size(); ++i )
      {
        sum_value = op(sum_value, v.get(i));
        v.set(i, sum_value);
      }

      return v;
    }
    else if constexpr( std::same_as<Zero, callable_zero_> )
    {
      return scan_common_impl<Wide::size()>(v, op);
    }
    else { return scan_common_impl<Wide::size()>(v, op, as_value(z, as<Wide>{})); }
  }
}
