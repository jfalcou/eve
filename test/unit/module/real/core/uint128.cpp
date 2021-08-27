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
EVE_TEST_TYPES( "Check  eve::uint128 lo and hi", eve::test::scalar:: uints_64)
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

EVE_TEST_TYPES( "Check  eve::uint128 + - < > & |", eve::test::scalar::uints_64)
<typename T>(eve::as<T>)
{
  using eve::uint128;
  auto vm = eve::valmax(eve::as<std::uint64_t>());
  uint128 Uint128Max(vm, vm);
  uint128 zero = 0;
  uint128 one = 1;
  uint128 one_2arg(0, 1);
  uint128 two = 2;
  uint128 three = 3;
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
  TTS_EXPECT(one < two);
  TTS_EXPECT(big > one);
  TTS_EXPECT(big >= two);
  TTS_EXPECT(big >= big_minus_one);
  TTS_EXPECT(big > big_minus_one);
  TTS_EXPECT(big_minus_one < big);
  TTS_EXPECT(big_minus_one <= big);
  TTS_EXPECT(big_minus_one != big);
  TTS_EXPECT(big < biggest);
  TTS_EXPECT(big <= biggest);
  TTS_EXPECT(biggest > big);
  TTS_EXPECT(biggest >= big);
  TTS_EQUAL(big, ~~big);
  TTS_EQUAL(one, (one | one));
  TTS_EQUAL(big, (big | big));
  TTS_EQUAL(one, (one | zero));
  TTS_EQUAL(one, (one & one));
  TTS_EQUAL(big, (big & big));
  TTS_EQUAL(zero, (one & zero));
  TTS_EQUAL(zero, (big & ~big));
  TTS_EQUAL(zero, (one ^ one));
  TTS_EQUAL(zero, (big ^ big));
  TTS_EQUAL(one, (one ^ zero));

   // Shift operators.
  TTS_EQUAL(big, big << 0);
  TTS_EQUAL(big, big >> 0);
  TTS_EXPECT((big << 1) > big);
  TTS_EXPECT((big >> 1) < big);
  TTS_EQUAL(big, ((big << 10) >> 10));
  TTS_EQUAL(big, ((big >> 1) << 1));
  TTS_EQUAL(one, ((one << 80) >> 80));
  TTS_EQUAL(zero, ((one >> 80) << 80));

  // Shift assignments.
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
  big_copy = big;
  big_copy <<= 10;
  TTS_EQUAL((big << 10), big_copy);
  big_copy = big;
  big_copy >>= 10;
  TTS_EQUAL((big >> 10), big_copy);
  big_copy = big;
  big_copy <<= 64;
  TTS_EQUAL((big << 64), big_copy);
  big_copy = big;
  big_copy >>= 64;
  TTS_EQUAL((big >> 64), big_copy);
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
  TTS_EQUAL((zero == 0u),  true);
  TTS_EQUAL((zero != 0), false);
  TTS_EQUAL((one == 0), false);
  TTS_EQUAL((one != 0u),  true);
  TTS_EQUAL((high_low == 0), false);
  TTS_EQUAL((high_low != 0),  true);

  uint128 test = zero;
  TTS_EQUAL(++test, one);
  TTS_EQUAL(test, one);
  TTS_EQUAL(test++, one);
  TTS_EQUAL(test, two);
  test -= 2u;
  TTS_EQUAL(test, zero);
  test += 2u;
  TTS_EQUAL(test, two);
  TTS_EQUAL(test, two);
  TTS_EQUAL(--test, one);
  TTS_EQUAL(test, one);
  TTS_EQUAL(test--, one);
  TTS_EQUAL(test, zero);
  test |= three;
  TTS_EQUAL(test, three);
  test &= one;
  TTS_EQUAL(test, one);
  test ^= three;
  TTS_EQUAL(test, two);
  test >>= 1;
  TTS_EQUAL(test, one);
  test <<= 1;
  TTS_EQUAL(test, two);

  TTS_EQUAL(big, +big);
  TTS_EQUAL(two, +two);
  TTS_EQUAL(Uint128Max, +Uint128Max);
  TTS_EQUAL(zero, +zero);

  TTS_EQUAL(big, -(-big));
  TTS_EQUAL(two, -((-one) - 1u));
  TTS_EQUAL(Uint128Max, -one);
  TTS_EQUAL(zero, -zero);

};

EVE_TEST_TYPES( "Check  eve::uint128 multiply", eve::test::scalar:: uints_64)
<typename T>(eve::as<T>)
{
  using eve::uint128;
  uint128 a, b, c;

  // Zero test.
  a = 0;
  b = 0;
  c = a * b;
  TTS_EQUAL(0, c);

  // Max carries.
  a = uint128(0) - 1u;
  b = uint128(0) - 1u;
  c = a * b;
  TTS_EQUAL(1, c);

  // Self-operation with max carries.
  c = uint128(0) - 1u;
  c *= c;
  TTS_EQUAL(1, c);

  // 1-bit x 1-bit.
  for (int i = 0; i < 64; ++i) {
    for (int j = 0; j < 64; ++j) {
      a = uint128(1) << i;
      b = uint128(1) << j;
      c = a * b;
      TTS_EQUAL((uint128(1) << (i + j)), c);
    }
  }

  // Verified with dc.
  a = uint128(0xffffeeeeddddcccc, 0xbbbbaaaa99998888);
  b = uint128(0x7777666655554444, 0x3333222211110000);
  c = a * b;
  TTS_EQUAL(uint128(0x530EDA741C71D4C3, 0xBF25975319080000), c);
  TTS_EQUAL(0, c - b * a);
  TTS_EQUAL((a*a - b*b), ((a+b) * (a-b)));

  // Verified with dc.
  a = uint128(0x0123456789abcdef, 0xfedcba9876543210);
  b = uint128(0x02468ace13579bdf, 0xfdb97531eca86420);
  c = a * b;
  TTS_EQUAL(uint128(0x97a87f4f261ba3f2, 0x342d0bbf48948200), c);
  TTS_EQUAL(0, c - b * a);
  TTS_EQUAL((a*a - b*b), ((a+b) * (a-b)));
};

EVE_TEST_TYPES( "alias test", eve::test::scalar:: uints_64)
<typename T>(eve::as<T>)
{
  using eve::uint128;
  uint128 x1 = uint128(1, 2);
  uint128 x2 = uint128(2, 4);
  x1 += x1;
  TTS_EQUAL(x2, x1);

  uint128 x3 = uint128(1, static_cast<std::uint64_t>(1) << 63);
  uint128 x4 = uint128(3, 0);
  x3 += x3;
  TTS_EQUAL(x4, x3);
};

EVE_TEST_TYPES( "divide and rem test", eve::test::scalar:: uints_64)
<typename T>(eve::as<T>)
{
  using eve::uint128;
  using std::swap;

  // a := q * b + r
  uint128 a, b, q, r;

  // Zero test.
  a = 0;
  b = 123;
  q = a / b;
  r = a % b;
  TTS_EQUAL(0, q);
  TTS_EQUAL(0, r);

  a = uint128(0x530eda741c71d4c3, 0xbf25975319080000);
  q = uint128(0x4de2cab081, 0x14c34ab4676e4bab);
  b = uint128(0x1110001);
  r = uint128(0x3eb455);
  TTS_EQUAL(a, q * b + r);  // Sanity-check.

  uint128 result_q, result_r;
  result_q = a / b;
  result_r = a % b;
  TTS_EQUAL(q, result_q);
  TTS_EQUAL(r, result_r);

  // Try the other way around.
  swap(q, b);
  result_q = a / b;
  result_r = a % b;
  TTS_EQUAL(q, result_q);
  TTS_EQUAL(r, result_r);
  // Restore.
  swap(b, q);

  // Dividend < divisor; result should be q:0 r:<dividend>.
  swap(a, b);
  result_q = a / b;
  result_r = a % b;
  TTS_EQUAL(0, result_q);
  TTS_EQUAL(a, result_r);
  // Try the other way around.
  swap(a, q);
  result_q = a / b;
  result_r = a % b;
  TTS_EQUAL(0, result_q);
  TTS_EQUAL(a, result_r);
  // Restore.
  swap(q, a);
  swap(b, a);

  // Try a large remainder.
  b = a / 2 + 1;
  uint128 expected_r =
      uint128(0x29876d3a0e38ea61, 0xdf92cba98c83ffff);
  // Sanity checks.
  TTS_EQUAL((a / 2 - 1), expected_r);
  TTS_EQUAL(a, b + expected_r);
  result_q = a / b;
  result_r = a % b;
  TTS_EQUAL(1, result_q);
  TTS_EQUAL(expected_r, result_r);
};

#ifdef SPY_SIMD_SUPPORTS_INT128
EVE_TEST_TYPES( "Check  __int128 support", eve::test::scalar:: uints_64)
<typename T>(eve::as<T>)
{
  using eve::uint128;
  if constexpr(spy::supports::int128_)
  {
    __int128 v = 1;
    uint128 a(v);
    TTS_EQUAL(a, 1);
    uint128 b(1, 1);
    __int128 w(b);
    uint128 c(w);
    TTS_EQUAL(c, b);
  }
  else
    TTS_PASS("__int128 not supported");
};
#endif
