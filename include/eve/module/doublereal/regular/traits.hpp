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
  template<floating_scalar_value Type> struct doublereal;

  template<typename T> struct as_doublereal;

  template<scalar_value T> struct as_doublereal<T>
  {
    using type = eve::doublereal<T>;
  };

  template<floating_scalar_value T> struct as_doublereal<doublereal<T>>
  {
    using type = eve::doublereal<T>;
  };

  template<floating_simd_value T> struct as_doublereal<T>
  {
    using type = eve::wide<eve::doublereal<element_type_t<T>>, cardinal_t<T>>;
  };

  template<floating_scalar_value T, typename N>
  struct as_doublereal<wide<doublereal<T>,N>>  { using type = wide<doublereal<T>,N>; };

  template<typename T>
  using as_doublereal_t = typename as_doublereal<T>::type;

  template<typename T>              struct as_real;
  template<floating_scalar_value T> struct as_real<doublereal<T>>  { using type = T; };
  template<floating_scalar_value T, typename N>
  struct as_real<wide<doublereal<T>,N>>  { using type = wide<T,N>; };

  template<typename T>
  using as_real_t = typename as_real<T>::type;

  template<typename T> struct is_doublereal                    : std::false_type {};
  template<typename T> struct is_doublereal<doublereal<T>>        : std::true_type {};
  template<typename T, typename N> struct is_doublereal<wide<doublereal<T>, N>>  : std::true_type {};

  template<typename T>
  inline constexpr bool is_doublereal_v = is_doublereal<T>::value;

  template<typename Wrapper, typename T>
  struct  supports_like<Wrapper,eve::doublereal<T>>
        : std::bool_constant<   std::same_as<eve::doublereal<T>, element_type_t<Wrapper>>
                            ||  std::same_as<T, element_type_t<Wrapper>>
                            ||  plain_scalar_value<Wrapper>
                            >
  {
  };

  namespace domain
  {
    using doublereal_converter = eve::decorated<eve::convert_by_<eve::as_doublereal, false>()>;
    inline constexpr doublereal_converter const doublereal = {};
  }

}
