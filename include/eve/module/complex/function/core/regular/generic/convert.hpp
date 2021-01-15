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

#include <eve/as.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/traits/as_wide.hpp>

namespace eve::detail
{
  template<value IN, scalar_value OUT>
  EVE_FORCEINLINE auto convert_(EVE_SUPPORTS(cpu_), IN const &v0, as_<OUT> const &tgt) noexcept
  {
    if constexpr(std::same_as<element_type_t<IN>, OUT>)
    {
      return v0;
    }
    else
    {
      if constexpr( scalar_value<IN> )
      {
        return static_cast<OUT>(v0);
      }
      else
      {
        using out_t = as_wide_t<OUT, cardinal_t<IN>>;

        // If input or output are aggregated, we can slice and combine without lose of performance
        if constexpr( has_aggregated_abi_v<IN> || has_aggregated_abi_v<out_t> )
        {
          auto[l,h] = v0.slice();
          auto ll = eve::convert(l,tgt);
          auto hh = eve::convert(h,tgt);
          return out_t{ll,hh};
        }
        else
        {
          return map(convert, v0, tgt);
        }
      }
    }
  }
}
