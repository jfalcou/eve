//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/convert.hpp>
#include <eve/function/count_true.hpp>
#include <eve/function/unalign.hpp>

#include <eve/detail/function/compress_store_impl_switch.hpp>

#include <array>
#include <bit>

// sse2/sse3 ---------------------------------------------------------
// switch based implementation

namespace eve::detail
{
  template<relative_conditional_expr C, typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(sse2_),
                          C c,
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
    requires (current_api < ssse3)
  {
    return compress_store_impl_switch[c](v, mask, ptr);
  }
}
