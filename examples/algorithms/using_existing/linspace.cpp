//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright : EVE Contributors & Maintainers
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/module/core.hpp>
#include <eve/algo.hpp>
#include <eve/algo/transform.hpp>
#include <vector>

//
// In this example, we implements the linspace function. linspace is a staple of numeric computation
// that, for a given pair of real [a,b], linspace(r,a,b) fills the range r with values so that
//
//  - the first element of r is equal to a;
//  - the last element of r is equal to b;
//  - all other elements are separated by (b-a)/(s.size()-1)
//
//  Precision is usually the cornerstone of proper linspace implementation. We use eve::lerp
//  to ensure proper accuracy.
//
//  A small set of corner cases exists, and we decided to follow matlab semantic for those.
//
template < eve::algo::relaxed_range R, eve::scalar_value T,  eve::scalar_value U>
R linspace(R& r, T a, U b )
requires( eve::floating_scalar_value<decltype(eve::read(r.begin()))>)
{
  EVE_ASSERT(eve::is_finite(a), "a is not finite");
  EVE_ASSERT(eve::is_finite(b), "b is not finite");

  using elt_t = decltype(eve::read(r.begin()));
  std::ptrdiff_t size = r.end()-r.begin();

  // Empty range needs nothing to be done
  if (size == 0u) return r;
  // Size 1 range is just [b] as per Matlab
  else if (size == 1u)  { *r.begin() = elt_t(b);        return r; }
  // Similar begin and end values simplify to fill
  else if (a == b)      { eve::algo::fill(r, elt_t(a)); return r; }
  else
  {
    // Computes 1/(size-1)
    elt_t step  = eve::rec((elt_t(size - 1)));

    // Make a view over [0 .... size-1]
    auto io     = eve::views::iota_with_step(elt_t{0}, step, size);

    // Compute lerp(a,b, iota[i] * step) for the whole range
    eve::algo::transform_to ( eve::views::zip(io, r)
                            , [a, b](auto i)
                              {
                                return eve::lerp(elt_t(a), elt_t(b), i);
                              }
                            );

    return r;
  }
}

// -----------------------

#include "test.hpp"

TTS_CASE("Test linspace(a,b) - Regular case")
{
  std::vector<float> r1(5);
  std::vector<float> r2{1.0f, 1.5f, 2.0f, 2.5f, 3.0f};
  linspace(r1, 1.0f, 3.0f);

  TTS_ALL_ULP_EQUAL(r1, r2, 0.5);
};

TTS_CASE("Test linspace(a,b) - Corner cases")
{
  std::vector<float> empty;
  linspace(empty,0.f,1.f);
  TTS_EQUAL(empty, std::vector<float>{});

  std::vector<float> single(1);
  linspace(single,0.f,4.2f);
  TTS_EQUAL(single[0], 4.2f);

  std::vector<float> same(32), same_ref(32,17.89f);
  linspace(same,17.89f,17.89f);

  TTS_ALL_ULP_EQUAL(same, same_ref, 0.5);
};
