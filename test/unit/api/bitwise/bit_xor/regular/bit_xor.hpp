//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_xor.hpp>
#include <type_traits>

TTS_CASE_TPL("Check operator^ return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;
  using ui_t = eve::detail::as_integer_t<T  , unsigned>;
  using vi_t = eve::detail::as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS(T()    ^ T()    , T   );
  TTS_EXPR_IS(T()    ^ v_t()  , T   );
  TTS_EXPR_IS(v_t()  ^ T()    , T   );
  TTS_EXPR_IS(T()    ^ ui_t() , T   );
  TTS_EXPR_IS(T()    ^ vi_t() , T   );
  TTS_EXPR_IS(ui_t() ^ T()    , ui_t);
  TTS_EXPR_IS(vi_t() ^ T()    , ui_t);
}

TTS_CASE_TPL( "Check operator^ behavior", EVE_TYPE)
{
  using eve::bit_cast;
  using eve::as;

  using v_t  = eve::element_type_t<T>;
  using ui_t = eve::detail::as_integer_t<T  , unsigned>;
  using vi_t = eve::detail::as_integer_t<v_t, unsigned>;
  using si_t = eve::detail::as_integer_t<T  , signed>;
  using wi_t = eve::detail::as_integer_t<v_t, signed>;

  TTS_EQUAL((T(0) ^ T(0)  ) , T(0) );
  TTS_EQUAL((T(0) ^ v_t(0)) , T(0) );
  TTS_EQUAL((T(0) ^ T(1)  ) , T(1) );
  TTS_EQUAL((T(0) ^ v_t(1)) , T(1) );
  TTS_EQUAL((T(1) ^ T(1)  ) , T(0) );
  TTS_EQUAL((T(1) ^ v_t(1)) , T(0) );
  TTS_EQUAL((T(1) ^ T(0)  ) , T(1) );
  TTS_EQUAL((T(1) ^ v_t(0)) , T(1) );

  TTS_EQUAL((T(0) ^ ui_t(1)), bit_cast(ui_t(1),as<T>()));
  TTS_EQUAL((T(0) ^ vi_t(1)), bit_cast(ui_t(1),as<T>()));
  TTS_EQUAL((T(0) ^ si_t(1)), bit_cast(si_t(1),as<T>()));
  TTS_EQUAL((T(0) ^ wi_t(1)), bit_cast(si_t(1),as<T>()));

  TTS_EQUAL((ui_t(0) ^ T(1)), bit_cast(T(1),as<ui_t>()));
  TTS_EQUAL((si_t(0) ^ T(1)), bit_cast(T(1),as<si_t>()));

  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL( (T(3) ^ T(2)  ) , T(1));
    TTS_EQUAL( (T(3) ^ v_t(2)) , T(1));
    TTS_EQUAL( (T(3) ^ T(1)  ) , T(2));
    TTS_EQUAL( (T(3) ^ v_t(1)) , T(2));
  }
}
