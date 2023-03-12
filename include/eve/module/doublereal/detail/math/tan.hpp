//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/doublereal/detail/trigo_base.hpp>
#include <eve/module/doublereal/detail/trigo_eval.hpp>

namespace eve::detail
{

  template<typename Z>
  auto doublereal_unary_dispatch(eve::tag::tan_, Z const& xx) noexcept
  {
    auto [s, c] =  sincos(xx);
    return s/c;
  }

  template<typename Z, decorator D>
  auto doublereal_unary_dispatch(eve::tag::tan_, D const & , Z const& a) noexcept
  requires(is_one_of<D>(types<quarter_circle_type, half_circle_type
                       , full_circle_type, medium_type, big_type> {}))
  {
    auto [s, c] =  D()(sincos)(a);
    return s/c;
  }



}
