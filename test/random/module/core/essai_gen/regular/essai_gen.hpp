//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/abs.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/frexp.hpp>
#include <eve/function/sign.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/platform.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <type_traits>
#include <random>

template< eve::real_scalar_value T = double > struct tester_real_distribution
{
  using result_type = T;
  struct param_type
  {
    T a;
    T b;
  };
  struct internal
  {
    std::uniform_int_distribution<int>  uird;
    std::uniform_real_distribution<T> urrd;
    internal(auto ea,  auto eb)
      :    uird(ea, eb),
           urrd(T(0.5), T(1)){};
    void reset() noexcept
    {
      uird.reset();
      urrd.reset();
    };
  };

  tester_real_distribution() : tester_real_distribution(0.0) { }

  tester_real_distribution( T aa, T bb = 1.0 )
  : a(aa),
    b(bb),
    across(eve::sign(a)*eve::sign(b) < 0),
    negative(a < 0),
    posd(initpos()),
    negd(initneg()),
    sd(a, b){};

  explicit tester_real_distribution( const param_type& params )
    : a(params.a),
      b(params.b),
      across(eve::sign(a)*eve::sign(b) > 0),
      negative(a < 0),
      posd(initpos()),
      negd(initneg()),
      sd(a, b){};



  void reset(){
    sd.reset();
    posd.reset();
    negd.reset();
  };

  template< class Generator > result_type operator()( Generator& g )
  {
    auto mant(T(0));
    auto expo(0);
    auto res(T(0));
    do {
      if (!across)
      {
        if (negative)
        {
          expo = negd.uird(g);
          mant = -negd.urrd(g);
        }
        else
        {
          expo = posd.uird(g);
          mant = posd.urrd(g);
        }
      }
      else
      {
        auto sgn = sd(g) <= T(0);
        if (sgn)
        {
          expo = negd.uird(g);
          mant = -negd.urrd(g);
        }
        else
        {
          expo = posd.uird(g);
          mant = posd.urrd(g);
        }
      }

      res = eve::pedantic_(eve::ldexp)(mant, expo);
    } while (res < a || res >=  b);
    return res;
  }

  template< class Generator > result_type operator()( Generator& g, const param_type& params );

  param_type param() const noexcept {
    return {a, b};
  }

  void param( const param_type& params ) noexcept
  {
    a = params.a;
    b = params.b;
  }

  result_type min()  const noexcept {return a; };
  result_type max()  const noexcept {return b; };

private:
  internal initp(auto a,  auto b) noexcept
  {
    auto minexp =  []{
      if constexpr(eve::platform::supports_denormals)
      {
        if( std::is_same_v<T, double > )return   -1074;  else return -148;
      }
      else return  eve::minexponent(eve::as<T>());
    };
    auto minval =  []{
      if constexpr(eve::platform::supports_denormals)
      {
         return eve::mindenormal(eve::as<T>());
      }
      else return  eve::smallestposval(eve::as<T>());
    };
    if (!a) a = minval();
    if (!b) b = -minval();
    auto [ma, ea] = eve::pedantic_(eve::frexp)(a);
    if (ea < minexp()) ea = minexp();
    auto [mb, eb] = eve::pedantic_(eve::frexp)(b);
    if (eb < minexp()) eb = minexp();
    internal dists(ea, eb);
    return dists;
  }


  internal initpos() noexcept
  {
    if (!across)
    {
      if (negative)
      {
        return initp(T(0), T(0));
      }
      else
       {
        return initp(a, b);
       }
    }
    else
    {
      return initp(T(0), b);
    }

  }

  internal initneg() noexcept
  {
    if (!across)
    {
      if (negative)
      {
        return initp(eve::abs(b), eve::abs(a));
      }
      else
       {
        return initp(T(0), T(0));
       }
    }
    else
    {
      return initp(T(0), -a);
    }

  }

  T a;
  T b;
  bool across;
  bool negative;
  internal posd;
  internal negd;
  std::uniform_real_distribution<T> sd;

};




TTS_CASE("wide random check on abs")
{
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 g(rd()); //Standard mersenne_twister_engine seeded with rd()
  auto min = 0.0f; //eve::mindenormal(eve::as(1.0f));
  auto max = eve::smallestposval(eve::as(1.0f));
  std::cout << min <<  " ---- " << max << std::endl;
  tester_real_distribution d(min, max);
  for(int i=0; i <1000 ; ++i)
  {
    auto r = d(g);
    std::cout << std::showpos << r << std::endl;
    if (r < min || r > max) std::cout << r << " zut" << std::endl;
  }
  TTS_EQUAL(0, 0);
}
