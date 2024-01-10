//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>

#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of gd", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::gd(T()), T);
  TTS_EXPR_IS(eve::gd(v_t()), v_t);
};

//==================================================================================================
// gd  tests
//==================================================================================================
auto maxi = []<typename T>(eve::as<T> const&)
{
  using v_t = eve::element_type_t<T>;
  v_t ovl   = eve::ieee_constant<0x1.6181480p+6f, 0x1.62e42fefa39efp+9>(eve::as<v_t>{}); // 88.376251220703125f,
                                                                             // 709.782712893384
  return T(ovl);
};
auto mini = []<typename T>(eve::as<T> const& tgt) { return -maxi(tgt); };

TTS_CASE_WITH("Check behavior of gd on wide",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(tts::constant(mini), tts::constant(maxi)),
                            tts::randoms(-1.0, 1.0)))
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  using eve::gd;
  using eve::sinh;

  TTS_ULP_EQUAL(gd(a0), map([](auto e) -> v_t { return std::atan(std::sinh(e)); }, a0), 2);
  TTS_ULP_EQUAL(gd(a1), map([](auto e) -> v_t { return std::atan(std::sinh(e)); }, a1), 2);
};


//==================================================================================================
// Tests for masked gd
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::gd)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, 
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::gd[mask](a0),
            eve::if_else(mask, eve::gd(a0), a0));
};
