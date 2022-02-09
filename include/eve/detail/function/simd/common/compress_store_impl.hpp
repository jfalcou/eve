//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/count_true.hpp>
#include <eve/function/slide_left.hpp>
#include <eve/function/store.hpp>
#include <eve/function/unalign.hpp>
#include <eve/function/unsafe.hpp>
#include <eve/memory/pointer.hpp>

#include <eve/detail/compress/compress.hpp>

namespace eve::detail
{
  template<relative_conditional_expr C, typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  unaligned_t<Ptr> compress_store_impl_(EVE_SUPPORTS(cpu_),
                                        C c,
                                        wide<T, N> v,
                                        logical<wide<U, N>> mask,
                                        Ptr ptr) noexcept
  {
    if constexpr ( has_emulated_abi_v<wide<T, N>> )
    {
      auto offset = c.offset(as(v));
      auto count  = c.count(as(v));
      auto* ptr_ = unalign(ptr);

      for (int idx = offset; idx != (int)(offset + count); ++idx) {
        if (mask.get(idx)) *ptr_++ = v.get(idx);
      }

      return ptr_;
    }
    else
    {
      auto parts = compress[c](v, mask);

      auto uptr = unalign(ptr);

      kumi::for_each([&](auto part_count) mutable {
        auto [part, count] = part_count;
        eve::store(part, uptr);
        uptr += count;
      }, parts);

      return uptr;
    }
  }

  template<real_scalar_value T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  unaligned_t<Ptr> compress_store_impl_(EVE_SUPPORTS(cpu_),
                                        wide<T, N> v,
                                        logical<wide<U, N>> mask,
                                        Ptr ptr) noexcept
  {
    return compress_store_impl(ignore_none, v, mask, ptr);
  }
}
