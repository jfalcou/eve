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
#include <eve/detail/function/simd/common/swizzle_helpers.hpp>

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
         if constexpr ( !std::is_pointer_v<Ptr> ) return unsafe(compress_store)(v, mask, ptr.get());
    else if constexpr ( !has_emulated_abi_v<wide<T, N>> && N() == 2 )
    {
      auto to_left     = eve::slide_left( v, eve::index<1> );
      auto compressed  = eve::if_else[mask]( v, to_left );
      eve::store(compressed, ptr);
      return ptr + eve::count_true(mask);
    }
    else
    {
      detail::for_<0,1, N{}()>([&](auto idx) mutable
      {
        *ptr = v.get(idx());
        ptr += mask.get(idx());
      });
      return ptr;
    }
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE
  logical<T>*  compress_store_(EVE_SUPPORTS(cpu_),
                               unsafe_type,
                               logical<wide<T, N>> v,
                               logical<wide<T, N>> mask,
                               logical<T>* ptr) noexcept
  {
    auto* raw_ptr =
      unsafe(compress_store)(v.mask(), mask, (typename logical<T>::mask_type*) ptr);
    return (logical<T> *)raw_ptr;
  }
}
