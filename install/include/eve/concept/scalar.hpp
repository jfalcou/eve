//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/kumi.hpp>
#include <eve/detail/meta.hpp>

#include <cstddef>
#include <cstdint>

#include <type_traits>

namespace eve
{
template<typename T>
concept plain_scalar_value = detail::one_of<T,
                                            float,
                                            double,
                                            std::int8_t,
                                            std::int16_t,
                                            std::int32_t,
                                            std::int64_t,
                                            std::uint8_t,
                                            std::uint16_t,
                                            std::uint32_t,
                                            std::uint64_t>;

namespace detail
{
  template<typename T> constexpr bool scalar_tuple()
  {
    if constexpr( kumi::product_type<T> )
    {
      return kumi::size_v<T> ? kumi::all_of(kumi::flatten_all(kumi::as_tuple_t<T> {}),
                                            []<typename M>(M) { return plain_scalar_value<M>; })
                             : false;
    }
    else { return false; }
  }
}

template<typename T>
concept product_scalar_value = detail::scalar_tuple<T>();

template<typename T>
concept arithmetic_scalar_value = plain_scalar_value<T> || product_scalar_value<T>;
}
