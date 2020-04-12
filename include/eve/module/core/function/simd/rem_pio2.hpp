//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
#include <eve/arch/wide.hpp>
#include <type_traits>
#include <tuple>
#include <array>

namespace eve::detail
{
  template<typename T, typename N,  typename ABI>
  EVE_FORCEINLINE std::tuple<wide<T, N, ABI>, wide<T, N, ABI>, wide<T, N, ABI>>
  rem_pio2_(EVE_SUPPORTS(cpu_)
           , wide<T, N, ABI> const &a0) noexcept
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      using t_t  =  wide<T, N, ABI>;
      using r_t = std::tuple<t_t, t_t, t_t>;

      static constexpr uint32_t size = N::value;
      alignas(t_t::static_alignment) std::array<T, size> tmp;
      alignas(t_t::static_alignment) std::array<T, size> txr;
      alignas(t_t::static_alignment) std::array<T, size> tyr;
      for(uint32_t i=0; i!=size; ++i)
      {
        std::tie(tmp[i],txr[i],tyr[i]) =  eve::rem_pio2(a0[i]);
      }
      return r_t( load(eve::as_aligned<t_t::static_alignment>(&tmp[ 0 ]), eve::as_<t_t>())
                , load(eve::as_aligned<t_t::static_alignment>(&txr[ 0 ]), eve::as_<t_t>())
                , load(eve::as_aligned<t_t::static_alignment>(&tyr[ 0 ]), eve::as_<t_t>()));
    }
    else
    {
      static_assert(std::is_floating_point_v<value_type_t<T>>, "rem_pio2 parameteris not IEEEValue");
      return {T{}, T{}, T{}};
    }
  }
}

#endif
