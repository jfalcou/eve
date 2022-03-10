//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
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
  struct tchebytchev_points_ : TraitsSupport
  {

//     template <eve::floating_scalar_value T,  eve::floating_scalar_value V>
//     EVE_FORCEINLINE auto operator()(T a, V b, ptrdiff_t n) const
//     {

//       EVE_ASSERT(eve::is_finite(a), "a is not finite");
//       EVE_ASSERT(eve::is_finite(b), "b is not finite");
//       using elt_t = common_compatible_t<T, V>;
//       auto ea = elt_t(a);
//       auto eb = elt_t(b);
//       auto s = rec(n);
//       auto base = average(ea, eb);
//       auto scale = average(-ea, eb);
//       auto f = [base, scale](auto i){ return base+full_circle(cospi)(i)*scale; };
//       return map(iota_with_step(s, 2*s, n), f);
//     }

    template <eve::scalar_value T>
    EVE_FORCEINLINE auto operator()(ptrdiff_t n, as<T> const &) const
    {
      auto f = [](auto i){ return (one(as<T>())+full_circle(cospi)(i))/2; };
      auto s = rec(T(n));
      return map(iota_with_step(s, 2*s, n), f);
    }
  };


  inline constexpr auto tchebytchev_points = eve::algo::function_with_traits<tchebytchev_points_>[eve::algo::copy.get_traits()];
}
