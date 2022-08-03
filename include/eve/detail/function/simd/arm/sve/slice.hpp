//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/arch/arm/sve/sve_true.hpp>

namespace eve::detail
{
//================================================================================================
// Single slice
//================================================================================================
template<typename T, typename N, typename Slice>
EVE_FORCEINLINE wide<T, typename N::split_type>
                slice(wide<T, N> a, Slice) noexcept requires sve_abi<abi_t<T, N>>
{
  if constexpr( !Slice::value ) return a.storage();
  else return svext(a, a, N::value / 2);
}

template<typename T, typename N, typename Slice>
EVE_FORCEINLINE logical<wide<T, typename N::split_type>>
                slice(logical<wide<T, N>> a, Slice) noexcept requires sve_abi<abi_t<T, N>>
{
  if constexpr( !Slice::value ) return a.storage();
  else
  {
    auto bits = a.bitmask();
    return svcmpne(sve_true<T>(), slice(bits, Slice{}), 0);
  }
}

//================================================================================================
// Both slice
//================================================================================================
template<typename T, typename N>
EVE_FORCEINLINE auto
slice(wide<T, N> a) noexcept requires sve_abi<abi_t<T, N>>
{
  std::array<wide<T, typename N::split_type>, 2> that {slice(a, lower_), slice(a, upper_)};
  return that;
}

template<typename T, typename N>
EVE_FORCEINLINE auto
slice(logical<wide<T, N>> a) noexcept requires sve_abi<abi_t<T, N>>
{
  std::array<logical<wide<T, typename N::split_type>>, 2> that {slice(a, lower_), slice(a, upper_)};
  return that;
}

}
