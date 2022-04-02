//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once
#include <eve/concept/value.hpp>
#include <eve/traits.hpp>

namespace eve
{
  template<floating_scalar_value Type> struct valder;

  template<typename T> struct as_valder;

  template<floating_scalar_value T> struct as_valder<T>
  {
    using type = eve::valder<T>;
  };

  template<floating_scalar_value T> struct as_valder<valder<T>>
  {
    using type = eve::valder<T>;
  };

  template<floating_simd_value T> struct as_valder<T>
  {
    using type = eve::wide<eve::valder<element_type_t<T>>, cardinal_t<T>>;
  };

  template<typename T>
  using as_valder_t = typename as_valder<T>::type;

  template<typename T>              struct as_val;
  template<value T>                 struct as_val<T>          { using type = T; };
  template<floating_scalar_value T> struct as_val<valder<T>>  { using type = T; };
  template<floating_scalar_value T, typename N>
  struct as_val<wide<valder<T>,N>>  { using type = wide<T,N>; };

  template<typename T>
  using as_val_t = typename as_val<T>::type;

  template<typename T> struct is_valder                   : std::false_type {};
  template<typename T> struct is_valder<valder<T>>        : std::true_type {};
  template<typename T> struct is_valder<wide<valder<T>>>  : std::true_type {};

  template<typename T>
  inline constexpr bool is_valder_v = is_valder<T>::value;

  template<typename T>
  struct as_logical<valder<T>> : as_logical_t<T>
  {};
  template<typename T, typename Sign>
  struct as_integer<valder<T>, Sign> : as_integer_t<T,  Sign>
  {};
  template<typename T>
  struct as_integer<valder<T>> : as_integer_t<T>
  {};
  template<typename T>
  struct as_uinteger<valder<T>> : as_uinteger_t<T>
  {};
}
