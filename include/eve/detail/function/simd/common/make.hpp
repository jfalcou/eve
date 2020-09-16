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
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

#include <cstddef>

namespace eve::detail
{
  //================================================================================================
  // Emulation
  //================================================================================================
  template<typename Pack, typename V0, typename... Values>
  EVE_FORCEINLINE Pack make(eve::as_<Pack> const &, eve::emulated_ const &, V0 v0, Values... vs) noexcept
  {
    using type = typename Pack::value_type;
    Pack        that;
    std::size_t i = 0;

    that[i++] = static_cast<type>(v0);
    ((that[i++] = vs), ...);

    return that;
  }

  template<typename Pack, typename Value>
  EVE_FORCEINLINE Pack make(eve::as_<Pack> const &, eve::emulated_ const &, Value vs) noexcept
  {
    using type = typename Pack::value_type;
    Pack that;
    for( auto &e : that ) e = static_cast<type>(vs);
    return that;
  }

  //================================================================================================
  // Aggregation
  //================================================================================================
  template<typename Pack, typename V0, typename... Values>
  EVE_FORCEINLINE Pack
  make(eve::as_<Pack> const &, eve::aggregated_ const &, V0 v0, Values... vs) noexcept
  {
    using type = typename Pack::value_type;
    Pack        that;
    std::size_t i = 0;

    that.set(i++, static_cast<type>(v0));
    ((that.set(i++, vs)), ...);

    return that;
  }

  template<typename Pack, typename Value>
  EVE_FORCEINLINE Pack make(eve::as_<Pack> const &, eve::aggregated_ const &, Value vs) noexcept
  {
    using sub_t = typename Pack::storage_type::value_type;
    Pack  that;

    that.storage().for_each( [sub_value = sub_t(vs)](auto& s) { s = sub_value; } );

    return that;
  }
}

