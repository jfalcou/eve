//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/function/abs.hpp>
#include <eve/function/pedantic/ldexp.hpp>
#include <eve/function/pedantic/frexp.hpp>
#include <eve/function/mantissa.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/sign.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/minexponent.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/platform.hpp>
#include <type_traits>
#include <random>

namespace eve
{
  template< eve::real_scalar_value T = double > struct tests_real_distribution
  {
    using result_type = T;
    struct param_type
    {
      T a;
      T b;
      param_type(T aa, T bb) : a(aa),  b(bb){};

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

    tests_real_distribution() : tests_real_distribution(0.0) { }

    tests_real_distribution( T aa, T bb = 1.0 )
      : a(aa),
        b(bb),
        across(eve::sign(a)*eve::sign(b) < 0),
        negative(a < 0),
        posd(initpos()),
        negd(initneg()),
        sd(a, b){};

    explicit tests_real_distribution( const param_type& params )
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
//       std::cout << "gen a" << a << " b " << b << std::endl;
//       std::cout << "ma   " << mantissa(a) << " mb " << mantissa(b) << std::endl;
//       std::cout << "ea   " << exponent(a) << " eb " << exponent(b) << std::endl;
//       std::cout << "ma - mb " << eve::abs(mantissa(a)- mantissa(b))<< std::endl;
      if(std::abs(a-b) < half(as(a))) return sd(g);
      auto mant(T(0));
      auto expo(0);
      auto res(T(0));
      int i = 0;
      do {
        ++i;
        if(i > 100)
        {

          std::cout << "raté " << std::endl;
          exit(1);
        }

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

        res = eve::pedantic(eve::ldexp)(mant, expo);
        std::cout << "icitte " << i << "a "<< a << " b " << b << "res "<< res << std::endl;
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
      auto [ma, ea] = eve::pedantic(eve::frexp)(a);
      if (ea < minexp()) ea = minexp();
      auto [mb, eb] = eve::pedantic(eve::frexp)(b);
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

  template<typename T>
  using prng =  std::conditional_t< std::is_floating_point_v<eve::element_type_t<T>>
                                    , eve::tests_real_distribution<eve::element_type_t<T>>
                                    , std::uniform_int_distribution<eve::element_type_t<T>>
                                    >;
}
