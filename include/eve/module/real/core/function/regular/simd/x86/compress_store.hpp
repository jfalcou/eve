//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once


namespace eve::detail
{
  template<real_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_(EVE_SUPPORTS(sse2_),
                    unsafe_type,
                    wide<T, N> v,
                    logical<wide<T, N>> mask,
                    Ptr ptr) noexcept
    requires (N() == 2 && sizeof(T) == 8)
  {
    return compress_store_(EVE_RETARGET(cpu_), unsafe_type{}, v, mask, ptr);
  }
}
