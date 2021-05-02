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
#include <eve/function/is_not_flint.hpp>
#include <eve/function/pedantic/is_not_flint.hpp>
#include <eve/function/trunc.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/logical.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::is_not_flint(simd)"
              , eve::test::simd::all_types
              )
<typename T>(eve::as_<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_not_flint(T())                    , logical<T>   );
  TTS_EXPR_IS( eve::is_not_flint(v_t())                  , logical<v_t> );
  TTS_EXPR_IS( eve::pedantic(eve::is_not_flint)(T())     , logical<T>   );
  TTS_EXPR_IS( eve::pedantic(eve::is_not_flint)(v_t())   , logical<v_t> );
};

//==================================================================================================
// Tests for eve::is_not_flint
//==================================================================================================
auto mfo2 = []<typename T>(eve::as_<T> const & tgt)
{
  return eve::maxflint(tgt);
};

auto mf2 = []<typename T>(eve::as_<T> const & tgt)
{
  return eve::maxflint(tgt)*4;
};

EVE_TEST( "Check behavior of eve::is_not_flint(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::randoms(mfo2, mf2))
        )
<typename T>(T const& a0,  T const a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  auto aa0 =  eve::trunc(a0)/2;
  auto aa1 =  eve::trunc(a1)/2;
  TTS_EQUAL(eve::is_not_flint(aa0), map([](auto e) -> eve::logical<v_t> { return  e != std::trunc(e); }, aa0));
  TTS_EQUAL(eve::pedantic(eve::is_not_flint)(aa1), map([](auto e) -> eve::logical<v_t> { return  (e != std::trunc(e)) || (e >  eve::maxflint(eve::as(e))); }, aa1));
};
