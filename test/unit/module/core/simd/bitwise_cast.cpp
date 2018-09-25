//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"
#include <tts/tests/relation.hpp>
#include <eve/function/simd/bitwise_cast.hpp>
#include <eve/pack.hpp>
#include <eve/logical.hpp>

TTS_CASE_TPL( "Check bitwise_cast between integer types"
            , eve::fixed<1>, eve::fixed<2> , eve::fixed<4>
            , eve::fixed<8>, eve::fixed<16>, eve::fixed<32>, eve::fixed<64>
            )
{
  using ps_t = eve::pack<std::uint16_t, T>;
  using pc_t = eve::pack<std::uint8_t , typename T::combined_type>;

  TTS_EQUAL ( eve::bitwise_cast<ps_t>( pc_t(0xFA)   ), ps_t(0xFAFA)  );
  TTS_EQUAL ( eve::bitwise_cast<pc_t>( ps_t(0xDCDC) ), pc_t(0xDC)    );
}

TTS_CASE_TPL( "Check bitwise_cast between integer and real types"
            , eve::fixed<1>, eve::fixed<2> , eve::fixed<4>
            , eve::fixed<8>, eve::fixed<16>, eve::fixed<32>, eve::fixed<64>
            )
{
  using pi_t = eve::pack<std::uint32_t, T>;
  using pf_t = eve::pack<float        , T>;

  TTS_EQUAL ( eve::bitwise_cast<pi_t>( pf_t(1.f)        ), pi_t(0x3F800000) );
  TTS_EQUAL ( eve::bitwise_cast<pf_t>( pi_t(0x3F800000) ), pf_t(1.f)        );
}

TTS_CASE_TPL( "Check bitwise_cast between arithmetic and logical types"
            , eve::fixed<1>, eve::fixed<2> //, eve::fixed<4>
            //, eve::fixed<8>, eve::fixed<16>, eve::fixed<32>, eve::fixed<64>
            )
{
  using pi_t = eve::pack<std::uint64_t, T>;
  using pl_t = eve::pack<eve::logical<double>, T>;
  using pm_t = eve::pack<eve::logical<float>, typename T::combined_type>;

  pl_t x( [](auto,auto) { return true; });
  pm_t y( [](auto,auto) { return true; });

  TTS_EQUAL ( eve::bitwise_cast<pi_t>(x), pi_t(0xFFFFFFFFFFFFFFFFULL)   );
  TTS_EQUAL ( eve::bitwise_cast<pl_t>(pi_t(0xFFFFFFFFFFFFFFFFULL)),   x );
  TTS_EQUAL ( eve::bitwise_cast<pm_t>(x), y);
  TTS_EQUAL ( eve::bitwise_cast<pl_t>(y), x);
  TTS_EQUAL ( eve::bitwise_cast<pl_t>(x), x);
}
