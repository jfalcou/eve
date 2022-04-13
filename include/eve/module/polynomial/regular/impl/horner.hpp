//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/polynomial/detail/horner_impl.hpp>

namespace eve::detail
{

  //================================================================================================
  //== Horner with ranges
  //================================================================================================
  template<value T0, range R>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_)
                                        , T0 xx, R const & r) noexcept
  requires (compatible_values<T0, typename R::value_type> && (!simd_value<R>))
  {
    return detail::horner_impl(regular_type(), xx, r);
  }

  template<value T0, range R>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_)
                                        , comp_type const &
                                        , T0 xx, R const & r) noexcept
  requires (compatible_values<T0, typename R::value_type> && (!simd_value<R>))
  {
    return detail::horner_impl(comp_type(), xx, r);
  }
  //================================================================================================
  //== variadic
  //================================================================================================

  template<value T0, value ...Ts>
  EVE_FORCEINLINE constexpr auto horner_(EVE_SUPPORTS(cpu_), T0 x, Ts... args) noexcept
  {
    return horner_impl(regular_type(), x, args...);
  }
}
