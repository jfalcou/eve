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
  concept plain_scalar  = std::is_same_v<T,float>         ||  std::is_same_v<T,double>
                      ||  std::is_same_v<T,std::int8_t>   ||  std::is_same_v<T,std::int16_t>
                      ||  std::is_same_v<T,std::int32_t>  ||  std::is_same_v<T,std::int64_t>
                      ||  std::is_same_v<T,std::uint8_t>  ||  std::is_same_v<T,std::uint16_t>
                      ||  std::is_same_v<T,std::uint32_t> ||  std::is_same_v<T,std::uint64_t>;

  namespace detail
  {
    template<typename T> constexpr bool scalar_tuple()
    {
      if constexpr(kumi::product_type<T>)
      {
        if constexpr(kumi::size<T>::value != 0)
        {
          using flatten_t = kumi::result::flatten_all_t<T>;
          return []<std::size_t... I>( std::index_sequence<I...> )
          {
            return (plain_scalar<kumi::element_t<I,flatten_t>> && ... && true);
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
  concept scalar  = plain_scalar<T> || detail::scalar_tuple<T>();
}
