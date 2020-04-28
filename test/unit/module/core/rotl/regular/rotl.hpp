//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/allbits.hpp>
#include <eve/function/rotl.hpp>

#include <bit>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <type_traits>

// TTS_CASE("Check eve::rotl return type")
// {
//   using i_t = eve::detail::as_integer_t<EVE_TYPE, signed>;
//   using u_t = eve::detail::as_integer_t<EVE_TYPE, unsigned>;

//   TTS_EXPR_IS(eve::rotl(EVE_TYPE(), EVE_TYPE()), (EVE_TYPE));
//   TTS_EXPR_IS(eve::rotl(EVE_TYPE(), i_t() ), (EVE_TYPE));
//   TTS_EXPR_IS(eve::rotl(EVE_TYPE(), u_t() ), (EVE_TYPE));
// }

// TTS_CASE("Check eve::rotl behavior")
// {
//   using ui_t = eve::detail::as_integer_t<EVE_VALUE, unsigned>;
//   TTS_EQUAL(eve::rotl(EVE_TYPE(0), 7), (EVE_TYPE(std::rotl(ui_t(0), 7))));
//   TTS_EQUAL(eve::rotl(EVE_TYPE(1), 4), (EVE_TYPE(std::rotl(ui_t(1), 4))));
//   TTS_EQUAL(eve::rotl(EVE_TYPE(3), 2), (EVE_TYPE(std::rotl(ui_t(3), 2))));
//   TTS_EQUAL(eve::rotl(eve::Allbits<EVE_TYPE>(), 1), (EVE_TYPE(std::rotl(ui_t(~0), 1))));
//   TTS_EQUAL(eve::rotl(EVE_TYPE(0), -7), (EVE_TYPE(std::rotl(ui_t(0), -7))));
//   TTS_EQUAL(eve::rotl(EVE_TYPE(1), -4), (EVE_TYPE(std::rotl(ui_t(1), -4))));
//   TTS_EQUAL(eve::rotl(EVE_TYPE(3), -2), (EVE_TYPE(std::rotl(ui_t(3), -2))));

//   TTS_EQUAL(eve::rotl(EVE_TYPE(0), 7), (EVE_TYPE(std::rotr(ui_t(0), -7))));
//   TTS_EQUAL(eve::rotl(EVE_TYPE(1), 4), (EVE_TYPE(std::rotr(ui_t(1), -4))));
//   TTS_EQUAL(eve::rotl(EVE_TYPE(3), 2), (EVE_TYPE(std::rotr(ui_t(3), -2))));
//   TTS_EQUAL(eve::rotl(eve::Allbits<EVE_TYPE>(), 1), (EVE_TYPE(std::rotr(ui_t(~0), -1))));
//   TTS_EQUAL(eve::rotl(EVE_TYPE(0), -7), (EVE_TYPE(std::rotr(ui_t(0), 7))));
//   TTS_EQUAL(eve::rotl(EVE_TYPE(1), -4), (EVE_TYPE(std::rotr(ui_t(1), 4))));
//   TTS_EQUAL(eve::rotl(EVE_TYPE(3), -2), (EVE_TYPE(std::rotr(ui_t(3), 2))));

// }

TTS_CASE("Check eve::rotl simd/simd behavior")
{
  //  using ui_t = eve::detail::as_integer_t<EVE_VALUE, unsigned>;
  //   TTS_EQUAL(eve::rotl(EVE_TYPE(0), EVE_TYPE(7)), (EVE_TYPE(std::rotl(ui_t(0), 7))));
  //   TTS_EQUAL(eve::rotl(EVE_TYPE(1), EVE_TYPE(4)), (EVE_TYPE(std::rotl(ui_t(1), 4))));
  //   TTS_EQUAL(eve::rotl(EVE_TYPE(3), EVE_TYPE(2)), (EVE_TYPE(std::rotl(ui_t(3), 2))));
  //   TTS_EQUAL(eve::rotl(eve::Allbits<EVE_TYPE>(), EVE_TYPE(1)), (EVE_TYPE(std::rotl(ui_t(~0),
  //   1)))); using i_t = eve::detail::as_integer_t<EVE_VALUE, signed>;

  //   TTS_EQUAL(eve::rotl(EVE_TYPE(0), i_t(-7)), (EVE_TYPE(std::rotl(ui_t(0), -7))));
  //   TTS_EQUAL(eve::rotl(EVE_TYPE(1), i_t(-4)), (EVE_TYPE(std::rotl(ui_t(1), -4))));
  //   TTS_EQUAL(eve::rotl(EVE_TYPE(3), i_t(-2)), (EVE_TYPE(std::rotl(ui_t(3), -2))));

  using t_t  = eve::wide<uint32_t, eve::fixed<4>>;
  using ii_t = eve::wide<int16_t, eve::fixed<4>>;
  TTS_EQUAL(eve::rotl(t_t(1), ii_t(-4)), (t_t(std::rotl(uint32_t(1), -4))));
  using t_t8  = eve::wide<uint32_t, eve::fixed<8>>;
  using ii_t8 = eve::wide<int16_t, eve::fixed<8>>;
  TTS_EQUAL(eve::rotl(t_t8(1), ii_t8(-4)), (t_t8(std::rotl(uint32_t(1), -4))));
  using t_t16  = eve::wide<uint32_t, eve::fixed<16>>;
  using ii_t16 = eve::wide<int16_t, eve::fixed<16>>;
  TTS_EQUAL(eve::rotl(t_t16(1), ii_t16(-4)), (t_t16(std::rotl(uint32_t(1), -4))));
  using jj_t16 = eve::wide<int64_t, eve::fixed<16>>;
  TTS_EQUAL(eve::rotl(t_t16(1), jj_t16(-4)), (t_t16(std::rotl(uint32_t(1), -4))));
}
