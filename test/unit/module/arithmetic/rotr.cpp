//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/function/rotr.hpp>
#include <eve/function/converter.hpp>
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of rotr"
            , eve::test::simd::unsigned_integers
            )
<typename T>(eve::as<T>)
{
  using eve::rotr;
  using v_t = eve::element_type_t<T>;
  using u_t = eve::as_integer_t<T, unsigned>;
  using i_t = eve::as_integer_t<T, signed>;
  using su_t = eve::as_integer_t<v_t, unsigned>;
  using si_t = eve::as_integer_t<v_t, signed>;

 TTS_EXPR_IS(rotr(T(), u_t() ) , T);
 TTS_EXPR_IS(rotr(T(), i_t() ) , T);
 TTS_EXPR_IS(rotr(T(), su_t()) , T);
 TTS_EXPR_IS(rotr(T(), si_t()) , T);
 TTS_EXPR_IS(rotr(T(), std::int32_t())  , T);

 TTS_EXPR_IS( rotr(v_t(), u_t())  , T);
 TTS_EXPR_IS( rotr(v_t(), i_t())  , T);
 TTS_EXPR_IS( rotr(v_t(), su_t())  , v_t);
 TTS_EXPR_IS( rotr(v_t(), si_t())  , v_t);
};


//==================================================================================================
// Specific generator - valmin or valmin+1 if T is signed
//==================================================================================================
auto mini = []<typename T>(eve::as<T> const & )
{
  using v_t = eve::element_type_t<T>;
  return -sizeof(v_t)*8+1;
};

auto maxi = []<typename T>(eve::as<T> const & )
{
  using v_t = eve::element_type_t<T>;
  return sizeof(v_t)*8-1;
};

//==================================================================================================
// rotr  tests
//==================================================================================================
EVE_TEST( "Check behavior of rotr on wide"
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax)
                             , eve::test::randoms(mini, maxi))
        )
  <typename T>(T a0, T a1)
{
  using eve::rotr;
  TTS_EQUAL( rotr(a0, 0u), a0);
  TTS_EQUAL( rotr(a0, 1u), map([](auto e){return std::rotr(e, 1u);}, a0));
  using v_t = eve::element_type_t<T>;
  auto ua1 = eve::int_(a1);
  TTS_EQUAL( rotr(a0, a1), map([](auto e, auto f) -> v_t {return std::rotr(e, f);}, a0, a1));
  TTS_EQUAL( rotr(a0, ua1), map([](auto e, auto f) -> v_t {return std::rotr(e, f);}, a0, ua1));
};
