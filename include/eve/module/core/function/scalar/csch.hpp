//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_CSCH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_CSCH_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/sinh.hpp>
#include <eve/function/rec.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto csch_(EVE_SUPPORTS(cpu_)
                                     , T a0) noexcept
  requires(T, floating_point<T>)
  {
    using t_abi = abi_type_t<T>;
    if constexpr(is_emulated_v<t_abi> ) return map(eve::csch, a0); 
    else if constexpr(is_aggregated_v<t_abi> ) return aggregate(eve::csch, a0);
    else
    {
      return rec(sinh(a0)); 
    }; 
  }
}

#endif
