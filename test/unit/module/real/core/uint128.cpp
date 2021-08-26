//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/uint128.hpp>
#include <cmath>


//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check  eve::uin128 lo and hi", eve::test::scalar::all_types)
<typename T>(eve::as<T>)
{
  TTS_EXPR_IS( eve::uint128(T())            , eve::uint128 );
  {
    auto const a = eve::uint128(1);
    TTS_EXPR_IS( a.lo()                      , std::uint64_t );
    TTS_EXPR_IS( a.hi()                      , std::uint64_t );
  }
  auto  a = eve::uint128(1);
  TTS_EXPR_IS( a.lo()                      , std::uint64_t &);
  TTS_EXPR_IS( a.hi()                      , std::uint64_t &);

};

EVE_TEST_TYPES( "Check  eve::uin128 lo and hi", eve::test::scalar::unsigned_types)
<typename T>(eve::as<T>)
{
  using eve::uint128;
  auto vm = eve::valmax(eve::as<std::uint64_t>());
  uint128 Uint128Max(vm, vm);
  uint128 zero = 0;
  uint128 one = 1;
  uint128 one_2arg(0, 1);
  uint128 two = 2;
//  uint128 three = 3;
  uint128 big(2000, 2);
  uint128 big_minus_one(2000, 1);
  uint128 bigger(2001, 1);
  uint128 biggest(vm, vm);
  uint128 high_low(1, 0);
  uint128 low_high(0, vm);
  TTS_EXPECT(one < two);
  TTS_EXPECT(two > one);
  TTS_EXPECT(one < big);
  TTS_EXPECT(one < big);
  TTS_EQUAL(one, one_2arg);
  //  EXPECT_NE(one, two);
  //   EXPECT_GT(big, one);
//   EXPECT_GE(big, two);
//   EXPECT_GE(big, big_minus_one);
//   EXPECT_GT(big, big_minus_one);
//   EXPECT_LT(big_minus_one, big);
//   EXPECT_LE(big_minus_one, big);
//   EXPECT_NE(big_minus_one, big);
//   EXPECT_LT(big, biggest);
//   EXPECT_LE(big, biggest);
//   EXPECT_GT(biggest, big);
//   EXPECT_GE(biggest, big);
  TTS_EQUAL(big, ~~big);
//   TTS_EQUAL(one, one | one);
//   TTS_EQUAL(big, big | big);
//   TTS_EQUAL(one, one | zero);
//   TTS_EQUAL(one, one & one);
//   TTS_EQUAL(big, big & big);
//   TTS_EQUAL(zero, one & zero);
//   TTS_EQUAL(zero, big & ~big);
//   TTS_EQUAL(zero, one ^ one);
//   TTS_EQUAL(zero, big ^ big);
//   TTS_EQUAL(one, one ^ zero);

//   // Shift operators.
  TTS_EQUAL(big, big << 0);
  TTS_EQUAL(big, big >> 0);
//   EXPECT_GT(big << 1, big);
//   EXPECT_LT(big >> 1, big);
  TTS_EQUAL(big, (big << 10) >> 10);
  TTS_EQUAL(big, (big >> 1) << 1);
  TTS_EQUAL(one, (one << 80) >> 80);
  TTS_EQUAL(zero, (one >> 80) << 80);

//   // Shift assignments.
  uint128 big_copy = big;
  big_copy <<= 0;
  TTS_EQUAL((big << 0), big_copy);
  big_copy = big;
  big_copy >>= 0;
  TTS_EQUAL((big >> 0), big_copy);
  big_copy = big;
  big_copy <<=  1;
  TTS_EQUAL((big << 1), big_copy);
  big_copy = big;
  big_copy >>=  1;
  TTS_EQUAL((big >> 1), big_copy);
//   big_copy = big;
//  TTS_EQUAL(big << 10, big_copy <<= 10);
//   big_copy = big;
//  TTS_EQUAL(big >> 10, big_copy >>= 10);
//   big_copy = big;
//  TTS_EQUAL(big << 64, big_copy <<= 64);
//   big_copy = big;
//  TTS_EQUAL(big >> 64, big_copy >>= 64);
   big_copy = big;
   big_copy <<= 73;
   TTS_EQUAL((big << 73), big_copy);
   big_copy = big;
   big_copy >>= 73;
   TTS_EQUAL((big >> 73), big_copy);

  TTS_EQUAL(biggest.lo(), vm);
  TTS_EQUAL(biggest.hi(), vm);
  TTS_EQUAL((zero + one), one);
  TTS_EQUAL((one + one), two);
  TTS_EQUAL((big_minus_one + one), big);
  TTS_EQUAL((one - one), zero);
  TTS_EQUAL((one - zero), one);
  TTS_EQUAL((zero - one), biggest);
  TTS_EQUAL((big - big), zero);
  TTS_EQUAL((big - one), big_minus_one);
  TTS_EQUAL((big + vm), bigger);
  TTS_EQUAL((biggest + 1u), zero);
  TTS_EQUAL((zero - 1u), biggest);
  TTS_EQUAL((high_low - one), low_high);
  TTS_EQUAL((low_high + one), high_low);
  TTS_EQUAL(((uint128(1) << 64) - 1u).hi(), 0);
  TTS_EQUAL(((uint128(1) << 64) - 1u).lo(),vm);
  TTS_EQUAL(!!one,  true);
  TTS_EQUAL(!!high_low,  true);
  TTS_EQUAL(!!zero, false);
  TTS_EQUAL(!one, false);
  TTS_EQUAL(!high_low, false);
  TTS_EQUAL(!zero,  true);
//  TTS_EQUAL(zero == 0u,  true);
//  TTS_EQUAL(zero != 0), false;
//  TTS_EQUAL(one == 0, false);
//  TTS_EQUAL(one != 0u,  true);
//  TTS_EQUAL(high_low == 0, false);
//  TTS_EQUAL(high_low != 0u,  true);

  uint128 test = zero;
  TTS_EQUAL(++test, one);
  TTS_EQUAL(test, one);
  TTS_EQUAL(test++, one);
  TTS_EQUAL(test, two);
  //TTS_EQUAL((test -= 2u), zero);
  //TTS_EQUAL(test, zero);
  //TTS_EQUAL(test += 2u, two);
  TTS_EQUAL(test, two);
  TTS_EQUAL(--test, one);
  TTS_EQUAL(test, one);
  TTS_EQUAL(test--, one);
  TTS_EQUAL(test, zero);
//  TTS_EQUAL(test |= three, three);
//   TTS_EQUAL(test &= one, one);
//   TTS_EQUAL(test ^= three, two);
//   TTS_EQUAL(test >>= 1, one);
//   TTS_EQUAL(test <<= 1, two);

  TTS_EQUAL(big, +big);
  TTS_EQUAL(two, +two);
  TTS_EQUAL(Uint128Max, +Uint128Max);
  TTS_EQUAL(zero, +zero);

  TTS_EQUAL(big, -(-big));
  TTS_EQUAL(two, -((-one) - 1u));
  TTS_EQUAL(Uint128Max, -one);
  TTS_EQUAL(zero, -zero);

};
