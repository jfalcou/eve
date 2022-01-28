//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/memory/stack_buffer.hpp>

#include <eve/function/load.hpp>
#include <eve/function/store.hpp>

#include <eve/function/convert.hpp>

#include <utility>

TTS_CASE("stack_buffer types")
{
  using N = eve::fixed<8>;

  {
    using T = eve::wide<int, N>;
    eve::stack_buffer<T> buf;
    auto const& cbuf = buf;

    TTS_TYPE_IS(decltype(buf.ptr()),  (eve::aligned_ptr<int, N>));
    TTS_TYPE_IS(decltype(cbuf.ptr()), (eve::aligned_ptr<int const, N>));
  }
  {
    using T = eve::logical<eve::wide<int, N>>;
    eve::stack_buffer<T> buf;
    auto const& cbuf = buf;

    TTS_TYPE_IS(decltype(buf.ptr()),  (eve::aligned_ptr<eve::logical<int>,       N>));
    TTS_TYPE_IS(decltype(cbuf.ptr()), (eve::aligned_ptr<eve::logical<int> const, N>));
  }
  {
    using p1 = kumi::tuple<std::uint8_t, int>;
    using T  = eve::wide<kumi::tuple<p1, double>, N>;
    eve::stack_buffer<T> buf;
    auto const& cbuf = buf;

    TTS_TYPE_IS(decltype(buf.ptr()),
      (eve::soa_ptr<
        eve::soa_ptr<eve::aligned_ptr<std::uint8_t, N>,
                    eve::aligned_ptr<int, N>>,
        eve::aligned_ptr<double, N>
      >));
    TTS_TYPE_IS(decltype(cbuf.ptr()),
      (eve::soa_ptr<
        eve::soa_ptr<eve::aligned_ptr<std::uint8_t const, N>,
                     eve::aligned_ptr<int const, N>>,
        eve::aligned_ptr<double const, N>
      >));
  }
};

template <typename T>
void stack_buffer_load_store_test(T x)
{
  // Trying to mess with alignment a bit
  eve::stack_buffer<T> buf1;
  int volatile bla; (void) bla;
  eve::stack_buffer<T> buf2;
  char volatile bla1; (void) bla1;
  eve::stack_buffer<T> buf3;
  char volatile bla3; (void) bla3;
  eve::stack_buffer<T> buf4;

  eve::store(x, buf1.ptr());
  eve::store(x, buf2.ptr());
  eve::store(x, buf3.ptr());
  eve::store(x, buf4.ptr());

  TTS_EQUAL(x, eve::load(buf1.ptr(), eve::lane<T::size()>));
  TTS_EQUAL(x, eve::load(buf2.ptr(), eve::lane<T::size()>));
  TTS_EQUAL(x, eve::load(buf3.ptr(), eve::lane<T::size()>));
  TTS_EQUAL(x, eve::load(buf4.ptr(), eve::lane<T::size()>));


  TTS_EQUAL(x, eve::load(std::as_const(buf1).ptr(), eve::lane<T::size()>));
  TTS_EQUAL(x, eve::load(std::as_const(buf2).ptr(), eve::lane<T::size()>));
  TTS_EQUAL(x, eve::load(std::as_const(buf3).ptr(), eve::lane<T::size()>));
  TTS_EQUAL(x, eve::load(std::as_const(buf4).ptr(), eve::lane<T::size()>));
}

EVE_TEST_TYPES("stack_buffer load/store",  eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  T x{[](int i, int) { return i; }};
  stack_buffer_load_store_test(x);
  stack_buffer_load_store_test( x > 2 );

  auto product_x = eve::zip(
      eve::zip(x,
               eve::convert(x + 2, eve::as<std::int8_t>{})),
      eve::convert(x + 1, eve::as<double>{}));

  stack_buffer_load_store_test(product_x);
};
