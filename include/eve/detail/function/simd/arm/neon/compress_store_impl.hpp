//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/function/compress_store_swizzle_mask_num.hpp>
#include <eve/detail/function/byte_16_runtime_shuffle.hpp>

#include <eve/function/if_else.hpp>
#include <eve/function/slide_left.hpp>

namespace eve::detail
{
  template<relative_conditional_expr C, typename T, typename U, typename N, typename Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(neon128_),
                          C c,
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
  {
    return compress_store_impl_using_masks(c, v, mask, ptr);
  }
}
