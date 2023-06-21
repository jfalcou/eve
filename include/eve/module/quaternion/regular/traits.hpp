//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include <eve/concept/value.hpp>
#include <eve/module/complex.hpp>
#include <eve/module/core/regular/converter.hpp>
#include <eve/traits.hpp>

namespace eve
{
  template<floating_scalar_value Type> struct quaternion;

  template<typename T> struct as_quaternion;

  template<scalar_value T> struct as_quaternion<T>
  {
    using type = eve::quaternion<T>;
  };

  template<floating_scalar_value T> struct as_quaternion<quaternion<T>>
  {
    using type = eve::quaternion<T>;
  };

  template<floating_simd_value T> struct as_quaternion<T>
  {
    using type = eve::wide<eve::quaternion<element_type_t<T>>, cardinal_t<T>>;
  };

  template<floating_scalar_value T, typename N>
  struct as_quaternion<wide<quaternion<T>,N>>  { using type = wide<quaternion<T>,N>; };

//   template<typename T>
//   using as_quaternion_t = typename as_quaternion<T>::type;

//   template<typename T>              struct as_real;
//   template<value T>                 struct as_real<T>           { using type = T; };
//   template<floating_scalar_value T> struct as_real<quaternion<T>>  { using type = T; };
//   template<floating_scalar_value T, typename N>
//   struct as_real<wide<quaternion<T>,N>>  { using type = wide<T,N>; };

//   template<typename T>
//   using as_real_t = typename as_real<T>::type;

  template<typename T> struct is_quaternion                       : std::false_type {};
  template<typename T> struct is_quaternion<quaternion<T>>        : std::true_type {};
  template<typename T, typename N> struct is_quaternion<wide<quaternion<T>, N>>  : std::true_type {};

  template<typename T>
  inline constexpr bool is_quaternion_v = is_quaternion<T>::value;

  template<typename Wrapper, typename T>
  struct  supports_like<Wrapper,eve::quaternion<T>>
        : std::bool_constant<   std::same_as<eve::quaternion<T>, element_type_t<Wrapper>>
                            ||  std::same_as<T, element_type_t<Wrapper>>
                            ||  plain_scalar_value<Wrapper>
                            >
  {
  };

  namespace domain
  {
    using quaternion_converter = eve::decorated<eve::convert_by_<eve::as_quaternion, false>()>;
    inline constexpr quaternion_converter const quaternion = {};
  }
}
