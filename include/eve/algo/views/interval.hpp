//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/views/iota.hpp>
#include <eve/algo/copy.hpp>

namespace eve::views
{
  //================================================================================================
  //! @addtogroup views
  //! @{
  //!  @var interval
  //!
  //!  @brief SIMD version of `std::interval`
  //!    - interval(a, b) returns a view of the sequence (a+i) from i = 0 to the last i such that a+n <= b
  //!    - interval_with_step(a, b, s) returns a view of the sequence (a+i*s) from i = 0
  //!        - to the last i such that a+s*i <= b if s is strictly positive
  //!        - to the last i such that a+s*i >= b if s is strictly negative
  //!      or an empty sequence if s is 0
  //!
  //!  **Required header:** `#include <eve/views/interval.hpp>`
  //! @}
  //================================================================================================

  template <typename TraitsSupport>
  struct interval_ : TraitsSupport
  {

    template <eve::scalar_value T,  eve::scalar_value V>
    EVE_FORCEINLINE auto operator()(T a, V b) const
    {

      EVE_ASSERT(eve::is_finite(a), "a is not finite");
      EVE_ASSERT(eve::is_finite(b), "b is not finite");
      using elt_t = common_compatible_t<T, V>;
      auto size = [] (elt_t l,  elt_t u) -> ptrdiff_t
      {
        const ptrdiff_t nelt  = ptrdiff_t(tolerant(floor)((u-l+1)));
        const elt_t     eps3  = 3*eps(as(l));

        if(!almost(is_equal)(l+(nelt-1), u, eps3))
        {
          if(almost(is_equal)(l+(nelt-2), u, eps3))  return nelt-1;
          else if(almost(is_equal)(l+nelt, u, eps3)) return nelt+1;
        }
        return nelt;
      };
      ptrdiff_t n = size(elt_t(a), elt_t(b));
      return eve::views::iota(elt_t(a), n);
    }

     template <eve::scalar_value T,  eve::scalar_value V>
    EVE_FORCEINLINE auto operator()(raw_type const &, T a, V b) const
    {
      EVE_ASSERT(eve::is_finite(a), "a is not finite");
      EVE_ASSERT(eve::is_finite(b), "b is not finite");
      using elt_t = common_compatible_t<T, V>;
      auto size = [] (elt_t l,  elt_t u) -> ptrdiff_t
      {
         return  ptrdiff_t(floor((u-l+1)));
      };
      ptrdiff_t n = size(elt_t(a), elt_t(b));
      return eve::views::iota(elt_t(a), n);
    }
  };

  inline constexpr auto interval = eve::algo::function_with_traits<interval_>[eve::algo::copy.get_traits()];

  template <typename TraitsSupport>
  struct interval_with_step_ : TraitsSupport
  {

    template <eve::scalar_value T,  eve::scalar_value U,  eve::scalar_value V>
    EVE_FORCEINLINE auto operator()(T a, V b, U step) const
    {

      EVE_ASSERT(eve::is_finite(a), "a is not finite");
      EVE_ASSERT(eve::is_finite(b), "b is not finite");
      using elt_t = common_compatible_t<T, U, V>;
      auto size = [] (elt_t l, elt_t s,  elt_t u) -> ptrdiff_t
      {
        if (s == 0 || sign(u-l) !=  sign(s)) return 0;
        const ptrdiff_t nelt  = ptrdiff_t(tolerant(floor)((u-l+s)/s));
        const elt_t     eps3  = 3*eps(as(l));

        if(!almost(is_equal)(l+(nelt-1)*s, u, eps3))
        {
          if(almost(is_equal)(l+(nelt-2)*s, u, eps3))  return nelt-1;
          else if(almost(is_equal)(l+nelt*s, u, eps3)) return nelt+1;
        }
        return nelt;
      };
      ptrdiff_t n = size(elt_t(a), elt_t(step), elt_t(b));
      return eve::views::iota_with_step(elt_t(a), elt_t(step), n);
    }

    template <eve::scalar_value T,  eve::scalar_value U,  eve::scalar_value V>
    EVE_FORCEINLINE auto operator()(raw_type const &, T a, V b, U step) const
    {

      EVE_ASSERT(eve::is_finite(a), "a is not finite");
      EVE_ASSERT(eve::is_finite(b), "b is not finite");
      using elt_t = common_compatible_t<T, U, V>;
      auto size = [] (elt_t l, elt_t s,  elt_t u) -> ptrdiff_t
      {
        if (s == 0 || sign(u-l) !=  sign(s)) return 0;
        return ptrdiff_t(floor((u-l+s)/s));
      };
      ptrdiff_t n = size(elt_t(a), elt_t(step), elt_t(b));
      return eve::views::iota_with_step(elt_t(a), elt_t(step), n);
    }
  };

  inline constexpr auto interval_with_step = eve::algo::function_with_traits<interval_with_step_>[eve::algo::copy.get_traits()];
}
