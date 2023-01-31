//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include <eve/concept/value.hpp>
#include <eve/module/core/regular/converter.hpp>
#include <eve/traits.hpp>

namespace eve
{
  template<floating_scalar_value Type> struct dd;

  template<typename T> struct as_dd;

  template<scalar_value T> struct as_dd<T>
  {
    using type = eve::dd<T>;
  };

  template<floating_scalar_value T> struct as_dd<dd<T>>
  {
    using type = eve::dd<T>;
  };

  template<floating_simd_value T> struct as_dd<T>
  {
    using type = eve::wide<eve::dd<element_type_t<T>>, cardinal_t<T>>;
  };

  template<floating_scalar_value T, typename N>
  struct as_dd<wide<dd<T>,N>>  { using type = wide<dd<T>,N>; };

  template<typename T>
  using as_dd_t = typename as_dd<T>::type;

  template<typename T>              struct as_real;
  template<floating_scalar_value T> struct as_real<dd<T>>  { using type = T; };
  template<floating_scalar_value T, typename N>
  struct as_real<wide<dd<T>,N>>  { using type = wide<T,N>; };

  template<typename T>
  using as_real_t = typename as_real<T>::type;

  template<typename T> struct is_dd                    : std::false_type {};
  template<typename T> struct is_dd<dd<T>>        : std::true_type {};
  template<typename T, typename N> struct is_dd<wide<dd<T>, N>>  : std::true_type {};

  template<typename T>
  inline constexpr bool is_dd_v = is_dd<T>::value;

  template<typename Wrapper, typename T>
  struct  supports_like<Wrapper,eve::dd<T>>
        : std::bool_constant<   std::same_as<eve::dd<T>, element_type_t<Wrapper>>
                            ||  std::same_as<T, element_type_t<Wrapper>>
                            ||  plain_scalar_value<Wrapper>
                            >
  {
  };

  namespace domain
  {
    using dd_converter = eve::decorated<eve::convert_by_<eve::as_dd, false>()>;
    inline constexpr dd_converter const dd = {};
  }

}
