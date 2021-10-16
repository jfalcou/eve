//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/mhalf.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/sqrt_2.hpp>
#include <eve/constant/sqrt_2o_2.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/all.hpp>
#include <eve/function/cospi.hpp>
#include <eve/function/erfc.hpp>
#include <eve/function/erfc_inv.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/is_finite.hpp>
#include <eve/function/is_gtz.hpp>
#include <eve/function/log.hpp>
#include <eve/function/log1p.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/rec.hpp>
#include <eve/function/sqr.hpp>
#include <eve/function/sqrt.hpp>
#include <eve/module/real/core/detail/generic/horn.hpp>
#include <eve/module/real/proba/detail/attributes.hpp>
#include <eve/module/real/proba/detail/urg01.hpp>
#include <eve/platform.hpp>

#include <concepts>
#include <type_traits>

namespace eve
{

 namespace detail
 {
   template < typename G, typename R> EVE_FORCEINLINE
   auto box_muller(G & gen, as<R> const & ) noexcept
   {
     auto x1 = detail::urg01(gen, as<R>());
     auto x2 = detail::urg01(gen, as<R>());
     auto rho = eve::sqrt(-2*eve::log1p(-x1));
     return rho*half_circle(cospi)(2*x2);
   }
 }

 template < typename T, typename U, typename Internal = T>
  struct normal_distribution{};

  template < floating_real_value T, floating_real_value U>
  requires  compatible_values<T, U>
  struct normal_distribution<T, U>
  {
    using is_distribution_t = void;
    using m_type = T;
    using s_type = U;
    using value_type = common_compatible_t<T, U>;
    using parameters = struct { value_type m; value_type s; };

    normal_distribution(T m_,  U s_)
      : m(m_), s(s_)
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    normal_distribution(parameters const & p)
      : m(p.m), s(p.s)
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      return fma(m, detail::box_muller(gen, as<R>()), s);
    }

    parameters params() const noexcept
    {
      return { .m = m, .s = s };
    }

    m_type m;
    s_type s;
  };

  template < floating_real_value U>
  struct normal_distribution<callable_zero_, U>
  {
    using is_distribution_t = void;
    using m_type = callable_zero_;
    using s_type = U;
    using value_type = U;
    using parameters = struct { callable_zero_ m;  value_type s;};

    normal_distribution(callable_zero_ const&, U s_)
      : s(s_)
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
    }

    normal_distribution(parameters const & p)
      : s(p.s)
    {
      EVE_ASSERT(all(is_gtz(s) && is_finite(s)), "s must be strictly positive and finite");
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {

      return detail::box_muller(gen, as<R>())*s;
    }

    parameters params() noexcept
    {
      return { .m = zero, .s = s };
    }

    s_type s;
  };

  template < floating_real_value T>
  struct normal_distribution<T, callable_one_>
  {
    using is_distribution_t = void;
    using m_type = T;
    using s_type = decltype(eve::one);
    using value_type = T;
    using parameters = struct { value_type m;  callable_one_ s;};

    normal_distribution(T m_, callable_one_ const &)
      : m(m_)
    {
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    normal_distribution(parameters const & p)
      : m(p.m)
    {
      EVE_ASSERT(all(is_finite(m)), "m must be finite");
    }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      return detail::box_muller(gen, as<R>())+m;
    }

    parameters params() noexcept
    {
      return { .m = m, .s = one };
    }

    m_type m;
  };

  template<typename T, typename U>  normal_distribution(T,U) -> normal_distribution<T,U>;

  template < floating_real_value T>
  struct normal_distribution<callable_zero_, callable_one_, T>
  {
    using is_distribution_t = void;
    using m_type = callable_zero_;
    using s_type = callable_one_;
    using value_type = T;
    using parameters = struct { callable_zero_ m;  callable_one_ s;};


    normal_distribution(parameters const & ) { }

    template < typename G, typename R = value_type> auto operator()(G & gen, as<R> const & )
      requires scalar_value<value_type>
    {
      return detail::box_muller(gen, as<R>());
    }

    parameters params() noexcept
    {
      return { .m = zero, .s = one };
    }

    constexpr normal_distribution( as<T> const&) {}
  };


  template<typename T>  normal_distribution(as<T> const&) -> normal_distribution<callable_zero_, callable_one_, T>;

  template<floating_real_value T>
  inline constexpr auto normal_distribution_01 = normal_distribution<callable_zero_, callable_one_, T>(as<T>{});

  namespace detail
  {
    //////////////////////////////////////////////////////
    /// cdf
   template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                                 , normal_distribution<T, U, I> const & d
                                 , V const &x ) noexcept
    {
      if constexpr(floating_value<T> && floating_value<U>)
        return  half(as(x))*erfc(sqrt_2o_2(as(x))*((d.m-x)/d.s));
      else if constexpr(std::same_as<T, callable_zero_> && floating_value<U>)
        return  half(as(x))*erfc(sqrt_2o_2(as(x))*(-x/d.s));
      else if constexpr(std::same_as<U, callable_one_> && floating_value<T>)
        return  half(as(x))*erfc(sqrt_2o_2(as(x))*((d.m-x)));
      else
        return  half(as(x))*erfc(sqrt_2o_2(as(x))*(-x));
    }

   template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto cdf_(EVE_SUPPORTS(cpu_)
                              , raw_type const &
                              , normal_distribution<T, U, I> const &d
                              , V const &x ) noexcept
    {
      using elt_t =  element_type_t<T>;
      if constexpr(std::same_as<elt_t, float>)
      {
        auto eval =  [](auto l)
          {
            auto al = eve::abs(l);
            auto k = rec(fma(T(0.2316419f),al,one(as(l))));
            auto w = horn<T
            , 0x3ea385fa   //           0.31938153f
            , 0xbeb68f87   //           -0.356563782f,
            , 0x3fe40778   //           1.781477937f,
            , 0xbfe91eea   //           -1.821255978f,
            , 0x3faa466f   //           1.330274429f,

            >(k);
            auto invsqrt_2pi = T(0.39894228040143267793994605993438186847585863116493);
            w*=k*invsqrt_2pi*eve::exp(-sqr(l)*half(as(l)));
            return if_else(is_gtz(l),oneminus(w),w);
          };
        if constexpr(floating_value<T> && floating_value<U>)
          return  eval((x-d.m)/d.s);
        else if constexpr(std::same_as<T, callable_zero_> && floating_value<U>)
          return  eval(x/d.s);
        else if constexpr(std::same_as<U, callable_one_> && floating_value<T>)
          return eval(x-d.m);
        else
          return eval(x);
      }
      else return cdf(d, x);
    }

    //////////////////////////////////////////////////////
    /// pdf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto pdf_(EVE_SUPPORTS(cpu_)
                                 , normal_distribution<T, U, I> const & d
                                 , V const &x ) noexcept
    {
      auto invsqrt_2pi = V(0.39894228040143267793994605993438186847585863116493);
      if constexpr(floating_value<T> && floating_value<U>)
      {
        auto invsig = rec(d.s);
        return eve::exp(mhalf(as(x))*sqr((x-d.m)*invsig))*invsqrt_2pi*invsig;
      }
      else if constexpr(std::same_as<T, callable_zero_> && floating_value<U>)
      {
        auto invsig = rec(d.s);
        return eve::exp(mhalf(as(x))*sqr(x*invsig))*invsqrt_2pi*invsig;
      }
      else if constexpr(std::same_as<U, callable_one_> && floating_value<T>)
      {
        return eve::exp(mhalf(as(x))*sqr((x-d.m)))*invsqrt_2pi;
      }
      else
        return eve::exp(mhalf(as(x))*sqr(x))*invsqrt_2pi;
    }

    //////////////////////////////////////////////////////
    /// mgf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto mgf_(EVE_SUPPORTS(cpu_)
                                 , normal_distribution<T, U, I> const & d
                                 , V const &x ) noexcept
    {
      auto invsqrt_2pi = V(0.39894228040143267793994605993438186847585863116493);
      if constexpr(floating_value<T> && floating_value<U>)
      {
        return eve::exp(d.m*x+sqr(d.s*x)*half(as(x)));
      }
      else if constexpr(std::same_as<T, callable_zero_> && floating_value<U>)
      {
        return eve::exp(sqr(d.s*x)*half(as(x)));
      }
      else if constexpr(std::same_as<U, callable_one_> && floating_value<T>)
      {
        return eve::exp(d.m*x+sqr(x)*half(as(x)));
      }
      else
        return eve::exp(sqr(d)*half(as(x)));
    }

    //////////////////////////////////////////////////////
    /// invcdf
    template<typename T, typename U, floating_value V
             , typename I = T>
    EVE_FORCEINLINE  auto invcdf_(EVE_SUPPORTS(cpu_)
                                 , normal_distribution<T, U, I> const & d
                                 , V const &x ) noexcept
    {
      if constexpr(floating_value<T> && floating_value<U>)
      {
        return fma(-sqrt_2(as(x))*erfc_inv( T(2)*x), d.s, d.m);
      }
      else if constexpr(std::same_as<T, callable_zero_> && floating_value<U>)
      {
        return -sqrt_2(as(x))*erfc_inv(2*x)*d.s;
      }
      else if constexpr(std::same_as<U, callable_one_> && floating_value<T>)
      {
        return -sqrt_2(as(x))*erfc_inv(2*x)+d.m;
      }
      else
        return -sqrt_2(as(x))*erfc_inv(2*x);
    }

    //////////////////////////////////////////////////////
    /// median
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto median_(EVE_SUPPORTS(cpu_)
                                  , normal_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<T>)
        return  d.m;
      else if constexpr (floating_value<U>)
        return zero(as<U>());
      else
        return zero(as<I>());
    }


    //////////////////////////////////////////////////////
    /// mean
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto mean_(EVE_SUPPORTS(cpu_)
                               , normal_distribution<T,U,I> const &d) noexcept
    {
      return median(d);
    }

    //////////////////////////////////////////////////////
    /// mode
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto mode_(EVE_SUPPORTS(cpu_)
                               , normal_distribution<T,U,I> const & d) noexcept
    {
      return median(d);
    }

    //////////////////////////////////////////////////////
    /// entropy
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto entropy_(EVE_SUPPORTS(cpu_)
                                  , normal_distribution<T,U,I> const & d) noexcept
    {
      auto twopie = T(17.0794684453471341309271017390931489900697770715304);
      if constexpr (floating_value<U>)
        return half(as<T>())*log(twopie*sqr(d.s));
      else
        return half(as<T>())*log(twopie);
    }


    //////////////////////////////////////////////////////
    /// skewness
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto skewness_(EVE_SUPPORTS(cpu_)
                                  , normal_distribution<T,U,I> const & ) noexcept
    {
      return I(0);
    }

    //////////////////////////////////////////////////////
    /// kurtosis
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto kurtosis_(EVE_SUPPORTS(cpu_)
                                  , normal_distribution<T,U,I> const & ) noexcept
    {
      return I(0);
    }

    //////////////////////////////////////////////////////
    /// mad
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto mad_(EVE_SUPPORTS(cpu_)
                                  , normal_distribution<T,U,I> const & d) noexcept
    {
      auto sqrt_2o_pi = T(0.79788456080286535587989211986876373695171726232986);
      if constexpr (floating_value<U>)
        return d.s*sqrt_2o_pi;
       else
        return sqrt_2o_pi;
    }

    //////////////////////////////////////////////////////
    /// var
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto var_(EVE_SUPPORTS(cpu_)
                                  , normal_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<U>)
        return sqr(d.s);
      else
        return one(as<I>());
    }

    //////////////////////////////////////////////////////
    /// stdev
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto stdev_(EVE_SUPPORTS(cpu_)
                                  , normal_distribution<T,U,I> const & d) noexcept
    {
      if constexpr (floating_value<U>)
        return d.s;
      else
        return one(as<I>());
    }

    //////////////////////////////////////////////////////
    /// kullback
    template<typename T, typename U,  typename I = T>
    EVE_FORCEINLINE  auto kullback_(EVE_SUPPORTS(cpu_)
                                  , normal_distribution<T,U,I> const & d1
                                  , normal_distribution<T,U,I> const & d2 ) noexcept
    {
      if constexpr (floating_value<T> && floating_value<U>)
      {
        auto srap = d1.s/d2.s;
        return half(as<T>())*(dec(sqr(srap)+sqr((d1.m-d2.m)/d2.s))+T(2)*eve::log(srap));
      }
      else if constexpr(std::same_as<T, callable_zero_> && floating_value<U>)
      {
        auto srap = d1.s/d2.s;
        return half(as<T>())*(dec(sqr(srap))+T(2)*eve::log(srap));
      }
      else if constexpr(std::same_as<U, callable_one_> && floating_value<T>)
      {
        return half(as<T>())*dec(oneminus(sqr((d1.m-d2.m)/d2.s)));
      }
      else
        return zero(as<I>());
    }

    //////////////////////////////////////////////////////
    /// confidence
    template<typename T, typename U, floating_real_value R
             , floating_real_value V, floating_real_value A,  typename I = T>
    EVE_FORCEINLINE  auto confidence_(EVE_SUPPORTS(cpu_)
                                     , normal_distribution<T,U,I> const & d
                                     , R const & x
                                     , std::array<V, 4> const & cov
                                     , A const & alpha ) noexcept
    {
      using v_t = typename normal_distribution<T,U,I>::value_type;
      R z = x;
      auto normz = -invcdf(normal_distribution_01<I>, alpha*v_t(0.5));
      auto halfwidth = normz;
      if constexpr(floating_real_value<T> && floating_real_value<U>)
        z = (z-d.m)/d.s;
      else if constexpr(floating_real_value<T>)
        z -= d.m;
      else if constexpr(floating_real_value<U>)
        z /= d.s;
      auto zvar = fma(fma(cov[3], z, 2*cov[1]), z, cov[0]);
      halfwidth *= eve::sqrt(zvar);
     if constexpr(floating_real_value<U>)
        halfwidth /= d.s;
      auto d01 =  normal_distribution_01<I>;
      return kumi::make_tuple(cdf(d01, z), cdf(d01, z-halfwidth), cdf(d01, z+halfwidth));
    }
  }
}
