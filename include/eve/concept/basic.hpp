//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <type_traits>
#include <cstdint>
#include <cstddef>

namespace eve
{
  template<typename T>
  concept builtin_vectorizable  =     std::is_arithmetic_v<T>
                                  && !std::is_same_v<T,bool>
                                  &&  sizeof(T) <= 8;

  namespace detail
  {
    template<typename T> constexpr bool vectorizable_tuple()
    {
      if constexpr(kumi::product_type<T>)
      {
        constexpr auto sz = kumi::size<T>::value;

        if constexpr(sz != 0)
        {
          return []<std::size_t... I>( std::index_sequence<I...> )
          {
            return (builtin_vectorizable<kumi::element_t<I,T>> && ... && true);
          }(std::make_index_sequence<sz>{});
        }
        else
        {
          return false;
        }
      }
      else
      {
        return false;
      }
    }
  }

  template<typename T>
  concept vectorizable  = builtin_vectorizable<T> || detail::vectorizable_tuple<T>();
}
