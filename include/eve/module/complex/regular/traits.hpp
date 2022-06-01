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
  template<floating_scalar_value Type> struct complex;

  template<typename T> struct as_complex;

  template<floating_scalar_value T> struct as_complex<T>
  {
    using type = eve::complex<T>;
  };

  template<floating_scalar_value T> struct as_complex<complex<T>>
  {
    using type = eve::complex<T>;
  };

  template<floating_simd_value T> struct as_complex<T>
  {
    using type = eve::wide<eve::complex<element_type_t<T>>, cardinal_t<T>>;
  };

  template<floating_scalar_value T, typename N>
  struct as_complex<wide<complex<T>,N>>  { using type = wide<complex<T>,N>; };

  template<typename T>
  using as_complex_t = typename as_complex<T>::type;

  template<typename T>              struct as_real;
  template<value T>                 struct as_real<T>           { using type = T; };
  template<floating_scalar_value T> struct as_real<complex<T>>  { using type = T; };
  template<floating_scalar_value T, typename N>
  struct as_real<wide<complex<T>,N>>  { using type = wide<T,N>; };

  template<typename T>
  using as_real_t = typename as_real<T>::type;

  template<typename T> struct is_complex                    : std::false_type {};
  template<typename T> struct is_complex<complex<T>>        : std::true_type {};
  template<typename T, typename N> struct is_complex<wide<complex<T>, N>>  : std::true_type {};

  template<typename T>
  inline constexpr bool is_complex_v = is_complex<T>::value;

  template<typename T>
  struct as_logical<complex<T>> : as_logical_t<T>
  {};
}
