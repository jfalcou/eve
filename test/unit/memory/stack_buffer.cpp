//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/memory/stack_buffer.hpp>

TTS_CASE("stack_buffer types")
{
  using N = eve::fixed<8>;

  {
    using T = eve::wide<int, N>;
    eve::stack_buffer<T> buf;
    auto const& cbuf = buf;

    TTS_TYPE_IS(decltype(buf.get_ptr()),  (eve::aligned_ptr<int, N>));
    TTS_TYPE_IS(decltype(cbuf.get_ptr()), (eve::aligned_ptr<int const, N>));
  }
  {
    using T = eve::logical<eve::wide<int, N>>;
    eve::stack_buffer<T> buf;
    auto const& cbuf = buf;

    TTS_TYPE_IS(decltype(buf.get_ptr()),  (eve::aligned_ptr<eve::logical<int>,       N>));
    TTS_TYPE_IS(decltype(cbuf.get_ptr()), (eve::aligned_ptr<eve::logical<int> const, N>));
  }
  {
    using p1 = kumi::tuple<std::uint8_t, int>;
    using T  = eve::wide<kumi::tuple<p1, double>, N>;
    eve::stack_buffer<T> buf;
    auto const& cbuf = buf;

    TTS_TYPE_IS(decltype(buf.get_ptr()),
      (eve::soa_ptr<
        eve::soa_ptr<eve::aligned_ptr<std::uint8_t, N>,
                    eve::aligned_ptr<int, N>>,
        eve::aligned_ptr<double, N>
      >));
    TTS_TYPE_IS(decltype(cbuf.get_ptr()),
      (eve::soa_ptr<
        eve::soa_ptr<eve::aligned_ptr<std::uint8_t const, N>,
                     eve::aligned_ptr<int const, N>>,
        eve::aligned_ptr<double const, N>
      >));
  }
};
