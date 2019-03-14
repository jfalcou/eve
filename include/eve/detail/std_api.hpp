//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_STD_API_HPP_INCLUDED
#define EVE_DETAIL_STD_API_HPP_INCLUDED

#include <tuple>

namespace std
{
  template<std::size_t I, typename T, typename N, typename ABI>
  struct tuple_element<I, eve::wide<T,N,ABI>>
  {
    using type = T;
  };

  template<typename T, typename N, typename ABI>
  struct tuple_size<eve::wide<T,N,ABI>> : N
  {};
}

namespace eve
{
  template<std::size_t I, typename T, typename N, typename ABI>
  auto get( wide<T,N,ABI> const& w)
  {
    return w[I];
  }

  template<std::size_t I, typename T, typename N, typename ABI>
  auto& get( wide<T,N,ABI>& w)
  {
    return w[I];
  }
}

#endif


