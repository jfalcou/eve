//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ALL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ALL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/extract.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<value T>
  EVE_FORCEINLINE bool all_(EVE_SUPPORTS(cpu_)
                           , T const &v) noexcept
  {
    if constexpr(scalar_value<T>)
    {
      return bool(v);
    }
    else if constexpr(logical_simd_value<T>)
    {
      if constexpr(has_aggregated_abi_v<T>)
      {
        return v.storage().apply( [](auto const&... e) { return eve::all((e.bits() & ...)); } );
      }
      else
      {
        for(int i=0; i < cardinal_v<T> ; ++i)
        {
          if (!extract(v, i)) return false;
        }
        return true;
      }
    }
    else
    {
      return all(is_nez(v));
    }
  }
}

#endif
