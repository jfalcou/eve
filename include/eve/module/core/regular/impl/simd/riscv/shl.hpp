//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
namespace eve::detail
{

template<plain_scalar_value T, callable_options O, typename N, integral_scalar_value U>
EVE_FORCEINLINE wide<T, N>
                shl_(EVE_REQUIRES(rvv_), O const&, wide<T, N> a, U s) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::float_) )
  {
    using i_t = typename wide<T, N>::template rebind<as_integer_t<T, unsigned>, N>;
    return shl(bit_cast(a, as<i_t> {}), s);
  }
  else return __riscv_vsll(a, s, N::value);
}
template<plain_scalar_value T, typename N, std::ptrdiff_t V, callable_options O>
EVE_FORCEINLINE auto
shl_(EVE_REQUIRES(rvv_), O const&, wide<T, N> a, index_t<V> const& s) noexcept
requires rvv_abi<abi_t<T, N>>
{
  return shl(a, V);
}
}
