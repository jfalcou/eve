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
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/saturated/abs.hpp>
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

    tests_real_distribution() : tests_real_distribution(0.0, 0.1, 10) { }

    tests_real_distribution( T aa, T bb, int nbb = 10)
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

    template< class Generator > result_type operator()( Generator& gen, result_type aa, result_type bb, int nb)
    {
      result_type res;
      if(aa == bb) res = aa;
      else if(bb <= aa+half(as(aa))) res = aa+(bb-aa)*sd(gen);
      else if((aa >= 0 && bb <= 1) || bb <= 0 && aa >= -1) res = aa+(bb-aa)*sd(gen);
      else if(aa >= -1 && bb <= 1)  res =((sd(gen)*(bb-aa) > -aa) ? -aa : bb)*sd(gen);
      else
      {
        auto i = ird(gen);
        std::cout << " i = " << i << " <= " << nb << std::endl;
        if (aa >= 1) // bb > aa
        {
          auto la =  log2(aa);
          auto f =  log2(bb)-la;
          auto rand = sd(gen);
          auto x = la+f*(i-1+rand)/nb;
          res = exp2(x);
        }
        else if (bb <= -1) // aa < bb
        {
           res = -(*this)(gen, abs(bb), abs(aa), nb);
        }
        else if (aa >= 0) // aa < 1,  bb > aa
        {
          if(i == 0)
          {
            auto r = sd(gen);
            if (r> aa) res =r;
            else i = 1;
          }
          else res = (*this)(gen, one(as(bb)), bb, nb);
        }
        else if (bb <= 0) // aa < -1
        {
          if(i == 0)
          {
            auto r = sd(gen);
            if (r> -bb) res =-r;
            else i = 1;
          }
          else res = (*this)(gen, mone(as(bb)), aa, nb);
        }
        else // aa < 0 bb > 0
        {
          auto choice = sd(gen)*average(bb, -aa) > bb/2;
          if (choice)
          {
            res = (*this)(gen, zero(as(bb)), bb, nb);
          }
          else
          {
            res = (*this)(gen, aa, zero(as(aa)), nb);
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

  /////////////////////////////////////////////////////////////////////
  // integral case

  template< eve::real_scalar_value T = std::int32_t > struct tests_integral_distribution
  {
    using result_type = T;
    struct param_type
    {
      T a;
      T b;
      int nb;
      param_type(T aa, T bb, int nbb) : a(aa),  b(bb), nb(nbb){};

    };

    tests_integral_distribution() : tests_integral_distribution(valmin(as<T>()), valmax(as<T>())) { }

    tests_integral_distribution( T aa, T bb, int nbb = sizeof(element_type_t<T>))
      : a(eve::min(aa, bb)),
        b(eve::max(aa, bb)),
        nb(nbb),
        toto(double(a), double(b), nb)
//         sd(0.0f, 1.0f),
//         ird(1, nb)
    {
    };

    explicit tests_integral_distribution( const param_type& params )
      : a(params.a),
        b(params.b),
        nb(params.nb),
        toto(double(a), double(b), nb)
//        sd(0.0f, 1.0f),
//        ird(1, params.nb)
    {};

    void reset(){
      toto.reset();
//       sd.reset();
//       ird.reset();
    };

    template< class Generator > result_type operator()( Generator& gen )
    {
      return (*this)(gen, a, b, nb);
    }

    template< class Generator > result_type operator()( Generator& gen, result_type aa, result_type bb, int nb)
    {
      return round(toto(gen));
   //    auto l2 = [](auto x){return log2(inc(double(x)));   };
//       auto e2 = [](auto x){return dec(T(exp2(round(x)))); };

//       result_type res;
//       if(aa == bb) res = aa;
//       else
//       {
//         auto i = ird(gen);
//         if (aa >= 0) // bb > aa
//         {
//           auto la =  l2(aa);
//           auto lb =  l2(bb);
//           auto f =   lb-la;
//           auto rand = sd(gen);
//           auto x = la+f*(i-1+rand)/nb;
//           res = e2(x);
//         }
//         else if (bb <= 0) // aa < bb
//         {
//           res = -(*this)(gen, saturated(abs)(bb), saturated(abs)(aa), nb);
//         }
//         else // aa < 0 bb > 0
//         {
//           auto choice = sd(gen)*average(bb, T(saturated(abs)(aa))) <  T(bb/2);
//           if (choice)
//           {
//             res = (*this)(gen, zero(as(bb)), bb, nb);
//           }
//           else
//           {
//             res = (*this)(gen, aa, zero(as(aa)), nb);
//           }

//         }
//       }
//       return res;
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
    tests_real_distribution <double > toto;
//    std::uniform_real_distribution<float> sd;
    //   std::uniform_int_distribution<int> ird;
  };

  template<typename T>
  using prng =  std::conditional_t< std::is_floating_point_v<eve::element_type_t<T>>
                                    , eve::tests_real_distribution<eve::element_type_t<T>>
                                    , eve::tests_integral_distribution<eve::element_type_t<T>>
                                    >;
}
