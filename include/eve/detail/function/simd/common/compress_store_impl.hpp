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

#include <eve/detail/function/compress_using_masks.hpp>

namespace eve::detail
{
  // generic impl ------------------

  template<real_scalar_value T, typename N, typename U, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_aggregated(wide<T, N> v,
                                    logical<wide<U, N>> mask,
                                    Ptr ptr)
  {
    auto [l, h] = v.slice();
    auto [ml, mh] = mask.slice();

    T* ptr1 = compress_store_impl(l, ml, ptr);
    return compress_store_impl(h, mh, ptr1);
  }

  template<real_scalar_value T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(cpu_),
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
  {
    if constexpr ( !has_emulated_abi_v<wide<T, N>> && N() == 2 )
    {
      auto to_left     = eve::slide_left( v, eve::index<1> );
      auto compressed  = eve::if_else[mask]( v, to_left );
      eve::store(compressed, ptr);
      return unalign(ptr) + eve::count_true(mask);
    }
    else if constexpr ( !has_emulated_abi_v<wide<T, N>> && N() > 2 )
    {
      return compress_store_impl_aggregated(v, mask, ptr);
    }
    else
    {
      auto* ptr_ = unalign(ptr);
      detail::for_<0,1, N{}()>([&](auto idx) mutable
      {
        *ptr_ = v.get(idx());
        ptr_ += mask.get(idx());
      });
      return ptr_;
    }
  }

  template<relative_conditional_expr C, typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(cpu_),
                          C c,
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
  {
         if constexpr ( C::is_complete && !C::is_inverted ) return unalign(ptr);
    else if constexpr ( C::is_complete )                    return compress_store_impl(v, mask, ptr);
    else if constexpr ( !has_emulated_abi_v<wide<T, N>> )
    {
      mask = mask && c.mask(as(mask));
      return compress_store_impl(v, mask, ptr);
    }
    else
    {
      auto offset = c.offset(as(v));
      auto count  = c.count(as(v));
      auto* ptr_ = unalign(ptr);

      for (int idx = offset; idx != offset + count; ++idx) {
        if (mask.get(idx)) *ptr_++ = v.get(idx);
      }

      return ptr_;
    }
  }
}
