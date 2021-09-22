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

namespace eve::detail
{
  template<relative_conditional_expr C,
           real_scalar_value T, real_scalar_value U, typename N,
           simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_(EVE_SUPPORTS(cpu_),
                    C c,
                    safe_type,
                    wide<T, N> v,
                    logical<wide<U, N>> mask,
                    Ptr ptr) noexcept
  {
    alignas(sizeof(v)) std::array<element_type_t<T>, N{}()> buffer;
    T* up_to = compress_store_impl(c, v, mask, buffer.begin());
    std::ptrdiff_t n = up_to - buffer.begin();

    auto* out = as_raw_pointer(ptr) + c.offset(as(mask));

    wide<T, N> compressed{aligned_ptr<T, N>{buffer.begin()}};

    store[keep_first(n)](compressed, out);
    return out + n;
  }

  template<relative_conditional_expr C,
           real_scalar_value T, real_scalar_value U, typename N,
           simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_(EVE_SUPPORTS(cpu_),
                     C c,
                     unsafe_type,
                     wide<T, N> v,
                     logical<wide<U, N>> mask,
                     Ptr ptr) noexcept
  {
    if (!C::is_complete) return safe(compress_store[c])(v, mask, ptr);
    else                 return compress_store_impl(c, v, mask, ptr);
  }

  template< relative_conditional_expr C, decorator Decorator
          , kumi::product_type T, real_scalar_value U, typename N
          , data_source Ptr
          >
  EVE_FORCEINLINE
  auto compress_store_(EVE_SUPPORTS(cpu_),
                       C c,
                       Decorator d,
                       wide<T, N> vs,
                       logical<wide<U, N>> mask,
                       Ptr ptrs) noexcept
  {
    return kumi::map ( [&] (auto v, auto p) {
      return compress_store(c, d, v, mask, p);
    }, vs.storage(), ptrs);
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
