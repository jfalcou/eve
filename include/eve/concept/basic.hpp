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
        if constexpr(kumi::size<T>::value != 0)
        {
          using flatten_t = kumi::result::flatten_all_t<T>;
          return []<std::size_t... I>( std::index_sequence<I...> )
          {
            return (builtin_vectorizable<kumi::element_t<I,flatten_t>> && ... && true);
          }(std::make_index_sequence<kumi::size<flatten_t>::value>{});
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
