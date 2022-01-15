//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/convert.hpp>
#include <eve/detail/function/compress_store_swizzle_mask_num.hpp>
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

// ssse3 -> avx2 (no bmi) ---------------------------------------------------------
// mask based (@aqrit from StackOverflow's idea)
namespace eve::detail
{
  template<relative_conditional_expr C, typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(sse4_1_),
                          C c,
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
    requires x86_abi<abi_t<T, N>> && ( N() == 4 )
  {
    return compress_store_impl_using_masks(c, v, mask, ptr);
  }

  template<typename T, typename U, typename N, typename Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(sse4_1_),
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
    requires x86_abi<abi_t<T, N>> && ( N() == 4 )
  {
    if constexpr ( N() == 4 && sizeof(T) == 8 && current_api == avx  )
    {
      return compress_store_impl_aggregated(v, mask, ptr);
    }
    else return compress_store_impl[eve::ignore_none](v, mask, ptr);
  }

  template<typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(ssse3_),
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
    requires x86_abi<abi_t<T, N>> && (current_api <= avx2) && ( N() == 8 )
  {
    return compress_store_impl_using_masks(eve::ignore_none, v, mask, ptr);
  }

  template<typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(ssse3_),
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
    requires x86_abi<abi_t<T, N>> && (current_api <= avx2) && ( N() == 16 )
  {
    return compress_store_impl_using_masks(eve::ignore_none, v, mask, ptr);
  }
}
