//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================

//
// Writing custom cmplx numbers.
//
// NOTE: we will definetly have a proper `eve::complex` but we don't have one yet.
//
// This example will demonstrate the basics of how you can write code that looks like
// it uses objects but actally utilizes parallel arrays and simd under the hood.
//
// Related termins are: SOA (structure of arrays) and ECS - entity component system.
//
// NOTE:
//   You might also want to have a look at:
//   examples/algorithms/using_existing/inclusive_scan_zip__using_zip_with_algorithms.cpp
//   where we don't declare an object for complex numbers and just deal with tuples.
//

#include <eve/eve.hpp>
#include <eve/module/algo.hpp>
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/traits/product_type.hpp>

#include <optional>
#include <vector>


// Ideally we would want to just be able to reflect on any struct, split it into members
// and then bring them in any derived class we want.
//
// However, that's not doable in modern C++.
// So your struct has to expose some reflection mechanism.
//
// On forceinline: time and time again we stumble apon the compiler not inlining simd code very well.
// So we recommend writing EVE_FORCEINLINE on all functions that are not the outside loop.
//

struct cmplx : eve::struct_support<cmplx, float, float>
{
  // Instead of normal getters/setters we suggest to write ADL friend functions.
  // This will also be accessible for `eve::wide<cmplx>`.
  // `eve::like` concept will make sure that this won't kick in for anything that did not opt in.

  EVE_FORCEINLINE friend decltype(auto) re(eve::like<cmplx> auto&& self)
  {
    return get<0>(std::forward<decltype(self)>(self));
  }

  EVE_FORCEINLINE friend decltype(auto) im(eve::like<cmplx> auto&& self)
  {
    return get<1>(std::forward<decltype(self)>(self));
  }

  // Operators ----------------------

  // For operators opt in just use the same concept instead of type itself.
  // Member wise equality for wide is generated automatically.
  // For scalar we have it because of inheriting from kumi::tuple.

  // Opt out of the </<=/>/>= generation.
  // You can also specialize eve::supports_ordering<cmplx>
  //
  // The operator+/operator- will be generated from operator+=/operator-=,
  // however -= will not be generated from += and unary -, we want to tap into a special instruction optimization
  using eve_disable_ordering = void;

  EVE_FORCEINLINE friend auto& operator+=(eve::like<cmplx> auto& self, eve::like<cmplx> auto other)
  {
    re(self) += re(other);
    im(self) += im(other);
    return self;
  }

  EVE_FORCEINLINE friend auto operator-(eve::like<cmplx> auto self)
  {
    re(self) = -re(self);
    im(self) = -im(self);
    return self;
  }

  EVE_FORCEINLINE friend auto& operator-=(eve::like<cmplx> auto& self, eve::like<cmplx> auto other)
  {
    re(self) -= re(other);
    im(self) -= im(other);
    return self;
  }

  // The ostream operator you don't need to customise for wide, it will do the right thing.
  friend std::ostream& operator<<(std::ostream& out, cmplx self)
  {
    return out << '(' << re(self) << " + " << im(self) << "i)";
  }

  // Custoizing eve functions ----

  // All eve callables are customiseable through tagged dispatch.
  // We find it useful but you do it at your own risk, we are quite likely to break you.
  // Alternatively - use your own functions.

  EVE_FORCEINLINE friend auto tagged_dispatch( eve::tag::abs_, eve::like<cmplx> auto self)
  {
    return eve::hypot(re(self), im(self));
  }
};

// ------------------
// Using

// Now we can use this complex with soa_vector and algorithms.
// The default plus and eve::zero will just work.
void inclusive_scan_complex(eve::algo::soa_vector<cmplx>& v, cmplx init)
{
  eve::algo::inclusive_scan_inplace(v, init);
}

// We can also zip verctors of individual fields and interpert that a a range complex.
// It is slighlty less efficient than using `soa_vector` but maybe you have the parts from somewhere else.
void inclusive_scan_complex_components(std::vector<float>& re_parts, std::vector<float>& im_parts, cmplx init)
{
  auto rng = eve::views::convert(
    eve::views::zip(re_parts, im_parts),  // zips as a range of `kumi::tuple<float, float>`
    eve::as<cmplx>{}                     // convert to a range of `cmplx`
  );
  eve::algo::inclusive_scan_inplace(rng, init);
}

// --------------------------------------------

#include "test.hpp"

#include <sstream>

bool rougly_equal(eve::like<cmplx> auto x, eve::like<cmplx> auto y)
{
  auto re_test = eve::abs(re(x) - re(y)) < 0.00001;
  auto im_test = eve::abs(im(x) - im(y)) < 0.00001;
  return eve::all(re_test && im_test);
}

TTS_CASE("wide works")
{
  // +
  {
    eve::wide<cmplx> x {cmplx {0.0, 0.1}};
    eve::wide<cmplx> y {cmplx {0.1, 0.0}};

    eve::wide<cmplx> expected {cmplx {0.1, 0.1}};
    eve::wide<cmplx> actual = x + y;
    TTS_EXPECT(rougly_equal(expected, actual));
  }

  // negate
  {
    eve::wide<cmplx> x {cmplx {0.0, 0.1}};

    eve::wide<cmplx> expected {cmplx {0.0, -0.1}};
    eve::wide<cmplx> actual = -x;
    TTS_EXPECT(rougly_equal(expected, actual));
  }

  // -
  {
    eve::wide<cmplx> x {cmplx {0.0, 0.1}};
    eve::wide<cmplx> y {cmplx {0.1, 0.0}};

    eve::wide<cmplx> expected {cmplx {-0.1, 0.1}};
    eve::wide<cmplx> actual = x - y;
    TTS_EXPECT(rougly_equal(expected, actual));
  }

  // abs
  {
    eve::wide<cmplx> x{cmplx{3.0, 4.0}};
    eve::wide<float> expected{5.0};
    eve::wide<float> actual = eve::abs(x);
    TTS_RELATIVE_EQUAL(expected, actual, 0.00001);
  }
};

TTS_CASE("scalar works")
{
  // +
  {
    cmplx x {0.0, 0.1};
    cmplx y {0.1, 0.0};

    cmplx expected {0.1, 0.1};
    cmplx actual = x + y;
    TTS_EXPECT(rougly_equal(expected, actual));
  }

  // negate
  {
    cmplx x {0.0, 0.1};

    cmplx expected {0.0, -0.1};
    cmplx actual = -x;
    TTS_EXPECT(rougly_equal(expected, actual));
  }

  // -
  {
    cmplx x {0.0, 0.1};
    cmplx y {0.1, 0.0};

    cmplx expected {-0.1, 0.1};
    cmplx actual = x - y;
    TTS_EXPECT(rougly_equal(expected, actual));
  }

  // abs
  {
    cmplx x{3.0, 4.0};
    float expected{5.0};
    float actual = eve::abs(x);
    TTS_RELATIVE_EQUAL(expected, actual, 0.00001);
  }
};

TTS_CASE("printing")
{
  std::stringstream s;
  eve::wide<cmplx, eve::fixed<4>> x{
    [](int i, int) { return cmplx{(float)i, -(float)i}; }
  };
  s << x;
  TTS_EQUAL(s.str(), "((0 + -0i), (1 + -1i), (2 + -2i), (3 + -3i))");
};

TTS_CASE("soa_vector scan")
{
  eve::algo::soa_vector<cmplx> actual {
    cmplx{1.0, 0.1},
    cmplx{2.0, 0.2},
    cmplx{3.0, 0.3},
  };
  inclusive_scan_complex(actual, cmplx{0.0, 0.0});
  eve::algo::soa_vector<cmplx> expected {
    cmplx{1.0, 0.1},
    cmplx{3.0, 0.3},
    cmplx{6.0, 0.6},
  };
  TTS_EQUAL(expected, actual);
};

TTS_CASE("components scan")
{
  std::vector<float> actual_re{1.0, 2.0, 3.0};
  std::vector<float> actual_im{0.1, 0.2, 0.3};

  std::vector<float> expected_re{1.0, 3.0, 6.0};
  std::vector<float> expected_im{0.1, 0.3, 0.6};

  inclusive_scan_complex_components(actual_im, actual_re, cmplx{0.0, 0.0});

  TTS_EQUAL(actual_re, expected_re);
  TTS_EQUAL(actual_im, expected_im);
};
