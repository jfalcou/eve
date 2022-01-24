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
  template<simd_value T, std::same_as<T>... Ts>
  EVE_FORCEINLINE auto interleave_(EVE_SUPPORTS(cpu_),T v0, Ts... vs) noexcept
  {
    auto const values = kumi::make_tuple(v0,vs...);
    constexpr auto nb   = 1 + sizeof...(Ts);

         if constexpr (T::size() == 1) return values;
    else if constexpr ( nb == 4 && (sizeof(eve::element_type_t<T>) < 8) )
    {
      auto a = v0;
      auto b = get<1>(values);
      auto c = get<2>(values);
      auto d = get<3>(values);

      auto [ab0, ab1] = interleave(a, b);
      auto [cd0, cd1] = interleave(c, d);

      using up_e_t = upgrade_t<eve::element_type_t<T>>;
      using up_t   = wide<up_e_t, eve::fixed<T::size() / 2>>;

      auto [abcd00, abcd01] = interleave(bit_cast(ab0, as<up_t>()), bit_cast(cd0, as<up_t>()));
      auto [abcd10, abcd11] = interleave(bit_cast(ab1, as<up_t>()), bit_cast(cd1, as<up_t>()));

      return kumi::make_tuple (
        bit_cast(abcd00, as(v0)),
        bit_cast(abcd01, as(v0)),
        bit_cast(abcd10, as(v0)),
        bit_cast(abcd11, as(v0))
      );
    }
    else
    {
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

  template<simd_value T, std::same_as<T>... Ts>
  EVE_FORCEINLINE auto interleave_(EVE_SUPPORTS(cpu_),logical<T> v0, logical<Ts>... vs) noexcept
  requires( T::abi_type::is_wide_logical )
  {
    auto that = interleave(v0.mask(),vs.mask()...);
    return  kumi::map( [](auto m) { return bit_cast(m, as<logical<T>>()); }, that);
  }
}
