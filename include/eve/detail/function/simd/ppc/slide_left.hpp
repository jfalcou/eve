//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/conditional.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, ppc_abi ABI, std::ptrdiff_t Shift>
  EVE_FORCEINLINE wide<T,N,ABI> slide_left_ ( EVE_SUPPORTS(vmx_)
                                            , wide<T,N,ABI> v, index_t<Shift>
                                            ) noexcept
  requires(Shift<=N::value)
  {
    using that_t  = wide<T,N,ABI>;

    if constexpr(Shift == N::value)
    {
      return that_t{0};
    }
    else if constexpr(Shift == 0)
    {
      return v;
    }
    else
    {
      if constexpr( std::same_as<T,double> )
      {
        using i_t = as_integer_t<wide<T,N,ABI>>;
        return bit_cast(slide_left(bit_cast(v, as_<i_t>()), index<Shift> ), as(v));
      }
      else
      {
        constexpr unsigned char offset = (Shift * sizeof(T)) << 3;
        __vector signed char shift = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,offset};
        that_t result = vec_slo( v.storage(), shift );

        // Mask noises from smaller sized registers
        if constexpr(N::value < expected_cardinal_v<T,ppc_>)
        {
          result &= keep_first(N::value-Shift).mask(as(result)).bits();
        }

        return result;
      }
    }
  }
}
