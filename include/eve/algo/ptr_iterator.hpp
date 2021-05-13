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
    using wide_value_type = eve::wide<std::remove_const_t<T>, cardinal>;

    unaligned_ptr_iterator() = default;
    explicit unaligned_ptr_iterator(T* ptr) : ptr(ptr) {}

    unaligned_ptr_iterator unaligned() const { return *this; }

    unaligned_ptr_iterator& operator+=(std::ptrdiff_t n) { ptr += n; return *this; }
    friend std::ptrdiff_t   operator-(unaligned_ptr_iterator x, unaligned_ptr_iterator y) { return x.ptr - y.ptr; }

    auto operator<=>(unaligned_ptr_iterator const&) const = default;

    template <relative_conditional_expr C>
    friend wide_value_type tagged_dispatch( eve::tag::load_, C cond, unaligned_ptr_iterator self )
    {
      return eve::load[cond](self.ptr, cardinal{});
    }

    friend wide_value_type tagged_dispatch( eve::tag::load_, unaligned_ptr_iterator self )
    {
      return eve::load(self.ptr, cardinal{});
    }

    template <relative_conditional_expr C>
    friend void tagged_dispatch(
      eve::tag::store_, C cond, wide_value_type v, unaligned_ptr_iterator self )
      requires (!std::is_const_v<T>)
    {
      eve::store[cond](v, self.ptr);
    }

    friend void tagged_dispatch( eve::tag::store_, wide_value_type v, unaligned_ptr_iterator self )
      requires ( !std::is_const_v<T> )
    {
      eve::store(v, self.ptr);
    }

    T* ptr;
  };

  template <typename T, typename Cardinal>
  struct aligned_ptr_iterator : operations_with_distance, forward_to_unaligned
  {
    using cardinal = Cardinal;
    using wide_value_type = eve::wide<std::remove_const_t<T>, cardinal>;

    using aligned_ptr_type = eve::aligned_ptr<T, Cardinal{}() * sizeof(T)>;

    aligned_ptr_iterator();
    explicit aligned_ptr_iterator(aligned_ptr_type ptr) : ptr{ptr} {}

    auto unaligned() const { return unaligned_ptr_iterator<T, Cardinal>{ptr.get()}; }
    aligned_ptr_iterator& operator+=(std::ptrdiff_t n) { ptr += n; return *this; }

    template <relative_conditional_expr C>
    friend wide_value_type tagged_dispatch( eve::tag::load_, C cond, aligned_ptr_iterator self )
    {
      return eve::load[cond](self.ptr, cardinal{});
    }

    friend wide_value_type tagged_dispatch( eve::tag::load_, aligned_ptr_iterator self )
    {
      return eve::load(self.ptr, cardinal{});
    }

    template <relative_conditional_expr C>
    friend void tagged_dispatch(
      eve::tag::store_, C cond, wide_value_type v, aligned_ptr_iterator self )
      requires ( !std::is_const_v<T> )
    {
      return eve::store[cond](v, self.ptr);
    }

    friend void tagged_dispatch( eve::tag::store_, wide_value_type v, aligned_ptr_iterator self )
      requires ( !std::is_const_v<T> )
    {
      return eve::store(v, self.ptr);
    }

    aligned_ptr_type ptr;
  };
}
