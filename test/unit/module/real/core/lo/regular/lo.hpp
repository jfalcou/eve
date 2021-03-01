//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/lo.hpp>
#include <eve/detail/meta.hpp>
#include <eve/concept/value.hpp>
#include <array>

TTS_CASE_TPL("Check lo return type", EVE_TYPE)
{
  using elt_t =eve::element_type_t<T>;
  using sui_t = eve::as_integer_t<elt_t, unsigned>;
  using sdui_t =  eve::detail::downgrade_t<sui_t>;
  using wdui_t = eve::wide<sdui_t, eve::cardinal_t<T> >;
  TTS_EXPR_IS((eve::lo(T())),wdui_t);
}

TTS_CASE_TPL("Check (eve::lo behavior", EVE_TYPE)
{
  using elt_t =eve::element_type_t<T>;
  using ui_t = eve::as_integer_t<elt_t, unsigned>;
  using dui_t = eve::detail::downgrade_t<ui_t>;
  if constexpr(sizeof(elt_t) > 1)
  {
    using wui_t = decltype(eve::lo(T(1)));
    TTS_EQUALe(eve::lo(T(1)), wui_t(1));
    TTS_EQUAL (eve::lo(T(ui_t(~0))), wui_t(dui_t(~0)));
    TTS_EQUAL (eve::lo(T(ui_t(~0) >> (sizeof(elt_t)*4) ), wui_t(dui_t(~0))));
    TTS_EQUAL (eve::lo((T(ui_t(~0) >> (sizeof(elt_t)*4)) <<(sizeof(elt_t)*4) )), wui_t(dui_t(0)));
  }
  else
  {
    using wui_t = decltype(eve::lo(T(1)));
    TTS_EQUALe(eve::lo(T(1)), wui_t(1));
    TTS_EQUAL (eve::lo(T(ui_t(~0))), wui_t(dui_t(~0)));
    TTS_EQUAL (eve::lo(T(ui_t(~0) >> (sizeof(elt_t)*4) ), wui_t(dui_t(~0)>> (sizeof(elt_t)*4)));
    TTS_EQUAL (eve::lo((T(ui_t(~0) >> (sizeof(elt_t)*4)) <<(sizeof(elt_t)*4) )), wui_t(dui_t(~0) >> (sizeof(elt_t)*4)));
  }
}
