//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"
#include "unit/memory/page.hpp"

#include <eve/memory/aligned_ptr.hpp>
#include <eve/module/core.hpp>

//==================================================================================================
// Write scalar to pointer-like entity
//==================================================================================================
TTS_CASE_TPL( "Check write to pointers"
              , eve::test::scalar::all_types
              )
<typename T>(tts::type<T>)
{
  auto [data, idx] = page<T , eve::expected_cardinal_t<T> >();

  auto* ptr   = &data[idx];
  auto* uptr  = &data[idx] - 1;

  eve::write(T{42}, eve::as_aligned(ptr));
  TTS_EQUAL( *ptr, T{42} );

  eve::write(T{42}, uptr);
  TTS_EQUAL( *uptr, T{42} );
};

//==================================================================================================
// Write scalar to Contiguous Iterators
//==================================================================================================
TTS_CASE_TPL( "Check write to Contiguous Iterators"
              , eve::test::scalar::all_types
              )
<typename T>(tts::type<T>)
{
  auto [data, idx] = page<T , eve::expected_cardinal_t<T> >();

  auto begin              = data.begin()  + idx;

  eve::write(T{69}, begin);
  TTS_EQUAL( *begin, T{69});
};

//==================================================================================================
// Write scalar to soa_ptr
//==================================================================================================
TTS_CASE_TPL( "Check write to soa_ptr"
              , eve::test::scalar::all_types
              )
<typename T>(tts::type<T>)
{
  int    x = 0;
  T      y = T(1);
  double z = 2.0;

  eve::write( kumi::tuple{x + 1, y + 1, z + 1}, eve::soa_ptr(&x, &y, &z));

  TTS_EQUAL(x, 1);
  TTS_EQUAL(y, (T)2);
  TTS_EQUAL(z, 3.0);
};
