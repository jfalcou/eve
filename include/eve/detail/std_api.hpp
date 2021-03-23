//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <tuple>

#ifdef __clang__
#  pragma clang diagnostic push
#  pragma clang diagnostic ignored "-Wmismatched-tags"
#endif

namespace std
{
  template<std::size_t I, typename T, typename N, typename ABI>
  struct tuple_element<I, eve::wide<T, N, ABI>>
  {
    using type = T;
  };

  template<std::size_t I, typename T, typename N, typename ABI>
  struct tuple_element<I, eve::logical<eve::wide<T, N, ABI>>>
  {
    using type = eve::logical<T>;
  };

  template<typename T, typename N, typename ABI>
  struct tuple_size<eve::wide<T, N, ABI>> : N
  {
  };

  template<typename T, typename N, typename ABI>
  struct tuple_size<eve::logical<eve::wide<T, N, ABI>>> : N
  {
  };
}
#ifdef __clang__
#  pragma clang diagnostic pop
#endif

namespace eve
{
  template<std::size_t I, typename Derived>
  auto get(detail::wide_ops<Derived> const &w)
  {
    return w.get(I);
  }
}
