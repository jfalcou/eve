//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/polynomial.hpp>
#include <cmath>
#include <array>
#include <vector>
#include <boost/math/special_functions/chebyshev.hpp>


//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of tchebeval on wide"
        , eve::test::simd::ieee_reals

        )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using i_t = eve::as_integer_t<v_t>;
  TTS_EXPR_IS( eve::tchebeval(T(), T())  , T);
  TTS_EXPR_IS( eve::tchebeval(T(), T(), T())  , T);
  TTS_EXPR_IS( eve::tchebeval(T(), T(), T())  , T);
  TTS_EXPR_IS( eve::tchebeval(T(), v_t(), v_t())  , T);
  TTS_EXPR_IS( eve::tchebeval(T(), v_t(), int())  , T);
  TTS_EXPR_IS( eve::tchebeval(T(), v_t(), i_t())  , T);
  TTS_EXPR_IS( eve::tchebeval(v_t(), v_t(), v_t()), v_t);

};

//==================================================================================================
//== tchebeval tests
//==================================================================================================
EVE_TEST( "Check behavior of tchebeval on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::ramp(0.0))
        )
<typename T>(T const& a0)
{
  using eve::tchebeval;
  using eve::fma;
  using eve::pedantic;
  using eve::numeric;
  using eve::one;
  using v_t = eve::element_type_t<T>;
  //============================================================================
  //== variadic
  //============================================================================
  std::vector<v_t> c1{1};
  std::vector<v_t> c2{1, 2};
  std::vector<v_t> c3{1, 2, 3};
  auto bcl1 = [c1](auto x)->v_t{return boost::math::chebyshev_clenshaw_recurrence(c1.data(), c1.size(), x);};
  auto bcl2 = [c2](auto x)->v_t{return boost::math::chebyshev_clenshaw_recurrence(c2.data(), c2.size(), x);};
  auto bcl3 = [c3](auto x)->v_t{return boost::math::detail::unchecked_chebyshev_clenshaw_recurrence(c3.data(), c3.size(), v_t(-1), v_t(1), v_t(x));};

  TTS_EQUAL(tchebeval(a0), T(0));
  TTS_EQUAL(tchebeval(a0, 1.0), T(0.5));
  TTS_EQUAL(tchebeval(a0, 1.0),    map(bcl1, a0));
  TTS_EQUAL(tchebeval(a0, 1.0, 2.0), map(bcl2, a0));
  TTS_EQUAL(tchebeval(a0, 1.0, 2.0, 3.0), map(bcl3, a0));
  TTS_ULP_EQUAL(tchebeval(0.0, 1.0, 2.0, 3.0), bcl3(0.0), 0.5);

  TTS_EQUAL((tchebeval)(a0), T(0));
  TTS_EQUAL((tchebeval)(a0, c1), T(0.5));
  TTS_EQUAL((tchebeval)(a0, c2),  map(bcl2, a0));
  TTS_EQUAL((tchebeval)(a0, c3),  map(bcl3, a0));
  TTS_ULP_EQUAL((tchebeval)(v_t(0.24), c3),  bcl3(v_t(0.24)), 2.0);
  TTS_ULP_EQUAL((tchebeval)(v_t(0.24), v_t(-1), v_t(1), c3),  bcl3(v_t(0.24)), 0.5);
  TTS_ULP_EQUAL((tchebeval)(v_t(-0.24), v_t(-1), v_t(1), c3),  bcl3(v_t(-0.24)), 0.5);
  TTS_ULP_EQUAL((tchebeval)(v_t(0.70), v_t(-1), v_t(1), c3),  bcl3(v_t(0.70)), 0.5);
  TTS_ULP_EQUAL((tchebeval)(v_t(-0.70), v_t(-1), v_t(1), c3),  bcl3(v_t(-0.70)), 2.0);


};
