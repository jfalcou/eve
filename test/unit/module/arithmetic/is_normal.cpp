//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/function/is_normal.hpp>
#include <eve/module/arithmetic/constant/smallestposval.hpp>
#include <eve/logical.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::is_normal(simd)"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_normal(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_normal(v_t())                  , logical<v_t> );
};

//==================================================================================================
// Tests for eve::is_normal
//==================================================================================================
auto mini = []<typename T>(eve::as<T> const & tgt)
{
  return 2*eve::smallestposval(tgt);
};
EVE_TEST( "Check behavior of eve::is_normal(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(eve::smallestposval, mini)
                              , eve::test::randoms(eve::zero, eve::mindenormal)
                              , eve::test::randoms(eve::zero, mini)
                              , eve::test::logicals(0, 3))
        )
<typename T, typename M>(T const& a0, T const& a1, T const& a2, M const & t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::is_normal(a0), map([](auto e) -> eve::logical<v_t> { return  std::fpclassify(e) == FP_NORMAL; }, a0));
  TTS_EQUAL(eve::is_normal(a1), map([](auto e) -> eve::logical<v_t> { return  std::fpclassify(e) == FP_NORMAL; }, a1));
  TTS_EQUAL(eve::is_normal(a2), map([](auto e) -> eve::logical<v_t> { return  std::fpclassify(e) == FP_NORMAL; }, a2));
  TTS_EQUAL(eve::is_normal[t](a0), eve::if_else(t, eve::is_normal(a0), eve::false_(eve::as(a0))));
};
