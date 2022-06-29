//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>
#include <eve/module/math.hpp>
#include <eve/module/core.hpp>
#include <complex>

template < typename T >
auto cv(std::complex < T > sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

TTS_CASE_WITH( "Check behavior of log on scalar"
        , tts::bunch<eve::test::scalar::ieee_reals>
        , tts::generate( tts::randoms(-10, 10)
                             , tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_ULP_EQUAL(eve::log(eve::complex<e_t>(e, f)),  cv(std::log(c_t(e, f))), 2);
      TTS_ULP_EQUAL(eve::log(eve::complex<e_t>(e, f)),  cv(std::log(c_t(e, f))), 2.0);
    }
  }
};

TTS_CASE_WITH( "Check behavior of log on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(-10, 10)
                             , tts::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  using z_t = eve::as_complex_t<T>;
  using c_t = std::complex<e_t>;
  auto std_ch = [](auto x, auto y){return cv(std::log(c_t(x, y))); };
  auto init_with_std = [std_ch](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z(std_ch(a0.get(i), a1.get(i)));
      b.set(i, z);
    }
    return b;
  };
  TTS_ULP_EQUAL(eve::log(z_t{a0,a1}), init_with_std(a0, a1), 2);
};

TTS_CASE_TPL( "Check return types of eve::log", tts::bunch<eve::test::scalar::ieee_reals>)
<typename T>(tts::type<T>)
{
  using eve::as;
  using eve::pedantic;
  using e_t = typename T::value_type;
  using c_t = eve::complex<e_t>;

  TTS_ULP_EQUAL((eve::log)(c_t(eve::minf (as<e_t>()), eve::mone(as<e_t>()))), c_t(eve::inf(as<e_t>()), -eve::pi(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::inf(as<e_t>()), 0)), c_t(eve::inf(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::minf(as<e_t>()), 0)), c_t(eve::inf(as<e_t>()), eve::pi(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::nan(as<e_t>()), eve::nan(as<e_t>()))),  c_t(eve::nan(as<e_t>()), eve::nan(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::inf  (as<e_t>()), eve::zero(as<e_t>()))),  c_t(eve::inf(as<e_t>()), eve::zero(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::minf (as<e_t>()), eve::zero(as<e_t>()))),  c_t(eve::inf(as<e_t>()), eve::pi(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::inf  (as<e_t>()), eve::zero(as<e_t>()))),  c_t(eve::inf (as<e_t>()), eve::zero (as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::one  (as<e_t>()), eve::inf (as<e_t>()))), c_t(eve::inf(as<e_t>()), eve::pio_2(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::one  (as<e_t>()), eve::nan (as<e_t>()))), c_t(eve::nan(as<e_t>()), eve::nan(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::inf  (as<e_t>()), eve::one (as<e_t>()))), c_t(eve::inf(as<e_t>()), eve::zero(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::minf (as<e_t>()), eve::one(as<e_t>()))),  c_t(eve::inf(as<e_t>()), eve::pi(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::inf  (as<e_t>()), eve::one (as<e_t>()))), c_t(eve::inf (as<e_t>()), eve::zero (as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::nan  (as<e_t>()), eve::one(as<e_t>()))),  c_t(eve::nan (as<e_t>()), eve::nan(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::nan  (as<e_t>()), eve::mone(as<e_t>()))), c_t(eve::nan (as<e_t>()), eve::nan(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::nan  (as<e_t>()), eve::nan(as<e_t>()))),  c_t(eve::nan (as<e_t>()), eve::nan(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::one  (as<e_t>()), -eve::inf (as<e_t>()))), c_t(eve::inf(as<e_t>()), -eve::pio_2(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::one  (as<e_t>()), -eve::nan (as<e_t>()))), c_t(eve::nan(as<e_t>()), -eve::nan(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::inf  (as<e_t>()), -eve::one (as<e_t>()))), c_t(eve::inf(as<e_t>()), -eve::zero(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::minf (as<e_t>()), -eve::one(as<e_t>()))),  c_t(eve::inf(as<e_t>()), -eve::pi(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::inf  (as<e_t>()), -eve::one (as<e_t>()))), c_t(eve::inf (as<e_t>()), -eve::zero (as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::nan  (as<e_t>()), -eve::one(as<e_t>()))),  c_t(eve::nan (as<e_t>()), -eve::nan(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::nan  (as<e_t>()), -eve::mone(as<e_t>()))), c_t(eve::nan (as<e_t>()), -eve::nan(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::nan  (as<e_t>()), -eve::nan(as<e_t>()))),  c_t(eve::nan (as<e_t>()), -eve::nan(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::nan(as<e_t>()), eve::zero(as<e_t>()))),  c_t(eve::nan(as<e_t>()), eve::nan(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::zero(as<e_t>()), eve::zero(as<e_t>()))), c_t(eve::minf(as<e_t>()), eve::zero(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::minf (as<e_t>()), eve::inf(as<e_t>()))),  c_t(eve::inf (as<e_t>()), eve::nan(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::inf  (as<e_t>()), eve::inf(as<e_t>()))),  c_t(eve::inf (as<e_t>()), eve::nan(as<e_t>())/4), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::minf (as<e_t>()), eve::minf(as<e_t>()))),  c_t(eve::inf (as<e_t>()), eve::nan(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::inf  (as<e_t>()), eve::minf(as<e_t>()))),  c_t(eve::inf (as<e_t>()), eve::nan(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::mzero(as<e_t>()))), c_t(eve::minf(as<e_t>()), eve::zero(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::nan  (as<e_t>()), eve::inf(as<e_t>()))),  c_t(eve::inf (as<e_t>()), eve::nan(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::nan  (as<e_t>()), -eve::inf(as<e_t>()))),  c_t(eve::inf (as<e_t>()), -eve::nan(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::minf (as<e_t>()), eve::nan(as<e_t>()))),  c_t(eve::nan (as<e_t>()), eve::nan(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::mone(as<e_t>()))), c_t(eve::zero(as<e_t>()), eve::pi(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::one(as<e_t>()))), c_t(eve::zero(as<e_t>())), 0.5);
  TTS_ULP_EQUAL((eve::log)(c_t(eve::zero(as<e_t>()), eve::one(as<e_t>()))),c_t(eve::zero(as<e_t>()), eve::pio_2(as<e_t>())), 0.5);

  TTS_ULP_EQUAL(eve::log(c_t(-4, 0)), c_t(eve::log(e_t(4)), eve::pi(as<e_t>())), 0);
  TTS_ULP_EQUAL(eve::log(e_t(-4)), eve::nan(as<e_t>()), 0);
//TTS_ULP_EQUAL(eve::cmplx(eve::log)(T(-4)), c_t(eve::log(T(4)), eve::pi(as<e_t>())), 0);

  //pedantic differences
  TTS_ULP_EQUAL(pedantic(eve::log)(c_t(eve::minf (as<e_t>()), eve::inf(as<e_t>()))),  c_t(eve::inf (as<e_t>()), 3*eve::pio_4(as<e_t>())), 0.5);
  TTS_ULP_EQUAL(pedantic(eve::log)(c_t(eve::inf  (as<e_t>()), eve::inf(as<e_t>()))),  c_t(eve::inf (as<e_t>()), eve::pi(as<e_t>())/4), 0.5);
  TTS_ULP_EQUAL(pedantic(eve::log)(c_t(eve::minf (as<e_t>()), eve::minf(as<e_t>()))),  c_t(eve::inf (as<e_t>()), -3*eve::pio_4(as<e_t>())), 0.5);
  TTS_ULP_EQUAL(pedantic(eve::log)(c_t(eve::inf  (as<e_t>()), eve::minf(as<e_t>()))),  c_t(eve::inf (as<e_t>()), -eve::pi(as<e_t>())/4), 0.5);
  TTS_ULP_EQUAL(pedantic(eve::log)(c_t(eve::mzero(as<e_t>()))), c_t(eve::minf(as<e_t>()), eve::pi(as<e_t>())), 0.5);
};
