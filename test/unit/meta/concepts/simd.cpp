//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/simd.hpp>

TTS_CASE("Check for plain_simd_value on regular types" )
{
  TTS_EXPECT( eve::plain_simd_value<eve::wide<signed char>> );
  TTS_EXPECT( eve::plain_simd_value<eve::wide<short>>       );
  TTS_EXPECT( eve::plain_simd_value<eve::wide<int>>         );

  TTS_EXPECT( eve::plain_simd_value<eve::wide<unsigned char> >);
  TTS_EXPECT( eve::plain_simd_value<eve::wide<unsigned short>>);
  TTS_EXPECT( eve::plain_simd_value<eve::wide<unsigned int>  >);

  TTS_EXPECT( eve::plain_simd_value<eve::wide<float> > );
  TTS_EXPECT( eve::plain_simd_value<eve::wide<double>> );
};

TTS_CASE("Check for plain_simd_value on cstdint/def types" )
{
  TTS_EXPECT( eve::plain_simd_value<eve::wide<std::int8_t> > );
  TTS_EXPECT( eve::plain_simd_value<eve::wide<std::int16_t>> );
  TTS_EXPECT( eve::plain_simd_value<eve::wide<std::int32_t>> );
  TTS_EXPECT( eve::plain_simd_value<eve::wide<std::int64_t>> );

  TTS_EXPECT( eve::plain_simd_value<eve::wide<std::uint8_t> > );
  TTS_EXPECT( eve::plain_simd_value<eve::wide<std::uint16_t>> );
  TTS_EXPECT( eve::plain_simd_value<eve::wide<std::uint32_t>> );
  TTS_EXPECT( eve::plain_simd_value<eve::wide<std::uint64_t>> );
};

TTS_CASE("Check for plain_simd_value on unsupported types" )
{
  TTS_EXPECT_NOT( eve::plain_simd_value<double>      );
  TTS_EXPECT_NOT( eve::plain_simd_value<int>         );
  TTS_EXPECT_NOT( eve::plain_simd_value<long double> );
  TTS_EXPECT_NOT( eve::plain_simd_value<bool>        );
  TTS_EXPECT_NOT( eve::plain_simd_value<void*>       );
  TTS_EXPECT_NOT((eve::plain_simd_value<kumi::tuple<int,float,std::int8_t>> ));
  TTS_EXPECT_NOT((eve::plain_simd_value<eve::wide<kumi::tuple<int,float,std::int8_t>>> ));
};

TTS_CASE("Check for product_simd_value on product_type" )
{
  TTS_EXPECT((eve::product_simd_value<eve::wide<kumi::tuple<int>>>));
  TTS_EXPECT((eve::product_simd_value<eve::wide<kumi::tuple<int,float>>>));
  TTS_EXPECT((eve::product_simd_value<eve::wide<kumi::tuple<int,std::int8_t,double>>>));
  TTS_EXPECT((eve::product_simd_value<eve::wide<kumi::tuple<int,kumi::tuple<std::int8_t,double>,float>>>));
};

TTS_CASE("Check for product_scalar on unsupported types" )
{
  TTS_EXPECT_NOT( eve::product_simd_value<long double>                           );
  TTS_EXPECT_NOT( eve::product_simd_value<std::int8_t>                           );
  TTS_EXPECT_NOT( eve::product_simd_value<void*>                                 );
  TTS_EXPECT_NOT( eve::product_simd_value<float>                                 );
  TTS_EXPECT_NOT((eve::product_simd_value<kumi::tuple<void*, int, long double>>) );
};

TTS_CASE("Check for arithmetic_simd_value on plain_simd_value" )
{
  TTS_EXPECT( eve::arithmetic_simd_value<eve::wide<signed char>> );
  TTS_EXPECT( eve::arithmetic_simd_value<eve::wide<short>>       );
  TTS_EXPECT( eve::arithmetic_simd_value<eve::wide<int>>         );

  TTS_EXPECT( eve::arithmetic_simd_value<eve::wide<unsigned char> >);
  TTS_EXPECT( eve::arithmetic_simd_value<eve::wide<unsigned short>>);
  TTS_EXPECT( eve::arithmetic_simd_value<eve::wide<unsigned int>  >);

  TTS_EXPECT( eve::arithmetic_simd_value<eve::wide<float> > );
  TTS_EXPECT( eve::arithmetic_simd_value<eve::wide<double>> );

  TTS_EXPECT( eve::arithmetic_simd_value<eve::wide<std::int8_t> > );
  TTS_EXPECT( eve::arithmetic_simd_value<eve::wide<std::int16_t>> );
  TTS_EXPECT( eve::arithmetic_simd_value<eve::wide<std::int32_t>> );
  TTS_EXPECT( eve::arithmetic_simd_value<eve::wide<std::int64_t>> );

  TTS_EXPECT( eve::arithmetic_simd_value<eve::wide<std::uint8_t> > );
  TTS_EXPECT( eve::arithmetic_simd_value<eve::wide<std::uint16_t>> );
  TTS_EXPECT( eve::arithmetic_simd_value<eve::wide<std::uint32_t>> );
  TTS_EXPECT( eve::arithmetic_simd_value<eve::wide<std::uint64_t>> );
};

TTS_CASE("Check for arithmetic_simd_value on product_type" )
{
  TTS_EXPECT((eve::arithmetic_simd_value<eve::wide<kumi::tuple<int>>>));
  TTS_EXPECT((eve::arithmetic_simd_value<eve::wide<kumi::tuple<int,float>>>));
  TTS_EXPECT((eve::arithmetic_simd_value<eve::wide<kumi::tuple<int,std::int8_t,double>>>));
  TTS_EXPECT((eve::arithmetic_simd_value<eve::wide<kumi::tuple<int,kumi::tuple<std::int8_t,double>,float>>>));
};

TTS_CASE("Check for arithmetic_simd_value on unsupported types" )
{
  TTS_EXPECT_NOT(  eve::arithmetic_simd_value<long double>             );
  TTS_EXPECT_NOT(  eve::arithmetic_simd_value<bool>                    );
  TTS_EXPECT_NOT(  eve::arithmetic_simd_value<void*>                   );
  TTS_EXPECT_NOT( (eve::arithmetic_simd_value<kumi::tuple<>>)          );
  TTS_EXPECT_NOT( (eve::arithmetic_simd_value<kumi::tuple<int,bool>>)  );
};

template<eve::plain_simd_value T>    auto check_overload(T)  { return +1;  }
template<eve::arithmetic_simd_value T>          auto check_overload(T)  { return +2;  }
template<eve::arithmetic_simd_value T>          auto check_overload2(T) { return +3;  }
template<eve::product_simd_value T>  auto check_overload3(T)  { return +10;  }
template<typename T>           auto check_overload(T)  { return -1;  }
template<typename T>           auto check_overload2(T) { return -3; }
template<typename T>           auto check_overload3(T)  { return -10;  }

TTS_CASE("Check for arithmetic_simd_value/plain_simd_value overload relationship" )
{
  TTS_EQUAL(check_overload(eve::wide<float>{})                  , +1);
  TTS_EQUAL(check_overload(eve::wide<kumi::tuple<int>>{})       , +2);
  TTS_EQUAL(check_overload(eve::wide<kumi::tuple<float,int>>{}) , +2);
  TTS_EQUAL(check_overload(eve::wide<kumi::tuple<float,kumi::tuple<short>,int>>{}) , +2);

  TTS_EQUAL(check_overload(4)                    , -1);
  TTS_EQUAL(check_overload(nullptr)              , -1);
  TTS_EQUAL(check_overload(kumi::tuple<>{})      , -1);
  TTS_EQUAL(check_overload(kumi::tuple{nullptr}) , -1);

  TTS_EQUAL(check_overload2(eve::wide<float>{})                  , +3);
  TTS_EQUAL(check_overload2(eve::wide<kumi::tuple<int>>{})       , +3);
  TTS_EQUAL(check_overload2(eve::wide<kumi::tuple<float,int>>{}) , +3);
  TTS_EQUAL(check_overload2(eve::wide<kumi::tuple<float,kumi::tuple<short>,int>>{}) , +3);

  TTS_EQUAL(check_overload2(4.f)                  , -3);
  TTS_EQUAL(check_overload2(nullptr)              , -3);
  TTS_EQUAL(check_overload2(kumi::tuple<>{})      , -3);
  TTS_EQUAL(check_overload2(kumi::tuple{nullptr}) , -3);

  TTS_EQUAL(check_overload3(eve::wide<kumi::tuple<int>>{})       , +10);
  TTS_EQUAL(check_overload3(eve::wide<kumi::tuple<float,int>>{}) , +10);
  TTS_EQUAL(check_overload3(eve::wide<kumi::tuple<float,kumi::tuple<short>,int>>{}) , +10);

  TTS_EQUAL(check_overload3(4)                    , -10);
  TTS_EQUAL(check_overload3(eve::wide<double>{})  , -10);
  TTS_EQUAL(check_overload3(nullptr)              , -10);
  TTS_EQUAL(check_overload3(kumi::tuple<>{})      , -10);
};
