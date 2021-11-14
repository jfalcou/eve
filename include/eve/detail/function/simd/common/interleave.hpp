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
  // N-ary interleave
  // This is the main one as it is easier to specify optimisation on this interface than on tuple
  //================================================================================================
  template<simd_value T, simd_value... Ts>
  EVE_FORCEINLINE auto interleave_(EVE_SUPPORTS(cpu_),T v0, Ts... vs) noexcept
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
            /*
              We look at interleave as a matrix transpose task:
                - I+card*O gives a linear index into the card * nb values matrix
                - We then compute the row and col to look for the proper data using / and %
                - We use those pseudo-coordinate to select the register in the tuple and the
                  the value inside the register.

              Note on codegen quality:
                - g++ and clang are able to turn this mess into an intrinsic based code if able
                - special cases are optimized in their respective arch file
            */
            return T{ kumi::get<((I+card*O)%nb)>(values).get((I+card*O)/nb)... };
          }( std::make_index_sequence<card>{}, std::integral_constant<std::size_t,J>{})...
        );
      }( std::make_index_sequence<nb>{});
    }
  }
}
