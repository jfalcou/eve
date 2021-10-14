//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once
#include "test_distribution.hpp"
#include "types.hpp"
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/maxflint.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mindenormal.hpp>
#include <tuple>

namespace eve::test
{
  //================================================================================================
  // Customization point for the size of data to be generated
  //================================================================================================
  template<typename T> constexpr std::size_t amount()
  {
    using card_t = eve::cardinal_t<T>;
    if constexpr( std::same_as<card_t, eve::scalar_cardinal>)
      return eve::expected_cardinal_v<T>;
    else
      return card_t::value;
  }

  //================================================================================================
  // Customization point for argument building
  //================================================================================================
  template<typename Sampler, typename Target>
  auto get_arg(Sampler const& s, eve::as<Target>)
  {
    return s;
  }

  template<typename T, std::size_t N, simd_value Target>
  auto get_arg(std::array<T,N> const& p, eve::as<Target>)
  {
    using type = as_wide_t< std::remove_cvref_t<decltype(*p.data())>, eve::cardinal_t<Target>>;
    return type(p.data());
  }

  template<typename T, std::size_t N, scalar_value Target>
  auto get_arg(std::array<T,N> const& p, eve::as<Target>)
  {
    std::array<Target,N> that;
    for(std::size_t i=0;i<N;++i) that[i] = static_cast<Target>(p[i]);
    return that;
  }

  //================================================================================================
  // Turn a list of samples into the correct type
  //================================================================================================
  template<typename S, typename T, std::size_t... N>
  auto make_args(S const& t, std::index_sequence<N...>, eve::as<T> tgt)
  {
    return std::make_tuple( get_arg(std::get<N>(t), tgt)... );
  }

  //================================================================================================
  // no-data generator - used to propagate types only
  //================================================================================================
  template<typename V, typename T> auto as_value(V v, as<T>)
  {
    if constexpr(std::is_invocable_v<V,as<T>>)  return v(eve::as<T>{});
    else                                         return static_cast<T>(v);
  }

  //================================================================================================
  // Turn a generator into a integral generator
  //================================================================================================
  template<typename G> inline auto as_integer(G g)
  {
    return [g]<typename T>(eve::as<T>, auto& s) { return g( eve::as<eve::as_integer_t<T>>{},s); };
  }

  template<typename G> inline auto as_signed_integer(G g)
  {
    return [g]<typename T>(eve::as<T>, auto& s) { return g( eve::as<eve::as_integer_t<T, signed>>{},s); };
  }

  template<typename G> inline auto as_unsigned(G g)
  {
    return [g]<typename T>(eve::as<T>, auto& s) { return g( eve::as<eve::as_integer_t<T, unsigned>>{},s); };
  }
  //================================================================================================
  // arithmetic ramp - generate V V+1 .. V+n
  //================================================================================================
  template<typename V> auto ramp(V v)
  {
    return  [=]<typename T>(eve::as<T>, auto&)
            {
              std::array<eve::element_type_t<T>, amount<T>()> d;
              for(std::size_t i = 0;i<amount<T>();++i) d[i] = v+i;
              return d;
            };
  }

  template<typename V, typename V1> auto ramp(V v,  V1 step)
  {
    return  [=]<typename T>(eve::as<T>, auto&)
            {
              std::array<eve::element_type_t<T>, amount<T>()> d;
              for(std::size_t i = 0;i<amount<T>();++i) d[i] = v+step*i;
              return d;
            };
  }

  template<typename V> auto reverse_ramp(V v)
  {
    return  [=]<typename T>(eve::as<T>, auto&)
            {
              std::array<eve::element_type_t<T>, amount<T>()> d;
              auto N = amount<T>();
              for(std::size_t i = 0;i<amount<T>();++i) d[N-i-1] = v+i;
              return d;
            };
  }

  template<typename V, typename V1> auto reverse_ramp(V v, V1 step)
  {
    return  [=]<typename T>(eve::as<T>, auto&)
            {
              std::array<eve::element_type_t<T>, amount<T>()> d;
              auto N = amount<T>();
              for(std::size_t i = 0;i<amount<T>();++i) d[N-i-1] = v+step*i;
              return d;
            };
  }

  template<typename V1,  typename V2> auto between(V1 v1, V2 v2)
  {
    return  [=]<typename T>(eve::as<T>, auto&)
            {
              using elt_t = element_type_t<T>;
              auto n = amount<T>()-1;
              elt_t w1 = as_value(v1,as<elt_t>{});
              elt_t w2 = as_value(v2,as<elt_t>{});
              elt_t a = n ? elt_t((w2 - w1))/n : elt_t(0);
              std::array<elt_t, amount<T>()> d;
              for(std::size_t i = 0;i<amount<T>();++i) d[i] = std::min( elt_t(a*i+w1), w2);
              return d;
            };
  }

  //================================================================================================
  // logical ramp - generate (v+1) % k == 0, (v+2) % k ==  0, ... (v+N) % k == 0
  //================================================================================================
  template<typename V, typename K> auto logicals(V v, K k)
  {
    return  [=]<typename T>(eve::as<T>, auto&)
            {
              std::array<eve::logical<eve::element_type_t<T>>,amount<T>()> d;
              for(std::size_t i = 0;i<amount<T>();++i) d[i] = ((v+i)%k) == 0;
              return d;
            };
  }

  //================================================================================================
  // random arithmetic values
  //================================================================================================
  template<typename Mn, typename Mx> auto randoms(Mn mn, Mx mx)
  {
    return [=]<typename T>(eve::as<T>, auto& gen)
           {
             using e_t = eve::element_type_t<T>;
             eve::prng<e_t> dist(as_value(mn,as<e_t>{}),as_value(mx,as<e_t>{}));
             std::array<e_t,amount<T>()> d;
             std::for_each(d.begin(),d.end(), [&](auto& e) { e = dist(gen); });
             return d;
           };
  }

  //================================================================================================
  // Constant value
  //================================================================================================
  template<typename V> auto value(V v)
  {
    return [=]<typename T>(eve::as<T> tgt, auto&)
           {
             std::array<eve::element_type_t<T>,amount<T>()> d;
             auto val = as_value(v,tgt);

             for(auto& e : d) e = val;

             return d;
           };
  }

  //================================================================================================
  // IEEE Special Constant value
  //================================================================================================
  inline auto limits()
  {
    return [=]<typename T>(eve::as<T>, auto&)
    {
      return []()
      {
        if constexpr(eve::floating_real_value<T>)
        {
          struct values
          {
            using type  = T;
            type nan         = eve::nan     (eve::as<type>{});
            type inf         = eve::inf     (eve::as<type>{});
            type minf        = eve::minf    (eve::as<type>{});
            type mzero       = eve::mzero   (eve::as<type>{});
            type zero        = eve::zero   (eve::as<type>{});
            type maxflint    = eve::maxflint(eve::as<type>{});
            type valmax      = eve::valmax(eve::as<type>{});
            type valmin      = eve::valmin(eve::as<type>{});
            type mindenormal = eve::mindenormal(eve::as<type>{});
          };

          return values{};
        }
        else
        {
          struct values
          {
            using type  = T;
            type valmax    = eve::valmax(eve::as<type>{});
            type valmin    = eve::valmin(eve::as<type>{});
          };

          return values{};
        }
      }();
    };
  }

  //================================================================================================
  // Generators combinator
  //================================================================================================
  template<typename... G> inline auto generate(G... g)
  {
    return [=]<typename T>(eve::as<T> t, auto& s)
           {
             return std::make_tuple(g(t,s)...);
           };
  }

  //================================================================================================
  // Lambda "seed" capture
  //================================================================================================
  template<typename TestBed> struct test_setup
  {
    test_setup(TestBed f) : base_test(f) {}
    auto operator+(auto TestBody) const
    {
      base_test( TestBody );
      return true;
    }

    TestBed base_test;
  };
}

#define EVE_TEST(DESCRIPTION,TYPES,SAMPLES)                                                         \
inline bool const TTS_CAT(register_,TTS_FUNCTION) =  ::eve::test::test_setup{                       \
[](auto tests)                                                                                      \
  {                                                                                                 \
    auto s = SAMPLES;                                                                               \
    auto const single_test = [=]<typename T>( eve::as<T> target)                                    \
    {                                                                                               \
      [=]<std::size_t... N>(std::index_sequence<N...>)                                              \
      {                                                                                             \
        ::tts::detail::test::acknowledge(::tts::detail::test                                        \
        {                                                                                           \
            std::string{DESCRIPTION} + " (with T = " + std::string{::tts::typename_<T>} + ")"       \
          , [=]()                                                                                   \
            {                                                                                       \
              std::mt19937::result_type seed(18102008);                                             \
              seed = ::tts::arguments.value({"-s", "--seed"}, seed);                                \
              std::mt19937 gen(seed);                                                               \
                                                                                                    \
              constexpr std::make_index_sequence<sizeof...(N)> size = {};                           \
              auto data = s(eve::as<T>{}, gen);                                                     \
              auto args = eve::test::make_args(data, size, eve::as<T>{}) ;                          \
              if( ::tts::verbose_status )                                                           \
              {                                                                                     \
                if(::tts::arguments[{"-d","--data"}])                                               \
                {                                                                                   \
                  std::cout << "Input data:\n";                                                     \
                  ((std::cout << " [" << ::tts::cyan                                                \
                                      << ::tts::typename_<decltype(std::get<N>(args))>              \
                                      << ::tts::reset                                               \
                              << "] = "                                                             \
                              << ::tts::as_string(std::get<N>(args))                                \
                              << "\n"),...);                                                        \
                }                                                                                   \
              }                                                                                     \
              tests(std::get<N>(args)...);                                                          \
            }                                                                                       \
          });                                                                                       \
      }(std::make_index_sequence<std::tuple_size<decltype ( s ( target                              \
                                                              , std::declval<std::mt19937&>()       \
                                                              )                                     \
                                                          )>::value>{});                            \
    };                                                                                              \
                                                                                                    \
    [&]<template<class...> class L,typename... Ts>(L<Ts...>)                                        \
    {                                                                                               \
      (single_test( eve::as<Ts>() ),...);                                                           \
    }( TYPES );                                                                                     \
                                                                                                    \
    return true;                                                                                    \
  }} + []                                                                                           \
/**/

#define EVE_TEST_TYPES(DESCRIPTION,TYPES)                                                           \
inline bool const TTS_CAT(register_,TTS_FUNCTION) =  ::eve::test::test_setup{                       \
[](auto tests)                                                                                      \
  {                                                                                                 \
    auto const single_test = [=]<typename T>( eve::as<T> )                                          \
    {                                                                                               \
      ::tts::detail::test::acknowledge(::tts::detail::test                                          \
      {                                                                                             \
          std::string{DESCRIPTION} + " (with T = " + std::string{::tts::typename_<T>} + ")"         \
        , [=]() {tests(eve::as<T>{}); }                                                             \
        });                                                                                         \
    };                                                                                              \
                                                                                                    \
    [&]<template<class...> class L,typename... Ts>(L<Ts...>)                                        \
    {                                                                                               \
      (single_test( eve::as<Ts>() ),...);                                                           \
    }( TYPES );                                                                                     \
                                                                                                    \
    return true;                                                                                    \
  }} + []                                                                                           \
/**/
