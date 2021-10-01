//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================

//
// This is a set of very basic examples with almost no comments to get
// you a feel for the library.
//
// You can find many details in other files.
//

// --------------------------
// Find a negative number

#include <eve/algo/as_range.hpp>
#include <eve/algo/find.hpp>

int const* find_negative_number(int const* f, int const* l)
{
  return eve::algo::find_if(eve::algo::as_range(f, l), [](auto x) { return x < 0; });
}

// -------------------------
// coordinates conversion

#include <eve/algo/container/soa_vector.hpp>
#include <eve/algo/transform.hpp>
#include <eve/algo/zip.hpp>

#include <eve/function/atan2.hpp>
#include <eve/function/sincos.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/function/zip.hpp>

#include <eve/product_type.hpp>

// See oop on how to have them more meaningful names
using cartesian = kumi::tuple<double, double>;
using polar     = kumi::tuple<double, float>;

struct
{
  EVE_FORCEINLINE auto operator()(eve::like<cartesian> auto c)
  {
    auto [x, y] = c;
    auto r      = eve::sqrt(x * x + y * y);
    auto phi    = eve::atan2(y, x);

    return eve::zip(r, phi);
  }
} inline constexpr convert_cartesian_to_polar;

struct
{
  EVE_FORCEINLINE auto operator()(eve::like<polar> auto p)
  {
    auto [r, angle_f] = p;
    auto angle_d = eve::convert(angle_f, eve::as<double>{});

    auto [sin, cos] = eve::sincos(angle_d);

    return eve::zip(r * cos, r * sin);
  }
} inline constexpr convert_polar_to_cartesian;

void polar_to_cartesian(
  eve::algo::soa_vector<polar> const & pol,
  eve::algo::soa_vector<cartesian>   & cart
)
{
  eve::algo::transform_to[eve::algo::unroll<1>](pol, cart, convert_polar_to_cartesian);
}

void cartesian_to_polar(
  eve::algo::soa_vector<cartesian> const & cart,
  eve::algo::soa_vector<polar>           & pol
)
{
  eve::algo::transform_to[eve::algo::unroll<1>](cart, pol, convert_cartesian_to_polar);
}

// Same function but if you use std::vectors.
// This is a bit less efficient

void polar_to_cartesian_vectors(
  std::vector<double> const & radius,
  std::vector<float>  const & angle,
  std::vector<double>       & x,
  std::vector<double>       & y
)
{
  eve::algo::transform_to[eve::algo::unroll<1>][eve::algo::no_aligning]
  (
    eve::algo::zip(radius, angle),
    eve::algo::zip(x, y),
    convert_polar_to_cartesian
  );
}

// -------------------------
// remove numbers outside of treshold

#include <eve/algo/remove.hpp>
#include <eve/function/is_even.hpp>

void erase_remove_numbers_outisde_of_treshold(
  std::vector<int>& v, int low, int up)
{
  v.erase(
    eve::algo::remove_if(v, [&](auto x) { return x < low || x > up; }),
    v.end()
  );
}

// --------------------------------------------

#include "test.hpp"

#include <eve/constant/pi.hpp>

#include <vector>

TTS_CASE("find_negative_number")
{
  std::vector<int> v {1, 2, -1, 4};
  int const       *found = find_negative_number(v.data(), v.data() + v.size());
  TTS_EQUAL((found - v.data()), 2);
}

TTS_CASE("polar/cartesian")
{
  float pi = eve::pi(eve::as<float> {});

  eve::algo::soa_vector<polar> pol {
      polar {1, 0},
      polar {2, 0},
      polar {1, pi},
      polar {1, -pi/2},
      polar {5, eve::atan2(3.0f, 4.0f)}};

  eve::algo::soa_vector<cartesian> cart {
    cartesian {1,  0},
    cartesian {2,  0},
    cartesian {-1, 0},
    cartesian {0, -1},
    cartesian {4, 3}
  };

  eve::algo::soa_vector<cartesian> actual_cart(5u);
  polar_to_cartesian(pol, actual_cart);

  for (std::size_t i = 0; i < cart.size(); ++i)
  {
    auto [ex, ey] = cart.get(i);
    auto [ax, ay] = actual_cart.get(i);
    TTS_RELATIVE_EQUAL(ex, ax, 0.00001);
    TTS_RELATIVE_EQUAL(ey, ay, 0.00001);
  }

  eve::algo::soa_vector<polar> actual_pol(5u);
  cartesian_to_polar(cart, actual_pol);

  for (std::size_t i = 0; i < cart.size(); ++i)
  {
    auto [er, ephi] = pol.get(i);
    auto [ar, aphi] = actual_pol.get(i);
    TTS_RELATIVE_EQUAL(er,     ar, 0.00001);
    TTS_RELATIVE_EQUAL(ephi, aphi, 0.00001);
  }
}

TTS_CASE("polar_to_cartesian, vectors")
{
  float pi = eve::pi(eve::as<float> {});

  std::vector<double> radius {1, 2, 1, 5};
  std::vector<float>  angle  {0, 0, pi, eve::atan2(3.0f, 4.0f)};

  std::vector<double> expected_x = {1, 2, -1, 4};
  std::vector<double> expected_y = {0, 0,  0, 3};

  std::vector<double> actual_x(4u);
  std::vector<double> actual_y(4u);

  polar_to_cartesian_vectors(radius, angle, actual_x, actual_y);

  for (std::size_t i = 0; i < expected_x.size(); ++i)
  {
    TTS_RELATIVE_EQUAL(expected_x[i], actual_x[i], 0.00001);
    TTS_RELATIVE_EQUAL(expected_y[i], actual_y[i], 0.00001);
  }
}

TTS_CASE("remove_numbers_outisde_of_treshold")
{
  std::vector<int> in      {-1, 5, 2, -3, 10, 1, -18};
  std::vector<int> expected{5, 2, 1};

  erase_remove_numbers_outisde_of_treshold(in, 0, 9);

  TTS_EQUAL(expected, in);
}
