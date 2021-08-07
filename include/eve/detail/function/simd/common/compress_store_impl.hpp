//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/count_true.hpp>
#include <eve/function/slide_left.hpp>
#include <eve/function/store.hpp>
#include <eve/function/unsafe.hpp>
#include <eve/memory/pointer.hpp>

namespace eve::detail
{
  template<relative_conditional_expr Cond, real_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_aggregated(Cond c,
                                    wide<T, N> v,
                                    logical<wide<T, N>> mask,
                                    Ptr ptr)
  {
    auto [l, h] = v.slice();
    auto [ml, mh] = mask.slice();

    T* ptr1 = compress_store_impl(c, l, ml, ptr);
    return compress_store_impl(c, h, mh, ptr1);
  }

  template<relative_conditional_expr Cond, real_scalar_value T, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(cpu_),
                          Cond c,
                          wide<T, N> v,
                          logical<wide<T, N>> mask,
                          Ptr ptr) noexcept
  {
    if constexpr ( !has_emulated_abi_v<wide<T, N>> && N() == 2 )
    {
      auto to_left     = eve::slide_left( v, eve::index<1> );
      auto compressed  = eve::if_else[mask]( v, to_left );
      eve::store(compressed, ptr);
      return as_raw_pointer(ptr) + eve::count_true(mask);
    }
    else if constexpr ( !has_emulated_abi_v<wide<T, N>> && N() > 2 )
    {
      return compress_store_impl_aggregated(c, v, mask, ptr);
    }
    else
    {
      auto* ptr_ = as_raw_pointer(ptr);
      detail::for_<0,1, N{}()>([&](auto idx) mutable
      {
        *ptr_ = v.get(idx());
        ptr_ += mask.get(idx());
      });
      return ptr_;
    }
  }
}
