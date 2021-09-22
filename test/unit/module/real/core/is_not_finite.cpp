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
#include <eve/function/is_not_finite.hpp>
#include <eve/logical.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::is_not_finite(simd)"
              , eve::test::simd::restricted::all_types
              )
<typename T>(eve::as<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_not_finite(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_not_finite(v_t())                  , logical<v_t> );
};

EVE_TEST( "Check behavior of eve::is_not_finite(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::ramp(0)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0,  M const & t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_not_finite(a0), map([](auto e) -> eve::logical<v_t> { return  e - e != 0; }, a0));
  TTS_EQUAL(eve::is_not_finite[t](a0), eve::if_else(t, eve::is_not_finite(a0), eve::false_(eve::as(a0))));
};

//==================================================================================================
// Test cases values
//==================================================================================================
EVE_TEST( "Check corner-cases behavior of eve::is_not_finite on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::limits())
        )
<typename T>(T const& cases)
{
  using type = typename T::type;
  using eve::as;
  TTS_EQUAL( eve::is_not_finite(cases.nan    ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_not_finite(-cases.nan   ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_not_finite(cases.minf   ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_not_finite(cases.inf    ) , eve::true_(as<type>()));
  TTS_EQUAL( eve::is_not_finite(cases.zero   ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_not_finite(cases.mzero  ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_not_finite(cases.valmin ) , eve::false_(as<type>()));
  TTS_EQUAL( eve::is_not_finite(cases.valmax ) , eve::false_(as<type>()));
};
