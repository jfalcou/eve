//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/arithmetic/regular/binarize_not.hpp>
#include <eve/module/arithmetic/regular/div.hpp>
#include <eve/module/arithmetic/regular/fnma.hpp>
#include <eve/module/arithmetic/regular/is_nez.hpp>

namespace eve::detail
{
  template<real_value T, real_value U>
  EVE_FORCEINLINE auto remdiv_ ( EVE_SUPPORTS(cpu_)
                            , pedantic_type const&,T const &a, U const &b
                            ) noexcept
  requires compatible_values<T, U>
  {
    using r_t = common_compatible_t<T, U>;
    if constexpr(has_native_abi_v<T>&& has_native_abi_v<U>)
    {
      auto d = pedantic(div)(a,b);
      if constexpr(floating_real_value<T>)
      {
        auto r = if_else(is_unordered(a, b) || is_infinite(a) || is_eqz(b)
                        , allbits
                        , if_else(is_eqz(a)
                                 , a
                                 , fnma(b, d, a)
                                 )
                        );
        return kumi::make_tuple( r_t(r), r_t(d) );
      }
      else
      {
        auto r = if_else(is_nez(b), fnma(b, d, a), a);
        return kumi::make_tuple( r_t(r), r_t(d) );
      }
    }
    else return apply_over2(remdiv, r_t(a), r_t(b));
  }

}
