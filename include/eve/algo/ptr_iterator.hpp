//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/concepts/value_type.hpp>
#include <eve/algo/iterator_helpers.hpp>

#include <eve/function/load.hpp>
#include <eve/function/store.hpp>
#include <eve/memory/aligned_ptr.hpp>

namespace eve::algo
{
  //================================================================================================
  //! @addtogroup eve.algo
  //! @{
  //!   @struct ptr_iterator
  //!   @brief An eve iterator on top of pointer or aligned pointer.
  //!
  //!   This should not be created directly but rather constructed from preprocess_range.
  //!
  //!   When ptr is aligned, the alignment should match the cardinal.
  //!
  //!    **Required header:** `#include <eve/algo/ptr_iterator.hpp>`
  //! @}
  //================================================================================================
  template <typename Ptr, typename Cardinal>
  struct ptr_iterator;

  namespace detail
  {
    template <typename Ptr, typename Cardinal>
    constexpr bool check_aligned_ptr_validity()
    {
      if constexpr (!detail::instance_of<Ptr, aligned_ptr>) return true;
      else return sizeof(value_type_t<Ptr>) * Cardinal{}() == Ptr::alignment();
    }
  }

  template <typename Ptr, typename Cardinal>
  struct ptr_iterator : operations_with_distance
  {
    static_assert(detail::check_aligned_ptr_validity<Ptr, Cardinal>());

    using value_type = value_type_t<Ptr>;
    using ptr_type   = Ptr;

    // internal helpers
    using reference_type = decltype(*Ptr{});
    using cv_value_type  = std::remove_reference_t<reference_type>;
    using wv_type        = eve::wide<value_type, Cardinal>;
    using unaligned_me   = ptr_iterator<unaligned_t<Ptr>, Cardinal>;

    ptr_iterator() = default;
    explicit ptr_iterator(Ptr ptr) : ptr(ptr) {}

    auto unaligned()        const { return unaligned_me{ unalign(ptr) }; }
    operator unaligned_me() const { return unaligned(); }

    auto previous_partially_aligned() const
    {
      if constexpr (detail::instance_of<Ptr, aligned_ptr> ) return *this;
      else
      {
        auto a_ptr = eve::previous_aligned_address(ptr, Cardinal{});
        return ptr_iterator<decltype(a_ptr), Cardinal>{a_ptr};
      }
    }

    auto next_partially_aligned() const
    {
      if constexpr (detail::instance_of<Ptr, aligned_ptr> ) return *this;
      else
      {
        auto a_ptr = eve::next_aligned_address(ptr, Cardinal{});
        return ptr_iterator<decltype(a_ptr), Cardinal>{a_ptr};
      }
    }

    static Cardinal iterator_cardinal() { return {}; }

    template <typename _Cardinal>
    auto cardinal_cast(_Cardinal c) const
    {
           if constexpr (!detail::instance_of<Ptr, aligned_ptr> ) return ptr_iterator<Ptr, _Cardinal>(ptr);
      else if constexpr (_Cardinal{}() > Cardinal{}()           ) return unaligned().cardinal_cast(c);
      else
      {
        using other_ptr = aligned_ptr<cv_value_type, _Cardinal>;
        using other_it  = ptr_iterator<other_ptr, _Cardinal>;
        return other_it{other_ptr{ptr.get()}};
      }
    }

    auto& operator*() const { return *ptr; }

    ptr_iterator& operator+=(std::ptrdiff_t n) { ptr += n; return *this; }

    template <typename OtherPtr>
    friend std::ptrdiff_t operator-(ptr_iterator x, ptr_iterator<OtherPtr, Cardinal> y) { return x.ptr - y.ptr; }

    template <typename OtherPtr>
    bool operator==(ptr_iterator<OtherPtr, Cardinal> const &x) const { return ptr == x.ptr; }

    template <typename OtherPtr>
    auto operator<=>(ptr_iterator<OtherPtr, Cardinal> const &x) const { return ptr <=> x.ptr; }

    template< relative_conditional_expr C, decorator S>
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::load_, C const& c, S const& s
                                                , eve::as<wv_type> const&, ptr_iterator self
                                                )
    {
      return eve::load(c, s, self.ptr, Cardinal{});
    }

    template <relative_conditional_expr C>
    EVE_FORCEINLINE friend void tagged_dispatch(eve::tag::store_,
                                                C cond, wv_type v,
                                                ptr_iterator self )
      requires (!std::is_const_v<cv_value_type>)
    {
      eve::store[cond](v, self.ptr);
    }

    EVE_FORCEINLINE friend void tagged_dispatch( eve::tag::store_, wv_type v, ptr_iterator self )
      requires (!std::is_const_v<cv_value_type>)
    {
      eve::store(v, self.ptr);
    }

    template <relative_conditional_expr C, decorator Decorator, typename U>
      requires (!std::is_const_v<cv_value_type>)
    EVE_FORCEINLINE friend auto tagged_dispatch(
      eve::tag::compress_store_, C c, Decorator d, wv_type v,
      logical<wide<U, Cardinal>> m, ptr_iterator self)
    {
      return unaligned_me{eve::compress_store(c, d, v, m, self.ptr)};
    }

    Ptr ptr;
  };

  template <typename T, typename Cardinal>
  using aligned_ptr_iterator = ptr_iterator<aligned_ptr<T, Cardinal>, Cardinal>;
}
