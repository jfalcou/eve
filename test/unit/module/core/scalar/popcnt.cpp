//==================================================================================================
/*
  Copyright 2018 Joel FALCOU

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */
//==================================================================================================
#include <eve/function/scalar/popcnt.hpp>
#include <lest/lest.hpp>

const lest::test specification[] =
{
  CASE( "Check popcnt correctness on 8 bits integrals" )
  {
    using eve::popcnt;

    EXPECT( popcnt(std::uint8_t{0})           == 0);
    EXPECT( popcnt(std::uint8_t{255})         == 8);
    EXPECT( popcnt(std::uint8_t{0b10101010})  == 4);

    EXPECT( popcnt(std::int8_t{0})          == 0);
    EXPECT( popcnt(std::int8_t{0b01111111}) == 7);
    EXPECT( popcnt(std::int8_t{-128})       == 1);
  }
  , CASE( "Check popcnt correctness on 16 bits integrals" )
  {
    using eve::popcnt;

    EXPECT( popcnt(std::uint16_t{0})                  ==  0 );
    EXPECT( popcnt(std::uint16_t{65535})              == 16 );
    EXPECT( popcnt(std::uint16_t{0b1010101010101010}) ==  8 );

    EXPECT( popcnt(std::int16_t{0})                   ==  0 );
    EXPECT( popcnt(std::int16_t{0b0111111111111111})  == 15 );
    EXPECT( popcnt(std::int16_t{-32768})              ==  1 );
  }
  , CASE( "Check popcnt correctness on 32 bits integrals" )
  {
    using eve::popcnt;

    EXPECT( popcnt(std::uint32_t{0})          == 0UL  );
    EXPECT( popcnt(std::uint32_t{0xFFFFFFFF}) == 32UL );
    EXPECT( popcnt(std::uint32_t{0xAAAAAAAA}) == 16UL );

    EXPECT( popcnt(std::int32_t{0})           ==  0UL );
    EXPECT( popcnt(std::int32_t{0x7FFFFFFF})  == 31UL );
    EXPECT( popcnt(std::int32_t{-2147483648}) ==  1UL );
  }
  , CASE( "Check popcnt correctness on 64 bits integrals" )
  {
    using eve::popcnt;

    EXPECT( popcnt(std::uint64_t{0})                      ==  0ULL);
    EXPECT( popcnt(std::uint64_t{0xFFFFFFFFFFFFFFFFULL})  == 64ULL);
    EXPECT( popcnt(std::uint64_t{0xAAAAAAAAAAAAAAAAULL})  == 32ULL);

    EXPECT( popcnt(std::int64_t{0})                       ==  0ULL);
    EXPECT( popcnt(std::int64_t{0x7FFFFFFFFFFFFFFFULL})   == 63ULL);
    EXPECT( popcnt(std::int64_t{-9223372036854775808LL})  ==  1ULL);
  }
};

int main( int argc, char** argv )
{
  return lest::run( specification, argc, argv );
}
