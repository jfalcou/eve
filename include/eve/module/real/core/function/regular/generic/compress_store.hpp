//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/function/compress_store_impl.hpp>

namespace eve::detail
{
  template<relative_conditional_expr C, real_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_(EVE_SUPPORTS(cpu_),
                    C c,
                    unsafe_type,
                    wide<T, N> v,
                    logical<wide<T, N>> mask,
                    Ptr ptr) noexcept
  {
    return compress_store_impl(c, v, mask, ptr);
  }

  template<relative_conditional_expr C, decorator Decorator, real_scalar_value T, typename N, simd_compatible_ptr<logical<wide<T, N>>> Ptr>
  EVE_FORCEINLINE
  logical<T>*  compress_store_(EVE_SUPPORTS(cpu_),
                               C c,
                               Decorator d,
                               logical<wide<T, N>> v,
                               logical<wide<T, N>> mask,
                               Ptr ptr) noexcept
  {
    auto* raw_ptr = compress_store(c, d, v.mask(), mask, ptr_cast<typename logical<T>::mask_type>(ptr));
    return (logical<T> *)raw_ptr;
  }

  template <decorator Decorator, simd_value T, simd_compatible_ptr<T> Ptr>
  EVE_FORCEINLINE
  auto compress_store_(EVE_SUPPORTS(cpu_),
                       Decorator d,
                       T v,
                       logical<T> mask,
                       Ptr ptr) noexcept
  {
    return compress_store(ignore_none, d, v, mask, ptr);
  }

  template <decorator Decorator, simd_value T, simd_compatible_ptr<T> Ptr>
  EVE_FORCEINLINE
  auto compress_store_(EVE_SUPPORTS(cpu_),
                       Decorator d,
                       logical<T> v,
                       logical<T> mask,
                       Ptr ptr) noexcept
  {
    return compress_store(ignore_none, d, v, mask, ptr);
  }
}
