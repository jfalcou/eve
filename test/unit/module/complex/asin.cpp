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
#include <boost/math/complex/asin.hpp>

template < typename T >
auto cv(std::complex < T > sc)
{
  return eve::complex<T>(sc.real(), sc.imag());
}

EVE_TEST( "Check behavior of asin on scalar"
        , eve::test::scalar::ieee_reals
        , eve::test::generate( eve::test::randoms(-10, 10)
                             , eve::test::randoms(-10, 10))
        )
  <typename T>(T const& a0, T const& a1 )
{
  std::cout << "------------- " << (spy::stdlib == spy::libcpp_)<< std::endl;
  auto ulp = (spy::stdlib == spy::libcpp_) ? 100.0 : 3.5;
  using e_t = typename T::value_type;
  using c_t = std::complex<e_t>;
  for(auto e : a0)
  {
    for(auto f : a1)
    {
      TTS_ULP_EQUAL(eve::asin(eve::complex<e_t>(e, f)),  cv(boost::math::asin(c_t(e, f))), ulp);
    }
  }
};

EVE_TEST( "Check behavior of asin on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-5, 5)
                             , eve::test::randoms(-5, 5))
        )
  <typename T>(T const& a0, T const&  a1)
{
  auto ulp = (spy::stdlib == spy::libcpp_) ? 100.0 : 2.0;
  using e_t = typename T::value_type;
  using ce_t = eve::complex<e_t>;
  using z_t = eve::as_complex_t<T>;
  using c_t = std::complex<e_t>;
  auto std_asin = [](auto x, auto y){return boost::math::asin(c_t(x, y)); };
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
};

EVE_TEST_TYPES( "Check return types of eve::asin", eve::test::scalar::ieee_reals)
  <typename T>(eve::as<T>)
{
  using e_t = eve::element_type_t<T>;
  using c_t = eve::complex<e_t>;
  using s_t = std::complex<e_t>;
  using eve::as;
  auto s_asin = [](auto x){return cv(boost::math::asin(x)); };
  // specific values tests
#ifndef boost_simd_no_invalids
  TTS_ULP_EQUAL(eve::asin(c_t(eve::nan (as<T>()),  eve::zero(as<T>()))), s_asin(s_t(eve::nan (as<T>()),  eve::zero(as<T>())) ),  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::nan  (as<T>()), eve::one(as<T>()))),  s_asin(s_t(eve::nan  (as<T>()), eve::one(as<T>()))  ),  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::nan  (as<T>()), eve::inf(as<T>()))),  s_asin(s_t(eve::nan  (as<T>()), eve::inf(as<T>()))  ),  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::nan  (as<T>()), eve::nan(as<T>()))),  s_asin(s_t(eve::nan  (as<T>()), eve::nan(as<T>()))  ),  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::zero (as<T>()), eve::nan (as<T>()))), s_asin(s_t(eve::zero (as<T>()), eve::nan (as<T>())) ),  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::one  (as<T>()), eve::nan (as<T>()))), s_asin(s_t(eve::one  (as<T>()), eve::nan (as<T>())) ),  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::inf  (as<T>()), eve::nan(as<T>()))),  c_t(eve::nan  (as<T>()), eve::inf(as<T>())),   2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::one  (as<T>()), eve::inf (as<T>()))), s_asin(s_t(eve::one  (as<T>()), eve::inf (as<T>())) ),  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::inf  (as<T>()), eve::one (as<T>()))), s_asin(s_t(eve::inf  (as<T>()), eve::one (as<T>())) ),  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::inf  (as<T>()), eve::inf(as<T>()))),  s_asin(s_t(eve::inf  (as<T>()), eve::inf(as<T>()))  ),  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::nan  (as<T>()), eve::one(as<T>()))), s_asin(s_t(-eve::nan  (as<T>()), eve::one(as<T>())) ),  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::nan  (as<T>()), eve::inf(as<T>()))), s_asin(s_t(-eve::nan  (as<T>()), eve::inf(as<T>())) ),  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::nan  (as<T>()), eve::nan(as<T>()))), s_asin(s_t(-eve::nan  (as<T>()), eve::nan(as<T>())) ),  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::zero (as<T>()), eve::nan (as<T>()))),s_asin(s_t(-eve::zero (as<T>()), eve::nan (as<T>()))), 2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::one  (as<T>()), eve::nan (as<T>()))),s_asin(s_t(-eve::one  (as<T>()), eve::nan (as<T>()))), 2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::inf  (as<T>()), eve::nan(as<T>()))), c_t(eve::nan  (as<T>()), eve::inf(as<T>())),  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::one  (as<T>()), eve::inf (as<T>()))),s_asin(s_t(-eve::one  (as<T>()), eve::inf (as<T>()))), 2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::inf  (as<T>()), eve::one (as<T>()))),s_asin(s_t(-eve::inf  (as<T>()), eve::one (as<T>()))), 2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::inf  (as<T>()), eve::inf(as<T>()))), s_asin(s_t(-eve::inf  (as<T>()), eve::inf(as<T>())) ),  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::nan  (as<T>()), eve::one(as<T>()))),  s_asin(s_t(eve::nan  (as<T>()), eve::one(as<T>()))  ),   2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::nan  (as<T>()), eve::inf(as<T>()))),  s_asin(s_t(eve::nan  (as<T>()), eve::inf(as<T>()))  ),   2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::nan  (as<T>()), eve::nan(as<T>()))),  s_asin(s_t(eve::nan  (as<T>()), eve::nan(as<T>()))  ),   2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::zero (as<T>()), eve::nan (as<T>()))), s_asin(s_t(eve::zero (as<T>()), eve::nan (as<T>())) ),  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::one  (as<T>()), eve::nan (as<T>()))), s_asin(s_t(eve::one  (as<T>()), eve::nan (as<T>())) ),  2.0);


  TTS_ULP_EQUAL(eve::asin(c_t(eve::one  (as<T>()),  eve::inf (as<T>()))), s_asin(s_t(eve::one  (as<T>()),  eve::inf (as<T>()))) ,  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::inf  (as<T>()),  eve::one (as<T>()))), s_asin(s_t(eve::inf  (as<T>()),  eve::one (as<T>()))) ,  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::inf  (as<T>()),  eve::inf(as<T>()))),  s_asin(s_t(eve::inf  (as<T>()),  eve::inf(as<T>())))  ,  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::nan  (as<T>()), eve::one(as<T>()))),  s_asin(s_t(-eve::nan  (as<T>()), eve::one(as<T>())))  ,  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::nan  (as<T>()), eve::inf(as<T>()))),  s_asin(s_t(-eve::nan  (as<T>()), eve::inf(as<T>())))  ,  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::nan  (as<T>()), eve::nan(as<T>()))),  s_asin(s_t(-eve::nan  (as<T>()), eve::nan(as<T>())))  ,  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::one  (as<T>()), eve::inf (as<T>()))), s_asin(s_t(-eve::one  (as<T>()), eve::inf (as<T>()))) ,  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::inf  (as<T>()), eve::one (as<T>()))), s_asin(s_t(-eve::inf  (as<T>()), eve::one (as<T>()))) ,  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::inf (as<T>()),  eve::inf(as<T>()))),  s_asin(s_t(-eve::inf (as<T>()),  eve::inf(as<T>())))  ,  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::one  (as<T>()), eve::nan (as<T>()))), s_asin(s_t(-eve::one  (as<T>()), eve::nan (as<T>()))) ,  2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::zero (as<T>()), eve::nan (as<T>()))), s_asin(s_t(-eve::zero (as<T>()), eve::nan (as<T>()))) ,  2.0);

  TTS_ULP_EQUAL(eve::asin(c_t(eve::inf  (as<T>()), eve::nan(as<T>()))),  c_t(eve::nan(as<T>()), eve::inf   (as<T>())),   2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(-eve::inf (as<T>()), eve::nan(as<T>()))),  c_t(eve::nan(as<T>()), eve::inf   (as<T>())),   2.0);


#endif
  TTS_ULP_EQUAL(eve::asin(c_t(eve::zero(as<T>()),  eve::zero(as<T>()))),   s_asin(s_t(eve::zero(as<T>()),  eve::zero(as<T>())))  ,2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::mzero(as<T>()),  eve::zero(as<T>()))),  s_asin(s_t(eve::mzero(as<T>()),  eve::zero(as<T>()))) ,2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::one  (as<T>()), eve::one (as<T>()))),   s_asin(s_t(eve::one  (as<T>()), eve::one (as<T>())))  ,2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::one  (as<T>()), eve::mone (as<T>()))),  s_asin(s_t(eve::one  (as<T>()), eve::mone (as<T>()))) ,2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::mone  (as<T>()), eve::one (as<T>()))),  s_asin(s_t(eve::mone  (as<T>()), eve::one (as<T>()))) ,2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(eve::mone  (as<T>()), eve::mone (as<T>()))), s_asin(s_t(eve::mone  (as<T>()), eve::mone (as<T>()))),2.0);

  TTS_ULP_EQUAL(eve::asin(c_t(1, 1)),       s_asin(s_t(1, 1)),        2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(1, 10)),      s_asin(s_t(1, 10)),       2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(10, 1)),      s_asin(s_t(10, 1)),       2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(10, 10)),     s_asin(s_t(10, 10)),       2.0);
  TTS_ULP_EQUAL(eve::asin(c_t(0.5, -0.5)),  s_asin(s_t(0.5, -0.5)),    2.0);
};
