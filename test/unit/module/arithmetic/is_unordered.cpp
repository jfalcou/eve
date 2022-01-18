//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/nan.hpp>
#include <eve/function/is_unordered.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::is_unordered(simd)"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_unordered(T(), T())     , logical<T>   );
  TTS_EXPR_IS( eve::is_unordered(v_t(), v_t()) , logical<v_t> );
  TTS_EXPR_IS( eve::is_unordered(T(), v_t())   , logical<T> );
  TTS_EXPR_IS( eve::is_unordered(v_t(), T())   , logical<T> );
};

//==================================================================================================
//== Tests for eve::is_unordered
//==================================================================================================
EVE_TEST( "Check behavior of eve::is_unordered(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::ramp(0)
                              , eve::test::reverse_ramp(4, 2)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T a0, T const& a1, M const & t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  a0.set(0, eve::nan(eve::as<v_t>()));
  TTS_EQUAL(eve::is_unordered(a0, a1), map([](auto e, auto f) -> eve::logical<v_t> { return  (e != e) || (f != f); }, a0, a1));
  TTS_EQUAL(eve::is_unordered(a0, v_t(1)), map([](auto e) -> eve::logical<v_t> { return  (e != e); }, a0));
  TTS_EQUAL(eve::is_unordered(v_t(14), a1), map([](auto e) -> eve::logical<v_t> { return (e != e); }, a1));
  TTS_EQUAL(eve::is_unordered[t](a0, a1), eve::if_else(t, eve::is_unordered(a0, a1), eve::false_(eve::as(a0))));
};

//==================================================================================================
//== Tests for eve::is_unordered corner cases for floating
//==================================================================================================
EVE_TEST( "Check behavior of eve::is_unordered(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::limits())
        )
<typename aT>(aT const& cases)
{
  using T = typename aT::type;
  using eve::detail::map;
  using eve::as;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_unordered(cases.nan, cases.nan ) , eve::true_(as<T>()));
  TTS_EQUAL(eve::is_unordered(cases.nan, T(1)      ) , eve::true_(as<T>()));
  TTS_EQUAL(eve::is_unordered(T(1), cases.nan      ) , eve::true_(as<T>()));
  TTS_EQUAL(eve::is_unordered(T(1), T(1)           ) , eve::false_(as<T>()));
  TTS_EQUAL(eve::is_unordered(T(1), v_t(1)         ) , eve::false_(as<T>()));
};
