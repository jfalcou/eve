//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_APPLY_OVER_HPP_INCLUDED
#define EVE_DETAIL_APPLY_OVER_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/abi.hpp>

namespace eve::detail
{
  
  template<typename Obj, simd_value T>
  EVE_FORCEINLINE auto apply_over(Obj f, T const & v)
  {
    using t_abi = abi_type_t<T>;
         if constexpr(aggregated<t_abi>) return aggregate(f, v);
    else if constexpr(emulated<t_abi>)   return map(f, v);
  }
}

#endif
