//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>

namespace eve::detail
{

template<signed_scalar_value T, typename N>
EVE_FORCEINLINE auto self_negate(wide<T,N> const& v) noexcept  -> wide<T, N>
requires sve_abi<abi_t<T, N>>
{
  return svneg_x(sve_true<T>(), v);
}

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_eq(wide<T, N> v, wide<T, N> w) noexcept -> as_logical_t<wide<T, N>>
requires sve_abi<abi_t<T, N>> { return svcmpeq(sve_true<T>(), v, w); }

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_neq(wide<T, N> v, wide<T, N> w) noexcept -> as_logical_t<wide<T, N>>
requires sve_abi<abi_t<T, N>> { return svcmpne(sve_true<T>(), v, w); }

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_less(wide<T, N> v, wide<T, N> w) noexcept -> as_logical_t<wide<T, N>>
requires sve_abi<abi_t<T, N>> { return svcmplt(sve_true<T>(), v, w); }

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_greater(wide<T, N> v, wide<T, N> w) noexcept -> as_logical_t<wide<T, N>>
requires sve_abi<abi_t<T, N>> { return svcmpgt(sve_true<T>(), v, w); }

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_leq(wide<T, N> v, wide<T, N> w) noexcept -> as_logical_t<wide<T, N>>
requires sve_abi<abi_t<T, N>> { return svcmple(sve_true<T>(), v, w); }

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_geq(wide<T, N> v, wide<T, N> w) noexcept -> as_logical_t<wide<T, N>>
requires sve_abi<abi_t<T, N>> { return svcmpge(sve_true<T>(), v, w); }


// ---------------------------------------------------------

template<typename T, typename U, typename N>
EVE_FORCEINLINE auto
self_logand(sve_ const&, logical<wide<T,N>> v, logical<wide<U,N>> w) noexcept -> logical<wide<T, N>>
requires(sve_abi<abi_t<T, N>> || sve_abi<abi_t<U, N>>)
{
  if constexpr(!is_aggregated_v<abi_t<T, N>>)
  {
    callable_object<tag::convert_> const cvt{};
    return svmov_z(v, cvt(w, as<logical<T>>{}));
  }
  else
  {
    auto[lv,hv] = v.slice();
    auto[lw,hw] = w.slice();
    return logical<wide<T, N>>{ lv && lw, hv && hw};
  }
}

template<typename T, typename U, typename N>
EVE_FORCEINLINE auto
self_logor(sve_ const&, logical<wide<T,N>> v, logical<wide<U,N>> w) noexcept -> logical<wide<T, N>>
requires(sve_abi<abi_t<T, N>> || sve_abi<abi_t<U, N>>)
{
  if constexpr(!is_aggregated_v<abi_t<T, N>>)
  {
    callable_object<tag::convert_> const cvt{};
    return svorr_z(sve_true<T>(), v, cvt(w, as<logical<T>>{}));
  }
  else
  {
    auto[lv,hv] = v.slice();
    auto[lw,hw] = w.slice();
    return logical<wide<T, N>>{ lv || lw, hv || hw};
  }
}

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_lognot(logical<wide<T, N>> v) noexcept -> logical<wide<T, N>>
requires sve_abi<abi_t<T, N>> { return svnot_z(sve_true<T>(), v); }

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_neq(logical<wide<T, N>> v, logical<wide<T, N>> w) noexcept -> logical<wide<T, N>>
requires sve_abi<abi_t<T, N>> { return sveor_z(sve_true<T>(), v, w); }

template<arithmetic_scalar_value T, typename N>
EVE_FORCEINLINE auto
self_eq(logical<wide<T, N>> v, logical<wide<T, N>> w) noexcept -> logical<wide<T, N>>
requires sve_abi<abi_t<T, N>> { return !(v != w); }
}
