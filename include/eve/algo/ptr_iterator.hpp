//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/algo/iterator_helpers.hpp>

#include <eve/function/load.hpp>
#include <eve/function/store.hpp>
#include <eve/memory/aligned_ptr.hpp>

namespace eve::algo
{
  template <typename T, typename Cardinal>
  struct unaligned_ptr_iterator : operations_with_distance
  {
    using cardinal = Cardinal;

    unaligned_ptr_iterator() = default;
    explicit unaligned_ptr_iterator(T* ptr) : ptr(ptr) {}

    unaligned_ptr_iterator unaligned() const { return *this; }

    unaligned_ptr_iterator& operator+=(std::ptrdiff_t n) { ptr += n; return *this; }
    friend std::ptrdiff_t   operator-(unaligned_ptr_iterator x, unaligned_ptr_iterator y) { return x.ptr - y.ptr; }

    auto operator<=>(unaligned_ptr_iterator const&) const = default;

    T* ptr;
  };

  template <typename T, typename Cardinal>
  struct aligned_ptr_iterator : operations_with_distance, forward_to_unaligned
  {
    using cardinal = Cardinal;
    using aligned_ptr_type = eve::aligned_ptr<T, Cardinal{}() * sizeof(T)>;

    aligned_ptr_iterator();
    explicit aligned_ptr_iterator(aligned_ptr_type ptr) : ptr{ptr} {}

    auto unaligned() const { return unaligned_ptr_iterator<T, Cardinal>{ptr.get()}; }
    aligned_ptr_iterator& operator+=(std::ptrdiff_t n) { ptr += n; return *this; }

    aligned_ptr_type ptr;
  };
}

// TODO: after #683 replace with a proper hook
namespace eve::detail
{
  template <relative_conditional_expr C, typename T, typename N>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), C cond, algo::aligned_ptr_iterator<T, N> it) {
    return eve::load[cond](it.ptr, N{});
  }

  template <typename T, typename N>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), algo::aligned_ptr_iterator<T, N> it) {
    return eve::load(it.ptr, N{});
  }


  template <relative_conditional_expr C, typename T, typename N>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), C cond, algo::unaligned_ptr_iterator<T, N> it) {
    return eve::load[cond](it.ptr, N{});
  }

  template <typename T, typename N>
  EVE_FORCEINLINE auto load_(EVE_SUPPORTS(cpu_), algo::unaligned_ptr_iterator<T, N> it) {
    return eve::load(it.ptr, N{});
  }

  // ---------------------------
  // store, we need to restrict the wide type but we can do that when the customization
  // is avaliable.
  template <relative_conditional_expr C, typename Wide, typename T, typename N>
    requires std::invocable<decltype(eve::store),
                            C,
                            Wide,
                            typename algo::aligned_ptr_iterator<T, N>::aligned_ptr_type>
  EVE_FORCEINLINE auto store_(EVE_SUPPORTS(cpu_), C cond, Wide wide, algo::aligned_ptr_iterator<T, N> it) {
    return eve::store[cond](wide, it.ptr);
  }

  template <typename Wide, typename T, typename N>
    requires std::invocable<decltype(eve::store),
                            Wide,
                            typename algo::aligned_ptr_iterator<T, N>::aligned_ptr_type>
  EVE_FORCEINLINE auto store_(EVE_SUPPORTS(cpu_), Wide wide, algo::aligned_ptr_iterator<T, N> it) {
    return eve::store(wide, it.ptr);
  }

  template <relative_conditional_expr C, typename Wide, typename T, typename N>
    requires std::invocable<decltype(eve::store), C, Wide, T*>
  EVE_FORCEINLINE auto store_(EVE_SUPPORTS(cpu_), C cond, Wide wide, algo::unaligned_ptr_iterator<T, N> it) {
    return eve::store[cond](wide, it.ptr);
  }

  template <typename Wide, typename T, typename N>
    requires std::invocable<decltype(eve::store), Wide, T*>
  EVE_FORCEINLINE auto store_(EVE_SUPPORTS(cpu_), Wide wide, algo::unaligned_ptr_iterator<T, N> it) {
    return eve::store(wide, it.ptr);
  }
}
