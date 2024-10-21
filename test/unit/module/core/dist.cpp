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
TTS_CASE_TPL("Check return types of dist", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  // regular
  TTS_EXPR_IS(eve::dist(T(), T()), T);
  TTS_EXPR_IS(eve::dist(T(), v_t()), T);
  TTS_EXPR_IS(eve::dist(v_t(), T()), T);
  TTS_EXPR_IS(eve::dist(T(), int()), T);
  TTS_EXPR_IS(eve::dist(int(), T()), T);
  TTS_EXPR_IS(eve::dist(v_t(), v_t()), v_t);

  TTS_EXPR_IS(eve::dist[eve::saturated](T(), T()), T);
  TTS_EXPR_IS(eve::dist[eve::saturated](T(), v_t()), T);
  TTS_EXPR_IS(eve::dist[eve::saturated](v_t(), T()), T);
  TTS_EXPR_IS(eve::dist[eve::saturated](T(), int()), T);
  TTS_EXPR_IS(eve::dist[eve::saturated](int(), T()), T);
  TTS_EXPR_IS(eve::dist[eve::saturated](v_t(), v_t()), v_t);
};

//==================================================================================================
//== dist tests
//==================================================================================================
TTS_CASE_WITH("Check behavior of dist(wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
                            tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T a0, T a1)
{
  using eve::dist;
  TTS_ULP_EQUAL(dist(a0, a1), eve::max(a0, a1) - eve::min(a0, a1), 2);
  TTS_ULP_EQUAL(dist[eve::saturated](a0, a1), [](auto a, auto b){
                  auto d = eve::dist(a, b);
                  if constexpr(eve::unsigned_value<T>) return d;
                  else  return eve::if_else(eve::is_ltz(d),  eve::valmax(eve::as<T>()),  d);
                }(a0, a1), 2);
  if constexpr(eve::floating_value<T>)
  {
    using eve::upper;
    using eve::lower;
    using eve::strict;
    TTS_EXPECT(eve::all(dist[upper](a0, a1) >= dist(a0, a1)));
    TTS_EXPECT(eve::all(dist[lower](a0, a1) <= dist(a0, a1)));

    std::cout << "upper strict" << dist[upper][strict](a0, a1) << std::endl;
    std::cout << "dist" << dist[upper](a0, a1) << std::endl;

    TTS_EXPECT(eve::all(dist[upper][strict](a0, a1) > dist(a0, a1)));
    /*TTS_EXPECT(eve::all(dist[lower][strict](a0, a1) < dist(a0, a1)));
    TTS_EXPECT(eve::all(dist[strict][upper](a0, a1) >= dist[upper](a0, a1)));
    TTS_EXPECT(eve::all(dist[strict][lower](a0, a1) <= dist[lower](a0, a1)));*/
  }
};

auto vmin = tts::constant(
    []<typename T>(eve::as<T> const& tgt)
    {
        return eve::valmin(tgt)/2;
    });
auto vmax = tts::constant(
    []<typename T>(eve::as<T> const& tgt)
    {
        return eve::valmax(tgt)/2;
    });
TTS_CASE_WITH("Check behavior of dist(wide)",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(vmin, vmax),
                            tts::randoms(vmin, vmax)))
<typename T>(T const& a0, T const& a1)
{
  using eve::dist;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL(dist(a0, a1),
                tts::map([](auto e, auto f) -> v_t { return std::max(e, f) - std::min(f, e); }, a0, a1),
                2);
  TTS_ULP_EQUAL(dist[eve::saturated](a0, a1),
                tts::map(
                    [](auto e, auto f) -> v_t
                    {
                      v_t d = eve::max(e, f) - eve::min(f, e);
                      if constexpr( eve::unsigned_value<v_t> ) return d;
                      else return d < 0 ? eve::valmax(eve::as(e)) : d;
                    },
                    a0,
                    a1),
                2);
};
