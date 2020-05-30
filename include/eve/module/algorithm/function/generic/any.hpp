//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_ALGORITHM_FUNCTION_GENERIC_ANY_HPP_INCLUDED
#define EVE_MODULE_ALGORITHM_FUNCTION_GENERIC_ANY_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/function/is_nez.hpp>

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE bool any_(EVE_SUPPORTS(cpu_)
                           , T const &v) noexcept
  {
    if constexpr(scalar_value<T>)
    {
      return bool(v);
    }
    else if constexpr(logical_simd_value<T>)
    {
      if constexpr( has_aggregated_abi_v<T> )
      {
        return v.storage().apply([](auto const &... e) { return eve::any((e.bits() | ...)); });
      }
      else
      {
        bool r = false;

        [&]<std::size_t... I>(std::index_sequence<I...> const &) { r = (r || ... || get<I>(v)); }
        (std::make_index_sequence<cardinal_v<T>> {});

        return r;
      }
    }
    else
    {
      return any(is_nez(v));
    }
  }
}

#endif
