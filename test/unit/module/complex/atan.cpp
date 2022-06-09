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
#include <complex>

template < typename T >
auto cv(std::complex < T > sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

TTS_CASE_TPL( "Check return types of eve::tan", tts::bunch<eve::test::scalar::ieee_reals>)
  <typename T>(tts::type<T>)
{
  using e_t = typename T::value_type;
  using c_t = eve::complex<e_t>;
  using eve::as;
  const int N = 16;
  std::array<c_t, N> inputs =
    { c_t(eve::zero(as<e_t>()),eve::zero(as<e_t>())),//0
      c_t(eve::inf(as<e_t>()),eve::zero(as<e_t>())), //1
      c_t(eve::minf(as<e_t>()),eve::zero(as<e_t>())),//2
      c_t(eve::nan(as<e_t>()),eve::zero(as<e_t>())), //3
      c_t(eve::zero(as<e_t>()),eve::inf(as<e_t>())), //4
      c_t(eve::inf(as<e_t>()),eve::inf(as<e_t>())),  //5
      c_t(eve::minf(as<e_t>()),eve::inf(as<e_t>())), //6
      c_t(eve::nan(as<e_t>()),eve::inf(as<e_t>())),  //7
      c_t(eve::zero(as<e_t>()),eve::minf(as<e_t>())),//8--
      c_t(eve::inf(as<e_t>()),eve::minf(as<e_t>())), //9
      c_t(eve::minf(as<e_t>()),eve::minf(as<e_t>())),//10
      c_t(eve::nan(as<e_t>()),eve::minf(as<e_t>())), //11
      c_t(eve::zero(as<e_t>()),eve::nan(as<e_t>())), //12
      c_t(eve::inf(as<e_t>()),eve::nan(as<e_t>())),  //13
      c_t(eve::minf(as<e_t>()),eve::nan(as<e_t>())), //14
      c_t(eve::nan(as<e_t>()),eve::nan(as<e_t>())),  //15
    };

  auto atanine = (eve::atan);
  auto tatanine= [](auto z){return -(eve::i*eve::atanh(eve::i*z));};
  for(int i=0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(atanine(inputs[i]), -atanine(-inputs[i]));
    TTS_IEEE_EQUAL(atanine(inputs[i]), tatanine(inputs[i]));
  }
};
