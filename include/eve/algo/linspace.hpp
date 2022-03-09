//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/algo/copy.hpp>
#include <eve/views/map.hpp>
#include <eve/views/iota.hpp>
//#include <eve/algo/views/linspace.hpp>
#include <iostream>
namespace eve::algo
{
  //================================================================================================
  //! @addtogroup algo
  //! @{
  //!  @var linspace
  //!
  //!  @brief SIMD version of `std::linspace`
  //!  For conversion/overflow behaviour, should follow the standard.
  //!
  //!  **Required header:** `#include <eve/algo/linspace.hpp>`
  //! @}
  //================================================================================================

  template <eve::scalar_value T>
  struct lerpoid
  {
    T a;
    T b;
    T invnm1;

    lerpoid(T a_, T b_, ptrdiff_t n) :
      a(a_), b(b_), invnm1(n == 1 ? 1 : eve::rec((T(eve::dec(n)))))
    {};
    auto operator()(auto i){return eve::lerp(a, b, i*invnm1); };
  };

  template <typename TraitsSupport>
  struct linspace_ : TraitsSupport
  {

    template <eve::scalar_value T,  eve::scalar_value U>
    EVE_FORCEINLINE auto operator()(T , U ,  ptrdiff_t n) const
    {
      using elt_t = T;
      EVE_ASSERT(eve::is_finite(a), "a is not finite");
      EVE_ASSERT(eve::is_finite(b), "b is not finite");
//       if (n == 0u) return eve::views::iota(elt_t{0}, 0);
//       else if (n == 1u) return eve::views::iota(elt_t{b}, 1);
//       else if (a == b)  return eve::views::iota_with_step(elt_t(a), elt_t(0), n);
//       else
//       {
        using elt_t = T; //decltype(eve::read(r.begin()));
        auto io = eve::views::iota(elt_t{0}, n);
        //     auto l = lerpoid(elt_t(a), elt_t(b), n);
        auto r = eve::views::map(io, eve::sqrt); //l);
        return r;
//      }
    }
  };

  inline constexpr auto linspace = function_with_traits<linspace_>[copy.get_traits()];

}
