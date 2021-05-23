//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/forward.hpp>
#include <eve/detail/is_wide.hpp>
#include <utility>
#include <array>

namespace eve
{
  template<typename Type, typename Size = expected_cardinal_t<Type>>
  struct as_wide;

  template<typename Type, typename Size> requires( std::is_arithmetic_v<Type> )
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

  //================================================================================================
  // Special case : kumi::tuple
  //================================================================================================
  template<typename... Ts, typename Size>
  struct as_wide<kumi::tuple<Ts...>,Size>
  {
    using type = kumi::tuple<typename as_wide<Ts,Size>::type...>;
  };

  template<typename Type, typename Size = expected_cardinal_t<Type> >
  using as_wide_t = typename as_wide<Type, Size>::type;
}

