//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================

// In this example we will have a look at how many utilities from eve
// come together in writing a non-trivial data oriented computation
//
// We have a set of balls at some altitude z in a gravity field G.
// At altitude 0, lays a floor on which each balls will bounce with some restitution coefficient
// The following code run a discrete simulation of this experiment using SoA vector and algorihms

#include <eve/algo/any_of.hpp>
#include <eve/algo/container/soa_vector.hpp>
#include <eve/algo/transform.hpp>
#include <eve/algo/remove.hpp>
#include <eve/product_type.hpp>
#include <eve/eve.hpp>

#include <chrono>
#include "display.hpp"
#include "test.hpp"

// Ball entity -------------------------------------------------------------------------------------
struct ball : eve::struct_support < ball
                                  , float, float, float, std::int32_t
                                  >
{
  EVE_FORCEINLINE friend decltype(auto) position(eve::like<ball> auto &&self)
  {
    return get<0>(std::forward<decltype(self)>(self));
  }

  EVE_FORCEINLINE friend decltype(auto) speed(eve::like<ball> auto &&self)
  {
    return get<1>(std::forward<decltype(self)>(self));
  }

  EVE_FORCEINLINE friend decltype(auto) elasticity(eve::like<ball> auto &&self)
  {
    return get<2>(std::forward<decltype(self)>(self));
  }

  EVE_FORCEINLINE friend decltype(auto) count(eve::like<ball> auto &&self)
  {
    return get<3>(std::forward<decltype(self)>(self));
  }
};

// Simulation step ---------------------------------
struct update
{
  auto operator()(eve::like<ball> auto const& b) const noexcept
  {
    auto falling = b;
    auto bounced = b;

    // Compute the case of the ball not bouncing
    // Update position
    position(falling) += speed(falling)*dt;

    // Update velocity with gravity
    speed(falling)    -= g*dt;

    // Compute the bounced ball case
    speed(bounced)    *= -elasticity(bounced);
    count(bounced)++;

    // Select the proper one based on position
    return eve::if_else(  count(b) < max_bounce
                        , eve::if_else( position(falling) <= 1e-4, bounced, falling)
                        , b
                        );
  }

  float dt,g;
  int max_bounce;
};

// Test driver ---------------------------------
TTS_CASE("Run a ball simulation")
{
  eve::algo::soa_vector<ball> balls;

  // Some options from the command line ---------------------------------
  auto gravity    = ::tts::arguments.value_or<float>(9.81f, "--gravity");
  auto time       = ::tts::arguments.value_or<int>(100, "--time_step");
  auto max_elast  = ::tts::arguments.value_or<float>(0.9f, "--elasticity");
  auto resolution = ::tts::arguments.value_or<int>(1, "--resolution");
  auto max_bounce = ::tts::arguments.value_or<int>(20, "--bounce");
  auto nb_balls   = ::tts::arguments.value_or<int>(200, "--size");
  auto render_size = 16 * resolution;

  // Generates the balls ---------------------------------
  for(int i=0;i<nb_balls;++i)
    balls.push_back( ball{10.f + (i%6),0., std::min(max_elast,std::rand()/(1.f*RAND_MAX)), 0} );

  int s = 0;
  std::vector<double> times;
  double current_time = 0;

  // Run the simulation once everyone made the maximum amount of bounce ---------------------------
  while( !balls.empty() )
  {
    display screen(202, render_size+2);

    // Surrounding box
    screen.line(0,'=','#');
    for(int l=1;l<render_size+1;++l) screen.line(l,' ','|');
    screen.line(render_size+1,'=','#');

    // Update callable
    update behavior{1.f/time, gravity,max_bounce};

    auto now = std::chrono::steady_clock::now();
    eve::algo::transform_inplace[eve::algo::unroll<2>](balls, behavior);
    auto then = std::chrono::steady_clock::now();

    // Display 200 balls
    for(std::size_t i=0;i<200;i++)
    {
      if(i < balls.size())
        screen.put( 'A' + count(balls.get(i))%27
                  , 1+i
                  , std::max(1, render_size - static_cast<int>(resolution*position(balls.get(i))))
                  );
    }

    auto duration = std::chrono::duration<double,std::nano>(then-now).count();
    times.push_back(duration);

    // Compute Gballs computed per second
    if(times.size() == 100)
    {
      current_time = 0;
      for(auto f: times) current_time += f;
      current_time /= 100;
      times.clear();
    }

    // Remove ball that bounced
    balls.erase ( eve::algo::remove_if(balls, [max_bounce](auto const& b) { return count(b) >= max_bounce; })
                , balls.end()
                );

    // Render
    screen.header() << "\x1B[2J\x1B[H> Step: " << s++ << " - # of balls: " << balls.size()
                    << " @ " << std::setprecision(3) << balls.size()/current_time << " Gballs/s"
                    << " => " << std::setprecision(3) << (balls.size()/current_time)*sizeof(ball)*2 << " GB/s\n";

    if(::tts::verbose_status) std::cout << screen.render();
  }

  TTS_PASS("Simulation completed");
}
