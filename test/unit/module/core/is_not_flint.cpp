//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of eve::is_not_flint(simd)"
              , eve::test::simd::all_types
              )
<typename T>(tts::type<T>)
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
auto mf2 = tts::constant([](auto const& tgt) { return eve::maxflint(tgt)*4; });

TTS_CASE_WITH ( "Check behavior of eve::is_not_flint(simd)"
              , eve::test::simd::ieee_reals
              , tts::generate ( tts::randoms(eve::valmin, eve::valmax)
                              , tts::randoms(eve::maxflint, mf2)
                              , tts::logicals(0, 3)
                              )
              )
<typename T, typename M>(T const& a0, T const& a1,  M const & t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  auto aa0 =  eve::trunc(a0)/2;
  auto aa1 =  eve::trunc(a1)/2;
  TTS_EQUAL(eve::is_not_flint(aa0), map([](auto e) -> eve::logical<v_t> { return  e != std::trunc(e); }, aa0));
  TTS_EQUAL(eve::pedantic(eve::is_not_flint)(aa1), map([](auto e) -> eve::logical<v_t> { return  (e != std::trunc(e)) || (e >  eve::maxflint(eve::as(e))); }, aa1));
  TTS_EQUAL(eve::is_not_flint[t](a0), eve::if_else(t, eve::is_not_flint(a0), eve::false_(eve::as(a0))));
};
