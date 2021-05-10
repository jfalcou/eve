//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/function/hypot.hpp>
#include <eve/function/diff/hypot.hpp>
#include <numeric>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of hypot"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::hypot;
  using eve::pedantic;
  using eve::diff;
  //regular
  TTS_EXPR_IS( hypot(T(), T()  ) , T);
  TTS_EXPR_IS( hypot(T(), v_t()) , T);
  TTS_EXPR_IS( hypot(v_t(), T()) , T);
  TTS_EXPR_IS( hypot(T(),int()) , T);
  TTS_EXPR_IS( hypot(int(), T()) , T);
  TTS_EXPR_IS( hypot(v_t(), v_t()) , v_t);

  //multi
  TTS_EXPR_IS( hypot(T(), T(), T()  )  , T);
  TTS_EXPR_IS( hypot(T(), v_t(), T())  , T);
  TTS_EXPR_IS( hypot(v_t(), T(), T())  , T);
  TTS_EXPR_IS( hypot(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( hypot(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( hypot(v_t(), T(), v_t()) , T);

  TTS_EXPR_IS( hypot(T(), int(), T())  , T);
  TTS_EXPR_IS( hypot(int(), T(), T())  , T);
  TTS_EXPR_IS( hypot(T(), T(), int() ) , T);
  TTS_EXPR_IS( hypot(int(), v_t(), T()) , T);
  TTS_EXPR_IS( hypot(int(), T(), v_t()) , T);
  TTS_EXPR_IS( hypot(v_t(), int(), T()) , T);
  TTS_EXPR_IS( hypot(v_t(), T(), int()) , T);
  TTS_EXPR_IS( hypot(v_t(), v_t(), v_t()) , v_t);

  //regular
  TTS_EXPR_IS( pedantic(hypot)(T(), T()  ) , T);
  TTS_EXPR_IS( pedantic(hypot)(T(), v_t()) , T);
  TTS_EXPR_IS( pedantic(hypot)(v_t(), T()) , T);
  TTS_EXPR_IS( pedantic(hypot)(T(),int()) , T);
  TTS_EXPR_IS( pedantic(hypot)(int(), T()) , T);
  TTS_EXPR_IS( pedantic(hypot)(v_t(), v_t()) , v_t);

  //multi
  TTS_EXPR_IS( pedantic(hypot)(T(), T(), T()  )  , T);
  TTS_EXPR_IS( pedantic(hypot)(T(), v_t(), T())  , T);
  TTS_EXPR_IS( pedantic(hypot)(v_t(), T(), T())  , T);
  TTS_EXPR_IS( pedantic(hypot)(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( pedantic(hypot)(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( pedantic(hypot)(v_t(), T(), v_t()) , T);

  TTS_EXPR_IS( pedantic(hypot)(T(), int(), T())  , T);
  TTS_EXPR_IS( pedantic(hypot)(int(), T(), T())  , T);
  TTS_EXPR_IS( pedantic(hypot)(T(), T(), int() ) , T);
  TTS_EXPR_IS( pedantic(hypot)(int(), v_t(), T()) , T);
  TTS_EXPR_IS( pedantic(hypot)(int(), T(), v_t()) , T);
  TTS_EXPR_IS( pedantic(hypot)(v_t(), int(), T()) , T);
  TTS_EXPR_IS( pedantic(hypot)(v_t(), T(), int()) , T);
  TTS_EXPR_IS( pedantic(hypot)(v_t(), v_t(), v_t()) , v_t);

  //regular
  TTS_EXPR_IS( diff(hypot)(T(), T()  ) , T);
  TTS_EXPR_IS( diff(hypot)(T(), v_t()) , T);
  TTS_EXPR_IS( diff(hypot)(v_t(), T()) , T);
  TTS_EXPR_IS( diff(hypot)(T(),int()) , T);
  TTS_EXPR_IS( diff(hypot)(int(), T()) , T);
  TTS_EXPR_IS( diff(hypot)(v_t(), v_t()) , v_t);

  //multi
  TTS_EXPR_IS( diff(hypot)(T(), T(), T()  )  , T);
  TTS_EXPR_IS( diff(hypot)(T(), v_t(), T())  , T);
  TTS_EXPR_IS( diff(hypot)(v_t(), T(), T())  , T);
  TTS_EXPR_IS( diff(hypot)(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( diff(hypot)(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( diff(hypot)(v_t(), T(), v_t()) , T);

  TTS_EXPR_IS( diff(hypot)(T(), int(), T())  , T);
  TTS_EXPR_IS( diff(hypot)(int(), T(), T())  , T);
  TTS_EXPR_IS( diff(hypot)(T(), T(), int() ) , T);
  TTS_EXPR_IS( diff(hypot)(int(), v_t(), T()) , T);
  TTS_EXPR_IS( diff(hypot)(int(), T(), v_t()) , T);
  TTS_EXPR_IS( diff(hypot)(v_t(), int(), T()) , T);
  TTS_EXPR_IS( diff(hypot)(v_t(), T(), int()) , T);
  TTS_EXPR_IS( diff(hypot)(v_t(), v_t(), v_t()) , v_t);

};

//==================================================================================================
//== hypot tests
//==================================================================================================
EVE_TEST( "Check behavior of hypot(wide)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-100.0, 100.0)
                              , eve::test::randoms(-100.0, 100.0)
                              , eve::test::randoms(-100.0, 100.0)
                              )
        )
  <typename T>(T const& a0, T const& a1, T const& a2 )
{
  using eve::hypot;
  using eve::pedantic;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL( hypot(a0, a1), map([](auto e, auto f) -> v_t { return std::hypot(e, f); }, a0, a1), 2);
  if constexpr(eve::floating_value<T>)
  {
    TTS_ULP_EQUAL( hypot(a0, a1, a2), map([](auto e, auto f,  auto g) { return std::hypot(e, f, g); }, a0, a1, a2), 2);
    TTS_ULP_EQUAL( pedantic(hypot)(a0, a1, a2), map([](auto e, auto f,  auto g) { return std::hypot(e, f, g); }, a0, a1, a2), 2);
  }
};

//==================================================================================================
//== diff(hypot) tests
//==================================================================================================
EVE_TEST( "Check behavior of diff(hypot)(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate ( eve::test::randoms(-100, 100)
                              , eve::test::randoms(-100, 100)
                              , eve::test::randoms(-100, 100)
                              )
            )
<typename T>( T const& a0, T const& a1, T const& a2 )
{
  using eve::hypot;
  using eve::as;
  using v_t =  eve::element_type_t<T>;
  TTS_ULP_EQUAL( eve::diff_1st(hypot)(a0, a1), map([](auto e , auto f) -> v_t { return e/std::hypot(e, f); }, a0, a1), 2);
  TTS_ULP_EQUAL( eve::diff_2nd(hypot)(a0, a1), map([](auto e , auto f) -> v_t { return f/std::hypot(e, f); }, a0, a1), 2);
  TTS_ULP_EQUAL( eve::diff_1st(hypot)(a0, a1, a2), map([](auto e, auto f, auto g) -> v_t { return e/std::hypot(e, f, g); }, a0, a1, a2), 2);
  TTS_ULP_EQUAL( eve::diff_2nd(hypot)(a0, a1, a2), map([](auto e, auto f, auto g) -> v_t { return f/std::hypot(e, f, g); }, a0, a1, a2), 2);
  TTS_ULP_EQUAL( eve::diff_3rd(hypot)(a0, a1, a2), map([](auto e, auto f, auto g) -> v_t { return g/std::hypot(e, f, g); }, a0, a1, a2), 2);
};

//==================================================================================================
//== Test for corner-cases values
//==================================================================================================
EVE_TEST( "Check corner-cases behavior of eve::hypot variants on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-100.0, 100.0),
                              eve::test::limits())
        )
<typename M, typename T>(T const& a0, M const& cases)
{
  using type = typename M::type;

  TTS_IEEE_EQUAL( eve::hypot(cases.nan, a0   ) , cases.nan   );
  TTS_EQUAL     ( eve::hypot(cases.minf, a0  ) , cases.inf   );
  TTS_EQUAL     ( eve::hypot(cases.mzero, cases.mzero ) , type(0)     );
  TTS_EQUAL     ( eve::hypot(cases.valmax/2, cases.valmax/2) , cases.inf);
  TTS_EQUAL     ( eve::hypot(cases.valmin/2, cases.valmin/2) , cases.inf);
  TTS_EQUAL     ( eve::pedantic(eve::hypot)(cases.mzero, cases.mzero ) , type(0)     );

  TTS_IEEE_EQUAL( eve::pedantic(eve::hypot)(cases.nan, a0    ) , cases.nan   );
  TTS_EQUAL     ( eve::pedantic(eve::hypot)(cases.minf, a0   ) , cases.inf   );
  TTS_EQUAL     ( eve::pedantic(eve::hypot)(cases.nan, cases.minf  ) , cases.inf   );
  TTS_EQUAL     ( eve::pedantic(eve::hypot)(cases.inf, cases.nan   ) , cases.inf   );

  TTS_EQUAL    ( eve::pedantic(eve::hypot)(cases.mzero, cases.mzero ) , type(0)     );
  TTS_ULP_EQUAL( eve::pedantic(eve::hypot)(cases.valmin/2, cases.valmin/2) , cases.valmax/eve::sqrt_2(eve::as<T>()), 2);
  TTS_ULP_EQUAL( eve::pedantic(eve::hypot)(cases.valmax/2, cases.valmax/2) , cases.valmax/eve::sqrt_2(eve::as<T>()), 2);;
};
