//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/detail/meta.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/valmax.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/if_else.hpp>
#include <eve/module/core/constant/one.hpp>
#include <eve/module/core/constant/false.hpp>
#include <eve/module/core/constant/mone.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/constant/allbits.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/logical.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::if_else", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using sT =  eve::element_type_t<T>;
  using eve::logical;

  // Condition is logical
  TTS_EXPR_IS( eve::if_else(logical<T>(), logical<T>()  , logical<T>()  ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(logical<T>(), logical<T>()  , logical<sT>() ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(logical<T>(), logical<sT>() , logical<T>()  ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(logical<T>(), T()           , T()           ) , T          );
  TTS_EXPR_IS( eve::if_else(logical<T>(), T()           , sT()          ) , T          );
  TTS_EXPR_IS( eve::if_else(logical<T>(), sT()          , T()           ) , T          );

  // Condition is scalar logical
  TTS_EXPR_IS( eve::if_else(logical<sT>(), logical<T>()  , logical<T>() ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(logical<sT>(), logical<T>()  , logical<sT>()) , logical<T> );
  TTS_EXPR_IS( eve::if_else(logical<sT>(), logical<sT>() , logical<T>() ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(logical<sT>(), T()           , T()          ) , T          );
  TTS_EXPR_IS( eve::if_else(logical<sT>(), T()           , sT()         ) , T          );
  TTS_EXPR_IS( eve::if_else(logical<sT>(), sT()          , T()          ) , T          );

  // Condition is bool
  TTS_EXPR_IS( eve::if_else(bool(), logical<T>()  , logical<T>() ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(bool(), logical<T>()  , logical<sT>()) , logical<T> );
  TTS_EXPR_IS( eve::if_else(bool(), logical<sT>() , logical<T>() ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(bool(), T()           , T()          ) , T          );
  TTS_EXPR_IS( eve::if_else(bool(), T()           , sT()         ) , T          );
  TTS_EXPR_IS( eve::if_else(bool(), sT()          , T()          ) , T          );

  // Condition is arithmetic
  TTS_EXPR_IS( eve::if_else(T(), logical<T>()  , logical<T>()  ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(T(), logical<T>()  , logical<sT>() ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(T(), logical<sT>() , logical<T>()  ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(T(), T()           , T()           ) , T          );
  TTS_EXPR_IS( eve::if_else(T(), T()           , sT()          ) , T          );
  TTS_EXPR_IS( eve::if_else(T(), sT()          , T()           ) , T          );

  // Condition is scalar arithmetic
  TTS_EXPR_IS( eve::if_else(sT(), logical<T>()  , logical<T>()  ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(sT(), logical<T>()  , logical<sT>() ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(sT(), logical<sT>() , logical<T>()  ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(sT(), T()           , T()           ) , T          );
  TTS_EXPR_IS( eve::if_else(sT(), T()           , sT()          ) , T          );
  TTS_EXPR_IS( eve::if_else(sT(), sT()          , T()           ) , T          );
};

EVE_TEST( "Check behavior of eve::if_else(logical,logical,logical) and eve::if_else(logical,wide,wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::randoms(-10, +10)
                              , eve::test::logicals(0,3)
                              , eve::test::logicals(0,3)
                              , eve::test::logicals(0,3)
                              )
        )
<typename T, typename M>( T const &a1,  T const & a2
                        , M const & m0, M const & m1, M const & m2)
{
  using eve::if_else;
  using eve::detail::map;
  using eve::one;
  using eve::mone;
  using eve::zero;
  using eve::allbits;
  using eve::nan;
  using eve::as;
  using v_t = eve::element_type_t<T>;
  TTS_EQUAL( if_else(m0, m1, m2), map([](auto e, auto f, auto g) { return e ? f : g; }, m0, m1, m2));
  TTS_EQUAL( if_else(m0, a1, a2), map([](auto e, auto f, auto g) { return e ? f : g; }, m0, a1, a2));
  TTS_EQUAL( if_else(m0, a1, one), map([](auto e, auto f) { return e ? f : v_t(1); }, m0, a1));
  TTS_EQUAL( if_else(m0, a1, zero), map([](auto e, auto f) { return e ? f : v_t(0); }, m0, a1));
  if constexpr(eve::signed_value<T>)
    TTS_EQUAL( if_else(m0, a1, mone), map([](auto e, auto f) { return e ? f : v_t(-1); }, m0, a1));
  else
    TTS_EQUAL( if_else(m0, a1, allbits), map([](auto e, auto f) { return e ? f : allbits(as<v_t>()); }, m0, a1));
  if constexpr(eve::floating_value<T>)
    TTS_IEEE_EQUAL( if_else(m0, a1, allbits), map([](auto e, auto f) { return e ? f : nan(as<v_t>()); }, m0, a1));
  TTS_EQUAL( if_else(true, m1, m2), map([]( auto f) { return f; }, m1));
  TTS_EQUAL( if_else(false, a1, a2), map([]( auto g) { return g; }, a2));

  using d_t = eve::detail::downgrade_t<M>;
  auto dm0 = eve::convert(m0, as<eve::element_type_t<d_t>>());
  TTS_EQUAL( if_else(dm0, m1, m2), map([](auto e, auto f, auto g) { return e ? f : g; }, dm0, m1, m2));
  TTS_EQUAL( if_else(dm0, a1, a2), map([](auto e, auto f, auto g) { return e ? f : g; }, dm0, a1, a2));
  TTS_EQUAL( if_else(dm0, a1, one), map([](auto e, auto f) { return e ? f : v_t(1); }, dm0, a1));
  TTS_EQUAL( if_else(dm0, a1, zero), map([](auto e, auto f) { return e ? f : v_t(0); }, dm0, a1));
  if constexpr(eve::signed_value<T>)
    TTS_EQUAL( if_else(dm0, a1, mone), map([](auto e, auto f) { return e ? f : v_t(-1); }, dm0, a1));
  else
    TTS_EQUAL( if_else(dm0, a1, allbits), map([](auto e, auto f) { return e ? f : allbits(as<v_t>()); }, dm0, a1));
  if constexpr(eve::floating_value<T>)
    TTS_IEEE_EQUAL( if_else(dm0, a1, allbits), map([](auto e, auto f) { return e ? f : nan(as<v_t>()); }, dm0, a1));

  using u_t = eve::detail::upgrade_t<M>;
  auto um0 = eve::convert(m0, as<eve::element_type_t<u_t>>());
  TTS_EQUAL( if_else(um0, m1, m2), map([](auto e, auto f, auto g) { return e ? f : g; }, um0, m1, m2));
  TTS_EQUAL( if_else(um0, a1, a2), map([](auto e, auto f, auto g) { return e ? f : g; }, um0, a1, a2));
  TTS_EQUAL( if_else(um0, a1, one), map([](auto e, auto f) { return e ? f : v_t(1); }, um0, a1));
  TTS_EQUAL( if_else(um0, a1, zero), map([](auto e, auto f) { return e ? f : v_t(0); }, um0, a1));
  if constexpr(eve::signed_value<T>)
    TTS_EQUAL( if_else(um0, a1, mone), map([](auto e, auto f) { return e ? f : v_t(-1); }, um0, a1));
  else
    TTS_EQUAL( if_else(um0, a1, allbits), map([](auto e, auto f) { return e ? f : allbits(as<v_t>()); }, um0, a1));
  if constexpr(eve::floating_value<T>)
    TTS_IEEE_EQUAL( if_else(um0, a1, allbits), map([](auto e, auto f) { return e ? f : nan(as<v_t>()); }, um0, a1));
};

EVE_TEST( "Check behavior of eve::if_else(conditional, a, b)"
        , eve::test::simd::uints_8
        , eve::test::generate ( eve::test::randoms(-10, +10), eve::test::logicals(0,3) )
        )
<typename T, typename L>( T const &a, L const& l )
{
  {
    T actual = eve::if_else[eve::ignore_first(1)](a, T(20));
    T expected = a;
    expected.set(0, 20);
    TTS_EQUAL(actual, expected);
    actual = eve::if_else[eve::ignore_first(1)](a, 20);
    TTS_EQUAL(actual, expected);
  }
  {
    L actual = eve::if_else[eve::ignore_first(1)](l, eve::false_(eve::as<L>()));
    L expected = l;
    expected.set(0, false);
    TTS_EQUAL(actual, expected);
    actual = eve::if_else[eve::ignore_first(1)](l, false);
    TTS_EQUAL(actual, expected);
  }
};
