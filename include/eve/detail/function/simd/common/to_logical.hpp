//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/forward.hpp>
#include <bitset>

namespace eve::detail
{
  //================================================================================================
  // Wide to Logical
  //================================================================================================
  template<typename T, typename N>
  EVE_FORCEINLINE auto to_logical( wide<T,N> const& v ) noexcept
  {
    if constexpr( is_aggregated_v<abi_t<T, N>> )
    {
      as_logical_t<wide<T,N>> that;
      that.storage().for_each( [](auto& s, auto const& o)  { s = to_logical(o); }, v );
      return that;
    }
    else
    {
      return map( [](auto e) { return logical<T>(e!=0); }, v );
    }
  }

  template<value T> EVE_FORCEINLINE auto to_logical( logical<T> v ) noexcept
  {
    return v;
  }

  template<scalar_value T> EVE_FORCEINLINE auto to_logical( T v ) noexcept
  {
    return logical<T>(v);
  }
}
