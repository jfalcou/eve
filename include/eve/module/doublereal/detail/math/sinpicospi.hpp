//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/doublereal/detail/trigo_base.hpp>
#include <eve/module/doublereal/detail/trigo_eval.hpp>

namespace eve::detail
{

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::sinpicospi_, Z const& a0) noexcept
  {
    if constexpr( has_native_abi_v<Z> )
    {
      auto x = abs(a0);
      if( eve::all(x <= pio_4(as(a0))) )
      {
        return quarter_circle(sinpicospi)(a0);
      }
      else if( eve::all(x <= pio_2(as(a0))) )
      {
        return half_circle(sinpicospi)(a0);
      }
      else if( eve::all(x <= pi(as(x))) )
      {
        return full_circle(sinpicospi)(a0);
      }
      else if( eve::all(x <= Z(1.0e15)) )
      {
        return medium(sinpicospi)(a0);
      }
      else
      {
        return big(sinpicospi)(a0);
      }
    }
    else return apply_over(sinpicospi, a0);
  }

  template<typename Z, decorator D>
  auto doublereal_unary_dispatch(eve::tag::sinpicospi_, D const & d, Z const& a0) noexcept
  requires(is_one_of<D>(types<quarter_circle_type, half_circle_type
                       , full_circle_type, medium_type, big_type> {}))
  {
    return kumi::tuple{d(sinpi)(a0), d(cospi)(a0)};//TODO optimize it
  }
}
