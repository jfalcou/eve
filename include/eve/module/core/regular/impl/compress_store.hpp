//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/function/compress_store_impl.hpp>

#include <eve/detail/kumi.hpp>

#include <eve/function/unalign.hpp>
#include <eve/function/safe.hpp>
#include <eve/memory/stack_buffer.hpp>

namespace eve::detail
{
  template<relative_conditional_expr C,
           scalar_value T, real_scalar_value U, typename N,
           simd_compatible_ptr<wide<T, N>> Ptr>
    requires (!has_store_equivalent<wide<T, N>, Ptr>)
  EVE_FORCEINLINE
  unaligned_t<Ptr> compress_store_(EVE_SUPPORTS(cpu_),
                    C c,
                    safe_type,
                    wide<T, N> v,
                    logical<wide<U, N>> mask,
                    Ptr ptr) noexcept
  {
    if ( C::is_complete && !C::is_inverted ) return unalign(ptr);
    else
    {
      stack_buffer<wide<T, N>> buffer;
      unaligned_t<Ptr> up_to = compress_store_impl(c, v, mask, buffer.ptr());
      std::ptrdiff_t n = up_to - buffer.ptr();

      unaligned_t<Ptr> out = unalign(ptr) + c.offset(as(mask));

      wide<T, N> compressed{buffer.ptr()};

      store[keep_first(n)](compressed, out);
      return out + n;
    }
  }

  template<relative_conditional_expr C,
           scalar_value T, real_scalar_value U, typename N,
           simd_compatible_ptr<wide<T, N>> Ptr>
    requires (!has_store_equivalent<wide<T, N>, Ptr>)
  EVE_FORCEINLINE
  unaligned_t<Ptr> compress_store_(EVE_SUPPORTS(cpu_),
                     C c,
                     unsafe_type,
                     wide<T, N> v,
                     logical<wide<U, N>> mask,
                     Ptr ptr) noexcept
  {
    if ( !C::is_complete || !C::is_inverted ) return safe(compress_store[c])(v, mask, ptr);
    else                                      return compress_store_impl(c, v, mask, ptr);
  }

  template <relative_conditional_expr C,
            decorator Decorator, simd_value T, simd_value U, typename Ptr>
    requires has_store_equivalent<T, Ptr>
  EVE_FORCEINLINE
  unaligned_t<Ptr> compress_store_(EVE_SUPPORTS(cpu_),
                                   C c,
                                   Decorator d,
                                   T v,
                                   logical<U> mask,
                                   Ptr ptr) noexcept
  {
    auto [v1, ptr1] = store_equivalent(v, ptr);
    auto res1 = compress_store(c, d, v1, mask, ptr1);
    return unalign(ptr) + (res1 - ptr1);
  }

  template<relative_conditional_expr C, decorator Decorator,
           real_scalar_value T, real_scalar_value U, typename N,
           simd_compatible_ptr<logical<wide<T, N>>> Ptr>
  EVE_FORCEINLINE
  logical<T>*  compress_store_(EVE_SUPPORTS(cpu_),
                               C c,
                               Decorator d,
                               logical<wide<T, N>> v,
                               logical<wide<U, N>> mask,
                               Ptr ptr) noexcept
  {
    auto* raw_ptr = compress_store(c, d, v.mask(), mask, ptr_cast<typename logical<T>::mask_type>(ptr));
    return (logical<T> *)raw_ptr;
  }

  template <decorator Decorator, simd_value T, simd_value U, typename Ptr>
  EVE_FORCEINLINE
  auto compress_store_(EVE_SUPPORTS(cpu_),
                       Decorator d,
                       T v,
                       logical<U> mask,
                       Ptr ptr) noexcept
    -> decltype(compress_store(ignore_none, d, v, mask, ptr))
  {
    return compress_store(ignore_none, d, v, mask, ptr);
  }

  template <decorator Decorator, simd_value T, simd_value U, typename Ptr>
  EVE_FORCEINLINE
  auto compress_store_(EVE_SUPPORTS(cpu_),
                       Decorator d,
                       logical<T> v,
                       logical<U> mask,
                       Ptr ptr) noexcept
    -> decltype(compress_store(ignore_none, d, v, mask, ptr))
  {
    return compress_store(ignore_none, d, v, mask, ptr);
  }
}
