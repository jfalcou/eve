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
#include <eve/constant/eps.hpp>
#include <eve/function/prev.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/saturated/prev.hpp>
#include <eve/function/pedantic/prev.hpp>
#include <eve/logical.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::prev", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
 using v_t   = eve::element_type_t<T>;
  using i_t   = eve::as_integer_t<  T, signed>;
  using u_t   = eve::as_integer_t<  T, unsigned>;
  using si_t  = eve::as_integer_t<v_t, signed>;
  using su_t  = eve::as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS(eve::prev(T())        , T);
  TTS_EXPR_IS(eve::prev(T(), i_t()) , T);
  TTS_EXPR_IS(eve::prev(T(), u_t()) , T);
  TTS_EXPR_IS(eve::prev(T(), si_t()), T);
  TTS_EXPR_IS(eve::prev(T(), su_t()), T);
};

//==================================================================================================
// Tests for eve::prev
//==================================================================================================
EVE_TEST( "Check behavior of eve::prev(eve::wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::randoms(-10, +10)
                              , eve::test::logicals(0,3)
                              )
        )
  <typename T, typename M>(T const& a0, M const& t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  if constexpr(eve::floating_real_value < v_t>)
  {
    auto n = [](auto e) -> v_t { return std::nextafter(e, eve::valmin(eve::as(e))); };
    TTS_EQUAL(eve::prev(a0)      , map(n, a0) );
    auto nn = [n](auto e) -> v_t { return n(n(e)); };
    TTS_EQUAL(eve::prev(a0, 2)   , map(nn, a0));
  }
  else
  {
    TTS_EQUAL(eve::prev(a0)      , eve::dec(a0));
    TTS_EQUAL(eve::prev(a0, 2)   , eve::dec(eve::dec(a0)));
  }
  TTS_EQUAL(eve::prev[t](a0)     , eve::if_else(t, eve::prev(a0), a0));
  TTS_EQUAL(eve::prev[t](a0, 2)  , eve::if_else(t, eve::prev(a0, 2), a0));
};


//==================================================================================================
// Test for corner-cases values
//==================================================================================================
EVE_TEST( "Check corner-cases behavior of eve::prev variants on wide"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::limits())
        )
<typename T>(T const& cases)
{
  using type = typename T::type;
  using eve::prev;
  using eve::pedantic;
  using eve::saturated;
  if constexpr(eve::floating_real_value<type>)
  {
    TTS_IEEE_EQUAL(prev(cases.inf   ) , cases.valmax);
    TTS_IEEE_EQUAL(prev(cases.minf    ) , cases.nan   );
    TTS_EQUAL     (prev(cases.mzero  ) , -cases.mindenormal);
    TTS_EQUAL     (prev(cases.zero   ) , -cases.mindenormal);
    TTS_EQUAL     (prev(cases.mindenormal ) , cases.zero);
    TTS_EQUAL     (prev(cases.valmin ) , cases.minf);
    TTS_EQUAL     (prev(type(1))      , type(1)-eve::eps(eve::as<type>())/2 );
    TTS_EQUAL     (prev(type(-1))       , type(-1)-eve::eps(eve::as<type>())   );

    TTS_IEEE_EQUAL(pedantic(prev)(cases.nan    ) , cases.nan   );
    TTS_IEEE_EQUAL(pedantic(prev)(cases.inf    ) , cases.valmax);
    TTS_IEEE_EQUAL(pedantic(prev)(cases.minf   ) , cases.nan   );
    TTS_EQUAL     (pedantic(prev)(cases.zero   ) , cases.mzero);
    TTS_EQUAL     (pedantic(prev)(cases.mzero  ) , -cases.mindenormal);
    TTS_EQUAL     (pedantic(prev)(cases.mindenormal ) , cases.zero);
    TTS_EQUAL     (pedantic(prev)(cases.valmin ) , cases.minf);
    TTS_EQUAL     (pedantic(prev)(type(1))       , type(1)-eve::eps(eve::as<type>())/2 );
    TTS_EQUAL     (pedantic(prev)(type(-1))      , type(-1)-eve::eps(eve::as<type>())   );
  }
  else
  {
    TTS_EQUAL(prev(type(2))                  , type(1));
    TTS_EQUAL(prev(type(3))                  , type(2));
    TTS_EQUAL(saturated(prev)(type(2))       , type(1));
    TTS_EQUAL(saturated(prev)(type(3))       , type(2));
    TTS_EQUAL(saturated(prev)(cases.valmin ) , cases.valmin);
  }
};
EVE_TEST( "Check corner-cases behavior of eve::prev with 2 parameters"
        , eve::test::simd::all_types
        , eve::test::generate(eve::test::limits())
        )
<typename T>(T const& cases)
{
  using type = typename T::type;
  using eve::prev;
  using eve::pedantic;
  using eve::saturated;
  if constexpr(eve::floating_real_value<type>)
  {
    TTS_IEEE_EQUAL(prev(cases.nan,  2) , cases.nan   );
    TTS_IEEE_EQUAL(prev(cases.inf, 2) , prev(cases.valmax));
    TTS_IEEE_EQUAL(prev(cases.minf,  2) , cases.nan   );
    TTS_EQUAL     (prev(cases.mzero,2) , prev(-cases.mindenormal));
    TTS_EQUAL     (prev(cases.zero, 2) , prev(-cases.mindenormal));
    TTS_EQUAL     (prev(cases.mindenormal, 2) , -cases.mindenormal);
    TTS_IEEE_EQUAL(prev(cases.valmin,2), cases.nan);
    TTS_EQUAL     (prev(type(1),   2) , type(1)-eve::eps(eve::as<type>()) );
    TTS_EQUAL     (prev(type(-1),    2) , type(-1)-eve::eps(eve::as<type>())*2   );

    TTS_IEEE_EQUAL(pedantic(prev)(cases.nan,  2) , cases.nan   );
    TTS_IEEE_EQUAL(pedantic(prev)(cases.inf,  2) , prev(cases.valmax));
    TTS_IEEE_EQUAL(pedantic(prev)(cases.minf,  2) , cases.nan   );
    TTS_EQUAL     (pedantic(prev)(cases.zero,2) , -cases.mindenormal);
    TTS_EQUAL     (pedantic(prev)(cases.mzero, 2) , prev(-cases.mindenormal));
    TTS_EQUAL     (pedantic(prev)(cases.mindenormal,2) , cases.zero);
    TTS_IEEE_EQUAL(pedantic(prev)(cases.valmin,2) , cases.nan);
    TTS_EQUAL     (pedantic(prev)(type(1),   2)  , type(1)-eve::eps(eve::as<type>()) );
    TTS_EQUAL     (pedantic(prev)(type(-1),    2)  , type(-1)-eve::eps(eve::as<type>())*2   );
  }
  else
  {
    TTS_EQUAL(prev(type(4), 2)                  , type(2));
    TTS_EQUAL(prev(type(5), 2)                  , type(3));
    TTS_EQUAL(saturated(prev)(type(4), 2)       , type(2));
    TTS_EQUAL(saturated(prev)(type(5), 2)       , type(3));
    TTS_EQUAL(saturated(prev)(cases.valmin, 2)  , cases.valmin);
  }
};
