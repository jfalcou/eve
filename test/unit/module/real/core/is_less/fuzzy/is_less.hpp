//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/fuzzy/is_less.hpp>
#include <eve/function/fuzzy.hpp>
#include <eve/function/prev.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/mindenormal.hpp>

TTS_CASE_TPL("Check eve::definitely(eve::is_less) return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using eve::logical;

  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS( eve::definitely(eve::is_less)(  T()         ,   T()         ) , logical<T>);
    TTS_EXPR_IS( eve::definitely(eve::is_less)(  T()         , v_t()         ) , logical<T>);
    TTS_EXPR_IS( eve::definitely(eve::is_less)(v_t()         ,   T()         ) , logical<T>);
    TTS_EXPR_IS( eve::definitely(eve::is_less)(  T()         ,   T(), unsigned()  ) , logical<T>);
    TTS_EXPR_IS( eve::definitely(eve::is_less)(  T()         , v_t(), unsigned()  ) , logical<T>);
    TTS_EXPR_IS( eve::definitely(eve::is_less)(v_t()         ,   T(), unsigned()  ) , logical<T>);
    TTS_EXPR_IS( eve::definitely(eve::is_less)(  T()         ,   T(), T()    ) , logical<T>);
    TTS_EXPR_IS( eve::definitely(eve::is_less)(  T()         , v_t(), T()    ) , logical<T>);
    TTS_EXPR_IS( eve::definitely(eve::is_less)(v_t()         ,   T(), T()    ) , logical<T>);
    using ui_t = eve::as_integer_t<T, unsigned>;
    TTS_EXPR_IS( eve::definitely(eve::is_less)(  T()         ,   T(), ui_t() ) , logical<T>);
    TTS_EXPR_IS( eve::definitely(eve::is_less)(  T()         , v_t(), ui_t() ) , logical<T>);
    TTS_EXPR_IS( eve::definitely(eve::is_less)(v_t()         ,   T(), ui_t() ) , logical<T>);
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}

TTS_CASE_TPL("Check eve::definitely(eve::is_less) behavior", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using eve::logical;

  if constexpr(eve::platform::supports_nans && eve::floating_value<T>)
  {
    TTS_EQUAL(eve::definitely(eve::is_less)(T(1)                  , T(1)                  )   , eve::false_(eve::as<T>()) );
    TTS_EQUAL(eve::definitely(eve::is_less)(T(1)                  , v_t(1)                )   , eve::false_(eve::as<T>()) );
    TTS_EQUAL(eve::definitely(eve::is_less)(T(1)                  , T(3)                  )   , eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::definitely(eve::is_less)(T(1)                  , v_t(3)                )   , eve::true_(eve::as<T>()));
    using eve::as;
    TTS_EQUAL(eve::definitely(eve::is_less)(T(1-eve::eps(as<T>()))     , T(1)                  , eve::eps(as<T>()))   , eve::false_(eve::as<T>()) );
    TTS_EQUAL(eve::definitely(eve::is_less)(T(1-2*eve::eps(as<T>()))   , T(1)                  , eve::eps(as<T>()))   , eve::true_(eve::as<T>()) );
    TTS_EQUAL(eve::definitely(eve::is_less)(T(1-eve::eps(as<T>()))     , v_t(1)                , eve::eps(as<T>()))   , eve::false_(eve::as<T>()) );
    TTS_EQUAL(eve::definitely(eve::is_less)(T(1)                       , T(3)                  , eve::eps(as<T>()))   , eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::definitely(eve::is_less)(T(1)                       , v_t(3)                , eve::eps(as<T>()))   , eve::true_(eve::as<T>()));

    using ui_t = eve::as_integer_t<T, unsigned>;

    TTS_EQUAL(eve::definitely(eve::is_less)(T(1)                  , T(1)                  , ui_t(3))   , eve::false_(eve::as<T>()) );
    TTS_EQUAL(eve::definitely(eve::is_less)(T(1)                  , v_t(1)                , ui_t(3))   , eve::false_(eve::as<T>()) );
    TTS_EQUAL(eve::definitely(eve::is_less)(T(1)                  , T(3)                  , ui_t(3))   , eve::true_(eve::as<T>()));
    TTS_EQUAL(eve::definitely(eve::is_less)(T(1)                  , v_t(3)                , ui_t(3))   , eve::true_(eve::as<T>()));
    auto md = eve::mindenormal(eve::as<v_t>());
    TTS_EQUAL(eve::definitely(eve::is_less)(v_t(-md)               , T(0)                 , ui_t(3))   , eve::false_(eve::as<T>()) );
    TTS_EQUAL(eve::definitely(eve::is_less)(v_t(-2*md)             , T(0)                 , ui_t(3))   , eve::false_(eve::as<T>()) );
    TTS_EQUAL(eve::definitely(eve::is_less)(v_t(-3*md)             , T(0)                 , ui_t(3))   , eve::false_(eve::as<T>()) );
    TTS_EQUAL(eve::definitely(eve::is_less)(v_t(-4*md)             , T(0)                 , ui_t(3))   , eve::true_(eve::as<T>()) );
    TTS_EQUAL(eve::definitely(eve::is_less)(v_t(1)                , v_t(1)               , ui_t(3))   , eve::false_(eve::as<T>()) );
  }
  else
  {
    TTS_PASS("Unsupported type");
  }
}
