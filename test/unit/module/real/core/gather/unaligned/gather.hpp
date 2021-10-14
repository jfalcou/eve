//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include <eve/function/gather.hpp>

TTS_CASE_TPL("Check eve::gather behavior with 32 bits indexes", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  v_t data[EVE_CARDINAL];
  for(std::size_t i = 0;i<EVE_CARDINAL;++i) data[i] = v_t(1) + i;

  eve::wide<std::int32_t, eve::fixed<EVE_CARDINAL>> maps([](auto i, auto c) { return i%3 ? i : c-i-1; });
  T ref( [&](auto i, auto) { return data[maps.get(i)]; } );

  const v_t* cdata = &data[0];
  TTS_EQUAL( ref, eve::gather(cdata   , maps) );
  TTS_EQUAL( ref, eve::gather(&data[0], maps) );
};

TTS_CASE_TPL("Check eve::gather behavior with 64 bits indexes", EVE_TYPE)
<typename T>(::tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  v_t data[EVE_CARDINAL];
  for(std::size_t i = 0;i<EVE_CARDINAL;++i) data[i] = v_t(1) + i;

  eve::wide<std::int64_t, eve::fixed<EVE_CARDINAL>> maps([](auto i, auto c) { return i%3 ? i : c-i-1; });
  T ref( [&](auto i, auto) { return data[maps.get(i)]; } );

  const v_t* cdata = &data[0];
  TTS_EQUAL( ref, eve::gather(cdata   , maps) );
  TTS_EQUAL( ref, eve::gather(&data[0], maps) );
};
