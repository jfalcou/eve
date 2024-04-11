//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/bessel.hpp>

TTS_CASE_TPL( "Check return types of cyl_bessel_in", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  using w_t = eve::wide<i_t, eve::cardinal_t<T>>;
  TTS_EXPR_IS(eve::cyl_bessel_in(T()  , T()  ), T  );
  TTS_EXPR_IS(eve::cyl_bessel_in(v_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::cyl_bessel_in(i_t(), T()  ), T  );
  TTS_EXPR_IS(eve::cyl_bessel_in(w_t(), T()  ), T  );
  TTS_EXPR_IS(eve::cyl_bessel_in(i_t(), v_t()), v_t);
  TTS_EXPR_IS(eve::cyl_bessel_in(w_t(), v_t()), T  );
};

TTS_CASE_WITH ( "Check behavior of cyl_bessel_in on wide"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(+2.,+6.), tts::randoms(0.0, 15.0))
              )
<typename T>([[maybe_unused]] T const& a0, [[maybe_unused]] T const& a1)
{
  using v_t = eve::element_type_t<T>;
  auto ia0 = eve::convert(a0, eve::as<eve::as_integer_t<v_t>>{});

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_ULP_EQUAL(eve::cyl_bessel_in(a0        , eve::inf(eve::as<v_t>())), eve::inf(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(a0        , eve::nan(eve::as<v_t>())), eve::nan(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(a0        , eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(a0        , eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(ia0       , eve::inf(eve::as<v_t>())), eve::inf(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(ia0       , eve::nan(eve::as<v_t>())), eve::nan(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(ia0       , eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(ia0       , eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(a0.get(0) , eve::inf(eve::as<v_t>())), eve::inf(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(a0.get(0) , eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(a0.get(0) , eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(a0.get(0) , eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(ia0.get(0), eve::inf(eve::as<v_t>())), eve::inf(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(ia0.get(0), eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(ia0.get(0), eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(ia0.get(0), eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(-a0        , eve::inf(eve::as<v_t>())), eve::inf(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(-a0        , eve::nan(eve::as<v_t>())), eve::nan(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(-a0        , eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(-a0        , eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(-ia0       , eve::inf(eve::as<v_t>())), eve::inf(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(-ia0       , eve::nan(eve::as<v_t>())), eve::nan(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(-ia0       , eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(-ia0       , eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(-a0.get(0) , eve::inf(eve::as<v_t>())), eve::inf(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(-a0.get(0) , eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(-a0.get(0) , eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(-a0.get(0) , eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(-ia0.get(0), eve::inf(eve::as<v_t>())), eve::inf(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(-ia0.get(0), eve::nan(eve::as<v_t>())), eve::nan(eve::as<v_t>()), 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(-ia0.get(0), eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>())  , 0);
    TTS_ULP_EQUAL(eve::cyl_bessel_in(-ia0.get(0), eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>())  , 0);
  }

#if defined(__cpp_lib_math_special_functions)
  auto std_cyl_bessel_in = [](auto a, auto b) -> v_t { return std::cyl_bessel_i(a,b); };
  TTS_RELATIVE_EQUAL(eve::cyl_bessel_in( a0,a1) , eve::detail::map(std_cyl_bessel_in, a0, a1), 1.5e-4);
  TTS_RELATIVE_EQUAL(eve::cyl_bessel_in( ia0,a1), eve::detail::map(std_cyl_bessel_in,ia0, a1), 1.5e-4);
#else
  TTS_PASS("No support for std::cyl_bessel_i");
#endif
};

//==================================================================================================
// Tests for masked cyl_bessel_in
//==================================================================================================
TTS_CASE_WITH ( "Check behavior of eve::masked(eve::cyl_bessel_in)(eve::wide)"
              , eve::test::simd::ieee_reals
              , tts::generate(tts::randoms(+2.,+10.), tts::randoms(0.0, 50.0), tts::logicals(0, 3))
              )
<typename T, typename M>(T const& a0, T const& a1,  M const& mask)
{
  TTS_IEEE_EQUAL(eve::cyl_bessel_in[mask](a0,a1), eve::if_else(mask, eve::cyl_bessel_in(a0,a1), a0));
};
