//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once
#include <eve/function/abs.hpp>
#include <eve/function/log2.hpp>
#include <eve/function/exp2.hpp>
#include <eve/concept/value.hpp>
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

//     struct internal
//     {
//       std::uniform_int_distribution<int>uird;
//       std::uniform_real_distribution<T> urrd;
//       internal(auto ea,  auto eb)
//         :    uird(0, 10),
//              urrd(T1.0), T(2.0)),
//       {
//       };
//       void reset() noexcept
//       {
//         uird.reset();
//         urrd.reset();
//       };
//     };

    tests_real_distribution() : tests_real_distribution(0.0) { }

    tests_real_distribution( T aa, T bb = 1.0 )
      : a(eve::min(aa, bb)),
        b(eve::max(aa, bb)),
        across(eve::sign(a)*eve::sign(b) < 0),
        negative(a < 0),
        posd(initpos()),
        negd(initneg()),
        sd(a, b){
    };

    explicit tests_real_distribution( const param_type& params )
      : a(params.a),
        b(params.b),
        sd(a, b),
        ird(0, 20){};

    void reset(){
      sd.reset();
      ird.reset
    };

    template< class Generator > result_type operator()( Generator& g )
    {
//       std::cout << "gen a" << a << " b " << b << std::endl;
//       std::cout << "ma   " << mantissa(a) << " mb " << mantissa(b) << std::endl;
//       std::cout << "ea   " << exponent(a) << " eb " << exponent(b) << std::endl;
//       std::cout << "ma - mb " << eve::abs(mantissa(a)- mantissa(b))<< std::endl;
      if(a == b) return a;
      else if((a >= 0 && b <= 1) || b <= 0 && a >= -1) return a+(b-a)*sd(g);
      else if(a >= -1 && b <= 1)  return ((sd(g)*(b-a) > -a) ? -a : b)*sd(g);
      else
      {
        auto i = ird(gen);
        if (a >= 1) // b > a
        {
          auto la =  log2(a);
          auto f =  log2(b)-la;
          auto x = la+f*i*inc(sd(gen));
          return exp2(x);
        }
        else if (b <= -1) // a < b
        {
          auto lb =  log2(abs(b));
          auto f =  log2(abs(a))-lb;
          auto x = lb+f*i*inc(sd(gen));
          return -exp2(x);
        }
        else if (a > 0) // a < 1,  b > a
        {
          if(i == 0)
          {
            auto r = sd(g);
            if (r> a) return r;
            else i = 1;
          }
          auto la =  log2(abs(a));
          auto f =  log2(abs(b))-la;
          auto x = la+f*i*inc(sd(gen));
          return exp2(x);
        }
        else if (b < 0) // a < -1
        {
          if(i == 0)
          {
            auto r = sd(g);
            if (r> -b) return -r;
            else i = 1;
          }
          auto lb =  log2(abs(b));
          auto f =  log2(abs(a))-lb;
          auto x = lb+f*i*inc(sd(gen));
          return -exp2(x);
        }
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

    T a;
    T b;
    std::uniform_real_distribution<T> sd;
    std::uniform_int_distribution<int> ird;
  };




  template<typename T>
  using prng =  std::conditional_t< std::is_floating_point_v<eve::element_type_t<T>>
                                    , eve::tests_real_distribution<eve::element_type_t<T>>
                                    , std::uniform_int_distribution<eve::element_type_t<T>>
                                    >;
}
