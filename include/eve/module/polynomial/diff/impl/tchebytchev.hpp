//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/polynomial/regular/tchebytchev.hpp>

namespace eve::detail
{

  template<scalar_value N, value T>
  EVE_FORCEINLINE constexpr auto tchebytchev_(EVE_SUPPORTS(cpu_)
                                  , diff_type<1> const &
                                  , N const &n
                                  , T const &x) noexcept
  {

    auto nn = convert(n, as<element_type_t<T>>());
    return nn*kind_2(tchebytchev)(n ? dec(n) : zero(as(n)), x);
  }

  template<scalar_value N, value T>
  EVE_FORCEINLINE constexpr auto tchebytchev_(EVE_SUPPORTS(cpu_)
                                  , decorated<diff_<1>(kind_1_type)> const &
                                  , N const &n
                                  , T const &x) noexcept
  {
    return diff(tchebytchev)(n, x);
  }

  template<scalar_value N, value T>
  EVE_FORCEINLINE constexpr auto tchebytchev_(EVE_SUPPORTS(cpu_)
                                  , decorated<diff_<1>(kind_2_type)> const &
                                  , N const &n
                                  , T const &x) noexcept
  requires index_compatible_values<N, T>
  {

    auto nn = convert(n, as<element_type_t<T>>());
    auto nnp1 =  inc(nn);
    auto z = ((nnp1*kind_2(tchebytchev)(inc(n), x)-x*kind_2(tchebytchev)(n, x)))/dec(sqr(x));
    auto z1 = nn*nnp1*inc(nnp1)/3;
    return  if_else(abs(x)-one(as(x))< eps(as(x))
                   , if_else(is_gez(x), z1, z1*alternate_sign(n))
                   , z);

  }

}
