//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/algo/as_range.hpp>
#include <eve/algo/iterator_helpers.hpp>
#include <eve/algo/views/convert.hpp>


namespace eve::algo::views
{
  //================================================================================================
  //! @addtogroup views
  //! @{
  //!    @struct base_plus_offset_iterator
  //!    @brief An iterator for all values from base to offset.
  //!    Should be created with `linspace_scaled` or `linspace`.
  //!    Not OK to compare two iterators generated from a different base.
  //!
  //!    **Required header:** `#include <eve/algo/views/linspace.hpp>`
  //!
  //!    Has a shorthand `eve::views::base_plus_offset_iterator` in `<eve/views/linspace.hpp>`.
  //! @}
  //================================================================================================

  template <typename T, typename N>
  struct linspace_iterator : operations_with_distance
  {
    using value_type = T;
    using wv_type    = eve::wide<value_type, N>;

    template <eve::scalar_value T> 
    struct lerpoid
    {
      T a;
      T b;
      T invnm1;
      
      lerpoid(T a_, T b_, ptrdiff_t n) :
        a(a_), b(b_), invnm1(eve::rec((elt_t(eve::dec(n)))))
      {};
      
      EVE_FORCEINLINE auto operator()(auto i){return eve::lerp(elt_t(a), elt_t(b), i*invnm1); }; 
    };

    value_type      a;
    value_type      b;
    std::ptrdiff_t  n;
    lerpoid l;
    wv_type         wide_cur;
    
    linspace_iterator() = default;

    EVE_FORCEINLINE linspace_iterator(value_type a,
                                      value_type b,
                                      ptrdiff_t  n, 
                                      std::ptrdiff_t i_) :
      a(a_),
      b(b_),
      i(0)
      l(a, b, n)
    {
      wide_cur = wv_type {[&](int j, int) { return j; }};
      wide_cur = l(wide_cur);
      operator+=(i_);
    }

 
    EVE_FORCEINLINE friend auto tagged_dispatch ( eve::tag::unalign_, base_plus_offset_iterator self )
    {
      return self;
    }

    base_plus_offset_iterator previous_partially_aligned() const { return *this; }
    base_plus_offset_iterator next_partially_aligned()     const { return *this; }

    static N iterator_cardinal() { return {}; }

    template <typename _N>
    auto cardinal_cast(_N) const { return linspace_iterator<T, _N>{a, b, n, i}; }

    linspace_iterator& operator+=(std::ptrdiff_t n)
    {
      i += n;
      wide_cur =  l(i);
      return *this;
    }

    friend std::ptrdiff_t operator-(base_plus_offset_iterator x, base_plus_offset_iterator y)
    {
      EVE_ASSERT(x.base == y.base,   "different base");
      EVE_ASSERT(x.scale == y.scale, "different scale");
      return x.i - y.i;
    }

    bool operator== (base_plus_offset_iterator const& x) const
    {
      EVE_ASSERT(base  == x.base,   "different base");
      EVE_ASSERT(scale == x.scale, "different scale");
      return i ==  x.i;
    }
    auto operator<=>(base_plus_offset_iterator const& x) const
    {
      EVE_ASSERT(base  == x.base,   "different base");
      EVE_ASSERT(scale == x.scale, "different scale");
      return i <=> x.i;
    }

    EVE_FORCEINLINE friend value_type tagged_dispatch(eve::tag::read_, base_plus_offset_iterator self)
    {
      return fam( self.base, eve::convert(self.i, eve::as<value_type>{}), self.scale);
    }

    template <typename U>
    EVE_FORCEINLINE friend auto tagged_dispatch(convert_, base_plus_offset_iterator self, eve::as<U> tgt)
    {
      return base_plus_offset_iterator<U, N>{
        eve::convert(self.base, tgt),
        eve::convert(self.scale, tgt),
        self.i
      };
    }

    template<relative_conditional_expr C, decorator S>
    EVE_FORCEINLINE friend wv_type tagged_dispatch(eve::tag::load_,
                                                   C const & c,
                                                   S const &,
                                                   eve::as<wv_type> const &,
                                                   base_plus_offset_iterator self)
    {
      if constexpr ( !C::has_alternative ) return self.wide_cur;
      else
      {
        return eve::replace_ignored(self.wide_cur, c, c.alternative);
      }
    }
  };

  //================================================================================================
  //! @addtogroup views
  //! @{
  //!    @var linspace_scaled
  //!    @brief A fuction to generate an `linspace`between a and b with n equidistant points
  //!
  //!    Example: linspace(0.0, 2.0, 5) is a view [0.0, 0.5, 1.0, 1.5, 2.0]
  //!
  //!    **Required header:** `#include <eve/algo/views/linspace.hpp>`
  //!
  //! @}
  //================================================================================================

  struct
  {
    template <typename T>
    EVE_FORCEINLINE auto operator()(T a, T b, ptrdiff_t n) const
    {
      using N = eve::fixed<eve::expected_cardinal_v<T>>;
      return linspace_iterator<T, N>{a, b, n, 0};
    }

    template <typename T>
    EVE_FORCEINLINE auto operator()(T base, T scale, std::ptrdiff_t size) const
    {
      auto f = operator()(base, scale);
      auto l = f + size;
      return eve::algo::as_range(f, l);
    }
  } inline constexpr linspace_scaled;

}
