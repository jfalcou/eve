//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/category.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
template<typename N, real_scalar_value U>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(vsx_),
                             wide<double, N> v,
                             as<U> const                   &tgt) noexcept requires ppc_abi<abi_t<double, N>>
{
  constexpr auto c_o = categorize<wide<U, N>>();
  auto           r   = v.storage();

  if constexpr( c_o == category::int64x2 ) return vec_cts(r, 0);
  else if constexpr( c_o == category::uint64x2 ) return vec_ctu(r, 0);
  else return map(convert, v, tgt);
}

template<typename N, real_scalar_value U>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(vmx_),
                             wide<float, N> v,
                             as<U> const                  &tgt) noexcept requires ppc_abi<abi_t<float, N>>
{
  constexpr auto c_o = categorize<wide<U, N>>();
  auto           r   = v.storage();

  if constexpr( c_o == category::int32x4 ) return vec_cts(r, 0);
  else if constexpr( c_o == category::uint32x4 ) return vec_ctu(r, 0);
  else return map(convert, v, tgt);
}

template<integral_scalar_value T, typename N, real_scalar_value U>
EVE_FORCEINLINE wide<U, N>
                convert_impl(EVE_SUPPORTS(vmx_),
                             wide<T, N>   v,
                             as<U> const                &tgt) noexcept requires ppc_abi<abi_t<T, N>>
{
  if constexpr( std::is_floating_point_v<U> )
  {
    if constexpr( sizeof(T) == sizeof(U) ) return vec_ctf(v.storage(), 0);
    else return convert(convert(v, as<as_integer_t<U>> {}), tgt);
  }
  else if constexpr( std::is_integral_v<U> )
  {
    // k->2.k integral conversion use interleave
    if constexpr( sizeof(U) / sizeof(T) == 2 ) return convert_integers_interleave(v, tgt);
    // k->2^-n.k integral conversion use computed vec_perm
    else if constexpr( sizeof(T) / sizeof(U) >= 2 ) return convert_integers_shuffle(v, tgt);
    // otherwise, go down convert chains
    else return convert_integers_chain(v, tgt);
  }
}
}
