//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_xor.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::bit_xor return type", EVE_TYPE)
{
  using eve::as_integer_t;
  using v_t = eve::element_type_t<T>;
  using ui_t = as_integer_t<T, unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS(eve::bit_xor(T()  , T()) , T);
  TTS_EXPR_IS(eve::bit_xor(T()  , v_t()), T);
  TTS_EXPR_IS(eve::bit_xor(v_t() , T()) , T);
  TTS_EXPR_IS(eve::bit_xor(T()  , ui_t())     , T);
  TTS_EXPR_IS(eve::bit_xor(T()  , vi_t())     , T);
  TTS_EXPR_IS(eve::bit_xor(ui_t()      , T()) , ui_t      );
  TTS_EXPR_IS(eve::bit_xor(vi_t()      , T()) , ui_t      );
}

TTS_CASE_TPL( "Check bit_xor behavior", EVE_TYPE)
{
  using eve::as_integer_t;
  using eve::bit_cast;
  using eve::as;

  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::bit_xor((T(0)), (T(0)))  , (T(0)));
  TTS_EQUAL(eve::bit_xor((T(0)), (v_t(0))) , (T(0)));
  TTS_EQUAL(eve::bit_xor((T(0)), (T(1)))  , (T(1)));
  TTS_EQUAL(eve::bit_xor((T(0)), (v_t(1))) , (T(1)));
  TTS_EQUAL(eve::bit_xor((T(1)), (T(1)))  , (T(0)));
  TTS_EQUAL(eve::bit_xor((T(1)), (v_t(1))) , (T(0)));
  TTS_EQUAL(eve::bit_xor((T(1)), (T(0)))  , (T(1)));
  TTS_EQUAL(eve::bit_xor((T(1)), (v_t(0))) , (T(1)));

  using ui_t = as_integer_t<T, unsigned>;
  using vi_t = as_integer_t<v_t, unsigned>;
  using si_t = as_integer_t<T, signed>;
  using wi_t = as_integer_t<v_t, signed>;

  TTS_EQUAL(eve::bit_xor((T(0)), ui_t(1)), bit_cast(ui_t(1),as<T>()));
  TTS_EQUAL(eve::bit_xor((T(0)), vi_t(1)), bit_cast(ui_t(1),as<T>()));
  TTS_EQUAL(eve::bit_xor((T(0)), si_t(1)), bit_cast(si_t(1),as<T>()));
  TTS_EQUAL(eve::bit_xor((T(0)), wi_t(1)), bit_cast(si_t(1),as<T>()));

  TTS_EQUAL(eve::bit_xor(ui_t(0), (T(1))), bit_cast(T(1),as<ui_t>()));
  TTS_EQUAL(eve::bit_xor(si_t(0), (T(1))), bit_cast(T(1),as<si_t>()));

  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL(eve::bit_xor(T(3), T(2) ) , T(1));
    TTS_EQUAL(eve::bit_xor(T(3), v_t(2)) , T(1));
    TTS_EQUAL(eve::bit_xor(T(3), T(1) ) , T(2));
    TTS_EQUAL(eve::bit_xor(T(3), v_t(1)) , T(2));
  }
}
