//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/forward.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/as.hpp>
#include <utility>

namespace eve
{
  template<typename Type, typename Size = expected_cardinal_t<Type>>
  struct as_wide;

  template<typename Type, typename Size>
  requires( std::is_arithmetic_v<Type>  || kumi::product_type<Type> )
  struct as_wide<Type,Size>
  {
    using type = eve::wide<Type,Size>;
  };

  template<typename T, typename Size>
  struct as_wide<eve::logical<T>,Size>
  {
    using type = eve::logical< typename as_wide<T,Size>::type >;
  };

  template<typename Type, typename N, typename Size>
  struct as_wide<eve::wide<Type,N>,Size>
  {
    using type = eve::wide<Type,Size>;
  };

  template<typename Type, typename N, typename Size>
  struct as_wide<eve::logical<eve::wide<Type,N>>,Size>
  {
    using type = eve::logical<eve::wide<Type,Size>>;
  };

  template<typename Type, typename Size = expected_cardinal_t<Type> >
  using as_wide_t = typename as_wide<Type, Size>::type;

  template<typename T, typename U>
  struct  as_wide_as
        : std::conditional< !simd_value<T> && simd_value<U>
                          , as_wide_t<T,cardinal_t<U>>
                          , T
                          >
  {};

  template<typename T, typename U>
  using as_wide_as_t = typename as_wide_as<T,U>::type;
}

