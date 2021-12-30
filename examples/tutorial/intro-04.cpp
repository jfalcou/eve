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
  struct polar_coords : eve::struct_support<polar_coords,float,float>
  {
    using eve_disable_ordering = void;

    friend decltype(auto) rho(eve::like<polar_coords> auto&& self)
    {
      return get<0>(std::forward<decltype(self)>(self));
    }

    friend decltype(auto) theta(eve::like<polar_coords> auto&& self)
    {
      return get<1>(std::forward<decltype(self)>(self));
    }
  };
}
//! [simd-udt-create]

//! [simd-soa_vector_out]
#include <vector>
#include <eve/algo/container/soa_vector.hpp>
#include <eve/algo/transform.hpp>
#include <eve/views/zip.hpp>

namespace udt
{
  auto to_polar( std::vector<float> const& xs, std::vector<float> const& ys)
  {
    eve::algo::soa_vector<polar_coords> outs(xs.size());

    eve::algo::transform_to ( eve::views::zip(xs, ys), outs
                            , [](auto in) { return to_polar( get<0>(in), get<1>(in) ); }
                            );

    return outs;
  }
}
//! [simd-soa_vector_out]

//! [simd-soa_vector_in]
#include <vector>
#include <eve/algo/container/soa_vector.hpp>
#include <eve/algo/transform.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/sin.hpp>

namespace udt
{
  struct cartesian_coords : eve::struct_support<cartesian_coords,float,float>
  {
    using eve_disable_ordering = void;

    friend decltype(auto) rho(eve::like<cartesian_coords> auto&& self)
    {
      return get<0>(std::forward<decltype(self)>(self));
    }

    friend decltype(auto) theta(eve::like<cartesian_coords> auto&& self)
    {
      return get<1>(std::forward<decltype(self)>(self));
    }
  };

  auto to_cartesian( eve::algo::soa_vector<polar_coords> const& ins)
  {
    eve::algo::soa_vector<cartesian_coords> outs(xs.size());

    eve::algo::transform_to ( ins, outs
                            , [](auto in)
                              {
                                auto r = rho(in);
                                auto t = theta(in);
                                return eve::wide<cartesian_coords>{ r * eve::cos(t), r * eve::sin(t) };
                              }
                            );

    return outs;
  }
}
//! [simd-soa_vector_in]

#include "test.hpp"

TTS_CASE("Check to_polar")
{
  auto [rho,theta] = to_polar(1,1);

  TTS_ULP_EQUAL(rho   , std::sqrt(2.f), 0.5);
  TTS_ULP_EQUAL(theta , 0.78539819f   , 0.5);
};
