//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_PPC_LOOKUP_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_PPC_LOOKUP_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/detail/function/simd/lookup.hpp>
#include <eve/forward.hpp>

namespace eve::detail
{
  template<typename T, typename I, typename N>
  EVE_FORCEINLINE wide<T,N,ppc_> lookup_( EVE_SUPPORTS(vmx_),
                                          wide<T,N,ppc_> a, wide<I,N,ppc_> idx
                                        ) noexcept
  {
    using t8_t = typename wide<T,N,ppc_>::template rebind<std::uint8_t, fixed<16>>;

    if constexpr(sizeof(I) == 1)
    {
      return vec_perm(a.storage(),a.storage(), bit_cast(idx,as<t8_t>()).storage());
    }
    else
    {
      t8_t  i1 = lookup(bit_cast(idx<<shift<I>, as(i1)), t8_t{repeater<I>});
            i1 = bit_cast(bit_cast(i1,as<wide<I,N,ppc_>>())+offset<I>,as<t8_t>());
      return bit_cast( lookup(bit_cast(a, as<t8_t>()),i1), as(a));
    }
  }
}

#endif
