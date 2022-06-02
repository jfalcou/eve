//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/scalar.hpp>

TTS_CASE("Check for plain_scalar on regular types" )
{
  TTS_EXPECT( eve::plain_scalar<signed char>);
  TTS_EXPECT( eve::plain_scalar<short>      );
  TTS_EXPECT( eve::plain_scalar<int>        );

  TTS_EXPECT( eve::plain_scalar<unsigned char>      );
  TTS_EXPECT( eve::plain_scalar<unsigned short>     );
  TTS_EXPECT( eve::plain_scalar<unsigned int>       );

  TTS_EXPECT( eve::plain_scalar<float>  );
  TTS_EXPECT( eve::plain_scalar<double> );
};

TTS_CASE("Check for plain_scalar on cstdint/def types" )
{
  TTS_EXPECT( eve::plain_scalar<std::int8_t>  );
  TTS_EXPECT( eve::plain_scalar<std::int16_t> );
  TTS_EXPECT( eve::plain_scalar<std::int32_t> );
  TTS_EXPECT( eve::plain_scalar<std::int64_t> );

  TTS_EXPECT( eve::plain_scalar<std::uint8_t>  );
  TTS_EXPECT( eve::plain_scalar<std::uint16_t> );
  TTS_EXPECT( eve::plain_scalar<std::uint32_t> );
  TTS_EXPECT( eve::plain_scalar<std::uint64_t> );

  TTS_EXPECT( eve::plain_scalar<std::size_t>    );
  TTS_EXPECT( eve::plain_scalar<std::ptrdiff_t> );
};

TTS_CASE("Check for plain_scalar on unsupported types" )
{
  TTS_EXPECT_NOT( eve::plain_scalar<long double>                  );
  TTS_EXPECT_NOT( eve::plain_scalar<bool>                         );
  TTS_EXPECT_NOT( eve::plain_scalar<void*>                        );
  TTS_EXPECT_NOT((eve::plain_scalar<kumi::tuple<int,float,std::int8_t>> ));
};

TTS_CASE("Check for product_scalar on product_type" )
{
  TTS_EXPECT((eve::product_scalar<kumi::tuple<int>>));
  TTS_EXPECT((eve::product_scalar<kumi::tuple<int,float>>));
  TTS_EXPECT((eve::product_scalar<kumi::tuple<int,std::int8_t,double>>));
  TTS_EXPECT((eve::product_scalar<kumi::tuple<int,kumi::tuple<std::int8_t,double>,float>>));
};

TTS_CASE("Check for product_scalar on unsupported types" )
{
  TTS_EXPECT_NOT( eve::product_scalar<long double>                           );
  TTS_EXPECT_NOT( eve::product_scalar<std::int8_t>                           );
  TTS_EXPECT_NOT( eve::product_scalar<void*>                                 );
  TTS_EXPECT_NOT((eve::product_scalar<float> )                               );
  TTS_EXPECT_NOT((eve::product_scalar<kumi::tuple<void*, int, long double>>) );
};

TTS_CASE("Check for scalar on plain_scalar" )
{
  TTS_EXPECT( eve::scalar<signed char>        );
  TTS_EXPECT( eve::scalar<short>              );
  TTS_EXPECT( eve::scalar<int>                );
  TTS_EXPECT( eve::scalar<unsigned char>      );
  TTS_EXPECT( eve::scalar<unsigned short>     );
  TTS_EXPECT( eve::scalar<unsigned int>       );
  TTS_EXPECT( eve::scalar<float>              );
  TTS_EXPECT( eve::scalar<double>             );

  TTS_EXPECT( eve::scalar<std::int8_t>    );
  TTS_EXPECT( eve::scalar<std::int16_t>   );
  TTS_EXPECT( eve::scalar<std::int32_t>   );
  TTS_EXPECT( eve::scalar<std::int64_t>   );
  TTS_EXPECT( eve::scalar<std::uint8_t>   );
  TTS_EXPECT( eve::scalar<std::uint16_t>  );
  TTS_EXPECT( eve::scalar<std::uint32_t>  );
  TTS_EXPECT( eve::scalar<std::uint64_t>  );
  TTS_EXPECT( eve::scalar<std::size_t>    );
  TTS_EXPECT( eve::scalar<std::ptrdiff_t> );
};

TTS_CASE("Check for scalar on product_type" )
{
  TTS_EXPECT((eve::scalar<kumi::tuple<int>>));
  TTS_EXPECT((eve::scalar<kumi::tuple<int,float>>));
  TTS_EXPECT((eve::scalar<kumi::tuple<int,std::int8_t,double>>));
  TTS_EXPECT((eve::scalar<kumi::tuple<int,kumi::tuple<std::int8_t,double>,float>>));
};

TTS_CASE("Check for scalar on unsupported types" )
{
  TTS_EXPECT_NOT(  eve::scalar<long double>             );
  TTS_EXPECT_NOT(  eve::scalar<bool>                    );
  TTS_EXPECT_NOT(  eve::scalar<void*>                   );
  TTS_EXPECT_NOT( (eve::scalar<kumi::tuple<>>)          );
  TTS_EXPECT_NOT( (eve::scalar<kumi::tuple<int,bool>>)  );
};

template<eve::plain_scalar T>         auto check_overload(T)  { return +1;  }
template<eve::scalar T>               auto check_overload(T)  { return +2;  }
template<eve::scalar T>               auto check_overload2(T) { return +3;  }
template<eve::product_scalar T>  auto check_overload3(T)  { return +10;  }
template<typename T>                  auto check_overload(T)  { return -1;  }
template<typename T>                  auto check_overload2(T) { return -3; }
template<typename T>                  auto check_overload3(T)  { return -10;  }

TTS_CASE("Check for scalar/plain_scalar overload relationship" )
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
