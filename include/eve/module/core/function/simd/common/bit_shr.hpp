//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BIT_SHR_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_BIT_SHR_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/shr.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U>
  EVE_FORCEINLINE auto bit_shr_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
  requires(T, vectorized<T>, integral<value_type_t<U>>, integral<value_type_t<T>>)
  {
    using t_abi = abi_type_t<T>;
    using u_abi = abi_type_t<U>;

    if constexpr(is_emulated_v<t_abi> || is_emulated_v<u_abi>)
    {
      return map(eve::bit_shr, a, b);
    }
    else if constexpr(is_aggregated_v<t_abi> || is_aggregated_v<u_abi>)
    {
      return aggregate(eve::bit_shr, a, b);
    }
    else
    {
      if constexpr(is_vectorizable_v<U>)
      {
        using u_t = wide<as_integer_t<value_type_t<T>, unsigned>
                               , typename T::cardinal_type, t_abi>;
        return bit_cast(eve::shr(bit_cast(a,as_<u_t>()), int(b)),as(a));
      }
      else
      {
        return bit_cast(map(eve::bit_shr, a, b), as(a));
      }
    }
  }
}

#endif
