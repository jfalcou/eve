//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"
#include "measures.hpp"
#include <eve/module/complex.hpp>
#include <complex>

template < typename T >
auto cv(std::complex < T > sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

TTS_CASE_WITH( "Check behavior of acosh on scalar"
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
      TTS_RELATIVE_EQUAL(eve::acosh(eve::complex<e_t>(e, f)),  cv(std::acosh(c_t(e, f))), 0.001);
    }
  }
};

TTS_CASE_WITH( "Check behavior of acosh on wide"
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
  auto std_ach = [](auto x, auto y){return std::acosh(c_t(x, y)); };
  auto init_with_std = [std_ach](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z = cv(std_ach(a0.get(i), a1.get(i)));
      b.set(i, z);
    }
    return b;
  };
  TTS_RELATIVE_EQUAL(eve::acosh(z_t{a0,a1}), init_with_std(a0, a1), 0.001);
};


TTS_CASE_TPL( "Check return types of eve::abs", tts::bunch<eve::test::scalar::ieee_reals>)
  <typename T>(tts::type<T>)
{
  using e_t = typename T::value_type;
  using c_t = eve::complex<e_t>;
  using eve::as;
  const int N = 22;
  std::array<c_t, N> inputs =
    { c_t(eve::zero(as<e_t>()),eve::zero(as<e_t>())),//0*
      c_t(eve::inf(as<e_t>()),eve::zero(as<e_t>())), //1*
      c_t(eve::minf(as<e_t>()),eve::zero(as<e_t>())),//2*
      c_t(eve::nan(as<e_t>()),eve::zero(as<e_t>())), //3*
      c_t(eve::zero(as<e_t>()),eve::inf(as<e_t>())), //4*
      c_t(eve::inf(as<e_t>()),eve::inf(as<e_t>())),  //5*
      c_t(eve::minf(as<e_t>()),eve::inf(as<e_t>())), //6*
      c_t(eve::nan(as<e_t>()),eve::inf(as<e_t>())),  //7*
      c_t(eve::zero(as<e_t>()),eve::minf(as<e_t>())),//8*
      c_t(eve::inf(as<e_t>()),eve::minf(as<e_t>())), //9*
      c_t(eve::minf(as<e_t>()),eve::minf(as<e_t>())),//10*
      c_t(eve::nan(as<e_t>()),eve::minf(as<e_t>())), //11*
      c_t(eve::zero(as<e_t>()),eve::nan(as<e_t>())), //12*
      c_t(eve::inf(as<e_t>()),eve::nan(as<e_t>())),  //13*
      c_t(eve::minf(as<e_t>()),eve::nan(as<e_t>())), //14*
      c_t(eve::nan(as<e_t>()),eve::nan(as<e_t>())),  //15*
      c_t(eve::mzero(as<e_t>()),eve::zero(as<e_t>())),//16*
      c_t(eve::one(as<e_t>()),eve::inf(as<e_t>())),   //17*
      c_t(eve::one(as<e_t>()),eve::nan(as<e_t>())),   //18*
      c_t(eve::minf(as<e_t>()),eve::one(as<e_t>())),  //19*
      c_t(eve::inf(as<e_t>()),eve::one(as<e_t>())),   //20*
      c_t(eve::nan(as<e_t>()),eve::one(as<e_t>())),   //21*
    };
  std::array<c_t, N> expected =
    { c_t(eve::zero(as<e_t>()),eve::pio_2(as<e_t>())), //0*
      c_t(eve::inf(as<e_t>()),eve::zero(as<e_t>())),   //1*
      c_t(eve::inf(as<e_t>()),eve::pi(as<e_t>())),     //2*
      c_t(eve::nan(as<e_t>()),eve::nan(as<e_t>())),    //3*
      c_t(eve::inf(as<e_t>()),eve::pio_2(as<e_t>())),  //4*
      c_t(eve::inf(as<e_t>()),eve::pio_4(as<e_t>())),  //5*
      c_t(eve::inf(as<e_t>()),3*eve::pio_4(as<e_t>())),//6*
      c_t(eve::inf(as<e_t>()),eve::nan(as<e_t>())),    //7*
      c_t(eve::inf(as<e_t>()),-eve::pio_2(as<e_t>())), //8*
      c_t(eve::inf(as<e_t>()),-eve::pio_4(as<e_t>())), //9*
      c_t(eve::inf(as<e_t>()),-3*eve::pio_4(as<e_t>())),//10*
      c_t(eve::inf(as<e_t>()),eve::nan(as<e_t>())),    //11*
      c_t(eve::nan(as<e_t>()),eve::nan(as<e_t>())),    //12
      c_t(eve::inf(as<e_t>()),eve::nan(as<e_t>())),    //13*
      c_t(eve::inf(as<e_t>()),eve::nan(as<e_t>())),    //14*
      c_t(eve::nan(as<e_t>()),eve::nan(as<e_t>())),    //15*
      c_t(eve::zero(as<e_t>()),eve::pio_2(as<e_t>())), //16*
      c_t(eve::inf(as<e_t>()),eve::pio_2(as<e_t>())),  //17*
      c_t(eve::nan(as<e_t>()),eve::nan(as<e_t>())),    //18*
      c_t(eve::inf(as<e_t>()),eve::pi(as<e_t>())),     //19*
      c_t(eve::inf(as<e_t>()),eve::zero(as<e_t>())),   //20*
      c_t(eve::nan(as<e_t>()),eve::nan(as<e_t>())),    //21
    };

  for(int i=0; i < N; ++i)
  {
    TTS_ULP_EQUAL(eve::acosh(inputs[i]), expected[i], 0.5);
    TTS_ULP_EQUAL(eve::acosh(eve::conj(inputs[i])), eve::conj(expected[i]), 0.5);
  }
};
