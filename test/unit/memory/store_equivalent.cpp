//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <eve/memory/stack_buffer.hpp>

using u32s = eve::wide<std::uint32_t>;
using u8s  = eve::wide<std::uint8_t, eve::fixed<u32s::size()>>;

struct my_ptr
{
  std::uint8_t* equivalent;

  using value_type = std::uint32_t;

  EVE_FORCEINLINE friend
  auto tagged_dispatch(eve::tag::store_equivalent_, auto ignore, u32s, my_ptr self)
  {
    return kumi::make_tuple(ignore, u8s{3}, self.equivalent);
  }

  EVE_FORCEINLINE friend
  auto tagged_dispatch(eve::tag::unalign_, my_ptr self)
  {
    return self.equivalent;
  }
};

TTS_CASE("store_equivalent")
{
  eve::stack_buffer<u8s> buf;

  static_assert(eve::has_store_equivalent<u32s, my_ptr>);
  static_assert(!eve::has_store_equivalent<u32s, std::uint32_t*>);

  {
    eve::store(u8s(0), buf.ptr());
    eve::store(u32s{}, my_ptr{buf.ptr()});

    TTS_EQUAL( u8s{buf.ptr()}, u8s{3} );
  }

  {
    eve::store(u8s(0), buf.ptr());
    eve::store[eve::keep_first(1)](u32s{}, my_ptr{buf.ptr()});

    u8s expected(0);
    expected.set(0, 3);

    TTS_EQUAL( u8s{buf.ptr()}, expected );
  }


  {
    eve::store(u8s(0), buf.ptr());
    eve::logical<u32s> m( [](int i, int) { return i == 0; } );
    std::uint8_t* res = eve::compress_store[eve::safe](u32s(0), m, my_ptr{buf.ptr()});

    u8s expected(0);
    expected.set(0, 3);

    TTS_EQUAL((res - buf.ptr().get()), 1);
    TTS_EQUAL( u8s{buf.ptr()}, expected );
  }

  {
    eve::store(u8s(0), buf.ptr());
    eve::logical<u32s> m( [](int i, int) { return i == 0; } );
    std::uint8_t* res = eve::compress_store[eve::unsafe][eve::keep_first(1)](u32s(0), m, my_ptr{buf.ptr()});

    u8s expected(0);
    expected.set(0, 3);

    TTS_EQUAL((res - buf.ptr().get()), 1);
    TTS_EQUAL( u8s{buf.ptr()}, expected );
  }
};
