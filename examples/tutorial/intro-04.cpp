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
    auto rho    = std::hypot(x, y);
    auto theta  = std::atan2(y, x);
    return { rho, theta };
  }
}
//! [scalar-udt]

//! [simd-udt-adapt]
// Opt-in for eve::product_type
#include <eve/product_type.hpp>

template<>
struct eve::is_product_type<adapt::polar_coords> : std::true_type
{};

// Standard Structured Bindings adaptation
namespace adapt
{
  template<std::size_t I> constexpr float& get( polar_coords& p) noexcept
  {
          if constexpr(I==0) return p.rho;
    else  if constexpr(I==1) return p.theta;
  }

  template<std::size_t I> constexpr float get( polar_coords const& p) noexcept
  {
          if constexpr(I==0) return p.rho;
    else  if constexpr(I==1) return p.theta;
  }
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
#include <eve/function/hypot.hpp>
#include <eve/function/atan2.hpp>

namespace adapt
{
  eve::wide<polar_coords> to_polar(eve::wide<float> x, eve::wide<float> y)
  {
    auto rho    = eve::hypot(x, y);
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
#include <eve/function/hypot.hpp>
#include <eve/function/atan2.hpp>

namespace udt
{
  auto to_polar(eve::wide<float> x, eve::wide<float> y)
  {
    auto rho    = eve::hypot(x, y);
    auto theta  = eve::atan2(y, x);
    return eve::wide<kumi::tuple<float,float>>{ rho, theta };
  }

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
    eve::algo::soa_vector<cartesian_coords> outs(ins.size());

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

namespace check
{
  auto to_polar(std::vector<float> const& x, std::vector<float> const& y)
  {
    std::vector<float> rho(x.size()), theta(x.size());

    for(std::size_t i=0;i<x.size();++i)
    {
      auto [r,t] = adapt::to_polar(x[i],y[i]);
      rho[i]    = r;
      theta[i]  = t;
    }

    return std::make_tuple(rho, theta);
  }
}

#include "test.hpp"

TTS_CASE("Check udt::to_polar")
{
  std::vector<float> xs{1,0.8,0.6,0.4,0.2,0.1,-0.1,-0.2,-0.4,-0.6,-0.8,-1   };
  std::vector<float> ys{0,0.1,0.2,0.4,0.6,0.8,   1, 0.8, 0.6, 0.4, 0.2, 0.1 };

  auto [scalar_rho, scalar_theta] = check::to_polar(xs,ys);
  auto outs = udt::to_polar(xs,ys);

  for(std::size_t i = 0; i < outs.size();++i)
  {
    auto out = outs.get(i);
    TTS_ULP_EQUAL(scalar_rho[i]   , get<0>(out) , 0.5);
    TTS_ULP_EQUAL(scalar_theta[i] , get<1>(out) , 0.5);
  }
};