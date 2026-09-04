//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/algo/algo/iterator_helpers.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/traits.hpp>

namespace eve::algo
{
  //================================================================================================
  //! @addtogroup eve_algorithms
  //! @{
  //!   @struct ptr_iterator
  //!   @brief An eve iterator on top of pointer or aligned pointer.
  //!
  //!   This should not be created directly but rather constructed from preprocess_range.
  //!
  //!   When ptr is aligned, the alignment should match the width.
  //!
  //!    **Required header:** `#include <eve/module/algo/algo/ptr_iterator.hpp>`
  //! @}
  //================================================================================================
  template <typename Ptr, width_type Width>
  struct ptr_iterator;

  namespace _
  {
    template <typename Ptr, width_type Width>
    constexpr bool check_aligned_ptr_validity()
    {
      if constexpr (!eve::_::is_aligned_ptr_v<Ptr>) return true;
      else return sizeof(value_type_t<Ptr>) * Width == Ptr::alignment();
    }
  }

  template <typename Ptr, width_type Width>
  struct ptr_iterator : operations_with_distance
  {
    static_assert(_::check_aligned_ptr_validity<Ptr, Width>());

    using value_type = value_type_t<Ptr>;
    using ptr_type   = Ptr;

    // internal helpers
    using reference_type = decltype(*Ptr{});
    using cv_value_type  = std::remove_reference_t<reference_type>;
    using wv_type        = eve::wide<value_type, Width>;
    using unaligned_me   = ptr_iterator<unaligned_t<Ptr>, Width>;

    ptr_iterator() = default;
    explicit ptr_iterator(Ptr p) : ptr(p) {}

    template <std::convertible_to<Ptr> UPtr>
    ptr_iterator(ptr_iterator<UPtr, Width> const& x) : ptr(x.ptr) {}

    EVE_FORCEINLINE auto unalign() const noexcept { return unaligned_me{eve::unalign(ptr)}; }

    auto previous_partially_aligned() const
    {
      if constexpr (eve::_::is_aligned_ptr_v<Ptr> ) return *this;
      else
      {
        auto a_ptr = eve::previous_aligned_address(ptr, fixed<Width>{});
        return ptr_iterator<decltype(a_ptr), Width>{a_ptr};
      }
    }

    auto next_partially_aligned() const
    {
      if constexpr (eve::_::is_aligned_ptr_v<Ptr> ) return *this;
      else
      {
        auto a_ptr = eve::next_aligned_address(ptr, fixed<Width>{});
        return ptr_iterator<decltype(a_ptr), Width>{a_ptr};
      }
    }

    static fixed<Width> iterator_width() { return {}; }

    template <width_type _Width>
    auto width_cast(fixed<_Width> c) const
    {
           if constexpr (!eve::_::is_aligned_ptr_v<Ptr> ) return ptr_iterator<Ptr, _Width>(ptr);
      else if constexpr (_Width > Width                   ) return unalign().width_cast(c);
      else
      {
        using other_ptr = aligned_ptr<cv_value_type, _Width>;
        using other_it  = ptr_iterator<other_ptr, _Width>;
        return other_it{other_ptr{ptr.get()}};
      }
    }

    auto& operator*() const { return *ptr; }

    ptr_iterator& operator+=(std::ptrdiff_t n) { ptr += n; return *this; }

    template <typename OtherPtr>
    friend std::ptrdiff_t operator-(ptr_iterator x, ptr_iterator<OtherPtr, Width> y) { return x.ptr - y.ptr; }

    template <typename OtherPtr>
    bool operator==(ptr_iterator<OtherPtr, Width> const &x) const { return ptr == x.ptr; }

    template <typename OtherPtr>
    auto operator<=>(ptr_iterator<OtherPtr, Width> const &x) const { return ptr <=> x.ptr; }

    template<callable_options O>
    EVE_FORCEINLINE auto load(O const& opts, as<wv_type> tgt) const
    {
      return eve::load[opts](ptr, tgt);
    }

    EVE_FORCEINLINE friend auto tagged_dispatch(eve::tag::store_equivalent_, relative_conditional_expr auto c, wv_type v, ptr_iterator self)
    {
      return kumi::make_tuple(c, v, self.ptr);
    }

    Ptr ptr;
  };
}
