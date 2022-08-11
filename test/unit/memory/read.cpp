//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"
#include "unit/memory/page.hpp"

#include <eve/memory/aligned_ptr.hpp>
#include <eve/module/core.hpp>

//==================================================================================================
// Read into scalar from pointer-like entity
//==================================================================================================
TTS_CASE_TPL( "Check read from pointers"
              , eve::test::scalar::all_types
              )
<typename T>(tts::type<T>)
{
  auto [data, idx] = page<T , eve::expected_cardinal_t<T> >();

  auto* ptr              = &data[idx];
  auto* uptr             = &data[idx] - 1;
  auto const* const_ptr  = ptr;
  auto const* const_uptr = uptr;

  TTS_EQUAL( eve::read(eve::as_aligned(ptr)      ), *ptr        );
  TTS_EQUAL( eve::read(eve::as_aligned(const_ptr)), *const_ptr  );
  TTS_EQUAL( eve::read(uptr)                      , *uptr       );
  TTS_EQUAL( eve::read(const_uptr)                , *const_uptr );
};

//==================================================================================================
// Read into scalar from Contiguous Iterators
//==================================================================================================
TTS_CASE_TPL( "Check read from Contiguous Iterators"
              , eve::test::scalar::all_types
              )
<typename T>(tts::type<T>)
{
  auto [data, idx] = page<T , eve::expected_cardinal_t<T> >();

  auto begin              = data.begin()  + idx;
  auto const const_begin  = data.cbegin() + idx;

  TTS_EQUAL( eve::read(begin)      , *begin       );
  TTS_EQUAL( eve::read(const_begin), *const_begin );
};

//==================================================================================================
// Read into scalar from soa_ptr
//==================================================================================================
TTS_CASE_TPL( "Check read from soa_ptr"
              , eve::test::scalar::all_types
              )
<typename T>(tts::type<T>)
{
  int    x = 0;
  T      y = T(1);
  double z = 2.0;

  auto [rx, ry, rz] = eve::read(eve::soa_ptr(&x, &y, &z));
  TTS_EQUAL(rx, x);
  TTS_EQUAL(ry, y);
  TTS_EQUAL(rz, z);
};
