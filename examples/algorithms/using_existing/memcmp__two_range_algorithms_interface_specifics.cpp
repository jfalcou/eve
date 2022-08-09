//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

//
// In this example we will implement a `std::memcmp` using `eve::algo::mismatch`
// We will look a bit at `eve::algo::zip` and note the differences between `std::mismatch`
// and `eve::algo::mismatch`.
//

#include <eve/algo/as_range.hpp>
#include <eve/algo/mismatch.hpp>
#include <eve/views/zip.hpp>

int memcmp_( void const* lhs, void const* rhs, std::size_t count )
//
// From cppreference: https://en.cppreference.com/w/cpp/string/byte/memcmp
//
// [memcmp] reinterprets the objects pointed to by lhs and rhs as arrays
// of unsigned char and compares the first `count` characters of these arrays.
// The comparison is done lexicographically. The sign of the result is the sign of
// the difference between the values of the first pair of bytes (both interpreted as unsigned char)
// that differ in the objects being compared.
{
  // `unsigned char` is not guarantied to be the same type as `std::uint8_t.
  // We don't support `char` and `unsigned char` in eve, only `std::int8_t` and `std::uint8_t`.
  // This is not only theory, when compiling for arm `char` is not `std::int8_t` nor it is `std::uint8_t`.
  // So we need to cast.
  auto const* f1 = reinterpret_cast<std::uint8_t const*>(lhs);
  auto const* l1 = f1 + static_cast<std::ptrdiff_t>(count);
  auto const* f2 = reinterpret_cast<std::uint8_t const*>(rhs);

  // eve::algo is range based so we need to wrap f1, l1 in a range.
  eve::algo::as_range  r1{f1, l1};

  // eve::algo::mismatch returns a zip_iterator and not std::pair.
  // It can also accept both arguments zipped together, like we use here.
  // In this case it's a matter of taste, but sometimes you want to have access
  // to `zip`, because of it's options like `zip[eve::algo::common_type]`.
  eve::views::zip_range    r1_r2 = eve::views::zip(r1, f2);
  eve::views::zip_iterator found = eve::algo::mismatch(r1_r2);

  // Same as with `std` end iterator means nothing is found - no mismatch.
  if (found == r1_r2.end()) return 0;

  // In eve with use `eve::read`/`eve::write` instead of `operator*` to access scalar values.
  // This is to avoid a `proxy references` problem (see `vector<bool>`)
  auto [v1, v2] = eve::read(found);

  return static_cast<int>(v1) - static_cast<int>(v2);
}

// --------------------------------------------

#include "test.hpp"

TTS_CASE("against std::memcmp")
{
  auto postprocess_res = [](int r) {
    if (r < 0)  return -1;
    if (r == 0) return 0;
    return 1;
  };

  auto test = [&](std::vector<std::uint8_t> const& a,
                 std::vector<std::uint8_t> const& b) {
    TTS_EQUAL(
      postprocess_res(std::memcmp(a.data(), b.data(), a.size())),
      postprocess_res(memcmp_(a.data(), b.data(), a.size()))
    );
    TTS_EQUAL(
      postprocess_res(std::memcmp(b.data(), a.data(), a.size())),
      postprocess_res(memcmp_(b.data(), a.data(), a.size()))
    );
  };

  test({}, {});
  test({'a'}, {'a'});
  test({254}, {255});
  test({1, 2, 3, 4, 5, 6},
       {1, 2, 4, 5, 4, 6});


  // We don't test a lot of offsets since mismatch itself is already tested.
  // We only care about outsides
  {
    std::vector<std::uint8_t> a(1000u);
    std::vector<std::uint8_t> b = a;

    test(a, b);

    a[237] = 243;
    test(a, b);
  }
};
