//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::is_not_nan(simd)"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_not_nan(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_not_nan(v_t())                  , logical<v_t> );
};

//==================================================================================================
// Tests for eve::is_not_nan
//==================================================================================================
EVE_TEST( "Check behavior of eve::is_not_nan(simd)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::ramp(0)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0,  M const & t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_not_nan(a0), map([](auto e) -> eve::logical<v_t> { return  (e == e); }, a0));
  TTS_EQUAL(eve::is_not_nan[t](a0), eve::if_else(t, eve::is_not_nan(a0), eve::false_(eve::as(a0))));
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
EVE_TEST( "Check corner-cases behavior of eve::is_not_nan on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::limits())
        )
<typename T>(T const& cases)
{
  using type = typename T::type;
  using eve::as;
  TTS_EQUAL( eve::is_not_nan(cases.nan    ) , eve::false_(as<type>()) );
  TTS_EQUAL( eve::is_not_nan(cases.minf   ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_not_nan(cases.inf    ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_not_nan(cases.mzero  ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_not_nan(cases.valmin ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_not_nan(cases.valmax ) , eve::true_(as<type>()));
};
