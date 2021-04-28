//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/lohi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/concept/value.hpp>
#include <array>

TTS_CASE_TPL("Check lohi return type", EVE_TYPE)
{
  using elt_t =eve::element_type_t<T>;
  using sui_t = eve::as_integer_t<elt_t, unsigned>;
  using sdui_t =  eve::detail::downgrade_t<sui_t>;
  if constexpr(eve::simd_value<T>)
  {
    using wdui_t = eve::wide<sdui_t, eve::cardinal_t<T> >;
    using typ = std::array<wdui_t,2>;
    TTS_EXPR_IS((eve::lohi(T())),typ);
  }
  else
  {
    using wdui_t = sdui_t;
    using typ = std::array<wdui_t,2>;
    TTS_EXPR_IS((eve::lohi(T())),typ);
  }
}

TTS_CASE_TPL("Check (eve::lohi behavior", EVE_TYPE)
{
  using elt_t =eve::element_type_t<T>;
  using ui_t = eve::as_integer_t<elt_t, unsigned>;
  using dui_t = eve::detail::downgrade_t<ui_t>;
  if constexpr(sizeof(elt_t) > 1)
  {
    {
      auto [p0, p1] = eve::lohi(T(1));
      using wui_t = decltype(p0);
      TTS_EQUAL(p0, wui_t(1));
      TTS_EQUAL(p1, wui_t(0));
    }

    {
      auto [p0, p1] = eve::lohi(T(ui_t(~0)));
      using wui_t = decltype(p0);
      TTS_EQUAL (p0, wui_t(dui_t(~0)));
      TTS_EQUAL (p1, wui_t(dui_t(~0)));
    }
    {
      auto [p0, p1] = eve::lohi(T(ui_t(~0) >> (sizeof(elt_t)*4) ));
      using wui_t = decltype(p0);
      TTS_EQUAL (p0, wui_t(dui_t(~0)));
      TTS_EQUAL (p1, wui_t(dui_t(0)));
    }
  }
  else
  {
    {
      auto [p0, p1] = eve::lohi(T(1));
      using wui_t = decltype(p0);
      TTS_EQUAL(p0, wui_t(1));
      TTS_EQUAL(p1, wui_t(0));
    }

    {
      auto [p0, p1] = eve::lohi(T(ui_t(~0)));
      using wui_t = decltype(p0);
      TTS_EQUAL (p0, wui_t(dui_t(~0)>> (sizeof(elt_t)*4)));
      TTS_EQUAL (p1, wui_t(dui_t(~0)>> (sizeof(elt_t)*4)));
    }
    {
      auto [p0, p1] = eve::lohi(T(ui_t(~0) >> (sizeof(elt_t)*4) ));
      using wui_t = decltype(p0);
      TTS_EQUAL (p0, wui_t(dui_t(~0)>> (sizeof(elt_t)*4)));
      TTS_EQUAL (p1, wui_t(dui_t(0)));
    }
  }
}
