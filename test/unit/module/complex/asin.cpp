//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
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

template < typename T >
auto sc(eve::complex < T > ec)
{
  return std::complex<T>(eve::real(ec), eve::imag(ec));
}

TTS_CASE_WITH ( "Check behavior of asin on scalar"
              , tts::bunch<eve::test::scalar::ieee_reals>
              , tts::generate( tts::randoms(1, 10)
                              , tts::randoms(1, 10)
                              )
              )
<typename T>(T const& a0, T const& a1 )
{
  auto ulp = (spy::stdlib == spy::libcpp_) ? 100.0 : 3.5;
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_RELATIVE_EQUAL(eve::asin(eve::complex<e_t>(e, f)),  cv(std::asin(c_t(e, f))), ulp);
      TTS_ULP_EQUAL(eve::domain::complex(eve::asin)(e), eve::asin(eve::complex<e_t>(e, e_t(0))), 0.5);
      TTS_ULP_EQUAL(eve::domain::complex(eve::asin)(e), eve::domain::complex(eve::asin)(eve::complex<e_t>(e, e_t(0))), 0.5);
    }
  }
};

TTS_CASE_WITH( "Check behavior of asin on wide"
        , eve::test::simd::ieee_reals
        , tts::generate(tts::randoms(1, 5)
                             , tts::randoms(1, 5))
        )
<typename T>(T const& a0, T const&  a1)
{
  auto ulp = (spy::stdlib == spy::libcpp_) ? 400.0 : 4.0;
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  using z_t = eve::as_complex_t<T>;
  using c_t = std::complex<e_t>;
  auto std_asin = [](auto x, auto y){return std::asin(c_t(x, y)); };
  auto init_with_std = [std_asin](auto a0,  auto a1){
    z_t b;
    for(int i = 0; i !=  eve::cardinal_v<T>; ++i)
    {
      ce_t z = cv(std_asin(a0.get(i), a1.get(i)));
      b.set(i, z);
    }
    return b;
  };
  TTS_ULP_EQUAL(eve::asin(z_t{a0,a1}), init_with_std(a0, a1), ulp);
  TTS_ULP_EQUAL(eve::domain::complex(eve::asin)(a0), eve::asin(z_t(a0, eve::zero(eve::as(a0)))), 0.5);
  TTS_ULP_EQUAL(eve::domain::complex(eve::asin)(a0), eve::domain::complex(eve::asin)(z_t(a0, eve::zero(eve::as(a0)))), 0.5);
};

TTS_CASE_TPL( "Check corner casesof eve::asin", eve::test::scalar::ieee_reals)
<typename T>(tts::type<T>)
{
  using c_t = eve::complex<T>;
  using eve::as;
  const int N = 12;
  auto zer = eve::zero(as<T>());
  auto mzer = eve::mzero(as<T>());
  auto inf = eve::inf(as<T>());
  auto nan = eve::nan(as<T>());
  auto one = eve::one(as<T>());
  std::array<c_t, N> inputs =
    {
      c_t(zer,zer), //0
      c_t(mzer,zer),//1
      c_t(one,inf), //2
      c_t(one,nan), //3
      c_t(inf,one), //4
      c_t(inf,inf), //5
      c_t(inf,nan), //6
      c_t(inf,one), //7
      c_t(nan,zer), //8
      c_t(nan, one),//9
      c_t(nan,inf), //10
      c_t(nan,nan), //11
    };
  using eve::conj;
  using eve::asin;

  auto test_asin = [](auto z){ return cv(std::asin(sc(z))); };
  for(int i=0; i < N; ++i)
  {
    TTS_IEEE_EQUAL(asin(inputs[i]), test_asin(inputs[i]));
    TTS_IEEE_EQUAL(asin(-inputs[i]), -asin(inputs[i]));
    TTS_IEEE_EQUAL(asin(conj(inputs[i])), conj(asin(inputs[i])));
  }
};

TTS_CASE_TPL( "Check return types of eve::asin", tts::bunch<eve::test::scalar::ieee_reals>)
<typename T>(tts::type<T>)
{
  using e_t = typename T::value_type;
  using c_t = eve::complex<e_t>;
  using s_t = std::complex<e_t>;
  using eve::as;
  auto s_asin = [](auto x){return cv(std::asin(x)); };

  TTS_ULP_EQUAL(eve::asin(c_t(eve::zero(as<e_t>()),  eve::zero(as<e_t>()))),   s_asin(s_t(eve::zero(as<e_t>()),  eve::zero(as<e_t>())))  ,2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::mzero(as<e_t>()),  eve::zero(as<e_t>()))),  s_asin(s_t(eve::mzero(as<e_t>()),  eve::zero(as<e_t>()))) ,2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::one  (as<e_t>()), eve::one (as<e_t>()))),   s_asin(s_t(eve::one  (as<e_t>()), eve::one (as<e_t>())))  ,2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::one  (as<e_t>()), eve::mone (as<e_t>()))),  s_asin(s_t(eve::one  (as<e_t>()), eve::mone (as<e_t>()))) ,2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::mone  (as<e_t>()), eve::one (as<e_t>()))),  s_asin(s_t(eve::mone  (as<e_t>()), eve::one (as<e_t>()))) ,2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::mone  (as<e_t>()), eve::mone (as<e_t>()))), s_asin(s_t(eve::mone  (as<e_t>()), eve::mone (as<e_t>()))),2.0);

  TTS_ULP_EQUAL(eve::asin(c_t(1, 1)),       s_asin(s_t(1, 1)),        300.0);
  TTS_ULP_EQUAL(eve::asin(c_t(1, 10)),      s_asin(s_t(1, 10)),       300.0);
  TTS_ULP_EQUAL(eve::asin(c_t(10, 1)),      s_asin(s_t(10, 1)),       300.0);
  TTS_ULP_EQUAL(eve::asin(c_t(10, 10)),     s_asin(s_t(10, 10)),       300.0);
  TTS_ULP_EQUAL(eve::asin(c_t(0.5, -0.5)),  s_asin(s_t(0.5, -0.5)),    300.0);
};
