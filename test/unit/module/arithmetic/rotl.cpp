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
#include <bit>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of rotl"
            , eve::test::simd::unsigned_integers
            )
<typename T>(eve::as<T>)
{
  using eve::rotl;
  using v_t = eve::element_type_t<T>;
  using u_t = eve::as_integer_t<T, unsigned>;
  using i_t = eve::as_integer_t<T, signed>;
  using su_t = eve::as_integer_t<v_t, unsigned>;
  using si_t = eve::as_integer_t<v_t, signed>;

 TTS_EXPR_IS(rotl(T(), u_t() ) , T);
 TTS_EXPR_IS(rotl(T(), i_t() ) , T);
 TTS_EXPR_IS(rotl(T(), su_t()) , T);
 TTS_EXPR_IS(rotl(T(), si_t()) , T);
 TTS_EXPR_IS(rotl(T(), std::int32_t())  , T);

 TTS_EXPR_IS( rotl(v_t(), u_t())  , T);
 TTS_EXPR_IS( rotl(v_t(), i_t())  , T);
 TTS_EXPR_IS( rotl(v_t(), su_t())  , v_t);
 TTS_EXPR_IS( rotl(v_t(), si_t())  , v_t);
};


auto maxi = []<typename T>(eve::as<T> const & )
{
  using v_t = eve::element_type_t<T>;
  return sizeof(v_t)*8-1;
};

//==================================================================================================
//== rotl  tests
//==================================================================================================
EVE_TEST( "Check behavior of rotl on wide"
        , eve::test::simd::unsigned_integers
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax)
                             , eve::test::randoms(0, maxi))
        )
  <typename T>(T a0, T a1)
{
  using eve::rotl;
  TTS_EQUAL( rotl(a0, 0u), a0);
  TTS_EQUAL( rotl(a0, 1u), map([](auto e){return std::rotl(e, 1u);}, a0));
  using v_t = eve::element_type_t<T>;
  a0 = eve::one(eve::as(a0));
  a1 = eve::detail::linear_ramp(eve::as(a0));
  a1 = a1 % (sizeof(v_t)*8);
  auto ua1 = eve::int_(a1);
  TTS_EQUAL( rotl(a0, a1), map([](auto e, auto f) -> v_t {return std::rotl(e, f);}, a0, a1));
  TTS_EQUAL( rotl(a0, ua1), map([](auto e, auto f) -> v_t {return std::rotl(e, f);}, a0, ua1));
};
