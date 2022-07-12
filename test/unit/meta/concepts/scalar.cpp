//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/scalar.hpp>

TTS_CASE("Check for plain_scalar_value on regular types" )
{
  TTS_EXPECT( eve::plain_scalar_value<signed char>  );
  TTS_EXPECT( eve::plain_scalar_value<short>        );
  TTS_EXPECT( eve::plain_scalar_value<int>          );
  TTS_EXPECT( eve::plain_scalar_value<decltype(1LL)>);

  TTS_EXPECT( eve::plain_scalar_value<unsigned char>  );
  TTS_EXPECT( eve::plain_scalar_value<unsigned short> );
  TTS_EXPECT( eve::plain_scalar_value<unsigned int>   );
  TTS_EXPECT( eve::plain_scalar_value<decltype(1ULL)> );

  TTS_EXPECT( eve::plain_scalar_value<float>  );
  TTS_EXPECT( eve::plain_scalar_value<double> );
};

TTS_CASE("Check for plain_scalar_value on cstdint/def types" )
{
  TTS_EXPECT( eve::plain_scalar_value<std::int8_t>  );
  TTS_EXPECT( eve::plain_scalar_value<std::int16_t> );
  TTS_EXPECT( eve::plain_scalar_value<std::int32_t> );
  TTS_EXPECT( eve::plain_scalar_value<std::int64_t> );

  TTS_EXPECT( eve::plain_scalar_value<std::uint8_t>  );
  TTS_EXPECT( eve::plain_scalar_value<std::uint16_t> );
  TTS_EXPECT( eve::plain_scalar_value<std::uint32_t> );
  TTS_EXPECT( eve::plain_scalar_value<std::uint64_t> );

  TTS_EXPECT( eve::plain_scalar_value<std::size_t>    );
  TTS_EXPECT( eve::plain_scalar_value<std::ptrdiff_t> );
};

TTS_CASE("Check for plain_scalar_value on unsupported types" )
{
  TTS_EXPECT_NOT( eve::plain_scalar_value<char>                         );
  TTS_EXPECT_NOT( eve::plain_scalar_value<long double>                  );
  TTS_EXPECT_NOT( eve::plain_scalar_value<bool>                         );
  TTS_EXPECT_NOT( eve::plain_scalar_value<void*>                        );
  TTS_EXPECT_NOT((eve::plain_scalar_value<kumi::tuple<int,float,std::int8_t>> ));
};

TTS_CASE("Check for product_scalar_value on product_type" )
{
  TTS_EXPECT((eve::product_scalar_value<kumi::tuple<int>>));
  TTS_EXPECT((eve::product_scalar_value<kumi::tuple<int,float>>));
  TTS_EXPECT((eve::product_scalar_value<kumi::tuple<int,std::int8_t,double>>));
  TTS_EXPECT((eve::product_scalar_value<kumi::tuple<int,kumi::tuple<std::int8_t,double>,float>>));
};

TTS_CASE("Check for product_scalar_value on unsupported types" )
{
  TTS_EXPECT_NOT( eve::product_scalar_value<long double>                           );
  TTS_EXPECT_NOT( eve::product_scalar_value<std::int8_t>                           );
  TTS_EXPECT_NOT( eve::product_scalar_value<void*>                                 );
  TTS_EXPECT_NOT((eve::product_scalar_value<float> )                               );
  TTS_EXPECT_NOT((eve::product_scalar_value<kumi::tuple<void*, int, long double>>) );
};

TTS_CASE("Check for arithmetic_scalar_value on plain_scalar_value" )
{
  TTS_EXPECT( eve::arithmetic_scalar_value<signed char>        );
  TTS_EXPECT( eve::arithmetic_scalar_value<short>              );
  TTS_EXPECT( eve::arithmetic_scalar_value<int>                );
  TTS_EXPECT( eve::arithmetic_scalar_value<unsigned char>      );
  TTS_EXPECT( eve::arithmetic_scalar_value<unsigned short>     );
  TTS_EXPECT( eve::arithmetic_scalar_value<unsigned int>       );
  TTS_EXPECT( eve::arithmetic_scalar_value<float>              );
  TTS_EXPECT( eve::arithmetic_scalar_value<double>             );

  TTS_EXPECT( eve::arithmetic_scalar_value<std::int8_t>    );
  TTS_EXPECT( eve::arithmetic_scalar_value<std::int16_t>   );
  TTS_EXPECT( eve::arithmetic_scalar_value<std::int32_t>   );
  TTS_EXPECT( eve::arithmetic_scalar_value<std::int64_t>   );
  TTS_EXPECT( eve::arithmetic_scalar_value<std::uint8_t>   );
  TTS_EXPECT( eve::arithmetic_scalar_value<std::uint16_t>  );
  TTS_EXPECT( eve::arithmetic_scalar_value<std::uint32_t>  );
  TTS_EXPECT( eve::arithmetic_scalar_value<std::uint64_t>  );
  TTS_EXPECT( eve::arithmetic_scalar_value<std::size_t>    );
  TTS_EXPECT( eve::arithmetic_scalar_value<std::ptrdiff_t> );
};

TTS_CASE("Check for arithmetic_scalar_value on product_type" )
{
  TTS_EXPECT((eve::arithmetic_scalar_value<kumi::tuple<int>>));
  TTS_EXPECT((eve::arithmetic_scalar_value<kumi::tuple<int,float>>));
  TTS_EXPECT((eve::arithmetic_scalar_value<kumi::tuple<int,std::int8_t,double>>));
  TTS_EXPECT((eve::arithmetic_scalar_value<kumi::tuple<int,kumi::tuple<std::int8_t,double>,float>>));
};

TTS_CASE("Check for arithmetic_scalar_value on unsupported types" )
{
  TTS_EXPECT_NOT(  eve::arithmetic_scalar_value<long double>             );
  TTS_EXPECT_NOT(  eve::arithmetic_scalar_value<bool>                    );
  TTS_EXPECT_NOT(  eve::arithmetic_scalar_value<void*>                   );
  TTS_EXPECT_NOT( (eve::arithmetic_scalar_value<kumi::tuple<>>)          );
  TTS_EXPECT_NOT( (eve::arithmetic_scalar_value<kumi::tuple<int,bool>>)  );
};

template<eve::plain_scalar_value T>       auto check_overload(T)  { return +1;  }
template<eve::arithmetic_scalar_value T>  auto check_overload(T)  { return +2;  }
template<eve::arithmetic_scalar_value T>  auto check_overload2(T) { return +3;  }
template<eve::product_scalar_value T>     auto check_overload3(T)  { return +10;  }
template<typename T>                      auto check_overload(T)  { return -1;  }
template<typename T>                      auto check_overload2(T) { return -3; }
template<typename T>                      auto check_overload3(T)  { return -10;  }

TTS_CASE("Check for arithmetic_scalar_value/plain_scalar_value overload relationship" )
{
  TTS_EQUAL(check_overload(4)                    , +1);
  TTS_EQUAL(check_overload(4.f)                  , +1);
  TTS_EQUAL(check_overload(kumi::tuple{4})       , +2);
  TTS_EQUAL(check_overload(kumi::tuple{3,5.f})   , +2);

  TTS_EQUAL(check_overload(nullptr)              , -1);
  TTS_EQUAL(check_overload(kumi::tuple<>{})      , -1);
  TTS_EQUAL(check_overload(kumi::tuple{nullptr}) , -1);

  TTS_EQUAL(check_overload2(4)                    , +3);
  TTS_EQUAL(check_overload2(4.f)                  , +3);
  TTS_EQUAL(check_overload2(kumi::tuple{4})       , +3);
  TTS_EQUAL(check_overload2(kumi::tuple{3,5.f})   , +3);

  TTS_EQUAL(check_overload2(nullptr)              , -3);
  TTS_EQUAL(check_overload2(kumi::tuple<>{})      , -3);
  TTS_EQUAL(check_overload2(kumi::tuple{nullptr}) , -3);

  TTS_EQUAL(check_overload3(kumi::tuple{4})                     , +10);
  TTS_EQUAL(check_overload3(kumi::tuple{3,5.f})                 , +10);
  TTS_EQUAL(check_overload3(kumi::tuple{3,kumi::tuple{4.},5.f}) , +10);

  TTS_EQUAL(check_overload3(4)                    , -10);
  TTS_EQUAL(check_overload3(4.f)                  , -10);
  TTS_EQUAL(check_overload3(nullptr)              , -10);
  TTS_EQUAL(check_overload3(kumi::tuple<>{})      , -10);
  TTS_EQUAL(check_overload3(kumi::tuple{nullptr}) , -10);
};
