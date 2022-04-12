//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/polynomial/detail/tchebeval_impl.hpp>

namespace eve::detail
{

  //================================================================================================
  //== Tchebeval with ranges
  //================================================================================================
  template<value T0, std::ranges::bidirectional_range R>
  EVE_FORCEINLINE constexpr auto tchebeval_(EVE_SUPPORTS(cpu_)
                                        , T0 xx, R const & r) noexcept
  requires (compatible_values<T0, typename R::value_type> && (!simd_value<R>))
  {
    return detail::tchebeval_impl(regular_type(), xx, r);
  }

  //================================================================================================
  //== N parameters (((..(a*x+b)*x+c)*x + ..)..)
  //================================================================================================

  template<value T0, value ...Ts>
  EVE_FORCEINLINE constexpr auto tchebeval_(EVE_SUPPORTS(cpu_), T0 x, Ts... args) noexcept
  {
    return tchebeval_impl(regular_type(), x, args...);
  }

}
