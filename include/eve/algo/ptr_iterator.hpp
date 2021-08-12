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
  struct aligned_ptr_iterator;

  template <typename T, typename Cardinal>
  struct unaligned_ptr_iterator : operations_with_distance
  {
    using cardinal        = Cardinal;
    using value_type      = std::remove_const_t<T>;
    using wide_value_type = eve::wide<value_type, cardinal>;

    unaligned_ptr_iterator() = default;
    explicit unaligned_ptr_iterator(T* ptr) : ptr(ptr) {}

    unaligned_ptr_iterator unaligned() const { return *this; }

    auto previous_partially_aligned() const
    {
      return aligned_ptr_iterator<T, cardinal>{eve::previous_aligned_address(ptr, cardinal{})};
    }

    template <typename _Cardinal>
    auto cardinal_cast(_Cardinal) const { return unaligned_ptr_iterator<T, _Cardinal>{ptr}; }

    value_type& operator*() const { return *ptr; }

    unaligned_ptr_iterator& operator+=(std::ptrdiff_t n) { ptr += n; return *this; }
    friend std::ptrdiff_t   operator-(unaligned_ptr_iterator x, unaligned_ptr_iterator y) { return x.ptr - y.ptr; }

    auto operator<=>(unaligned_ptr_iterator const&) const = default;


    template< relative_conditional_expr C, decorator S, typename Pack>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::load_, C const& c, S const& s
                                , eve::as<Pack> const&, unaligned_ptr_iterator self
                                )
    {
      return eve::load(c, s, self.ptr, Cardinal{});
    }

    template <relative_conditional_expr C>
    EVE_FORCEINLINE friend void tagged_dispatch(
      eve::tag::store_, C cond, wide_value_type v, unaligned_ptr_iterator self )
      requires (!std::is_const_v<T>)
    {
      eve::store[cond](v, self.ptr);
    }

    EVE_FORCEINLINE friend void tagged_dispatch( eve::tag::store_, wide_value_type v, unaligned_ptr_iterator self )
      requires ( !std::is_const_v<T> )
    {
      eve::store(v, self.ptr);
    }

    template <relative_conditional_expr C, decorator Decorator>
      requires ( !std::is_const_v<T> )
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::compress_store_, C c, Decorator d, wide_value_type v, logical<wide_value_type> m, unaligned_ptr_iterator self)
    {
      return unaligned_ptr_iterator{eve::compress_store(c, d, v, m, self.ptr)};
    }

    T* ptr;
  };

  template <typename T, typename Cardinal>
  struct aligned_ptr_iterator : operations_with_distance, forward_to_unaligned
  {
    using cardinal          = Cardinal;
    using value_type        = std::remove_const_t<T>;
    using aligned_ptr_type  = eve::aligned_ptr<T, Cardinal>;
    using wide_value_type   = eve::wide<value_type, cardinal>;

    aligned_ptr_iterator() = default;
    explicit aligned_ptr_iterator(aligned_ptr_type ptr) : ptr{ptr} {}

    // Need this for totally ordered.
    operator unaligned_ptr_iterator<T, Cardinal>() const {
      return unaligned_ptr_iterator<T, Cardinal>{ptr.get()};
    }

    value_type& operator*() const { return *ptr; }
    auto get() const { return ptr.get(); }
    auto unaligned() const { return unaligned_ptr_iterator<T, Cardinal>{ptr.get()}; }
    auto previous_partially_aligned() const { return *this; }

    template <typename _Cardinal>
    auto cardinal_cast(_Cardinal) const
    {
      using other_it  = aligned_ptr_iterator<T, _Cardinal>;
      using other_ptr = typename other_it::aligned_ptr_type;
      return other_it{other_ptr{ptr.get()}};
    }

    aligned_ptr_iterator& operator+=(std::ptrdiff_t n) { ptr += n; return *this; }

    template< relative_conditional_expr C, decorator S, typename Pack>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::load_, C const& c, S const& s
                                , eve::as<Pack> const&, aligned_ptr_iterator self
                                )
    {
      return eve::load(c, s, self.ptr, Cardinal{});
    }

    template <relative_conditional_expr C>
    EVE_FORCEINLINE friend void tagged_dispatch(
      eve::tag::store_, C cond, wide_value_type v, aligned_ptr_iterator self )
      requires ( !std::is_const_v<T> )
    {
      return eve::store[cond](v, self.ptr);
    }

    EVE_FORCEINLINE friend void tagged_dispatch( eve::tag::store_, wide_value_type v, aligned_ptr_iterator self )
      requires ( !std::is_const_v<T> )
    {
      return eve::store(v, self.ptr);
    }

    template <relative_conditional_expr C, decorator Decorator>
      requires ( !std::is_const_v<T> )
    EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::compress_store_, C c, Decorator d, wide_value_type v, logical<wide_value_type> m, aligned_ptr_iterator self)
    {
      return unaligned_ptr_iterator<T, Cardinal>{eve::compress_store(c, d, v, m, self.ptr)};
    }

    aligned_ptr_type ptr;
  };
}
