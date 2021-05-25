//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <utility>

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

namespace eve
{
  template<std::size_t I,typename T, typename N, typename ABI> auto get(wide<T,N,ABI> w)
  {
    return w.get(I);
  }

  template<std::size_t I,typename T, typename N, typename ABI>
  auto get(logical<wide<T,N,ABI>> w)
  {
    return w.get(I);
  }
}
