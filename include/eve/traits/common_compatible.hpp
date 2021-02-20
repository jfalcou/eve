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

#include <eve/concept/value.hpp>
#include <eve/traits/as_floating_point.hpp>
#include <concepts>

namespace eve::detail
{
  template<typename T,int S,int V> struct cmn
  {
    using type = T;
    static constexpr bool is_valid = (V==1) || (V==0 && S==1);

    template<value A, int S1, int V1, int S2, int V2>
    friend cmn<A,std::max(S1,S2),std::max(V1,V2)> operator%(cmn<A,S1,V1>, cmn<A,S2,V2>);

    template<simd_value A, simd_value B, int S1, int V1, int S2, int V2>
    friend cmn<A,std::max(S1,S2),std::max(V1,V2)+1> operator%(cmn<A,S1,V1>, cmn<B,S2,V2>);

    template<scalar_value A, scalar_value B, int S1, int V1, int S2, int V2>
    friend cmn<A,std::max(S1,S2)+1,std::max(V1,V2)> operator%(cmn<A,S1,V1>, cmn<B,S2,V2>);

    template<simd_value A, scalar_value B, int S1, int V1, int S2, int V2>
    friend cmn<A,std::max(S1,S2),std::max(V1,V2)> operator%(cmn<A,S1,V1>, cmn<B,S2,V2>);

    template<scalar_value A, simd_value B, int S1, int V1, int S2, int V2>
    friend cmn<B,std::max(S1,S2),std::max(V1,V2)> operator%(cmn<A,S1,V1>, cmn<B,S2,V2>);
  };

  // Use a layer of std::void_t to make common_compatible SFINAE-friendly
  template<typename L, typename Enable = void>
  struct  common_compatible_impl
  {};

  template<typename... Ts>
  struct  common_compatible_impl< types<Ts...>
                                , std::enable_if_t< decltype( (detail::cmn< Ts
                                                                          , scalar_value<Ts>
                                                                          , simd_value<Ts>
                                                                          >{}
                                                              % ... )
                                                            )::is_valid
                                                  >
                                >
        : decltype( (detail::cmn<Ts,scalar_value<Ts>,simd_value<Ts>>{} % ... ) )
  {};
}

namespace eve
{
  template<typename... Ts> struct common_compatible;

  template<typename T> struct common_compatible<T>
  {
    using type = T;
  };

  template<typename T0, typename... Ts>
  struct common_compatible<T0,Ts...> : detail::common_compatible_impl<detail::types<T0,Ts...>>
  {};

  template<typename... Ts>
  using common_compatible_t = typename common_compatible<Ts...>::type;


  template < typename... Ts> using common_compatible_floating_t =
    as_floating_point_t<common_compatible_t<Ts...>>;

  template < typename... Ts> using common_compatible_floating_elt_t =
    element_type_t<common_compatible_floating_t<Ts...>>;
}
