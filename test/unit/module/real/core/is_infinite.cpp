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
#include <eve/function/is_infinite.hpp>
#include <eve/logical.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::is_infinite(simd)"
              , eve::test::simd::all_types
              )
<typename T>(eve::as_<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_infinite(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_infinite(v_t())                  , logical<v_t> );
};

//==================================================================================================
// Test cases values
//==================================================================================================
EVE_TEST( "Check corner-cases behavior of eve::is_infinite on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::limits())
        )
<typename T>(T const& cases)
{
  using type = typename T::type;
  using eve::as;
  TTS_EQUAL( eve::is_infinite(cases.nan    ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_infinite(-cases.nan   ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_infinite(cases.minf   ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_infinite(cases.inf    ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_infinite(cases.zero   ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_infinite(cases.mzero  ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_infinite(cases.valmin ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_infinite(cases.valmax ) , eve::false_(as<type>()));
};
