//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/nan.hpp>
#include <eve/function/nb_values.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_odd.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::nb_values(simd)"
              , eve::test::simd::all_types
              )
<typename T>(eve::as_<T>)
{
  using i_t = eve::as_integer_t<T, unsigned>;
  using v_t = eve::element_type_t<T>;
  using vi_t = eve::element_type_t<i_t>;
  TTS_EXPR_IS( eve::nb_values(T(), T()), i_t  );
  TTS_EXPR_IS( eve::nb_values(T(), v_t()), i_t  );
  TTS_EXPR_IS( eve::nb_values(v_t(), T()), i_t  );
  TTS_EXPR_IS( eve::nb_values(v_t(), v_t()), vi_t );
};

//==================================================================================================
// Tests for eve::nb_values
//==================================================================================================
EVE_TEST_TYPES( "Check behavior of eve::nb_values(simd)"
        , eve::test::simd::all_types
              )
  <typename T>(eve::as_<T>)
{
  using r_t = eve::as_integer_t<T, unsigned>;

  if constexpr(eve::floating_value<T>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_EQUAL(eve::nb_values(eve::inf(eve::as<T>())  , eve::inf(eve::as<T>()))  , r_t(0)            );
      TTS_EQUAL(eve::nb_values(eve::minf(eve::as<T>()) , eve::minf(eve::as<T>())) , r_t(0)            );
      TTS_EQUAL(eve::nb_values(eve::nan(eve::as<T>())  , eve::nan(eve::as<T>()))  , eve::valmax(eve::as<r_t>()));
    }

    auto eps = eve::eps(eve::as<T>());

    TTS_EQUAL( eve::nb_values(T(1)  ,  eve::inc(eps)  ) , r_t(1));
    TTS_EQUAL( eve::nb_values(T(1)  , -eve::dec(eps)  ) , r_t(2));
    TTS_EQUAL( eve::nb_values(T(1)  , -eve::dec(eps/2)) , r_t(1));
    TTS_EQUAL( eve::nb_values(T(-0.), T(0)            ) , r_t(1));

    TTS_EXPECT(eve::all(eve::is_odd(eve::nb_values(T(-10), T(10)))));
  }
  else if constexpr(eve::signed_value<T>)
  {
    TTS_EXPECT(eve::all(eve::is_even(eve::nb_values(T(-10), T(10)))));
  }
  else
  {
    TTS_EQUAL(eve::nb_values(T(1), T(10)), r_t(9));
    TTS_EQUAL(eve::nb_values(T(0), T( 0)), r_t(0));
  }
};
