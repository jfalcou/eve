//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VSX_MUL_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_PPC_VSX_MUL_HPP_INCLUDED

#include <eve/wide.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/constant/constant.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T, typename N>
  EVE_FORCEINLINE wide<T, N, vsx_> mul_(EVE_SUPPORTS(vsx_),
                                        wide<T, N, ppc_> const &v0,
                                        wide<T, N, ppc_> const &v1) noexcept
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(std::is_same_v<T, float>)
        return vec_madd(v0.storage(),v1.storage(), bs::Mzero<V0>().storage());
      if constexpr(std::is_same_v<T, double>)
        return vec_mul(v0.storage(),v1.storage());
    }
    else
    {
      if constexpr(sizeof(T) == 1)
      {
        auto l = vec_mule(v0.storage(),v1.storage());
        auto r = vec_mulo(v0.storage(),v1.storage());
        return vec_mergel(vec_pack(l,l),vec_pack(r,r));
      }
      else if constexpr(sizeof(T) == 2)
      {
        vec_mladd(v0.storage(),v1.storage(),Zero<V0>().storage());
      }
      else if constexpr(sizeof(T) == 4)
      {
        return v0.storage() * v1.storage();
      }
      else 
      {
        return vec_mul(v0.storage(),v1.storage());
      }
    }
    
  }

}

#endif
