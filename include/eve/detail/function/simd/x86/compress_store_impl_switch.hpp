//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/convert.hpp>

namespace eve::detail
{

  template<relative_conditional_expr C, typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_switch_(EVE_SUPPORTS(sse2_),
                                 C c,
                                 wide<T, N> v,
                                 logical<wide<U, N>> mask,
                                 Ptr ptr) noexcept
    requires (sizeof(U) == 2)
  {
    return compress_store_impl_switch(c, v, convert(mask, as<logical<std::uint8_t>>{}), ptr);
  }
}
