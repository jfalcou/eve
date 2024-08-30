//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include <eve/conditional.hpp>
namespace eve::detail
{

template<relative_conditional_expr C, typename T, typename N, typename U>
EVE_FORCEINLINE auto
compress_(EVE_SUPPORTS(rvv_), C c, wide<T, N> v, logical<wide<U, N>> mask) noexcept
requires rvv_abi<abi_t<T, N>>
{
  auto                c_mask          = expand_mask(c, as<wide<T, N>> {});
  auto                formated_mask   = bit_cast(mask, as<logical<wide<T, N>>> {});
  logical<wide<T, N>> real_mask       = __riscv_vmand(c_mask, formated_mask, N::value);
  wide<T, N>          init            = make(as<wide<T, N>> {}, static_cast<T>(0));
  wide<T, N>          compressed      = __riscv_vcompress_tu(init, v, real_mask, N::value);
  auto                new_element_num = count_true(real_mask);
  kumi::tuple         cur {compressed, new_element_num};
  return kumi::tuple<decltype(cur)> {cur};
}
}
