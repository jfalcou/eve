//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/constant/half.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/average.hpp>
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
      int nb;
      param_type(T aa, T bb, int nbb) : a(aa),  b(bb), nb(nbb){};

    };

    tests_real_distribution() : tests_real_distribution(0.0, 0.1, 300) { }

    tests_real_distribution( T aa, T bb, int nbb = 300)
      : a(eve::min(aa, bb)),
        b(eve::max(aa, bb)),
        nb(nbb),
        sd(T(0),T(1)),
        ird(0, nb){
    };

    explicit tests_real_distribution( const param_type& params )
      : a(params.a),
        b(params.b),
        nb(params.nb),
        sd(T(0),T(1)),
        ird(0, params.nb){};

    void reset(){
      sd.reset();
      ird.reset();
    };

    template< class Generator > result_type operator()( Generator& gen )
    {
      return (*this)(gen, a, b, nb);
    }

    template< class Generator > result_type operator()( Generator& gen, result_type aa,  result_type bb, int nb)
    {
      result_type res;
      if(aa == bb) return aa;
      else if(bb <= aa+half(as(aa))) res = aa+(bb-aa)*sd(gen);
      else if((aa >= 0 && bb <= 1) || bb <= 0 && aa >= -1) res = aa+(bb-aa)*sd(gen);
      else if(aa >= -1 && bb <= 1)  res =((sd(gen)*(bb-aa) > -aa) ? -aa : bb)*sd(gen);
      else
      {
        auto i = ird(gen);
        if (aa >= 1) // bb > aa
        {
          auto la =  log2(aa);
          auto f =  log2(bb)-la;
          auto rand = sd(gen);
          auto x = la+f*i*rand/nb;
          res = exp2(x);
        }
        else if (bb <= -1) // aa < bb
        {
          auto lb =  log2(abs(bb));
          auto f =  log2(abs(aa))-lb;
          auto x = lb+f*i*inc(sd(gen))/nb;
          res =-exp2(x);
        }
        else if (aa >= 0) // aa < 1,  bb > aa
        {
          if(i == 0)
          {
            auto r = sd(gen);
            if (r> aa) res =r;
            else i = 1;
          }
          else return (*this)(gen, one(as(bb)), bb, nb);
        }
        else if (bb <= 0) // aa < -1
        {
          if(i == 0)
          {
            auto r = sd(gen);
            if (r> -bb) res =-r;
            else i = 1;
          }
          else return (*this)(gen, mone(as(bb)), aa, nb);
        }
        else // aa < 0 bb > 0
        {
          auto choice = sd(gen)*average(bb, -aa) > bb/2;
          if (choice)
          {
            return (*this)(gen, zero(as(bb)), bb, nb);
          }
          else
          {
            return (*this)(gen, aa, zero(as(aa)), nb);
          }

        }
      }
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

    T a;
    T b;
    int nb;
    std::uniform_real_distribution<T> sd;
    std::uniform_int_distribution<int> ird;
  };




  template<typename T>
  using prng =  std::conditional_t< std::is_floating_point_v<eve::element_type_t<T>>
                                    , eve::tests_real_distribution<eve::element_type_t<T>>
                                    , std::uniform_int_distribution<eve::element_type_t<T>>
                                    >;
}
