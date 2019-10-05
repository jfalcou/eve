//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SATURATE_HPP
#define SATURATE_HPP

#include <eve/function/saturate.hpp>
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/as.hpp>

TTS_CASE(" saturate types check")
{
  using eve::as_;
  using eve::saturate;
  using eve::Valmax;
  using eve::Valmin;

  // return type conformity test
  TTS_EXPR_IS(saturate[ as_<Type>() ](float(1)), float);
  TTS_EXPR_IS(saturate[ as_<Type>() ](double(1)), double);
  TTS_EXPR_IS(saturate[ as_<Type>() ](int8_t(1)), int8_t);
  TTS_EXPR_IS(saturate[ as_<Type>() ](int16_t(1)), int16_t);
  TTS_EXPR_IS(saturate[ as_<Type>() ](int32_t(1)), int32_t);
  TTS_EXPR_IS(saturate[ as_<Type>() ](int64_t(1)), int64_t);
  TTS_EXPR_IS(saturate[ as_<Type>() ](uint8_t(1)), uint8_t);
  TTS_EXPR_IS(saturate[ as_<Type>() ](uint16_t(1)), uint16_t);
  TTS_EXPR_IS(saturate[ as_<Type>() ](uint32_t(1)), uint32_t);
  TTS_EXPR_IS(saturate[ as_<Type>() ](uint64_t(1)), uint64_t);
}

TTS_CASE(" saturate ")
{
  using eve::as_;
  using eve::Inf;
  using eve::Minf;
  using eve::saturate;
  using eve::Valmax;
  using eve::Valmin;

  if constexpr(std::is_floating_point_v<Type>)
  {
    TTS_EQUAL(saturate[ as_<Type>() ](Valmax<float>()), Valmax<float>());
    TTS_EQUAL(saturate[ as_<Type>() ](Valmax<double>()), double(Valmax<Type>()));
    TTS_EQUAL(saturate[ as_<Type>() ](Valmin<float>()), Valmin<float>());
    TTS_EQUAL(saturate[ as_<Type>() ](Valmin<double>()), double(Valmin<Type>()));
    TTS_EQUAL(saturate[ as_<Type>() ](Inf<float>()), Inf<float>());
    TTS_EQUAL(saturate[ as_<Type>() ](Inf<double>()), double(Inf<Type>()));
    TTS_EQUAL(saturate[ as_<Type>() ](Minf<float>()), Minf<float>());
    TTS_EQUAL(saturate[ as_<Type>() ](Minf<double>()), double(Minf<Type>()));
  }
  if constexpr(std::is_same_v<Type, int16_t>)
  {
    TTS_EQUAL(1u, saturate[ as_<Type>() ](1ull));
    TTS_EQUAL(2u, saturate[ as_<Type>() ](2ull));
    TTS_EQUAL(6u, saturate[ as_<Type>() ](6ull));
    TTS_EQUAL(24u, saturate[ as_<Type>() ](24ull));
    TTS_EQUAL(120u, saturate[ as_<Type>() ](120ull));
    TTS_EQUAL(720u, saturate[ as_<Type>() ](720ull));
    TTS_EQUAL(5040u, saturate[ as_<Type>() ](5040ull));
    TTS_EQUAL(uint16_t(Valmax<Type>()), saturate[ as_<Type>() ](40320ull));
    TTS_EQUAL(uint16_t(Valmax<Type>()), saturate[ as_<Type>() ](362880ull));
    TTS_EQUAL(uint16_t(Valmax<Type>()), saturate[ as_<Type>() ](3628800ull));
    TTS_EQUAL(uint16_t(Valmax<Type>()), saturate[ as_<Type>() ](39916800ull));
    TTS_EQUAL(uint16_t(Valmax<Type>()), saturate[ as_<Type>() ](479001600ull));
    TTS_EQUAL(1, saturate[ as_<Type>() ](1ll));
    TTS_EQUAL(2, saturate[ as_<Type>() ](2ll));
    TTS_EQUAL(6, saturate[ as_<Type>() ](6ll));
    TTS_EQUAL(24, saturate[ as_<Type>() ](24ll));
    TTS_EQUAL(120, saturate[ as_<Type>() ](120ll));
    TTS_EQUAL(720, saturate[ as_<Type>() ](720ll));
    TTS_EQUAL(5040, saturate[ as_<Type>() ](5040ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](40320ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](362880ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](3628800ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](39916800ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](479001600ll));
    TTS_EQUAL(-1, saturate[ as_<Type>() ](-1ll));
    TTS_EQUAL(-2, saturate[ as_<Type>() ](-2ll));
    TTS_EQUAL(-6, saturate[ as_<Type>() ](-6ll));
    TTS_EQUAL(-24, saturate[ as_<Type>() ](-24ll));
    TTS_EQUAL(-120, saturate[ as_<Type>() ](-120ll));
    TTS_EQUAL(-720, saturate[ as_<Type>() ](-720ll));
    TTS_EQUAL(-5040, saturate[ as_<Type>() ](-5040ll));
    TTS_EQUAL(Valmin<Type>(), saturate[ as_<Type>() ](-40320ll));
    TTS_EQUAL(Valmin<Type>(), saturate[ as_<Type>() ](-362880ll));
    TTS_EQUAL(Valmin<Type>(), saturate[ as_<Type>() ](-3628800ll));
    TTS_EQUAL(Valmin<Type>(), saturate[ as_<Type>() ](-39916800ll));
    TTS_EQUAL(Valmin<Type>(), saturate[ as_<Type>() ](-479001600ll));
  }
  if constexpr(std::is_same_v<Type, uint16_t>)
  {
    TTS_EQUAL(1u, saturate[ as_<Type>() ](1ull));
    TTS_EQUAL(2u, saturate[ as_<Type>() ](2ull));
    TTS_EQUAL(6u, saturate[ as_<Type>() ](6ull));
    TTS_EQUAL(24u, saturate[ as_<Type>() ](24ull));
    TTS_EQUAL(120u, saturate[ as_<Type>() ](120ull));
    TTS_EQUAL(720u, saturate[ as_<Type>() ](720ull));
    TTS_EQUAL(5040u, saturate[ as_<Type>() ](5040ull));
    TTS_EQUAL(40320u, saturate[ as_<Type>() ](40320ull));
    TTS_EQUAL((Valmax<Type>()), saturate[ as_<Type>() ](362880ull));
    TTS_EQUAL((Valmax<Type>()), saturate[ as_<Type>() ](3628800ull));
    TTS_EQUAL((Valmax<Type>()), saturate[ as_<Type>() ](39916800ull));
    TTS_EQUAL((Valmax<Type>()), saturate[ as_<Type>() ](479001600ull));
    TTS_EQUAL(1, saturate[ as_<Type>() ](1ll));
    TTS_EQUAL(2, saturate[ as_<Type>() ](2ll));
    TTS_EQUAL(6, saturate[ as_<Type>() ](6ll));
    TTS_EQUAL(24, saturate[ as_<Type>() ](24ll));
    TTS_EQUAL(120, saturate[ as_<Type>() ](120ll));
    TTS_EQUAL(720, saturate[ as_<Type>() ](720ll));
    TTS_EQUAL(5040, saturate[ as_<Type>() ](5040ll));
    TTS_EQUAL(40320, saturate[ as_<Type>() ](40320ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](362880ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](3628800ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](39916800ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](479001600ll));
  }
  if constexpr(std::is_same_v<Type, int8_t>)
  {
    TTS_EQUAL(1u, saturate[ as_<Type>() ](1ull));
    TTS_EQUAL(2u, saturate[ as_<Type>() ](2ull));
    TTS_EQUAL(6u, saturate[ as_<Type>() ](6ull));
    TTS_EQUAL(24u, saturate[ as_<Type>() ](24ull));
    TTS_EQUAL(120u, saturate[ as_<Type>() ](120ull));
    TTS_EQUAL(uint8_t(Valmax<Type>()), saturate[ as_<Type>() ](720ull));
    TTS_EQUAL(uint8_t(Valmax<Type>()), saturate[ as_<Type>() ](5040ull));
    TTS_EQUAL(uint8_t(Valmax<Type>()), saturate[ as_<Type>() ](40320ull));
    TTS_EQUAL(uint8_t(Valmax<Type>()), saturate[ as_<Type>() ](362880ull));
    TTS_EQUAL(uint8_t(Valmax<Type>()), saturate[ as_<Type>() ](3628800ull));
    TTS_EQUAL(uint8_t(Valmax<Type>()), saturate[ as_<Type>() ](39916800ull));
    TTS_EQUAL(uint8_t(Valmax<Type>()), saturate[ as_<Type>() ](479001600ull));
    TTS_EQUAL(1, saturate[ as_<Type>() ](1ll));
    TTS_EQUAL(2, saturate[ as_<Type>() ](2ll));
    TTS_EQUAL(6, saturate[ as_<Type>() ](6ll));
    TTS_EQUAL(24, saturate[ as_<Type>() ](24ll));
    TTS_EQUAL(120, saturate[ as_<Type>() ](120ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](720ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](5040ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](40320ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](362880ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](3628800ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](39916800ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](479001600ll));
    TTS_EQUAL(-1, saturate[ as_<Type>() ](-1ll));
    TTS_EQUAL(-2, saturate[ as_<Type>() ](-2ll));
    TTS_EQUAL(-6, saturate[ as_<Type>() ](-6ll));
    TTS_EQUAL(-24, saturate[ as_<Type>() ](-24ll));
    TTS_EQUAL(-120, saturate[ as_<Type>() ](-120ll));
    TTS_EQUAL(Valmin<Type>(), saturate[ as_<Type>() ](-720ll));
    TTS_EQUAL(Valmin<Type>(), saturate[ as_<Type>() ](-5040ll));
    TTS_EQUAL(Valmin<Type>(), saturate[ as_<Type>() ](-40320ll));
    TTS_EQUAL(Valmin<Type>(), saturate[ as_<Type>() ](-362880ll));
    TTS_EQUAL(Valmin<Type>(), saturate[ as_<Type>() ](-3628800ll));
    TTS_EQUAL(Valmin<Type>(), saturate[ as_<Type>() ](-39916800ll));
    TTS_EQUAL(Valmin<Type>(), saturate[ as_<Type>() ](-479001600ll));
  }
  if constexpr(std::is_same_v<Type, uint8_t>)
  {
    TTS_EQUAL(1u, saturate[ as_<Type>() ](1ull));
    TTS_EQUAL(2u, saturate[ as_<Type>() ](2ull));
    TTS_EQUAL(6u, saturate[ as_<Type>() ](6ull));
    TTS_EQUAL(24u, saturate[ as_<Type>() ](24ull));
    TTS_EQUAL(120u, saturate[ as_<Type>() ](120ull));
    TTS_EQUAL((Valmax<Type>()), saturate[ as_<Type>() ](720ull));
    TTS_EQUAL((Valmax<Type>()), saturate[ as_<Type>() ](5040ull));
    TTS_EQUAL((Valmax<Type>()), saturate[ as_<Type>() ](40320ull));
    TTS_EQUAL((Valmax<Type>()), saturate[ as_<Type>() ](362880ull));
    TTS_EQUAL((Valmax<Type>()), saturate[ as_<Type>() ](3628800ull));
    TTS_EQUAL((Valmax<Type>()), saturate[ as_<Type>() ](39916800ull));
    TTS_EQUAL((Valmax<Type>()), saturate[ as_<Type>() ](479001600ull));
    TTS_EQUAL(1, saturate[ as_<Type>() ](1ll));
    TTS_EQUAL(2, saturate[ as_<Type>() ](2ll));
    TTS_EQUAL(6, saturate[ as_<Type>() ](6ll));
    TTS_EQUAL(24, saturate[ as_<Type>() ](24ll));
    TTS_EQUAL(120, saturate[ as_<Type>() ](120ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](720ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](5040ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](40320ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](362880ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](3628800ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](39916800ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](479001600ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-1ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-2ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-6ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-24ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-120ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-720ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-5040ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-40320ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-362880ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-3628800ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-39916800ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-479001600ll));
  }
  if constexpr(std::is_same_v<Type, int32_t>)
  {
    TTS_EQUAL(1u, saturate[ as_<Type>() ](1ull));
    TTS_EQUAL(2u, saturate[ as_<Type>() ](2ull));
    TTS_EQUAL(6u, saturate[ as_<Type>() ](6ull));
    TTS_EQUAL(24u, saturate[ as_<Type>() ](24ull));
    TTS_EQUAL(120u, saturate[ as_<Type>() ](120ull));
    TTS_EQUAL(720u, saturate[ as_<Type>() ](720ull));
    TTS_EQUAL(5040u, saturate[ as_<Type>() ](5040ull));
    TTS_EQUAL(40320u, saturate[ as_<Type>() ](40320ull));
    TTS_EQUAL(362880u, saturate[ as_<Type>() ](362880ull));
    TTS_EQUAL(3628800u, saturate[ as_<Type>() ](3628800ull));
    TTS_EQUAL(39916800u, saturate[ as_<Type>() ](39916800ull));
    TTS_EQUAL(479001600u, saturate[ as_<Type>() ](479001600ull));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](4294967296));
    TTS_EQUAL(1, saturate[ as_<Type>() ](1ll));
    TTS_EQUAL(2, saturate[ as_<Type>() ](2ll));
    TTS_EQUAL(6, saturate[ as_<Type>() ](6ll));
    TTS_EQUAL(24, saturate[ as_<Type>() ](24ll));
    TTS_EQUAL(120, saturate[ as_<Type>() ](120ll));
    TTS_EQUAL(720, saturate[ as_<Type>() ](720ll));
    TTS_EQUAL(5040, saturate[ as_<Type>() ](5040ll));
    TTS_EQUAL(40320, saturate[ as_<Type>() ](40320ll));
    TTS_EQUAL(362880, saturate[ as_<Type>() ](362880ll));
    TTS_EQUAL(3628800, saturate[ as_<Type>() ](3628800ll));
    TTS_EQUAL(39916800, saturate[ as_<Type>() ](39916800ll));
    TTS_EQUAL(479001600, saturate[ as_<Type>() ](479001600ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](4294967296ll));
    TTS_EQUAL(-1, saturate[ as_<Type>() ](-1ll));
    TTS_EQUAL(-2, saturate[ as_<Type>() ](-2ll));
    TTS_EQUAL(-6, saturate[ as_<Type>() ](-6ll));
    TTS_EQUAL(-24, saturate[ as_<Type>() ](-24ll));
    TTS_EQUAL(-120, saturate[ as_<Type>() ](-120ll));
    TTS_EQUAL(-720, saturate[ as_<Type>() ](-720ll));
    TTS_EQUAL(-5040, saturate[ as_<Type>() ](-5040ll));
    TTS_EQUAL(-40320, saturate[ as_<Type>() ](-40320ll));
    TTS_EQUAL(-362880, saturate[ as_<Type>() ](-362880ll));
    TTS_EQUAL(-3628800, saturate[ as_<Type>() ](-3628800ll));
    TTS_EQUAL(-39916800, saturate[ as_<Type>() ](-39916800ll));
    TTS_EQUAL(-479001600, saturate[ as_<Type>() ](-479001600ll));
    TTS_EQUAL(Valmin<Type>(), saturate[ as_<Type>() ](-4294967296ll));
  }
  if constexpr(std::is_same_v<Type, uint32_t>)
  {
    TTS_EQUAL(1u, saturate[ as_<Type>() ](1ull));
    TTS_EQUAL(2u, saturate[ as_<Type>() ](2ull));
    TTS_EQUAL(6u, saturate[ as_<Type>() ](6ull));
    TTS_EQUAL(24u, saturate[ as_<Type>() ](24ull));
    TTS_EQUAL(120u, saturate[ as_<Type>() ](120ull));
    TTS_EQUAL(720u, saturate[ as_<Type>() ](720ull));
    TTS_EQUAL(5040u, saturate[ as_<Type>() ](5040ull));
    TTS_EQUAL(40320u, saturate[ as_<Type>() ](40320ull));
    TTS_EQUAL(362880u, saturate[ as_<Type>() ](362880ull));
    TTS_EQUAL(3628800u, saturate[ as_<Type>() ](3628800ull));
    TTS_EQUAL(39916800u, saturate[ as_<Type>() ](39916800ull));
    TTS_EQUAL(479001600ull, saturate[ as_<Type>() ](479001600ull));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](4294967296ull));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](8589934592ull));
    TTS_EQUAL(1, saturate[ as_<Type>() ](1ll));
    TTS_EQUAL(2, saturate[ as_<Type>() ](2ll));
    TTS_EQUAL(6, saturate[ as_<Type>() ](6ll));
    TTS_EQUAL(24, saturate[ as_<Type>() ](24ll));
    TTS_EQUAL(120, saturate[ as_<Type>() ](120ll));
    TTS_EQUAL(720, saturate[ as_<Type>() ](720ll));
    TTS_EQUAL(5040, saturate[ as_<Type>() ](5040ll));
    TTS_EQUAL(40320, saturate[ as_<Type>() ](40320ll));
    TTS_EQUAL(362880, saturate[ as_<Type>() ](362880ll));
    TTS_EQUAL(3628800, saturate[ as_<Type>() ](3628800ll));
    TTS_EQUAL(39916800, saturate[ as_<Type>() ](39916800ll));
    TTS_EQUAL(479001600, saturate[ as_<Type>() ](479001600ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](4294967296ll));
    TTS_EQUAL(Valmax<Type>(), saturate[ as_<Type>() ](8589934592ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-1ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-2ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-6ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-24ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-120ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-720ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-5040ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-40320ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-362880ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-3628800ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-39916800ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-479001600ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-4294967296ll));
  }
  if constexpr(std::is_same_v<Type, int64_t>)
  {
    TTS_EQUAL(1u, saturate[ as_<Type>() ](1ull));
    TTS_EQUAL(2u, saturate[ as_<Type>() ](2ull));
    TTS_EQUAL(6u, saturate[ as_<Type>() ](6ull));
    TTS_EQUAL(24u, saturate[ as_<Type>() ](24ull));
    TTS_EQUAL(120u, saturate[ as_<Type>() ](120ull));
    TTS_EQUAL(720u, saturate[ as_<Type>() ](720ull));
    TTS_EQUAL(5040u, saturate[ as_<Type>() ](5040ull));
    TTS_EQUAL(40320u, saturate[ as_<Type>() ](40320ull));
    TTS_EQUAL(362880u, saturate[ as_<Type>() ](362880ull));
    TTS_EQUAL(3628800u, saturate[ as_<Type>() ](3628800ull));
    TTS_EQUAL(39916800u, saturate[ as_<Type>() ](39916800ull));
    TTS_EQUAL(479001600ull, saturate[ as_<Type>() ](479001600ull));
    TTS_EQUAL(4294967296ull, saturate[ as_<Type>() ](4294967296ull));
    TTS_EQUAL(1, saturate[ as_<Type>() ](1ll));
    TTS_EQUAL(2, saturate[ as_<Type>() ](2ll));
    TTS_EQUAL(6, saturate[ as_<Type>() ](6ll));
    TTS_EQUAL(24, saturate[ as_<Type>() ](24ll));
    TTS_EQUAL(120, saturate[ as_<Type>() ](120ll));
    TTS_EQUAL(720, saturate[ as_<Type>() ](720ll));
    TTS_EQUAL(5040, saturate[ as_<Type>() ](5040ll));
    TTS_EQUAL(40320, saturate[ as_<Type>() ](40320ll));
    TTS_EQUAL(362880, saturate[ as_<Type>() ](362880ll));
    TTS_EQUAL(3628800, saturate[ as_<Type>() ](3628800ll));
    TTS_EQUAL(39916800, saturate[ as_<Type>() ](39916800ll));
    TTS_EQUAL(479001600, saturate[ as_<Type>() ](479001600ll));
    TTS_EQUAL(4294967296ll, saturate[ as_<Type>() ](4294967296ll));
    TTS_EQUAL(-1, saturate[ as_<Type>() ](-1ll));
    TTS_EQUAL(-2, saturate[ as_<Type>() ](-2ll));
    TTS_EQUAL(-6, saturate[ as_<Type>() ](-6ll));
    TTS_EQUAL(-24, saturate[ as_<Type>() ](-24ll));
    TTS_EQUAL(-120, saturate[ as_<Type>() ](-120ll));
    TTS_EQUAL(-720, saturate[ as_<Type>() ](-720ll));
    TTS_EQUAL(-5040, saturate[ as_<Type>() ](-5040ll));
    TTS_EQUAL(-40320, saturate[ as_<Type>() ](-40320ll));
    TTS_EQUAL(-362880, saturate[ as_<Type>() ](-362880ll));
    TTS_EQUAL(-3628800, saturate[ as_<Type>() ](-3628800ll));
    TTS_EQUAL(-39916800, saturate[ as_<Type>() ](-39916800ll));
    TTS_EQUAL(-479001600, saturate[ as_<Type>() ](-479001600ll));
    TTS_EQUAL(-4294967296ll, saturate[ as_<Type>() ](-4294967296ll));
  }

  if constexpr(std::is_same_v<Type, uint64_t>)
  {
    TTS_EQUAL(1u, saturate[ as_<Type>() ](1ull));
    TTS_EQUAL(2u, saturate[ as_<Type>() ](2ull));
    TTS_EQUAL(6u, saturate[ as_<Type>() ](6ull));
    TTS_EQUAL(24u, saturate[ as_<Type>() ](24ull));
    TTS_EQUAL(120u, saturate[ as_<Type>() ](120ull));
    TTS_EQUAL(720u, saturate[ as_<Type>() ](720ull));
    TTS_EQUAL(5040u, saturate[ as_<Type>() ](5040ull));
    TTS_EQUAL(40320u, saturate[ as_<Type>() ](40320ull));
    TTS_EQUAL(362880u, saturate[ as_<Type>() ](362880ull));
    TTS_EQUAL(3628800u, saturate[ as_<Type>() ](3628800ull));
    TTS_EQUAL(39916800u, saturate[ as_<Type>() ](39916800ull));
    TTS_EQUAL(479001600ull, saturate[ as_<Type>() ](479001600ull));
    TTS_EQUAL(4294967296ull, saturate[ as_<Type>() ](4294967296ull));
    TTS_EQUAL(1, saturate[ as_<Type>() ](1ll));
    TTS_EQUAL(2, saturate[ as_<Type>() ](2ll));
    TTS_EQUAL(6, saturate[ as_<Type>() ](6ll));
    TTS_EQUAL(24, saturate[ as_<Type>() ](24ll));
    TTS_EQUAL(120, saturate[ as_<Type>() ](120ll));
    TTS_EQUAL(720, saturate[ as_<Type>() ](720ll));
    TTS_EQUAL(5040, saturate[ as_<Type>() ](5040ll));
    TTS_EQUAL(40320, saturate[ as_<Type>() ](40320ll));
    TTS_EQUAL(362880, saturate[ as_<Type>() ](362880ll));
    TTS_EQUAL(3628800, saturate[ as_<Type>() ](3628800ll));
    TTS_EQUAL(39916800, saturate[ as_<Type>() ](39916800ll));
    TTS_EQUAL(479001600, saturate[ as_<Type>() ](479001600ll));
    TTS_EQUAL(4294967296ll, saturate[ as_<Type>() ](4294967296ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-1ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-2ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-6ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-24ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-120ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-720ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-5040ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-40320ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-362880ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-3628800ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-39916800ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-479001600ll));
    TTS_EQUAL(0, saturate[ as_<Type>() ](-4294967296ll));
  }
}

#endif
