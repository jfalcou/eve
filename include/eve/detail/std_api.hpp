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
  template<std::size_t I, typename T, typename N>
  struct tuple_element<I, eve::wide<T, N>>
  {
    using type = T;
  };

  template<std::size_t I, typename T, typename N>
  struct tuple_element<I, eve::logical<eve::wide<T, N>>>
  {
    using type = eve::logical<T>;
  };

  template<typename T, typename N>
  struct tuple_size<eve::wide<T, N>> : N
  {
  };

  template<typename T, typename N>
  struct tuple_size<eve::logical<eve::wide<T, N>>> : N
  {
  };
}

namespace eve
{
  template<std::size_t I,typename T, typename N> auto get(wide<T,N> w)
  {
    return w.get(I);
  }

  template<std::size_t I,typename T, typename N>
  auto get(logical<wide<T,N>> w)
  {
    return w.get(I);
  }
}
