//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/func/bit_cast.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N, std::ptrdiff_t Shift>
  EVE_FORCEINLINE wide<T, N> slide_right_ ( EVE_SUPPORTS(vmx_), wide<T, N> v, index_t<Shift> ) noexcept
    requires(Shift<=N::value) && ppc_abi<abi_t<T, N>>
  {
    using that_t  = wide<T, N>;

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
        using i_t = as_integer_t<wide<T, N>>;
        return bit_cast(slide_right(bit_cast(v, as<i_t>()), index<Shift> ), as(v));
      }
      else
      {
        constexpr unsigned char offset = (Shift * sizeof(T)) << 3;
        __vector signed char shift = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,offset};

        return vec_sro( v.storage(), shift );
      }
    }
  }
}
