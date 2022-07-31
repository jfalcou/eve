//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
template<typename T, typename U, typename N>
EVE_FORCEINLINE as_logical_t<wide<T, N>>
self_logand(sve_fixed_ const&, logical<wide<T, N>> v, logical<wide<U, N>> w) noexcept
{
  static_assert(sizeof(T) == sizeof(U), "not implemented");
  return svmov_z(v, w);
}

template<typename T, typename U, typename N>
EVE_FORCEINLINE as_logical_t<wide<T, N>>
self_logor(sve_fixed_ const&, logical<wide<T, N>> v, logical<wide<U, N>> w) noexcept
{
  static_assert(sizeof(T) == sizeof(U), "not implemented");
  return svorr_z(svptrue_b8(), v, w);
}

template<typename T, typename U, typename N>
EVE_FORCEINLINE as_logical_t<wide<T, N>>
self_neq(sve_fixed_ const&, logical<wide<T, N>> v, logical<wide<U, N>> w) noexcept
{
  static_assert(sizeof(T) == sizeof(U), "not implemented");
  return sveor_z(svptrue_b8(), v, w);
}

//================================================================================================
template<real_value T, typename N>
EVE_FORCEINLINE as_logical_t<wide<T, N>>
                self_less(wide<T, N> v, wide<T, N> w) noexcept requires sve_abi<abi_t<T, N>>
{
  return svcmplt(svptrue_b8(), v, w);
}

template<real_value T, typename N>
EVE_FORCEINLINE as_logical_t<wide<T, N>>
                self_greater(wide<T, N> v, wide<T, N> w) noexcept requires sve_abi<abi_t<T, N>>
{
  return svcmpgt(svptrue_b8(), v, w);
}

template<real_value T, typename N>
EVE_FORCEINLINE as_logical_t<wide<T, N>>
                self_geq(wide<T, N> v, wide<T, N> w) noexcept requires sve_abi<abi_t<T, N>>
{
  return svcmpge(svptrue_b8(), v, w);
}

template<real_value T, typename N>
EVE_FORCEINLINE as_logical_t<wide<T, N>>
                self_leq(wide<T, N> v, wide<T, N> w) noexcept requires sve_abi<abi_t<T, N>>
{
  return svcmple(svptrue_b8(), v, w);
}

}
