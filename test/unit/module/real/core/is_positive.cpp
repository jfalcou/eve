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
#include <eve/function/is_positive.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/one.hpp>
#include <eve/logical.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::is_positive(simd)"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_positive(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_positive(v_t())                  , logical<v_t> );
};

//==================================================================================================
// Tests for eve::is_positive
//==================================================================================================

EVE_TEST( "Check behavior of eve::is_positive(simd)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::ramp(0.0))
        )
<typename T>(T const& a0)
{
  using eve::detail::map;
  using eve::one;
  using eve::bit_or;
  using eve::as;
  using eve::bitofsign;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_positive(a0), map([](auto e) -> eve::logical<v_t> { return   bit_or(bitofsign(e), one(as(e))) > v_t(0); }, a0));
  TTS_EQUAL(eve::is_positive(-a0), map([](auto e) -> eve::logical<v_t> { return  bit_or(bitofsign(e), one(as(e))) > v_t(0); }, -a0));
};


//==================================================================================================
// Test for corner-cases values
//==================================================================================================
EVE_TEST( "Check corner-cases behavior of eve::is_positive on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::limits())
        )
<typename T>(T const& cases)
{
  using type = typename T::type;
  using eve::as;
  TTS_EQUAL( eve::is_positive(cases.nan    ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_positive(-cases.nan   ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_positive(cases.minf   ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_positive(cases.inf    ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_positive(cases.zero   ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_positive(cases.mzero  ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_positive(cases.valmin ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_positive(cases.valmax ) , eve::true_(as<type>()));
};
