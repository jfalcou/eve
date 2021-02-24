//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
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
  template<typename Pack, typename V0, typename... Vs>
  EVE_FORCEINLINE auto make_emulated(V0 v0, Vs... vs) noexcept
  {
    using s_t = typename Pack::storage_type;
    using t_t = typename Pack::value_type;
    return s_t{static_cast<t_t>(v0), static_cast<t_t>(vs)...};
  }

  template<typename Pack, typename V> EVE_FORCEINLINE auto make_emulated(V v) noexcept
  {
    using s_t = typename Pack::storage_type;
    using t_t = typename Pack::value_type;
    return [&]<std::size_t... N>( std::index_sequence<N...> )
    {
      return s_t{ ((void)N,static_cast<t_t>(v))... };
    }(std::make_index_sequence<s_t{}.size()>{});
  }

  template<typename T, typename N, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as_<wide<T,N,emulated_>> const &, Vs... vs) noexcept
  {
    return make_emulated<wide<T,N,emulated_>>(vs...);
  }

  template<typename T, typename N, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as_<logical<wide<T,N,emulated_>>> const &, Vs... vs) noexcept
  {
    return make_emulated<logical<wide<T,N,emulated_>>>(vs...);
  }

  //================================================================================================
  // Aggregation
  //================================================================================================
  template<typename Pack, typename V0, typename... Vs>
  EVE_FORCEINLINE Pack make_aggregated(V0 v0, Vs... vs) noexcept
  {
    using t_t = typename Pack::value_type;
    Pack that;

    that.set(0, static_cast<t_t>(v0));
    [&]<std::size_t... N>( std::index_sequence<N...> )
    {
      (that.set(N+1, static_cast<t_t>(vs)),...);
    }(std::make_index_sequence<sizeof...(Vs)>{});

    return that;
  }

  template<typename Pack, typename V> EVE_FORCEINLINE Pack make_aggregated( V v) noexcept
  {
    using sub_t = typename Pack::storage_type::value_type;
    Pack  that;

    that.storage().for_each( [sub_value = sub_t(v)](auto& s) { s = sub_value; } );

    return that;
  }

  template<typename T, typename N, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as_<wide<T,N,aggregated_>> const &, Vs... vs) noexcept
  {
    return make_aggregated<wide<T,N,aggregated_>>(vs...);
  }

  template<typename T, typename N, typename... Vs>
  EVE_FORCEINLINE auto make(eve::as_<logical<wide<T,N,aggregated_>>> const &, Vs... vs) noexcept
  {
    return make_aggregated<logical<wide<T,N,aggregated_>>>(vs...);
  }
}
