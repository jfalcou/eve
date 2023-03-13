//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>

#include <type_traits>
#include <algorithm>

namespace eve::detail
{
  template<ordered_value T, ordered_value U, ordered_value V>
  EVE_FORCEINLINE auto
  fsm_(EVE_SUPPORTS(cpu_), promote_type const&, T const& a, U const& b, V const& c) noexcept
  {
    using er_t = common_type_t<element_type_t<T>, element_type_t<U>, element_type_t<V>>;
    constexpr auto N = std::max({cardinal_v<T>,cardinal_v<U>,cardinal_v<V>});
    using r_t = wide<er_t, fixed<N>>;
    auto cv_t = as(eve::as<er_t>());
    return fsm(convert(a, cv_t), convert(b, cv_t), convert(c,cv_t));
  }
}
