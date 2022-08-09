//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/logical.hpp>

TTS_CASE("Check for logical_scalar/simd_value on regular types" )
{
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<signed char>>    );
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<short>>          );
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<int>>            );
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<unsigned char> > );
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<unsigned short>> );
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<unsigned int>  > );
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<float> >         );
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<double>>         );

  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<signed char>>   > );
  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<short>>         > );
  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<int>>           > );
  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<unsigned char> >> );
  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<unsigned short>>> );
  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<unsigned int>  >> );
  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<float> >        > );
  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<double>>        > );
};

TTS_CASE("Check for logical_scalar/simd_value on cstdint/def types" )
{
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<std::int8_t>>    );
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<std::int16_t>>   );
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<std::int32_t>>   );
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<std::int64_t> >  );
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<std::uint8_t>>   );
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<std::uint16_t>>  );
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<std::uint32_t>>  );
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<std::uint64_t>>  );
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<std::size_t>>    );
  TTS_EXPECT( eve::logical_scalar_value<eve::logical<std::ptrdiff_t> >);

  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<std::int8_t>>>   );
  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<std::int16_t>>>  );
  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<std::int32_t>>>  );
  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<std::int64_t>>>  );
  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<std::uint8_t>>>  );
  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<std::uint16_t>>> );
  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<std::uint32_t>>> );
  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<std::uint64_t>>> );
  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<std::size_t>>>   );
  TTS_EXPECT( eve::logical_simd_value<eve::logical<eve::wide<std::ptrdiff_t>>>);
};

TTS_CASE("Check for logical_scalar/simd_value on unsupported types" )
{
  TTS_EXPECT_NOT( eve::logical_scalar_value<signed char>    );
  TTS_EXPECT_NOT( eve::logical_scalar_value<short>          );
  TTS_EXPECT_NOT( eve::logical_scalar_value<int>            );
  TTS_EXPECT_NOT( eve::logical_scalar_value<unsigned char>  );
  TTS_EXPECT_NOT( eve::logical_scalar_value<unsigned short> );
  TTS_EXPECT_NOT( eve::logical_scalar_value<unsigned int>   );
  TTS_EXPECT_NOT( eve::logical_scalar_value<float>          );
  TTS_EXPECT_NOT( eve::logical_scalar_value<double>         );
  TTS_EXPECT_NOT( eve::logical_scalar_value<double>         );
  TTS_EXPECT_NOT( eve::logical_scalar_value<int>            );
  TTS_EXPECT_NOT( eve::logical_scalar_value<long double>    );
  TTS_EXPECT_NOT( eve::logical_scalar_value<bool>           );
  TTS_EXPECT_NOT( eve::logical_scalar_value<void*>          );

  TTS_EXPECT_NOT( eve::logical_simd_value<eve::wide<signed char>   >);
  TTS_EXPECT_NOT( eve::logical_simd_value<eve::wide<short>         >);
  TTS_EXPECT_NOT( eve::logical_simd_value<eve::wide<int>           >);
  TTS_EXPECT_NOT( eve::logical_simd_value<eve::wide<unsigned char> >);
  TTS_EXPECT_NOT( eve::logical_simd_value<eve::wide<unsigned short>>);
  TTS_EXPECT_NOT( eve::logical_simd_value<eve::wide<unsigned int>  >);
  TTS_EXPECT_NOT( eve::logical_simd_value<eve::wide<float>         >);
  TTS_EXPECT_NOT( eve::logical_simd_value<eve::wide<double>        >);
  TTS_EXPECT_NOT( eve::logical_simd_value<eve::wide<double>        >);
  TTS_EXPECT_NOT( eve::logical_simd_value<eve::wide<int>           >);
  TTS_EXPECT_NOT( eve::logical_simd_value<long double>              );
  TTS_EXPECT_NOT( eve::logical_simd_value<bool>                     );
  TTS_EXPECT_NOT( eve::logical_simd_value<void*>                    );

  TTS_EXPECT_NOT((eve::logical_scalar_value<kumi::tuple<int,float,std::int8_t>> ));
  TTS_EXPECT_NOT((eve::logical_scalar_value<eve::wide<kumi::tuple<int,float,std::int8_t>>> ));
  TTS_EXPECT_NOT((eve::logical_simd_value<kumi::tuple<int,float,std::int8_t>> ));
  TTS_EXPECT_NOT((eve::logical_simd_value<eve::wide<kumi::tuple<int,float,std::int8_t>>> ));
};

template<eve::logical_scalar_value T>  auto check_overload(T)  { return +20;  }
template<eve::logical_simd_value T>    auto check_overload(T)  { return +10;  }
template<typename T>                   auto check_overload(T)  { return   0;  }
template<eve::plain_simd_value T>      auto check_overload(T)  { return -10;  }
template<eve::plain_scalar_value T>    auto check_overload(T)  { return -20;  }

TTS_CASE("Check for logical_scalar_value overload relationship" )
{
  TTS_EQUAL(check_overload(eve::logical<float>{})           , +20);
  TTS_EQUAL(check_overload(eve::logical<eve::wide<float>>{}), +10);
  TTS_EQUAL(check_overload(nullptr)                         ,   0);
  TTS_EQUAL(check_overload(4)                               , -20);
  TTS_EQUAL(check_overload(eve::wide<float>{})              , -10);
};
