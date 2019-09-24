//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_REM_PIO2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_REM_PIO2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/load.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/wide.hpp>
#include <type_traits>
#include <tuple>
#include <array>

namespace eve::detail
{
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE std::tuple<wide<T, N, ABI>, wide<T, N, ABI>>
  rem_pio2_(EVE_SUPPORTS(cpu_)
           , wide<T, N, ABI> const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      using t_t  =  wide<T, N, ABI>; 
      using r_t = std::pair<t_t, t_t>;
      
      static constexpr uint32_t size = N::value;
      alignas(t_t::static_alignment) std::array<T, size> tmp;
      alignas(t_t::static_alignment) std::array<T, size> txr;
      for(uint32_t i=0; i!=size; ++i)
      {
        std::tie(tmp[i],txr[i]) =  eve::rem_pio2(a0[i]);
      }
      return r_t( load(&tmp[0], eve::as_<t_t>())
                , load(&txr[0], eve::as_<t_t>()));
    }
    else
    {
      static_assert(std::is_floating_point_v<value_type_t<T>>, "rem_pio2 paramete is not IEEEValue");
      return {T{}, T{}}; 
    }
  }
}

#endif
