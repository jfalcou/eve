//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

//
// In this example we will have a look on how to use zip with an algorithm
// by implementing inclusive_scan for complex numbers of parallel arrays.
//
// NOTE:
//   you might want to have a look at: `examples/oop/complex_numbers__declaring_an_object_type.cpp`
//   where we show how we can declare an object for complex numbers, which should improve
//   readability and reusability.
//
// NOTE:
//   examples/algorithms/using_existing/memcmp__two_range_algorithms_interface_specifics.cpp also
//   showcases zip.

#include <eve/module/algo.hpp>

#include <vector>

using cmplx_tuple = kumi::tuple<float, float>;

void inclusive_scan_complex(std::vector<float>& re, std::vector<float>& im, cmplx_tuple init)
{
  // Construct a view to both vectors as one range.
  eve::views::zip_range zipped = eve::views::zip(re, im);


  // The value type for zip is a wide<tuple<elements...>
  // kumi::tuple is a tuple implementation we use in eve
  auto plus = [](eve::wide<cmplx_tuple> x, eve::wide<cmplx_tuple> y) {
    // The wide<tuple> provides a tuple like interface and
    // can be decomposed with structured bindings.
    auto& [x_re, x_im] = x;
    auto  [y_re, y_im] = y;

    x_re += y_re;
    x_im += y_im;
    return x;
  };

  eve::algo::inclusive_scan_inplace     // in eve we have two versions of inclusive_scan
                                        // _inplace and _to. The _to one is like std.
                                        // the _inplace is the same as passing first as the output
                                        // and is slightly more efficient
                                        // ---
  [eve::algo::allow_frequency_scaling]( // When using maximum width registers some CPUs (intel avx512)
                                        // will very noticeably reduce frequecny. In this example we assume
                                        // the input arrays to be very large and this being acceptable.
                                        // ---
    zipped,                             // we iterate over both vectors as one range
                                        // ---
    std::pair{plus, eve::zero},         // In eve we need not only the operation but also
                                        // an identity element for that operation, so we accept a pair.
                                        // eve::zero is an equivalent to cmplx_tuple{0.0, 0.0}
                                        // but we use the knowledge that it's zero to generate better
                                        // code for some platforms.
                                        // ---
    init                                // init value.
                                        // Passing eve::zero here is not supported properly at the moment: FIX-955.
  );
}

// -----------------------

#include "test.hpp"

TTS_CASE("inclusive_scan_complex")
{
  std::vector<float> actual_re{1.0, 2.0, 3.0};
  std::vector<float> actual_im{0.1, 0.2, 0.3};

  std::vector<float> expected_re{1.0, 3.0, 6.0};
  std::vector<float> expected_im{0.1, 0.3, 0.6};

  inclusive_scan_complex(actual_im, actual_re, cmplx_tuple{0.0, 0.0});

  TTS_EQUAL(actual_re, expected_re);
  TTS_EQUAL(actual_im, expected_im);
};
