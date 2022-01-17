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

#include <eve/function/interleave.hpp>

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

    constexpr auto nb   = 1 + sizeof...(Ts);
    constexpr auto card = T::size();


         if constexpr ( T::size() == 1                    ) return values;
    else if constexpr ( !has_emulated_abi_v<T> && nb == 2 )
    {
      if constexpr ( T::size() == 2 ) return interleave(v0, vs...); // For two elements it's the same logic
      else // basic aggregation logic
      {
        auto[a0b0,a1b1] = v0.slice();
        auto[a2b2,a3b3] = get<1>(values).slice();
        auto[a0a1,b0b1] = eve::deinterleave(a0b0,a1b1);
        auto[a2a3,b2b3] = eve::deinterleave(a2b2,a3b3);

        return kumi::make_tuple(T{a0a1, a2a3}, T{b0b1, b2b3});
      }
    }
    else
    {
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
