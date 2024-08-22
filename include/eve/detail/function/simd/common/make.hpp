//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>

#include <cstddef>

namespace eve::detail
{
  //================================================================================================
  // Emulation Helpers
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

  //================================================================================================
  // Aggregation Helpers
  //================================================================================================
  template<typename Pack, typename V0, typename... Vs>
  EVE_FORCEINLINE Pack make_aggregated(V0 v0, Vs... vs) noexcept
  {
    using sub_t = typename Pack::template rescale<typename Pack::cardinal_type::split_type>;

    // Package all values then split in 2 sides
    auto values = kumi::make_tuple(v0,vs...);
    auto [ls,hs] = kumi::split(values, kumi::index<Pack::size()/2>);

    // Rebuild sub-type with both parts of the pack of values
    auto constexpr build = [](auto... e) { return sub_t{e...}; };
    return Pack{ kumi::apply(build,ls), kumi::apply(build,hs) };
  }

  template<typename Pack, typename V> EVE_FORCEINLINE Pack make_aggregated( V v) noexcept
  {
    using sub_t = typename Pack::storage_type::value_type;
    Pack  that;

    that.storage().for_each( [sub_value = sub_t(v)](auto& s) { s = sub_value; } );

    return that;
  }

  template<callable_options O, typename Target, typename T0, typename... TS>
  EVE_FORCEINLINE constexpr auto make_(EVE_REQUIRES(cpu_), O const&, as<Target>, T0 v, TS... vs) noexcept
  {
    using type = typename Target::storage_type;
    using v_type = typename Target::value_type;

    if constexpr (has_aggregated_abi_v<Target>)
    {
      return make_aggregated<Target>(v, vs...);
    }
    else if constexpr (has_emulated_abi_v<Target>)
    {
      return make_emulated<Target>(v, vs...);
    }
    else if constexpr (kumi::product_type<Target>)
    {
      using kumi::get;
      type that;

      kumi::for_each_index( [&]<typename I, typename M>(I, M& m) { m = M{ get<I::value>(v), get<I::value>(vs)... }; }
                          , that
                          );

      return that;
    }
    else
    {
      if constexpr (sizeof...(vs) == 0)
      {
        return [&]<std::size_t... N>(std::index_sequence<N...> const&)
        {
          auto val = [](auto vv, auto)
          {
            if constexpr (logical_value<Target>) return as_logical_t<v_type>(vv).bits();
            else                                 return vv;
          };

          return type { val(v, N)... };
        }(std::make_index_sequence<Target::cardinal_type::value>());
      }
      else
      {
        if constexpr (logical_value<Target>) return type {as_logical_t<v_type>(v).bits(), as_logical_t<v_type>(vs).bits()...};
        else                                 return type {v, vs...};
      }
    }
  }
}
