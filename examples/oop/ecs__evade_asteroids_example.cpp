//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================

// FIX-#984: This example is not done yet. Maybe I took a too complicated problem.
//
// In this example we will have a look at how many utilities from eve
// come together in writing an entity-componet system.
//
// This is only a small part of a complete game.
//
// NOTE: we don't know the first thing about writing video games, so we probably doing
//       it all wrong. The main idea is to show SOA + vectorization in action.
//
// Problem is:
//   we have a player, a circle with a fixed radius
//   we have asteroids flying around
//   asteroids move with a given speed
//   if a player hits an asteroid, game over
//   asteroids cannot hit each other.

#include <eve/algo/container/soa_vector.hpp>
#include <eve/eve.hpp>
#include <eve/product_type.hpp>

#include <eve/algo/any_of.hpp>
#include <eve/algo/transform.hpp>
#include <eve/algo/remove.hpp>

// Geometry ---------------------------------

namespace geometry
{
  struct vec2D : eve::struct_support<vec2D, std::int32_t, std::int32_t>
  {
    EVE_FORCEINLINE friend decltype(auto) x(eve::like<vec2D> auto &&self)
    {
      return get<0>(std::forward<decltype(self)>(self));
    }

    EVE_FORCEINLINE friend decltype(auto) y(eve::like<vec2D> auto &&self)
    {
      return get<1>(std::forward<decltype(self)>(self));
    }
  };

  struct point2D : eve::struct_support<point2D, std::int32_t, std::int32_t>
  {
    EVE_FORCEINLINE friend decltype(auto) x(eve::like<point2D> auto &&self)
    {
      return get<0>(std::forward<decltype(self)>(self));
    }

    EVE_FORCEINLINE friend decltype(auto) y(eve::like<point2D> auto &&self)
    {
      return get<1>(std::forward<decltype(self)>(self));
    }

    EVE_FORCEINLINE friend auto& operator+=(eve::like<point2D> auto& self, eve::like<vec2D> auto vec)
    {
      x(self) += x(vec);
      y(self) += y(vec);
      return self;
    }

    EVE_FORCEINLINE friend auto operator+(eve::like<point2D> auto a, eve::like<vec2D> auto vec)
    {
      a += vec;
      return a;
    }

    EVE_FORCEINLINE friend auto operator+(eve::like<vec2D> auto vec, eve::like<point2D> auto a)
    {
      return a + vec;
    }
  };

  struct circle2D : eve::struct_support<circle2D, point2D, std::int32_t>
  {
    EVE_FORCEINLINE friend decltype(auto) center(eve::like<circle2D> auto &&self)
    {
      return get<0>(std::forward<decltype(self)>(self));
    }

    EVE_FORCEINLINE friend decltype(auto) radius(eve::like<circle2D> auto &&self)
    {
      return get<1>(std::forward<decltype(self)>(self));
    }
  };

  // Declare as an object so that we don't have to worry about lambdas
  struct
  {
    EVE_FORCEINLINE auto operator()(eve::like<point2D> auto a, eve::like<point2D> auto b) const
    {
      // There might be a better way to do it that I just don't know
      auto x_distance = x(a) - x(b);
      auto y_distance = y(a) - y(b);
      return x_distance * x_distance + y_distance * y_distance;
    }
  } inline constexpr distance_square;

  struct
  {
    EVE_FORCEINLINE auto operator()(eve::like<circle2D> auto a, eve::like<circle2D> auto b) const
    {
      auto dist_square  = distance_square(center(a), center(b));
      auto ra_rb        = radius(a) + radius(b);
      auto ra_rb_square = ra_rb * ra_rb;
      return ra_rb_square > dist_square;
    }
  } inline constexpr circles_intersect;
}

// Game ---------------------------------

constexpr int player_radius = 50;
constexpr int x_max         = 20000;
constexpr int y_max         = 10000;

constexpr int garbage_collect_each_steps = 100;


constexpr geometry::point2D center_field {x_max / 2, y_max / 2};

struct game_object : eve::struct_support<game_object, geometry::circle2D, geometry::vec2D>
{
  EVE_FORCEINLINE friend decltype(auto) circle(eve::like<game_object> auto &&self)
  {
    return get<0>(std::forward<decltype(self)>(self));
  }

  EVE_FORCEINLINE friend decltype(auto) speed(eve::like<game_object> auto &&self)
  {
    return get<1>(std::forward<decltype(self)>(self));
  }
};

struct
{
  EVE_FORCEINLINE auto operator()(eve::like<game_object> auto obj) const
  {
    center(circle(obj));
    return obj;
  }
} inline constexpr move_game_object;

struct game
{
  game_object player {center_field, player_radius, geometry::vec2D{0, 0}};

  eve::algo::soa_vector<game_object> asteroids;

  int laps_to_garbage_collect{garbage_collect_each_steps};

  bool time_step()
  {
    move_game_object(player);
    eve::algo::transform_inplace(asteroids, move_game_object);

    // Assume that the time loop/speeds are small enough that collision
    // cannot happen in between.
    if (is_game_over())
    {
      // report game over
      return false;
    }

    garbage_collect();
    return true;
  }

  bool is_game_over()
  {
    // Disable unrolling because the predicate is pretty big.
    return eve::algo::any_of[eve::algo::unroll<1>](asteroids, [&](auto ast)
    {
      return geometry::circles_intersect(circle(ast), circle(player));
    });
  }

  void garbage_collect()
  {
    if (laps_to_garbage_collect)
    {
      --laps_to_garbage_collect;
      return;
    }
    laps_to_garbage_collect = garbage_collect_each_steps;

    eve::algo::remove_if(asteroids, [](auto ast) {
      auto pos = center(circle(ast));
      return x(pos) > x_max || x(pos) < 0 || y(pos) > y_max || y(pos) < 0;
    });
  }
};

// --------------------------------------------

#include "test.hpp"

TTS_CASE("geometry, circle intersect")
{
  geometry::circle2D a {geometry::point2D {0, 0}, 2};
  geometry::circle2D b {geometry::point2D {100, 2}, 2};
  geometry::circle2D c {geometry::point2D {3, 2}, 2};

  TTS_EXPECT_NOT(geometry::circles_intersect(a, b));
  TTS_EXPECT(geometry::circles_intersect(a, c));
}

TTS_CASE("geometry, point + vec")
{
  geometry::point2D a   {0, 0};
  geometry::vec2D   vec {1, 0};
  a += vec;
  TTS_EQUAL(a, (geometry::point2D{1, 0}));
  a = a + vec;
  TTS_EQUAL(a, (geometry::point2D{2, 0}));
  a = vec + a;
  TTS_EQUAL(a, (geometry::point2D{3, 0}));
}
