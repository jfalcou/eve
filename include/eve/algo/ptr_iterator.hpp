//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/iterator_helpers.hpp>

#include <eve/function/load.hpp>
#include <eve/function/store.hpp>
#include <eve/memory/aligned_ptr.hpp>

namespace eve::algo
{
  template <typename T, typename Cardinal>
  struct aligned_ptr_iterator;

  template <typename T, typename Cardinal>
  struct unaligned_ptr_iterator : operations_with_distance
  {
    using value_type      = std::remove_const_t<T>;
    using wv_type = eve::wide<value_type, Cardinal>;

    unaligned_ptr_iterator() = default;
    explicit unaligned_ptr_iterator(T* ptr) : ptr(ptr) {}

    unaligned_ptr_iterator unaligned() const { return *this; }

    auto previous_partially_aligned() const
    {
      return aligned_ptr_iterator<T, Cardinal>{eve::previous_aligned_address(ptr, Cardinal{})};
    }

    static Cardinal iterator_cardinal() { return {}; }

    template <typename _Cardinal>
    auto cardinal_cast(_Cardinal) const { return unaligned_ptr_iterator<T, _Cardinal>{ptr}; }

    auto& operator*() const { return *ptr; }

    unaligned_ptr_iterator& operator+=(std::ptrdiff_t n) { ptr += n; return *this; }
    friend std::ptrdiff_t   operator-(unaligned_ptr_iterator x, unaligned_ptr_iterator y) { return x.ptr - y.ptr; }

    bool operator==(unaligned_ptr_iterator const &x) const { return ptr == x.ptr; }
    auto operator<=>(unaligned_ptr_iterator const &x) const { return ptr <=> x.ptr; }

    template< relative_conditional_expr C, decorator S>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::load_, C const& c, S const& s
                                , eve::as<wv_type> const&, unaligned_ptr_iterator self
                                )
    {
      return eve::load(c, s, self.ptr, Cardinal{});
    }

    template <relative_conditional_expr C>
    EVE_FORCEINLINE friend void tagged_dispatch(
      eve::tag::store_, C cond, wv_type v, unaligned_ptr_iterator self )
      requires (!std::is_const_v<T>)
    {
      eve::store[cond](v, self.ptr);
    }

    EVE_FORCEINLINE friend void tagged_dispatch( eve::tag::store_, wv_type v, unaligned_ptr_iterator self )
      requires ( !std::is_const_v<T> )
    {
      eve::store(v, self.ptr);
    }

    template <relative_conditional_expr C, decorator Decorator, typename U>
      requires ( !std::is_const_v<T> )
    EVE_FORCEINLINE friend auto tagged_dispatch(
      eve::tag::compress_store_, C c, Decorator d, wv_type v,
      logical<wide<U, Cardinal>> m, unaligned_ptr_iterator self)
    {
      return unaligned_ptr_iterator{eve::compress_store(c, d, v, m, self.ptr)};
    }

    T* ptr;
  };

  template <typename T, typename Cardinal>
  struct aligned_ptr_iterator : operations_with_distance
  {
    using value_type        = std::remove_const_t<T>;
    using aligned_ptr_type  = eve::aligned_ptr<T, Cardinal>;
    using wv_type   = eve::wide<value_type, Cardinal>;

    aligned_ptr_iterator() = default;
    explicit aligned_ptr_iterator(aligned_ptr_type ptr) : ptr{ptr} {}

    // Need this for totally ordered.
    operator unaligned_ptr_iterator<T, Cardinal>() const {
      return unaligned_ptr_iterator<T, Cardinal>{ptr.get()};
    }

    auto& operator*() const { return *ptr; }
    auto get() const { return ptr.get(); }
    auto unaligned() const { return unaligned_ptr_iterator<T, Cardinal>{ptr.get()}; }
    auto previous_partially_aligned() const { return *this; }

    static Cardinal iterator_cardinal() { return {}; }

    template <typename _Cardinal>
    auto cardinal_cast(_Cardinal c) const
    {
      if constexpr (_Cardinal{}() > Cardinal{}()) return unaligned().cardinal_cast(c);
      else
      {
        using other_it  = aligned_ptr_iterator<T, _Cardinal>;
        using other_ptr = typename other_it::aligned_ptr_type;
        return other_it{other_ptr{ptr.get()}};
      }
    }

    aligned_ptr_iterator& operator+=(std::ptrdiff_t n) { ptr += n; return *this; }

    template <typename T1, typename N1>
    bool operator==(aligned_ptr_iterator<T1, N1> y) const
    {
      return unaligned() == y.unaligned();
    }

    template <typename T1, typename N1>
    bool operator==(unaligned_ptr_iterator<T1, N1> y) const
    {
      return unaligned() == y;
    }

    template <typename T1, typename N1>
    auto operator<=>(aligned_ptr_iterator<T1, N1> y) const
    {
      return unaligned() <=> y.unaligned();
    }

    template <typename T1, typename N1>
    auto operator<=>(unaligned_ptr_iterator<T1, N1> y) const
    {
      return unaligned() <=> y;
    }

    template <typename T1, typename N1>
    std::ptrdiff_t operator-(aligned_ptr_iterator<T1, N1> y) const
    {
      return unaligned() - y.unaligned();
    }

    template <typename T1, typename N1>
    std::ptrdiff_t operator-(unaligned_ptr_iterator<T1, N1> y) const
    {
      return unaligned() - y;
    }

    template <typename T1, typename N1>
    friend std::ptrdiff_t operator-(unaligned_ptr_iterator<T1, N1> x, aligned_ptr_iterator y)
    {
      return x - y.unaligned();
    }


    template< relative_conditional_expr C, decorator S>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::load_, C const& c, S const& s
                                , eve::as<wv_type> const&, aligned_ptr_iterator self
                                )
    {
      return eve::load(c, s, self.ptr, Cardinal{});
    }

    template <relative_conditional_expr C>
    EVE_FORCEINLINE friend void tagged_dispatch(
      eve::tag::store_, C cond, wv_type v, aligned_ptr_iterator self )
      requires ( !std::is_const_v<T> )
    {
      return eve::store[cond](v, self.ptr);
    }

    EVE_FORCEINLINE friend void tagged_dispatch( eve::tag::store_, wv_type v, aligned_ptr_iterator self )
      requires ( !std::is_const_v<T> )
    {
      return eve::store(v, self.ptr);
    }

    template <relative_conditional_expr C, decorator Decorator, typename U>
      requires ( !std::is_const_v<T> )
    EVE_FORCEINLINE friend auto tagged_dispatch(
      eve::tag::compress_store_, C c, Decorator d, wv_type v,
      logical<wide<U, Cardinal>> m, aligned_ptr_iterator self)
    {
      return unaligned_ptr_iterator<T, Cardinal>{eve::compress_store(c, d, v, m, self.ptr)};
    }

    aligned_ptr_type ptr;
  };
}
