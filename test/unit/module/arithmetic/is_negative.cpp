//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::is_negative(simd)"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_negative(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_negative(v_t())                  , logical<v_t> );
};

//==================================================================================================
// Tests for eve::is_negative
//==================================================================================================

EVE_TEST( "Check behavior of eve::is_negative(simd)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::ramp(0.0)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T  a0,  M const & t)
{
  using eve::detail::map;
  using eve::one;
  using eve::bit_or;
  using eve::as;
  using eve::bitofsign;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_negative(a0), map([](auto e) -> eve::logical<v_t> { return   bit_or(bitofsign(e), one(as(e))) < v_t(0); }, a0));
  TTS_EQUAL(eve::is_negative(-a0), map([](auto e) -> eve::logical<v_t> { return  bit_or(bitofsign(e), one(as(e))) < v_t(0); }, -a0));
  TTS_EQUAL(eve::is_negative[t](a0), eve::if_else(t, eve::is_negative(a0), eve::false_(eve::as(a0))));
};


//==================================================================================================
// Test for corner-cases values
//==================================================================================================
EVE_TEST( "Check corner-cases behavior of eve::is_negative on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::limits())
        )
<typename T>(T const& cases)
{
  using type = typename T::type;
  using eve::as;
  TTS_EQUAL( eve::is_negative(cases.nan    ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_negative(-cases.nan   ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_negative(cases.minf   ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_negative(cases.inf    ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_negative(cases.zero   ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_negative(cases.mzero  ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_negative(cases.valmin ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_negative(cases.valmax ) , eve::false_(as<type>()));
};
