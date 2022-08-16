//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of rem", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::pedantic;
  using eve::rem;

  // regular
  TTS_EXPR_IS(rem(T(), T()), T);
  TTS_EXPR_IS(rem(T(), v_t()), T);
  TTS_EXPR_IS(rem(v_t(), T()), T);
  TTS_EXPR_IS(rem(v_t(), v_t()), v_t);

  // conditionnal
  TTS_EXPR_IS(rem[eve::logical<T>()](T(), T()), T);
  TTS_EXPR_IS(rem[eve::logical<T>()](T(), v_t()), T);
  TTS_EXPR_IS(rem[eve::logical<T>()](v_t(), T()), T);
  TTS_EXPR_IS(rem[eve::logical<v_t>()](T(), T()), T);
  TTS_EXPR_IS(rem[eve::logical<v_t>()](T(), v_t()), T);
  TTS_EXPR_IS(rem[eve::logical<v_t>()](v_t(), T()), T);

  // pedantic
  TTS_EXPR_IS(pedantic(rem)(T(), T()), T);
  TTS_EXPR_IS(pedantic(rem)(T(), v_t()), T);
  TTS_EXPR_IS(pedantic(rem)(v_t(), T()), T);
  TTS_EXPR_IS(pedantic(rem)(v_t(), v_t()), v_t);

  // pedantic conditionnal
  TTS_EXPR_IS(pedantic(rem[eve::logical<T>()])(T(), T()), T);
  TTS_EXPR_IS(pedantic(rem[eve::logical<T>()])(T(), v_t()), T);
  TTS_EXPR_IS(pedantic(rem[eve::logical<T>()])(v_t(), T()), T);
  TTS_EXPR_IS(pedantic(rem[eve::logical<v_t>()])(T(), T()), T);
  TTS_EXPR_IS(pedantic(rem[eve::logical<v_t>()])(T(), v_t()), T);
  TTS_EXPR_IS(pedantic(rem[eve::logical<v_t>()])(v_t(), T()), T);
};

//==================================================================================================
//==  rem simd tests
//==================================================================================================
auto mini = []<typename T>(eve::as<T> const&)
{ return std::is_signed_v<eve::element_type_t<T>> ? -100 : 0; };

TTS_CASE_WITH("Check behavior of rem on wide",
              eve::test::simd::ieee_reals // all_types
              ,
              tts::generate(tts::randoms(tts::constant(mini), 100),
                            tts::randoms(tts::constant(mini), 100)))
<typename T>(T a0, T a1)
{
  using eve::pedantic;
  using eve::rem;
  using eve::detail::map;

  auto thrs = std::same_as<eve::element_type_t<T>, float> ? 5e-4 : 5e-12;
  TTS_RELATIVE_EQUAL(
      pedantic(rem)(a0, a1), map([](auto e, auto f) { return eve::rem(e, f); }, a0, a1), thrs);

  a1 = eve::if_else(eve::is_eqz(a1), eve::one, a1);
  TTS_RELATIVE_EQUAL(rem(a0, a1), map([](auto e, auto f) { return eve::rem(e, f); }, a0, a1), thrs);
};

//==================================================================================================
//== Test for fixed values
//==================================================================================================
TTS_CASE_TPL("Check fixed-cases behavior of eve::rem", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::rem;

  if constexpr( eve::signed_value<T> )
  {
    TTS_EQUAL(rem(T(-1), T(2)), T(-1));
    TTS_EQUAL(rem(v_t(-1), T(2)), T(-1));
    TTS_EQUAL(rem(T(-1), v_t(2)), T(-1));
    TTS_EQUAL(rem(T(-4), T(3)), T(-1));
    TTS_EQUAL(rem(v_t(-4), T(3)), T(-1));
    TTS_EQUAL(rem(T(-4), v_t(3)), T(-1));
  }

  TTS_EQUAL(rem(T(12), T(4)), T(0));
  TTS_EQUAL(rem(T(1), T(2)), T(1));
  TTS_EQUAL(rem(T(4), T(3)), T(1));

  TTS_EQUAL(rem(v_t(12), T(4)), T(0));
  TTS_EQUAL(rem(v_t(1), T(2)), T(1));
  TTS_EQUAL(rem(v_t(4), T(3)), T(1));

  TTS_EQUAL(rem(T(12), v_t(4)), T(0));
  TTS_EQUAL(rem(T(1), v_t(2)), T(1));
  TTS_EQUAL(eve::toward_zero(rem)(T(4), v_t(3)), T(1));
  if constexpr( eve::floating_real_value<T> )
    TTS_IEEE_EQUAL(eve::pedantic(rem)(T(4), T(0)), eve::nan(eve::as<T>()));
  else TTS_EQUAL(eve::pedantic(rem)(T(4), T(0)), T(4));
};

//==================================================================================================
//==  conditional rem tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of rem on signed types",
              eve::test::simd::signed_types,
              tts::generate(tts::randoms(tts::constant(mini), 127),
                            tts::randoms(tts::constant(mini), 127),
                            tts::randoms(tts::constant(mini), 127)))
<typename T>(T a0, T a1, T a2)
{
  using eve::is_nez;
  using eve::pedantic;
  using eve::rem;
  using eve::detail::map;
  if constexpr( eve::supports_fma3 )
  {
    TTS_ULP_EQUAL(pedantic(rem[is_nez(a2)])(a0, a2),
                  map([](auto e, auto f) { return is_nez(f) ? pedantic(rem)(e, f) : e; }, a0, a2),
                  160);

    a2 = eve::if_else(a2 >= 0, eve::one, a2);
    TTS_ULP_EQUAL(rem[is_nez(a2)](a0, a2),
                  map([](auto e, auto f) { return pedantic(rem)(e, f); }, a0, a2),
                  160);

    TTS_ULP_EQUAL(
        rem[a2 > T(64)](a0, a1),
        map([](auto e, auto f, auto g) { return g > 64 ? pedantic(rem)(e, f) : e; }, a0, a1, a2),
        2);
    a1 = eve::if_else(eve::is_eqz(a1), eve::one, a1);
    TTS_ULP_EQUAL(
        rem[a2 > T(64)](a0, a1),
        map([](auto e, auto f, auto g) { return g > 64 ? pedantic(rem)(e, f) : e; }, a0, a1, a2),
        2);
  }
  else
  {
    TTS_RELATIVE_EQUAL((rem[is_nez(a2)])(a0, a2),
                       map([](auto e, auto f) { return is_nez(f) ? rem(e, f) : e; }, a0, a2),
                       0.001);

    a2 = eve::if_else(a2 >= 0, eve::one, a2);
    TTS_RELATIVE_EQUAL(
        rem[is_nez(a2)](a0, a2), map([](auto e, auto f) { return rem(e, f); }, a0, a2), 0.001);

    TTS_RELATIVE_EQUAL(
        rem[a2 > T(64)](a0, a1),
        map([](auto e, auto f, auto g) { return g > 64 ? rem(e, f) : e; }, a0, a1, a2),
        0.001);
    a1 = eve::if_else(eve::is_eqz(a1), eve::one, a1);
    TTS_RELATIVE_EQUAL(
        rem[a2 > T(64)](a0, a1),
        map([](auto e, auto f, auto g) { return g > 64 ? rem(e, f) : e; }, a0, a1, a2),
        0.001);
  }
};


//==================================================================================================
// Tests for masked rem
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::rem)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax),
                            tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         T const& a1,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::rem[mask](a0, a1),
            eve::if_else(mask, eve::rem(a0, a1), a0));
};
