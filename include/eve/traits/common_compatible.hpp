//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/traits/as_floating_point.hpp>

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
  //================================================================================================
  //! @addtogroup traits Type Traits
  //! @{
  //!
  //! @struct common_compatible
  //!
  //! @brief Computes the type compatible with a list of [values](@ref value)
  //!
  //! If all `Ts...` are all identical to a given `T` and model eve::value, provides the member
  //! typedef `type` which is defined as `T`.
  //!
  //! If `Ts...` contains a set of types modeling eve::scalar_value and a set of types modeling
  //! eve::simd_value all identical to a given `T`, provides the member typedef `type` which is
  //! defined as `T`.
  //!
  //! Otherwise, the program is ill-formed.
  //!
  //! @tparam Ts Variadic list of types to process
  //!
  //! #### Member types
  //!
  //! |Name   | Definition                                      |
  //! |:------|:------------------------------------------------|
  //! |`type` | The type defined as compatible with all `Ts...` |
  //!
  //! <br/>
  //! #### Helper types
  //!
  //! @code{.cpp}
  //! template<typename Ts...>
  //! using common_compatible_t = typename common_compatible<Ts...>::type;
  //! @endcode
  //!
  //! <br/>
  //! #### Example
  //!
  //! [**See it live on Compiler Explorer**](https://godbolt.org/z/h8eePWxn3)
  //!
  //! @include{lineno} doc/traits/common_compatible.cpp
  //!
  //! @}
  //================================================================================================
  template<typename... Ts> struct common_compatible {};

  template<typename T> struct common_compatible<T>
  {
    using type = T;
  };

  template<typename T0, typename... Ts>
  struct common_compatible<T0,Ts...> : detail::common_compatible_impl<detail::types<T0,Ts...>>
  {};

  template<typename... Ts>
  using common_compatible_t = typename common_compatible<Ts...>::type;
}
