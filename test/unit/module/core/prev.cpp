//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of eve::prev", eve::test::simd::all_types)
<typename T>(tts::type<T>)
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
TTS_CASE_WITH( "Check behavior of eve::prev(eve::wide)"
        , eve::test::simd::all_types
        , tts::generate ( tts::randoms(-10, +10)
                              , tts::logicals(0,3)
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
TTS_CASE_TPL( "Check corner-cases behavior of eve::prev variants on wide", eve::test::simd::all_types)
<typename T>(tts::type<T> const& tgt)
{
  using eve::prev;
  using eve::pedantic;
  using eve::saturated;

  auto cases = tts::limits(tgt);

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_IEEE_EQUAL(prev(cases.inf   ) , cases.valmax);
    TTS_IEEE_EQUAL(prev(cases.minf    ) , cases.nan   );
    TTS_EQUAL     (prev(cases.mzero  ) , -cases.mindenormal);
    TTS_EQUAL     (prev(cases.zero   ) , -cases.mindenormal);
    TTS_EQUAL     (prev(cases.mindenormal ) , cases.zero);
    TTS_EQUAL     (prev(cases.valmin ) , cases.minf);
    TTS_EQUAL     (prev(T(1))      , T(1)-eve::eps(eve::as<T>())/2 );
    TTS_EQUAL     (prev(T(-1))       , T(-1)-eve::eps(eve::as<T>())   );

    TTS_IEEE_EQUAL(pedantic(prev)(cases.nan    ) , cases.nan   );
    TTS_IEEE_EQUAL(pedantic(prev)(cases.inf    ) , cases.valmax);
    TTS_IEEE_EQUAL(pedantic(prev)(cases.minf   ) , cases.nan   );
    TTS_EQUAL     (pedantic(prev)(cases.zero   ) , cases.mzero);
    TTS_EQUAL     (pedantic(prev)(cases.mzero  ) , -cases.mindenormal);
    TTS_EQUAL     (pedantic(prev)(cases.mindenormal ) , cases.zero);
    TTS_EQUAL     (pedantic(prev)(cases.valmin ) , cases.minf);
    TTS_EQUAL     (pedantic(prev)(T(1))       , T(1)-eve::eps(eve::as<T>())/2 );
    TTS_EQUAL     (pedantic(prev)(T(-1))      , T(-1)-eve::eps(eve::as<T>())   );
  }
  else
  {
    TTS_EQUAL(prev(T(2))                  , T(1));
    TTS_EQUAL(prev(T(3))                  , T(2));
    TTS_EQUAL(saturated(prev)(T(2))       , T(1));
    TTS_EQUAL(saturated(prev)(T(3))       , T(2));
    TTS_EQUAL(saturated(prev)(cases.valmin ) , cases.valmin);
  }
};

TTS_CASE_TPL( "Check corner-cases behavior of eve::prev with 2 parameters", eve::test::simd::all_types )
<typename T>(tts::type<T> const& tgt)
{
  using eve::prev;
  using eve::pedantic;
  using eve::saturated;

  auto cases = tts::limits(tgt);

  if constexpr(eve::floating_real_value<T>)
  {
    TTS_IEEE_EQUAL(prev(cases.nan,  2) , cases.nan   );
    TTS_IEEE_EQUAL(prev(cases.inf, 2) , prev(cases.valmax));
    TTS_IEEE_EQUAL(prev(cases.minf,  2) , cases.nan   );
    TTS_EQUAL     (prev(cases.mzero,2) , prev(-cases.mindenormal));
    TTS_EQUAL     (prev(cases.zero, 2) , prev(-cases.mindenormal));
    TTS_EQUAL     (prev(cases.mindenormal, 2) , -cases.mindenormal);
    TTS_IEEE_EQUAL(prev(cases.valmin,2), cases.nan);
    TTS_EQUAL     (prev(T(1),   2) , T(1)-eve::eps(eve::as<T>()) );
    TTS_EQUAL     (prev(T(-1),    2) , T(-1)-eve::eps(eve::as<T>())*2   );

    TTS_IEEE_EQUAL(pedantic(prev)(cases.nan,  2) , cases.nan   );
    TTS_IEEE_EQUAL(pedantic(prev)(cases.inf,  2) , prev(cases.valmax));
    TTS_IEEE_EQUAL(pedantic(prev)(cases.minf,  2) , cases.nan   );
    TTS_EQUAL     (pedantic(prev)(cases.zero,2) , -cases.mindenormal);
    TTS_EQUAL     (pedantic(prev)(cases.mzero, 2) , prev(-cases.mindenormal));
    TTS_EQUAL     (pedantic(prev)(cases.mindenormal,2) , cases.zero);
    TTS_IEEE_EQUAL(pedantic(prev)(cases.valmin,2) , cases.nan);
    TTS_EQUAL     (pedantic(prev)(T(1),   2)  , T(1)-eve::eps(eve::as<T>()) );
    TTS_EQUAL     (pedantic(prev)(T(-1),    2)  , T(-1)-eve::eps(eve::as<T>())*2   );
  }
  else
  {
    TTS_EQUAL(prev(T(4), 2)                  , T(2));
    TTS_EQUAL(prev(T(5), 2)                  , T(3));
    TTS_EQUAL(saturated(prev)(T(4), 2)       , T(2));
    TTS_EQUAL(saturated(prev)(T(5), 2)       , T(3));
    TTS_EQUAL(saturated(prev)(cases.valmin, 2)  , cases.valmin);
  }
};
