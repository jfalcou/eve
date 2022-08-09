//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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
  };

    template<typename A, typename B, int S1, int V1, int S2, int V2>
    constexpr auto operator%(cmn<A,S1,V1>, cmn<B,S2,V2>)
    {
      constexpr bool sa = scalar_value<A> , sb  = scalar_value<B>;
      constexpr bool va = simd_value<A>   , vb  = simd_value<B>;
      constexpr int mxs = std::max(S1,S2) , mxv = std::max(V1,V2);

            if constexpr(std::same_as<A,B>) return cmn<A,mxs  ,mxv  >{};
      else  if constexpr(va && vb)          return cmn<A,mxs  ,mxv+1>{};
      else  if constexpr(sa && sb)          return cmn<A,mxs+1,mxv  >{};
      else  if constexpr(va && sb)          return cmn<A,mxs  ,mxv  >{};
      else  if constexpr(sa && vb)          return cmn<B,mxs  ,mxv  >{};
      else  if constexpr(value<A>)          return cmn<A,S1,V1>{};
      else                                  return cmn<B,S2,V2>{};
    }

  // Use a layer of std::void_t to make common_compatible SFINAE-friendly
  template<typename L, typename Enable = void>
  struct  common_compatible_impl
  {};

  template<typename T>
  using cmn_t = detail::cmn<T, scalar_value<T>, simd_value<T>>;

  template<typename... Ts>
  auto compact(){ return (cmn_t<Ts>{} % ... ); }

  template<typename... Ts>
  struct  common_compatible_impl
          < types<Ts...>
          , std::enable_if_t<decltype( compact<Ts...>() )::is_valid>
          >
  {
    using base = decltype(compact<Ts...>());
    using type = typename base::type;
  };
}

namespace eve
{
  //================================================================================================
  //! @addtogroup traits
  //! @{
  //!
  //! @struct common_compatible
  //!
  //! @brief Computes the type compatible with a list of [values](@ref eve::value)
  //!
  //! **Required header:** `#include <eve/traits/common_compatible.hpp>`
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

  template < typename... Ts> using common_compatible_floating_t =
    as_floating_point_t<common_compatible_t<Ts...>>;

  template < typename... Ts> using common_compatible_floating_elt_t =
    element_type_t<common_compatible_floating_t<Ts...>>;
}
