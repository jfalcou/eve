//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/polynomial/detail/newton_impl.hpp>

namespace eve::detail
{
//================================================================================================
//== Newton with iterators
//================================================================================================

template<value T0, std::input_iterator IT0, std::input_iterator IT1>
EVE_FORCEINLINE constexpr auto
newton_(EVE_SUPPORTS(cpu_),
        numeric_type const&,
        T0         xx,
        IT0 const& firstc,
        IT0 const& lastc,
        IT1 const& firstn) noexcept
-> decltype( detail::newton_impl(numeric_type(), xx, firstc, lastc, firstn))
{
  return detail::newton_impl(numeric_type(), xx, firstc, lastc, firstn);
}

//================================================================================================
//== Newton with ranges
//================================================================================================
template<value T0, range R1, range R2>
EVE_FORCEINLINE constexpr auto
newton_(EVE_SUPPORTS(cpu_), numeric_type const&, T0 xx, R1 const& rc, R2 const& rn) noexcept
-> decltype(detail::newton_impl(numeric_type(), xx, rc, rn))
{
  return detail::newton_impl(numeric_type(), xx, rc, rn);
}
}
