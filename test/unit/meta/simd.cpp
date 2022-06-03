//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/simd.hpp>

TTS_CASE("Check for plain_simd on regular types" )
{
  TTS_EXPECT( eve::plain_simd<eve::wide<signed char>> );
  TTS_EXPECT( eve::plain_simd<eve::wide<short>>       );
  TTS_EXPECT( eve::plain_simd<eve::wide<int>>         );

  TTS_EXPECT( eve::plain_simd<eve::wide<unsigned char> >);
  TTS_EXPECT( eve::plain_simd<eve::wide<unsigned short>>);
  TTS_EXPECT( eve::plain_simd<eve::wide<unsigned int>  >);

  TTS_EXPECT( eve::plain_simd<eve::wide<float> > );
  TTS_EXPECT( eve::plain_simd<eve::wide<double>> );
};

TTS_CASE("Check for plain_simd on cstdint/def types" )
{
  TTS_EXPECT( eve::plain_simd<eve::wide<std::int8_t> > );
  TTS_EXPECT( eve::plain_simd<eve::wide<std::int16_t>> );
  TTS_EXPECT( eve::plain_simd<eve::wide<std::int32_t>> );
  TTS_EXPECT( eve::plain_simd<eve::wide<std::int64_t>> );

  TTS_EXPECT( eve::plain_simd<eve::wide<std::uint8_t> > );
  TTS_EXPECT( eve::plain_simd<eve::wide<std::uint16_t>> );
  TTS_EXPECT( eve::plain_simd<eve::wide<std::uint32_t>> );
  TTS_EXPECT( eve::plain_simd<eve::wide<std::uint64_t>> );

  TTS_EXPECT( eve::plain_simd<eve::wide<std::size_t>>    );
  TTS_EXPECT( eve::plain_simd<eve::wide<std::ptrdiff_t>> );
};

TTS_CASE("Check for plain_simd on unsupported types" )
{
  TTS_EXPECT_NOT( eve::plain_simd<double>      );
  TTS_EXPECT_NOT( eve::plain_simd<int>         );
  TTS_EXPECT_NOT( eve::plain_simd<long double> );
  TTS_EXPECT_NOT( eve::plain_simd<bool>        );
  TTS_EXPECT_NOT( eve::plain_simd<void*>       );
  TTS_EXPECT_NOT((eve::plain_simd<kumi::tuple<int,float,std::int8_t>> ));
  TTS_EXPECT_NOT((eve::plain_simd<eve::wide<kumi::tuple<int,float,std::int8_t>>> ));
};

TTS_CASE("Check for product_simd on product_type" )
{
  TTS_EXPECT((eve::product_simd<eve::wide<kumi::tuple<int>>>));
  TTS_EXPECT((eve::product_simd<eve::wide<kumi::tuple<int,float>>>));
  TTS_EXPECT((eve::product_simd<eve::wide<kumi::tuple<int,std::int8_t,double>>>));
  TTS_EXPECT((eve::product_simd<eve::wide<kumi::tuple<int,kumi::tuple<std::int8_t,double>,float>>>));
};

TTS_CASE("Check for product_scalar on unsupported types" )
{
  TTS_EXPECT_NOT( eve::product_simd<long double>                           );
  TTS_EXPECT_NOT( eve::product_simd<std::int8_t>                           );
  TTS_EXPECT_NOT( eve::product_simd<void*>                                 );
  TTS_EXPECT_NOT( eve::product_simd<float>                                 );
  TTS_EXPECT_NOT((eve::product_simd<kumi::tuple<void*, int, long double>>) );
};

TTS_CASE("Check for simd on plain_simd" )
{
  TTS_EXPECT( eve::simd<eve::wide<signed char>> );
  TTS_EXPECT( eve::simd<eve::wide<short>>       );
  TTS_EXPECT( eve::simd<eve::wide<int>>         );

  TTS_EXPECT( eve::simd<eve::wide<unsigned char> >);
  TTS_EXPECT( eve::simd<eve::wide<unsigned short>>);
  TTS_EXPECT( eve::simd<eve::wide<unsigned int>  >);

  TTS_EXPECT( eve::simd<eve::wide<float> > );
  TTS_EXPECT( eve::simd<eve::wide<double>> );

  TTS_EXPECT( eve::simd<eve::wide<std::int8_t> > );
  TTS_EXPECT( eve::simd<eve::wide<std::int16_t>> );
  TTS_EXPECT( eve::simd<eve::wide<std::int32_t>> );
  TTS_EXPECT( eve::simd<eve::wide<std::int64_t>> );

  TTS_EXPECT( eve::simd<eve::wide<std::uint8_t> > );
  TTS_EXPECT( eve::simd<eve::wide<std::uint16_t>> );
  TTS_EXPECT( eve::simd<eve::wide<std::uint32_t>> );
  TTS_EXPECT( eve::simd<eve::wide<std::uint64_t>> );

  TTS_EXPECT( eve::simd<eve::wide<std::size_t>>    );
  TTS_EXPECT( eve::simd<eve::wide<std::ptrdiff_t>> );
};

TTS_CASE("Check for simd on product_type" )
{
  TTS_EXPECT((eve::simd<eve::wide<kumi::tuple<int>>>));
  TTS_EXPECT((eve::simd<eve::wide<kumi::tuple<int,float>>>));
  TTS_EXPECT((eve::simd<eve::wide<kumi::tuple<int,std::int8_t,double>>>));
  TTS_EXPECT((eve::simd<eve::wide<kumi::tuple<int,kumi::tuple<std::int8_t,double>,float>>>));
};

TTS_CASE("Check for simd on unsupported types" )
{
  TTS_EXPECT_NOT(  eve::simd<long double>             );
  TTS_EXPECT_NOT(  eve::simd<bool>                    );
  TTS_EXPECT_NOT(  eve::simd<void*>                   );
  TTS_EXPECT_NOT( (eve::simd<kumi::tuple<>>)          );
  TTS_EXPECT_NOT( (eve::simd<kumi::tuple<int,bool>>)  );
};

template<eve::plain_simd T>    auto check_overload(T)  { return +1;  }
template<eve::simd T>          auto check_overload(T)  { return +2;  }
template<eve::simd T>          auto check_overload2(T) { return +3;  }
template<eve::product_simd T>  auto check_overload3(T)  { return +10;  }
template<typename T>           auto check_overload(T)  { return -1;  }
template<typename T>           auto check_overload2(T) { return -3; }
template<typename T>           auto check_overload3(T)  { return -10;  }

TTS_CASE("Check for simd/plain_simd overload relationship" )
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
