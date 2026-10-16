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
  namespace _
  {
    template<typename Type, typename Size = expected_cardinal_t<Type>>
    extern undefined<Type, Size> as_wide;

    template<typename Type, typename Size>
    requires (arithmetic_scalar_value<Type>)
    extern eve::wide<Type,Size> as_wide<Type,Size>;

    template<typename T, typename Size>
    extern eve::logical<decltype(as_wide<T,Size>)> as_wide<eve::logical<T>,Size>;

    template<typename Type, typename N, typename Size>
    extern eve::wide<Type,Size> as_wide<eve::wide<Type,N>,Size>;

    template<typename Type, typename N, typename Size>
    extern eve::logical<eve::wide<Type,Size>> as_wide<eve::logical<eve::wide<Type,N>>,Size>;

    template<typename T, typename U>
    extern undefined<Type, U> as_wide_as;

    template<value T, typename U>
    extern T as_wide_as<T, U>;

    template<scalar_value T, simd_value U>
    extern as_wide_t<T,cardinal_t<U>> as_wide_as<T, U>;
  }

  template<typename Type, typename Size = expected_cardinal_t<Type> >
  using as_wide_t = decltype(as_wide<Type, Size>);

  template<typename T, typename U>
  using as_wide_as_t = decltype(as_wide_as<std::remove_cvref_t<T>, std::remove_cvref_t<U>>);
}
