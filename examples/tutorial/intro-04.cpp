//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
//! [empty]

//! [empty]

//! [scalar-udt]
#include <cmath>

namespace adapt
{
  struct polar_coords
  {
    float rho, theta;
  };

  polar_coords to_polar(float x, float y)
  {
    auto rho    = std::sqrt(x * x + y * y);
    auto theta  = std::atan2(y, x);
    return { rho, theta };
  }
}
//! [scalar-udt]

//! [simd-udt-adapt]
// Opt-in for eve::product_type
template<>
struct eve::is_product_type<adapt::polar_coords> : std::true_type
{};

// Standard Structured Bindings adaptation
template<std::size_t I> constexpr float& get( adapt::polar_coords& p) noexcept
{
        if constexpr(I==0) return p.rho;
  else  if constexpr(I==1) return p.theta;
}

template<std::size_t I> constexpr float get( adapt::polar_coords const& p) noexcept
{
        if constexpr(I==0) return p.rho;
  else  if constexpr(I==1) return p.theta;
}

template<>
struct std::tuple_size<adapt::polar_coords>  : std::integral_constant<std::size_t, 2>
{};

template<std::size_t I>
struct std::tuple_element<I,adapt::polar_coords>
{
  using type = float;
};
//! [simd-udt-adapt]

//! [simd-udt-to_polar]
namespace adapt
{
  eve::wide<polar_coords> to_polar(eve::wide<float> x, eve::wide<float> y)
  {
    auto rho    = eve::sqrt(x * x + y * y);
    auto theta  = eve::atan2(y, x);
    return eve::wide<polar_coords>{ rho, theta };
  }
}
//! [simd-udt-to_polar]

//! [simd-udt-create]
#include <eve/product_type.hpp>

namespace udt
{
  struct polar_coordinates : eve::struct_support<polar_coordinates,float,float>
  {
    using eve_disable_ordering = void;

    friend decltype(auto) rho(eve::like<polar_coordinates> auto&& self)
    {
      return get<0>(std::forward<decltype(self)>(self));
    }

    friend decltype(auto) theta(eve::like<polar_coordinates> auto&& self)
    {
      return get<1>(std::forward<decltype(self)>(self));
    }
  };
}
//! [simd-udt-create]

//! [simd-udt-to_polar-new]
namespace udt
{
  eve::wide<polar_coordinates> to_polar(eve::wide<float> x, eve::wide<float> y)
  {
    auto rho    = eve::sqrt(x * x + y * y);
    auto theta  = eve::atan2(y, x);
    return eve::wide<polar_coordinates>{ rho, theta };
  }
}
//! [simd-udt-to_polar-new]

#include "test.hpp"

TTS_CASE("Check to_polar")
{
  auto [rho,theta] = to_polar(1,1);

  TTS_ULP_EQUAL(rho   , std::sqrt(2.f), 0.5);
  TTS_ULP_EQUAL(theta , 0.78539819f   , 0.5);
};
