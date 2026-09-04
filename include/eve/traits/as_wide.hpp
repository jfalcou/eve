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
  template<typename Type, std::ptrdiff_t Width = expected_width_v<Type>>
  struct as_wide
  {
    // This case should never be picked up but clang++ insists on trying to
    // instantiate it in place it makes no sense. We return void so clang
    // lets the code compile as it should.
    using type = void;
  };

  template<typename Type, width_type Width>
  requires (arithmetic_scalar_value<Type>)
  struct as_wide<Type,Width>
  {
    using type = eve::wide<Type,Width>;
  };

  template<typename T, width_type Width>
  struct as_wide<eve::logical<T>,Width>
  {
    using type = eve::logical< typename as_wide<T,Width>::type >;
  };

  template<typename Type, width_type N, width_type Width>
  struct as_wide<eve::wide<Type,N>,Width>
  {
    using type = eve::wide<Type,Width>;
  };

  template<typename Type, width_type N, width_type Width>
  struct as_wide<eve::logical<eve::wide<Type,N>>,Width>
  {
    using type = eve::logical<eve::wide<Type,Width>>;
  };

  template<typename Type, width_type Width = expected_width_v<Type> >
  using as_wide_t = typename as_wide<Type, Width>::type;

  template<typename T, typename U>
  struct  as_wide_as;


  template<scalar_value T, simd_value U>
  struct as_wide_as<T, U> {
    using type = as_wide_t<T,width_v<U>>;
  };

  template<value T, typename U>
  struct as_wide_as<T, U> {
    using type = T;
  };

  template<typename T, typename U>
  using as_wide_as_t = typename as_wide_as<std::remove_cvref_t<T>, std::remove_cvref_t<U>>::type;
}
