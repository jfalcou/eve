//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/deps/kumi.hpp>
#include <eve/detail/wide_forward.hpp>
#include <eve/as.hpp>

namespace eve
{
  template<typename Type, cardinal_type Cardinal = expected_cardinal_v<Type>>
  struct as_wide
  {
    // This case should never be picked up but clang++ insists on trying to
    // instantiate it in place it makes no sense. We return void so clang
    // lets the code compile as it should.
    using type = void;
  };

  template<typename Type, cardinal_type Cardinal>
  requires (arithmetic_scalar_value<Type>)
  struct as_wide<Type,Cardinal>
  {
    using type = eve::wide<Type,Cardinal>;
  };

  template<typename T, cardinal_type Cardinal>
  struct as_wide<eve::logical<T>,Cardinal>
  {
    using type = eve::logical< typename as_wide<T,Cardinal>::type >;
  };

  template<typename Type, cardinal_type N, cardinal_type Cardinal>
  struct as_wide<eve::wide<Type,N>,Cardinal>
  {
    using type = eve::wide<Type,Cardinal>;
  };

  template<typename Type, cardinal_type N, cardinal_type Cardinal>
  struct as_wide<eve::logical<eve::wide<Type,N>>,Cardinal>
  {
    using type = eve::logical<eve::wide<Type,Cardinal>>;
  };

  template<typename Type, cardinal_type Cardinal = expected_cardinal_v<Type> >
  using as_wide_t = typename as_wide<Type, Cardinal>::type;

  template<typename T, typename U>
  struct  as_wide_as;


  template<scalar_value T, simd_value U>
  struct as_wide_as<T, U> {
    using type = as_wide_t<T,cardinal_v<U>>;
  };

  template<value T, typename U>
  struct as_wide_as<T, U> {
    using type = T;
  };

  template<typename T, typename U>
  using as_wide_as_t = typename as_wide_as<std::remove_cvref_t<T>, std::remove_cvref_t<U>>::type;
}
