//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/detail/abi.hpp>
#include <eve/product_type.hpp>

namespace eve::detail
{
  //================================================================================================
  // N-ary deinterleave
  // This is the main one as it is easier to specify optimisation on this interface than on tuple
  //================================================================================================
  template<simd_value T, std::same_as<T>... Ts>
  EVE_FORCEINLINE auto deinterleave_(EVE_SUPPORTS(cpu_),T v0, Ts... vs) noexcept
  {
    auto const values = kumi::make_tuple(v0,vs...);

    if constexpr(T::size() == 1)
    {
      return values;
    }
    else
    {
      constexpr auto nb   = 1 + sizeof...(Ts);
      constexpr auto card = T::size();

      return [&]<std::size_t... J>(std::index_sequence<J...>)
      {
        return kumi::make_tuple
        ( [&]<std::size_t O, std::size_t... I>
          (std::index_sequence<I...>, std::integral_constant<std::size_t,O>)
          {
            // Total element index is I * nb + O.
            // so / card for vec and % card for element
            return T{ kumi::get<(I * nb + O) / card>(values).get((I * nb + O) % card) ...  };
          }( std::make_index_sequence<card>{}, std::integral_constant<std::size_t,J>{})...
        );
      }( std::make_index_sequence<nb>{} );
    }
  }
}
