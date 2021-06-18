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
#include <eve/function/is_nan.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/logical.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::is_nan(simd)"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_nan(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_nan(v_t())                  , logical<v_t> );
};

//==================================================================================================
// Tests for eve::is_nan
//==================================================================================================

EVE_TEST( "Check behavior of eve::is_nan(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::ramp(0))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_nan(a0), map([](auto e) -> eve::logical<v_t> { return  (e != e); }, a0));
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
EVE_TEST( "Check corner-cases behavior of eve::is_nan on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::limits())
        )
<typename T>(T const& cases)
{
  using type = typename T::type;
  using eve::as;
  TTS_EQUAL( eve::is_nan(cases.nan    ) , eve::true_(as<type>()) );
  TTS_EQUAL( eve::is_nan(cases.minf   ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_nan(cases.inf    ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_nan(cases.mzero  ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_nan(cases.valmin ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_nan(cases.valmax ) , eve::false_(as<type>()));
};
