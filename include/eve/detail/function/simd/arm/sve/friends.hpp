//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>

namespace eve::detail
{
template<real_value T, typename N>
EVE_FORCEINLINE auto
self_eq(wide<T, N> v, wide<T, N> w) noexcept -> as_logical_t<wide<T, N>>
requires sve_abi<abi_t<T, N>> { return svcmpeq(sve_true<T>(), v, w); }

template<real_value T, typename N>
EVE_FORCEINLINE auto
self_neq(wide<T, N> v, wide<T, N> w) noexcept -> as_logical_t<wide<T, N>>
requires sve_abi<abi_t<T, N>> { return svcmpne(sve_true<T>(), v, w); }

template<real_value T, typename N>
EVE_FORCEINLINE auto
self_lognot(logical<wide<T, N>> v) noexcept -> logical<wide<T, N>>
requires sve_abi<abi_t<T, N>> { return svnot_z(sve_true<T>(), v); }

template<real_value T, typename N>
EVE_FORCEINLINE auto
self_neq(logical<wide<T, N>> v, logical<wide<T, N>> w) noexcept -> logical<wide<T, N>>
requires sve_abi<abi_t<T, N>> { return sveor_z(sve_true<T>(), v, w); }

template<real_value T, typename N>
EVE_FORCEINLINE auto
self_eq(logical<wide<T, N>> v, logical<wide<T, N>> w) noexcept -> logical<wide<T, N>>
requires sve_abi<abi_t<T, N>> { return !(v != w); }
}
