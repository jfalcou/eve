//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of div"
          , eve::test::simd::all_types
          )
<typename T>(tts::type<T>)
{
 using v_t = eve::element_type_t<T>;

  //downward
  TTS_EXPR_IS( eve::downward(eve::div)(T(), T()  ) , T);
  TTS_EXPR_IS( eve::downward(eve::div)(T(), v_t()) , T);
  TTS_EXPR_IS( eve::downward(eve::div)(v_t(), T()) , T);
  TTS_EXPR_IS( eve::downward(eve::div)(v_t(), v_t()) , v_t);

  TTS_EXPR_IS( eve::upward(eve::div)(T(), T()  ) , T);
  TTS_EXPR_IS( eve::upward(eve::div)(T(), v_t()) , T);
  TTS_EXPR_IS( eve::upward(eve::div)(v_t(), T()) , T);
  TTS_EXPR_IS( eve::upward(eve::div)(v_t(), v_t()) , v_t);

  TTS_EXPR_IS( eve::to_nearest(eve::div)(T(), T()  ) , T);
  TTS_EXPR_IS( eve::to_nearest(eve::div)(T(), v_t()) , T);
  TTS_EXPR_IS( eve::to_nearest(eve::div)(v_t(), T()) , T);
  TTS_EXPR_IS( eve::to_nearest(eve::div)(v_t(), v_t()) , v_t);

  //conditionnal
  TTS_EXPR_IS( eve::div[eve::logical<T>()](T(), T()  ) , T);
  TTS_EXPR_IS( eve::div[eve::logical<T>()](T(), v_t()) , T);
  TTS_EXPR_IS( eve::div[eve::logical<T>()](v_t(), T()) , T);
  TTS_EXPR_IS( eve::div[eve::logical<v_t>()](T(), T()  ) , T);
  TTS_EXPR_IS( eve::div[eve::logical<v_t>()](T(), v_t()) , T);
  TTS_EXPR_IS( eve::div[eve::logical<v_t>()](v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::div[eve::logical<T>()])(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::div[eve::logical<T>()])(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::div[eve::logical<T>()])(v_t(), T()) , T);
  TTS_EXPR_IS( eve::saturated(eve::div[eve::logical<v_t>()])(T(), T()  ) , T);
  TTS_EXPR_IS( eve::saturated(eve::div[eve::logical<v_t>()])(T(), v_t()) , T);
  TTS_EXPR_IS( eve::saturated(eve::div[eve::logical<v_t>()])(v_t(), T()) , T);
};

//==================================================================================================
//==  div simd tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of div on wide"
        , eve::test::simd::integers//all_types
        , tts::generate ( tts::randoms(0, 100)
                              , tts::randoms(1, 11)
                              , tts::randoms(1, 11)
                              )
        )
  <typename T>(T a0, T , T a2)
{
  using eve::div;
  using eve::downward;
  using eve::upward;
  using eve::to_nearest;
  using eve::detail::map;
  a2 = eve::if_else(eve::is_eqz(a2), eve::one, a2);

  TTS_EQUAL( eve::div(a0, a2), map([](auto e, auto f) { return eve::div(e, f); }, a0, a2));
  TTS_EQUAL( downward(div)(a0, a2), map([&](auto e, auto f) { return downward(div)(e, f); }, a0, a2));
  TTS_EQUAL( upward(div)(a0, a2), map([&](auto e, auto f) { return upward(div)(e, f); }, a0, a2));
  TTS_EQUAL( to_nearest(div)(a0, a2), map([&](auto e, auto f) { return to_nearest(div)(e, f); }, a0, a2));
};


//==================================================================================================
//== Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL ( "Check corner-cases behavior of eve::div variants on wide"
              , eve::test::simd::integers
              )
<typename T>(tts::type<T>)
{
  using eve::div;
  using eve::downward;
  using eve::upward;
  using eve::to_nearest;
  using v_t = eve::element_type_t<T>;

  // downward
  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(downward(eve::div)(  T(-1),   T(2)), T(-1));
    TTS_EQUAL(downward(eve::div)(v_t(-1),   T(2)), T(-1));
    TTS_EQUAL(downward(eve::div)(  T(-1), v_t(2)), T(-1));

    TTS_EQUAL(downward(eve::div)(  T(-4),   T(3)), T(-2));
    TTS_EQUAL(downward(eve::div)(v_t(-4),   T(3)), T(-2));
    TTS_EQUAL(downward(eve::div)(  T(-4), v_t(3)), T(-2));
    TTS_EQUAL(downward(eve::div)(  T(-4), v_t(4)), T(-1));

    TTS_EQUAL(downward(eve::div)(  T(4),   T(-3)), T(-2));
    TTS_EQUAL(downward(eve::div)(v_t(4),   T(-3)), T(-2));
    TTS_EQUAL(downward(eve::div)(  T(4), v_t(-3)), T(-2));
    TTS_EQUAL(downward(eve::div)(  T(4), v_t(-4)), T(-1));

    TTS_EQUAL(downward(eve::div)(T(-12),   T(-4)), T(3));
    TTS_EQUAL(downward(eve::div)(T(-1) ,   T(-2)), T(0));
    TTS_EQUAL(downward(eve::div)(T(-4) ,   T(-3)), T(1));
    TTS_EQUAL(downward(eve::div)(T(-4) ,   T(-4)), T(1));
    TTS_EQUAL(downward(eve::div)(T(0) ,    T(-4)), T(0));
    TTS_EQUAL(downward(eve::div)(T(0) ,    T(4)), T(0));
  }

  TTS_EQUAL(downward(eve::div)(T(12), T(4)), T(3));
  TTS_EQUAL(downward(eve::div)(T(1) , T(2)), T(0));
  TTS_EQUAL(downward(eve::div)(T(4) , T(3)), T(1));
  TTS_EQUAL(downward(eve::div)(T(4) , T(4)), T(1));

  TTS_EQUAL(downward(eve::div)(v_t(12), T(4)), T(3));
  TTS_EQUAL(downward(eve::div)(v_t(1) , T(2)), T(0));
  TTS_EQUAL(downward(eve::div)(v_t(4) , T(3)), T(1));

  TTS_EQUAL(downward(eve::div)(T(12), v_t(4)), T(3));
  TTS_EQUAL(downward(eve::div)(T(1) , v_t(2)), T(0));
  TTS_EQUAL(downward(eve::div)(T(4) , v_t(3)), T(1));

  // upward
  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(upward(eve::div)(   T(-1) ,   T(2)), T(0));
    TTS_EQUAL(upward(eve::div)( v_t(-1) ,   T(2)), T(0));
    TTS_EQUAL(upward(eve::div)(   T(-1) , v_t(2)), T(0));

    TTS_EQUAL(upward(eve::div)(  T(-4),   T(3)), T(-1));
    TTS_EQUAL(upward(eve::div)(v_t(-4),   T(3)), T(-1));
    TTS_EQUAL(upward(eve::div)(  T(-4), v_t(3)), T(-1));
    TTS_EQUAL(upward(eve::div)(  T(-4), v_t(4)), T(-1));

    TTS_EQUAL(upward(eve::div)(  T(4),   T(-3)), T(-1));
    TTS_EQUAL(upward(eve::div)(v_t(4),   T(-3)), T(-1));
    TTS_EQUAL(upward(eve::div)(  T(4), v_t(-3)), T(-1));
    TTS_EQUAL(upward(eve::div)(  T(4), v_t(-4)), T(-1));

    TTS_EQUAL(upward(eve::div)(T(-12),   T(-4)), T(3));
    TTS_EQUAL(upward(eve::div)(T(-1) ,   T(-2)), T(1));
    TTS_EQUAL(upward(eve::div)(T(-4) ,   T(-3)), T(2));
    TTS_EQUAL(upward(eve::div)(T(-4) ,   T(-4)), T(1));
    TTS_EQUAL(upward(eve::div)(T(0) ,    T(-4)), T(0));
    TTS_EQUAL(upward(eve::div)(T(0) ,    T(4)), T(0));
    TTS_EQUAL(upward(eve::div)(T(1) ,    T(2)), T(1));
  }

  TTS_EQUAL(upward(eve::div)(T(12), T(4)), T(3));
  TTS_EQUAL(upward(eve::div)(T(1) , T(2)), T(1));
  TTS_EQUAL(upward(eve::div)(T(4) , T(3)), T(2));

  TTS_EQUAL(upward(eve::div)(v_t(12), T(4)), T(3));
  TTS_EQUAL(upward(eve::div)(v_t(1) , T(2)), T(1));
  TTS_EQUAL(upward(eve::div)(v_t(4) , T(3)), T(2));

  TTS_EQUAL(upward(eve::div)(T(12), v_t(4)), T(3));
  TTS_EQUAL(upward(eve::div)(T(1) , v_t(2)), T(1));
  TTS_EQUAL(upward(eve::div)(T(4) , v_t(3)), T(2));

  // nearest
  if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::to_nearest(eve::div)(   T(-1) ,   T(2)), T(0));
    TTS_EQUAL(eve::to_nearest(eve::div)( v_t(-1) ,   T(2)), T(0));
    TTS_EQUAL(eve::to_nearest(eve::div)(   T(-1) , v_t(2)), T(0));
    TTS_EQUAL(eve::to_nearest(eve::div)(   T(1) ,   T(-2)), T(0));
    TTS_EQUAL(eve::to_nearest(eve::div)( v_t(1) ,   T(-2)), T(0));
    TTS_EQUAL(eve::to_nearest(eve::div)( v_t(1) , v_t(-2)), v_t(0));
    TTS_EQUAL(eve::to_nearest(eve::div)(  T(-2) ,   T(-2)), T(1));


    TTS_EQUAL(eve::to_nearest(eve::div)(   T(-3) ,   T(2)), T(-2));
    TTS_EQUAL(eve::to_nearest(eve::div)( v_t(-3) ,   T(2)), T(-2));
    TTS_EQUAL(eve::to_nearest(eve::div)(   T(-3) , v_t(2)), T(-2));
    TTS_EQUAL(eve::to_nearest(eve::div)(   T(3) ,   T(-2)), T(-2));
    TTS_EQUAL(eve::to_nearest(eve::div)( v_t(3) ,   T(-2)), T(-2));
    TTS_EQUAL(eve::to_nearest(eve::div)( v_t(3) , v_t(-2)), v_t(-2));
  }

  TTS_EQUAL(eve::to_nearest(eve::div)(T(12), T(4)), T(3));
  TTS_EQUAL(eve::to_nearest(eve::div)(T(2) , T(2)), T(1));
  TTS_EQUAL(eve::to_nearest(eve::div)(T(1) , T(2)), T(0));
  TTS_EQUAL(eve::to_nearest(eve::div)(T(3) , T(2)), T(2));
  TTS_EQUAL(eve::to_nearest(eve::div)(T(5) , T(2)), T(2));
  TTS_EQUAL(eve::to_nearest(eve::div)(T(4) , T(3)), T(1));

  TTS_EQUAL(eve::to_nearest(eve::div)(v_t(12), T(4)), T(3));
  TTS_EQUAL(eve::to_nearest(eve::div)(v_t(1) , T(2)), T(0));
  TTS_EQUAL(eve::to_nearest(eve::div)(v_t(3) , T(2)), T(2));
  TTS_EQUAL(eve::to_nearest(eve::div)(v_t(5) , T(2)), T(2));
  TTS_EQUAL(eve::to_nearest(eve::div)(v_t(4) , T(3)), T(1));

  TTS_EQUAL(eve::to_nearest(eve::div)(T(12), v_t(4)), T(3));
  TTS_EQUAL(eve::to_nearest(eve::div)(T(1) , v_t(2)), T(0));
  TTS_EQUAL(eve::to_nearest(eve::div)(T(3) , v_t(2)), T(2));
  TTS_EQUAL(eve::to_nearest(eve::div)(T(5) , v_t(2)), T(2));
  TTS_EQUAL(eve::to_nearest(eve::div)(T(4) , v_t(3)), T(1));
};


//==================================================================================================
//==  conditional div tests on simd
//==================================================================================================
auto mini = tts::constant ( []<typename T>(eve::as<T> const &)
                            {
                              return std::is_signed_v<eve::element_type_t<T>> ? -128 : 0;
                            }
                          );

TTS_CASE_WITH ( "Check behavior of div on signed types"
              , eve::test::simd::signed_types
              , tts::generate ( tts::randoms(mini, 127)
                              , tts::randoms(mini, 127)
                              , tts::randoms(mini, 127)
                              )
              )
<typename T>( T a0, T a1, T a2)
{
  using eve::div;
  using eve::downward;
  using eve::upward;
  using eve::to_nearest;
  using eve::is_nez;
  using eve::detail::map;
  TTS_EQUAL( downward(div[is_nez(a2)])(a0, a2), map([](auto e, auto f) { return  is_nez(f) ? downward(div)(e, f): e; }, a0, a2));
  TTS_EQUAL( upward(div[is_nez(a2)])(a0, a2), map([](auto e, auto f) { return  is_nez(f) ? upward(div)(e, f): e; }, a0, a2));
  TTS_EQUAL( to_nearest(div[is_nez(a2)])(a0, a2), map([](auto e, auto f) { return  is_nez(f) ? to_nearest(div)(e, f): e; }, a0, a2));

  a1 =  eve::if_else(eve::is_eqz(a1), eve::one, a1);
  TTS_EQUAL( downward(div[a2 > T(64)])(a0, a1), map([](auto e, auto f, auto g) { return  g > 64 ? downward(div)(e, f): e; }, a0, a1, a2));
  TTS_EQUAL( upward(div[a2 > T(64)])(a0, a1), map([](auto e, auto f, auto g) { return  g > 64 ? upward(div)(e, f): e; }, a0, a1, a2));
  TTS_EQUAL( to_nearest(div[a2 > T(64)])(a0, a1), map([](auto e, auto f, auto g) { return  g > 64 ? to_nearest(div)(e, f): e; }, a0, a1, a2));
};
