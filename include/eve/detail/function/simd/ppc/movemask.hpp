//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/logical.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <utility>

namespace eve::detail
{
  // Adapted from this completely unsuspecting thread:
  // https://stackoverflow.com/questions/33938584/on-powerpc-is-there-any-equivalent-of-intels-movemask-intrinsics
  template<arithmetic_scalar_value T, typename N>
  EVE_FORCEINLINE auto movemask(logical<wide<T, N>> const &v) noexcept
  requires ppc_abi<abi_t<T, N>>
  {
    auto mask = []()
    {
      constexpr auto spacing = sizeof(T)*8;
      return  []<std::size_t... I,std::size_t... J>
              (std::index_sequence<I...>,std::index_sequence<J...>)
      {
        using vu8 = __vector unsigned char;
        return vu8{(I,128)...,(J*spacing)...};
      }(std::make_index_sequence<16-N::value>{}, std::make_index_sequence<N::value>{});
    }();

    auto result = vec_vbpermq(bit_cast(v.bits(),as(mask)), mask);
    return std::pair{result[0], eve::lane<1>};
  }
}
