//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/traits/product_type.hpp>

namespace eve::detail
{
  //================================================================================================
  // Interleave pairs of wides
  //================================================================================================
  template<scalar_value T, typename N>
  EVE_FORCEINLINE auto interleave_(EVE_SUPPORTS(vmx_), wide<T,N> v0, wide<T,N> v1) noexcept
  requires (N::value > 1) && ppc_abi<abi_t<T,N>>
  {
    using type = wide<T,N>;

    auto ptn = []<typename O, std::size_t... I>( O, std::index_sequence<I...> )
    {
      __vector unsigned char v =  { ( I<(N::value*sizeof(T))
                                    ? O::value
                                      + ( ((I/sizeof(T)) % 2 == 0) ? 0 : 16)
                                      + I%sizeof(T)
                                      + sizeof(T)*(I/(sizeof(T)*2))
                                    : 255
                                    )...
                                  };
      return v;
    };

    if constexpr( current_api >= vsx || sizeof(T) < 8)
    {
      __vector unsigned char const sl = ptn ( std::integral_constant<int,0>{}
                                            , std::make_index_sequence<16>{}
                                            );
      __vector unsigned char const sh = ptn ( std::integral_constant<int,(N::value*sizeof(T))/2>{}
                                            , std::make_index_sequence<16>{}
                                            );
      return kumi::make_tuple ( type(vec_perm(v0.storage(),v1.storage(),sl))
                              , type(vec_perm(v0.storage(),v1.storage(),sh))
                              );
    }
    else
    {
      return interleave_(EVE_RETARGET(cpu_),v0,v1);
    }
  }
}
