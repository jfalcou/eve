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
  template<real_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_(EVE_SUPPORTS(cpu_),
                    unsafe_type,
                    wide<T, N> v,
                    logical<wide<T, N>> mask,
                    Ptr ptr) noexcept
  {
    return compress_store_impl(v, mask, ptr);
  }

  template<real_scalar_value T, typename N, simd_compatible_ptr<logical<wide<T, N>>> Ptr>
  EVE_FORCEINLINE
  logical<T>*  compress_store_(EVE_SUPPORTS(cpu_),
                               unsafe_type,
                               logical<wide<T, N>> v,
                               logical<wide<T, N>> mask,
                               Ptr ptr) noexcept
  {
    auto* raw_ptr =
      unsafe(compress_store)(v.mask(), mask, ptr_cast<typename logical<T>::mask_type>(ptr));
    return (logical<T> *)raw_ptr;
  }
}
