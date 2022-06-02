//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/basic.hpp>
#include <string>

TTS_CASE("Check for builtin_vectorizable on regular types" )
{
  TTS_EXPECT( eve::builtin_vectorizable<signed char>);
  TTS_EXPECT( eve::builtin_vectorizable<char>       );
  TTS_EXPECT( eve::builtin_vectorizable<short>      );
  TTS_EXPECT( eve::builtin_vectorizable<int>        );
  TTS_EXPECT( eve::builtin_vectorizable<long>       );
  TTS_EXPECT( eve::builtin_vectorizable<long long>  );

  TTS_EXPECT( eve::builtin_vectorizable<unsigned char>      );
  TTS_EXPECT( eve::builtin_vectorizable<unsigned short>     );
  TTS_EXPECT( eve::builtin_vectorizable<unsigned int>       );
  TTS_EXPECT( eve::builtin_vectorizable<unsigned long>      );
  TTS_EXPECT( eve::builtin_vectorizable<unsigned long long> );

  TTS_EXPECT( eve::builtin_vectorizable<float>  );
  TTS_EXPECT( eve::builtin_vectorizable<double> );
};

TTS_CASE("Check for builtin_vectorizable on cstdint/def types" )
{
  TTS_EXPECT( eve::builtin_vectorizable<std::int8_t>  );
  TTS_EXPECT( eve::builtin_vectorizable<std::int16_t> );
  TTS_EXPECT( eve::builtin_vectorizable<std::int32_t> );
  TTS_EXPECT( eve::builtin_vectorizable<std::int64_t> );

  TTS_EXPECT( eve::builtin_vectorizable<std::uint8_t>  );
  TTS_EXPECT( eve::builtin_vectorizable<std::uint16_t> );
  TTS_EXPECT( eve::builtin_vectorizable<std::uint32_t> );
  TTS_EXPECT( eve::builtin_vectorizable<std::uint64_t> );

  TTS_EXPECT( eve::builtin_vectorizable<std::size_t>    );
  TTS_EXPECT( eve::builtin_vectorizable<std::ptrdiff_t> );
};

TTS_CASE("Check for builtin_vectorizable on unsupported types" )
{
  TTS_EXPECT_NOT( eve::builtin_vectorizable<std::string>                  );
  TTS_EXPECT_NOT( eve::builtin_vectorizable<bool>                         );
  TTS_EXPECT_NOT( eve::builtin_vectorizable<void*>                        );
  TTS_EXPECT_NOT((eve::builtin_vectorizable<kumi::tuple<int,float,char>> ));
};

TTS_CASE("Check for vectorizable on builtin_vectorizable" )
{
  TTS_EXPECT( eve::vectorizable<signed char>        );
  TTS_EXPECT( eve::vectorizable<char>               );
  TTS_EXPECT( eve::vectorizable<short>              );
  TTS_EXPECT( eve::vectorizable<int>                );
  TTS_EXPECT( eve::vectorizable<long>               );
  TTS_EXPECT( eve::vectorizable<long long>          );
  TTS_EXPECT( eve::vectorizable<unsigned char>      );
  TTS_EXPECT( eve::vectorizable<unsigned short>     );
  TTS_EXPECT( eve::vectorizable<unsigned int>       );
  TTS_EXPECT( eve::vectorizable<unsigned long>      );
  TTS_EXPECT( eve::vectorizable<unsigned long long> );
  TTS_EXPECT( eve::vectorizable<float>              );
  TTS_EXPECT( eve::vectorizable<double>             );

  TTS_EXPECT( eve::vectorizable<std::int8_t>    );
  TTS_EXPECT( eve::vectorizable<std::int16_t>   );
  TTS_EXPECT( eve::vectorizable<std::int32_t>   );
  TTS_EXPECT( eve::vectorizable<std::int64_t>   );
  TTS_EXPECT( eve::vectorizable<std::uint8_t>   );
  TTS_EXPECT( eve::vectorizable<std::uint16_t>  );
  TTS_EXPECT( eve::vectorizable<std::uint32_t>  );
  TTS_EXPECT( eve::vectorizable<std::uint64_t>  );
  TTS_EXPECT( eve::vectorizable<std::size_t>    );
  TTS_EXPECT( eve::vectorizable<std::ptrdiff_t> );
};

TTS_CASE("Check for vectorizable on product_type" )
{
  TTS_EXPECT((eve::vectorizable<kumi::tuple<int>>));
  TTS_EXPECT((eve::vectorizable<kumi::tuple<int,float>>));
  TTS_EXPECT((eve::vectorizable<kumi::tuple<int,signed char,double>>));
  TTS_EXPECT((eve::vectorizable<kumi::tuple<int,kumi::tuple<signed char,double>,float>>));
};

TTS_CASE("Check for vectorizable on unsupported types" )
{
  TTS_EXPECT_NOT(  eve::vectorizable<std::string>             );
  TTS_EXPECT_NOT(  eve::vectorizable<bool>                    );
  TTS_EXPECT_NOT(  eve::vectorizable<void*>                   );
  TTS_EXPECT_NOT( (eve::vectorizable<kumi::tuple<>>)          );
  TTS_EXPECT_NOT( (eve::vectorizable<kumi::tuple<int,bool>>)  );
};

template<eve::builtin_vectorizable T> auto check_overload(T)  { return +1;  }
template<eve::vectorizable T>         auto check_overload(T)  { return +2;  }
template<eve::vectorizable T>         auto check_overload2(T) { return +3;  }
template<typename T>                  auto check_overload(T)  { return -1;  }
template<typename T>                  auto check_overload2(T) { return -10; }

TTS_CASE("Check for vectorizable/builtin_vectorizable overload relationship" )
{
  TTS_EQUAL(check_overload(4)                    , +1);
  TTS_EQUAL(check_overload(4.f)                  , +1);
  TTS_EQUAL(check_overload(kumi::tuple{4})       , +2);
  TTS_EQUAL(check_overload(kumi::tuple{3,5.f})   , +2);

  TTS_EQUAL(check_overload2(4)                    , +3);
  TTS_EQUAL(check_overload2(4.f)                  , +3);
  TTS_EQUAL(check_overload2(kumi::tuple{4})       , +3);
  TTS_EQUAL(check_overload2(kumi::tuple{3,5.f})   , +3);

  TTS_EQUAL(check_overload(nullptr)              , -1);
  TTS_EQUAL(check_overload(kumi::tuple<>{})      , -1);
  TTS_EQUAL(check_overload(kumi::tuple{nullptr}) , -1);

  TTS_EQUAL(check_overload2(nullptr)              , -10);
  TTS_EQUAL(check_overload2(kumi::tuple<>{})      , -10);
  TTS_EQUAL(check_overload2(kumi::tuple{nullptr}) , -10);
};
