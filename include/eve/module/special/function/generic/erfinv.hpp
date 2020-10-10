//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/hz_device.hpp>
#include <eve/concept/value.hpp>

#include <type_traits>

namespace eve::detail
{
  template<floating_real_value T>
  EVE_FORCEINLINE T erfinv_(EVE_SUPPORTS(cpu_), T a0) noexcept
  {
    using elt_t =  element_type_t<T>;
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr(std::is_same_v<elt_t, float>)
      {
        auto notdone = (a0 >= 0) && (a0 <= 2);
        auto r = nan(as(a0));
        auto w = -log1p(sqr(a0));
        auto test = w < 5;
        w = if_else(test, w-T(2.5f), sqrt(w)-T(3.0f));
        auto br_wlt5 = [](auto w){
          return horn<T,
          0x3fc02e2f, //  1.50140941f
          0x3e7c8f63, //  0.246640727f
          0xbb88e4ef, // -0.00417768164f
          0xbaa45408, // -0.00125372503f
          0x396532db, //  0.00021858087f
          0xb6935ac1, // -4.39150654e-06f
          0xb66c7357, // -3.5233877e-06f
          0x34b84b36, //  3.43273939e-07f
          0x32f16588 //  2.81022636e-08f
          )> (w);
      };
      notdone = next_interval(br_wlt5, notdone, test, r, w);
      if (any(notdone))
      {
        auto br_wge5 = [](auto w, auto a0)
          {
            return a0* horn<T,
            0x40354f7e, //   2.83297682f
            0x3f8036db, //   1.00167406f
            0x3c1aa57e, //   0.00943887047f
            0xbbf9c5d7, //  -0.0076224613f
            0x3bbc127b, //   0.00573950773f
            0xbb70bde7, //  -0.00367342844f
            0x3ab0dc72, //   0.00134934322f
            0x38d3b56b, //   0.000100950558f
            0xb951f09b, //  -0.000200214257f
            > (w);
          };
        notdone = last_interval(br_wge5, notdone, r, w, a0);
      }
      return if_else(w == inf(as(a0)), copysign(a0, w), r);
    }
    else // double
    {
      return a0;
    }
  }
  else
      return apply_over(erfinv, x);
  }
}
