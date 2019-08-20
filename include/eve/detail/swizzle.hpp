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

#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/patterns.hpp>
#include <type_traits>

// TODO: std:bitcast instead
#include <eve/function/bit_cast.hpp>

namespace eve::detail
{
  //----------------------------------------------------------------------------------------------
  // Handle Zeroing
  template<typename Pack, typename Pattern>
  EVE_FORCEINLINE auto process_zeros( Pack const& v, Pattern p ) noexcept
  {
    constexpr auto sz = Pattern::size(cardinal_v<Pack>);
    using type = typename Pack::value_type;

    if constexpr( p.has_zeros(sz) )
    {
      // Turn pattern into 0/~0 then mask
      auto const impl = [=](auto... i)
                        {
                          using i_t = as_integer_t<type,unsigned>;
                          constexpr i_t nz = ~i_t(0), zz = i_t(0);
                          return Pack(bit_cast((p(i,sz)==-1 ? zz : nz),as_<type>())...);
                        };

      return v & apply<sz>(impl);
    }
    else
    {
      return v;
    }
  }

  //----------------------------------------------------------------------------------------------
  // Index to bytes conversion
  template<typename Pack, typename Shuffler, std::size_t... I>
  EVE_FORCEINLINE constexpr auto as_bytes_impl(Shuffler p, std::index_sequence<I...> const &)
  {
    constexpr auto sz = Shuffler::size(Pack::size());
    constexpr auto b = sizeof(typename Pack::value_type);

    return values< (p(I/b,sz) == -1 ? 0xFF : p(I/b,sz)*b+I%b) ...>();
  }

  template<typename Pack, typename Shuffler, typename Bytes>
  EVE_FORCEINLINE constexpr auto as_bytes(Shuffler p, as_<Bytes> const&) noexcept
  {
    constexpr auto bytes = as_bytes_impl<Pack>(p, std::make_index_sequence<Bytes::size()>{});
    return apply( [](auto... v) { return Bytes(v...); }, bytes);
  }
}
