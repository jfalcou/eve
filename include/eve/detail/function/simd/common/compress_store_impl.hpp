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
#include <eve/function/unsafe.hpp>
#include <eve/memory/pointer.hpp>

namespace eve::detail
{
  // permutation masks ------------------

  template <std::unsigned_integral T>
  EVE_FORCEINLINE constexpr auto pattern_4_elements(std::array<T, 8> idxs)
  {
    using row = std::array<T, 4>;

    return std::array {
      row{ idxs[3],       0,       0,       0 },  // 000
      row{ idxs[0], idxs[3],       0,       0 },  // 001
      row{ idxs[1], idxs[3],       0,       0 },  // 010
      row{ idxs[0], idxs[1], idxs[3],       0 },  // 011
      row{ idxs[2], idxs[3],       0,       0 },  // 100
      row{ idxs[0], idxs[2], idxs[3],       0 },  // 101
      row{ idxs[1], idxs[2], idxs[3],       0 },  // 110
      row{ idxs[0], idxs[1], idxs[2], idxs[3] },  // 111
    };
  }

  // See compress_store_num for explanation
  template <std::unsigned_integral T>
  EVE_FORCEINLINE constexpr auto pattern_8_elements(std::array<T, 8> idxs)
  {
    using row = std::array<T, 8>;

    std::array<row, 27> res = {};

    for (unsigned i = 0; i != 27; ++i)
    {
      unsigned number_of_9s = 0, number_of_3s = 0, number_of_1s = 0;
      unsigned base_3_value = i;

      if (base_3_value >= 9) ++number_of_9s, base_3_value -= 9;
      if (base_3_value >= 9) ++number_of_9s, base_3_value -= 9;
      if (base_3_value >= 3) ++number_of_3s, base_3_value -= 3;
      if (base_3_value >= 3) ++number_of_3s, base_3_value -= 3;
      if (base_3_value >= 1) ++number_of_1s, base_3_value -= 1;
      if (base_3_value >= 1) ++number_of_1s, base_3_value -= 1;

      auto* it = res[i].begin();
      if (number_of_1s) *it++ = idxs[0], --number_of_1s;
      if (number_of_1s) *it++ = idxs[1], --number_of_1s;
      if (number_of_3s) *it++ = idxs[2], --number_of_3s;
      if (number_of_3s) *it++ = idxs[3], --number_of_3s;
      if (number_of_9s) *it++ = idxs[4], --number_of_9s;
      if (number_of_9s) *it++ = idxs[5], --number_of_9s;
      *it++ = idxs[6];
      *it++ = idxs[7];
    }

    return res;
  }

  template <std::unsigned_integral T>
  constexpr auto idxs_bytes = [] {
    std::array<T, 8> res = {};

    for (unsigned i = 0; i != 8; ++i)
    {
      unsigned byte_idx = i * sizeof(T);

      if constexpr ( sizeof(T) == 4 )
      {
        res[i] = (byte_idx + 3) << 24 | (byte_idx + 2) << 16 | (byte_idx + 1) << 8 | byte_idx;
      }
      else if constexpr ( sizeof(T) == 2 )
      {
        res[i] = (byte_idx + 1) << 8 | byte_idx;
      }
      else if constexpr ( sizeof(T) == 1 )
      {
        res[i] = byte_idx;
      }
    }

    return res;
  }();

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
      return as_raw_pointer(ptr) + eve::count_true(mask);
    }
    else if constexpr ( !has_emulated_abi_v<wide<T, N>> && N() > 2 )
    {
      return compress_store_impl_aggregated(v, mask, ptr);
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

  template<relative_conditional_expr C, typename T, typename U, typename N, simd_compatible_ptr<wide<T, N>> Ptr>
  EVE_FORCEINLINE
  T* compress_store_impl_(EVE_SUPPORTS(cpu_),
                          C c,
                          wide<T, N> v,
                          logical<wide<U, N>> mask,
                          Ptr ptr) noexcept
  {
         if constexpr ( C::is_complete && !C::is_inverted ) return as_raw_pointer(ptr);
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
      auto* ptr_ = as_raw_pointer(ptr);

      for (int idx = offset; idx != offset + count; ++idx) {
        if (mask.get(idx)) *ptr_++ = v.get(idx);
      }

      return ptr_;
    }
  }
}
