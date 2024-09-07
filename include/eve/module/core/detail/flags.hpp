//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve
{

  template<std::uint8_t I> struct fp_class
  {
    static constexpr std::uint8_t value = I;
    template<std::uint8_t J>
    friend constexpr fp_class<I|J> operator|(fp_class, fp_class<J>) { return {}; }
  };

  inline constexpr fp_class<1>   qnan    = {};
  inline constexpr fp_class<2>   poszero = {};
  inline constexpr fp_class<4>   negzero = {};
  inline constexpr fp_class<8>   posinf  = {};
  inline constexpr fp_class<16>  neginf  = {};
  inline constexpr fp_class<32>  denorm  = {};
  inline constexpr fp_class<64>  neg     = {};
  inline constexpr fp_class<128> snan    = {};
}
