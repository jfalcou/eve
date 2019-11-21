//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ULP_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ULP_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/min.hpp>
#include <eve/function/sub.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto ulp_(EVE_SUPPORTS(cpu_)
                                     , T const &a0) noexcept
  requires(T, behave_as<floating_point,T>)
  {
    using t_abi = abi_type_t<T>;
    if constexpr(is_aggregated_v<t_abi>)
    {
      return aggregate(ulp, a0);
    }
    else if constexpr(is_emulated_v<t_abi>)
    {
      return map(ulp, a0);
    }
    using i_t = as_integer_t<T,unsigned>;
    auto x = eve::abs(a0);
    i_t aa = bitwise_cast(x, as<i_t>());
    i_t bb = dec(aa);
    aa = inc(aa);
    return if_else(is_eqz(a0)
                  , Mindenormal<T>()
                  , if_else(is_not_finite(a0)
                           , Nan<T>(), 
                            eve::min(x-bitwise_cast(bb, as<T>())
                                    , bitwise_cast(aa, as<T>())-x)
                           )
                  );
  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto ulp_(EVE_SUPPORTS(cpu_)
                                     , T const &a) noexcept
  requires(T, behave_as<integral,T>)
  {
    return T(1); 
  }
}

#endif
