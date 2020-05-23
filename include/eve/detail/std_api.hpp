//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_STD_API_HPP_INCLUDED
#define EVE_DETAIL_STD_API_HPP_INCLUDED

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
    using type = T;
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
  template<std::size_t I, typename T, typename N, typename ABI>
  auto get(wide<T, N, ABI> const &w)
  {
    return w[ I ];
  }

  template<std::size_t I, typename T, typename N, typename ABI>
  auto &get(wide<T, N, ABI> &w)
  {
    return w[ I ];
  }

  template<std::size_t I, typename T, typename N, typename ABI>
  auto get(logical<wide<T, N, ABI>> const &w)
  {
    return w[ I ];
  }

  template<std::size_t I, typename T, typename N, typename ABI>
  auto &get(logical<wide<T, N, ABI>> &w)
  {
    return w[ I ];
  }
}

#endif
