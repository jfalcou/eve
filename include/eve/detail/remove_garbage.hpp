//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/traits.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <utility>

namespace eve::detail
{
  template<typename W> auto remove_garbage(W v) noexcept
  {
    using v_t   = element_type_t<W>;
    using c_t   = cardinal_t<W>;
    using ec_t  = expected_cardinal_t<v_t, typename W::abi_type>;

    if constexpr(c_t::value < ec_t::value)
    {
      auto const exact_mask = []<std::size_t... I>(std::index_sequence<I...>)
      {
        return as_logical_t<as_wide_t<v_t,ec_t>>((I<c_t::value)...).mask();
      }(std::make_index_sequence<ec_t::value>{});

      v = bit_cast(bit_cast(v,as<as_wide_t<v_t,ec_t>>()) & exact_mask, as(v));
    }

    return v;
  }
}
