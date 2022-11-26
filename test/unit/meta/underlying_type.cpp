//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/logical.hpp>
#include <eve/module/complex.hpp>
#include <eve/traits/underlying_type.hpp>
#include <eve/wide.hpp>

TTS_CASE( "Check for underlying_type: scalar types")
{
  using eve::logical;
  using eve::complex;

  TTS_TYPE_IS( eve::underlying_type_t<bool>                             , bool          );
  TTS_TYPE_IS( eve::underlying_type_t<int>                              , int           );
  TTS_TYPE_IS( eve::underlying_type_t<complex<float>>                   , float         );
  TTS_TYPE_IS( eve::underlying_type_t<logical<int>>                     , logical<int>  );
  TTS_TYPE_IS( eve::underlying_type_t<eve::as_logical_t<complex<float>>>, logical<float>);
};

TTS_CASE( "Check for underlying_type: SIMD types")
{
  using eve::logical;
  using eve::wide;
  using eve::complex;

  TTS_TYPE_IS((eve::underlying_type_t<wide<int,eve::fixed<8>>>)               , int           );
  TTS_TYPE_IS( eve::underlying_type_t<wide<int>>                              , int           );
  TTS_TYPE_IS( eve::underlying_type_t<wide<complex<float>>>                   , float         );
  TTS_TYPE_IS( eve::underlying_type_t<logical<wide<int>>>                     , logical<int>  );
  TTS_TYPE_IS( eve::underlying_type_t<eve::as_logical_t<wide<complex<float>>>>, logical<float>);
};

TTS_CASE( "Check for underlying_type: multiple types")
{
  using eve::wide;
  using eve::complex;

  TTS_TYPE_IS((eve::underlying_type_t<double,double,double,double>), double );
  TTS_TYPE_IS((eve::underlying_type_t<int,double,wide<float>,char>), float  );
  TTS_TYPE_IS((eve::underlying_type_t<eve::complex<double>,wide<complex<double>>,int>), double);
  TTS_TYPE_IS((eve::underlying_type_t<eve::complex<double>,int,wide<complex<double>>>), double);
  TTS_TYPE_IS((eve::underlying_type_t<int,eve::complex<double>,wide<complex<double>>>), double);
};
