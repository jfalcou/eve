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
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>
#include <eve/function/is_infinite.hpp>
#include <eve/logical.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::is_infinite(simd)"
              , eve::test::simd::restricted::all_types
              )
<typename T>(eve::as<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_infinite(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_infinite(v_t())                  , logical<v_t> );
};

//==================================================================================================
// Tests for eve::is_infinite
//==================================================================================================

EVE_TEST( "Check behavior of eve::is_infinite(simd)"
        , eve::test::simd::restricted::ieee_reals
        , eve::test::generate ( eve::test::ramp(0)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T  a0,  M const & t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  a0 = eve::if_else(eve::is_eqz(a0), eve::inf(eve::as<v_t>()), eve::zero);
  TTS_EQUAL(eve::is_infinite(a0), map([](auto e) -> eve::logical<v_t> { return e-e != 0 && e == e; }, a0));
  TTS_EQUAL(eve::is_infinite[t](a0), eve::if_else(t, eve::is_infinite(a0), eve::false_(eve::as(a0))));
};
//==================================================================================================
// Test cases values
//==================================================================================================
EVE_TEST( "Check corner-cases behavior of eve::is_infinite on wide"
        , eve::test::simd::restricted::ieee_reals
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
