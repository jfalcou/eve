//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
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
  // Customization point for the size of data tobe geenrated
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
  auto get_arg(Sampler const& s, eve::as_<Target>)
  {
    return s;
  }

  template<typename T, std::size_t N, simd_value Target>
  auto get_arg(std::array<T,N> const& p, eve::as_<Target>)
  {
    using type = as_wide_t< std::remove_cvref_t<decltype(*p.data())>, eve::cardinal_t<Target>>;
    return type(p.data());
  }

  template<typename T, std::size_t N, scalar_value Target>
  auto get_arg(std::array<T,N> const& p, eve::as_<Target>)
  {
    std::array<Target,N> that;
    for(std::size_t i=0;i<N;++i) that[i] = static_cast<Target>(p[i]);
    return that;
  }

  //================================================================================================
  // Turn a list of samples into the correct type
  //================================================================================================
  template<typename S, typename T, std::size_t... N>
  auto make_args(S const& t, std::index_sequence<N...>, eve::as_<T> tgt)
  {
    return std::make_tuple( get_arg(std::get<N>(t), tgt)... );
  }

  //================================================================================================
  // no-data generator - used to propagate types only
  //================================================================================================
  template<typename V, typename T> auto as_value(V v, as_<T>)
  {
    if constexpr(std::is_invocable_v<V,as_<T>>)  return v(eve::as_<T>{});
    else                                         return static_cast<T>(v);
  }

  //================================================================================================
  // Turn a generator into a integral generator
  //================================================================================================
  template<typename G> inline auto as_integer(G g)
  {
    return [g]<typename T>(eve::as_<T>, auto& s) { return g( eve::as_<eve::as_integer_t<T>>{},s); };
  }

  //================================================================================================
  // arithmetic ramp - generate V V+1 .. V+n
  //================================================================================================
  template<typename V> auto ramp(V v)
  {
    return  [=]<typename T>(eve::as_<T>, auto&)
    {
      std::array<eve::element_type_t<T>, amount<T>()> d;
      for(std::size_t i = 0;i<amount<T>();++i) d[i] = v+i;
      return d;
    };
  }

  template<typename V1,  typename V2> auto ramp(V1 v1, V2 v2)
  {
    return  [=]<typename T>(eve::as_<T>, auto&)
    {
      using elt_t = element_type_t<T>;
      auto n = amount<T>()-1;
      elt_t a = n ? elt_t((v2-v1))/n : elt_t(0);
      std::array<elt_t, amount<T>()> d;
      for(std::size_t i = 0;i<amount<T>();++i) d[i] = a*i+v1;
      return d;
    };
  }

  //================================================================================================
  // logical ramp - generate 1 % K 2 %k .. N %K
  //================================================================================================
  template<typename V, typename K> auto logicals(V v, K k)
  {
    return  [=]<typename T>(eve::as_<T>, auto&)
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
    return [=]<typename T>(eve::as_<T>, auto& gen)
    {
      using e_t = eve::element_type_t<T>;
      eve::prng<e_t> dist(as_value(mn,as_<e_t>{}),as_value(mx,as_<e_t>{}));
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
    return [=]<typename T>(eve::as_<T> tgt, auto&)
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
    return [=]<typename T>(eve::as_<T>, auto&)
    {
      return []()
      {
        if constexpr(eve::floating_real_value<T>)
        {
          struct values
          {
            using type  = T;
            type nan         = eve::nan     (eve::as_<type>{});
            type inf         = eve::inf     (eve::as_<type>{});
            type minf        = eve::minf    (eve::as_<type>{});
            type mzero       = eve::mzero   (eve::as_<type>{});
            type zero        = eve::zero   (eve::as_<type>{});
            type maxflint    = eve::maxflint(eve::as_<type>{});
            type valmax      = eve::valmax(eve::as_<type>{});
            type valmin      = eve::valmin(eve::as_<type>{});
            type mindenormal = eve::mindenormal(eve::as_<type>{});
          };

          return values{};
        }
        else
        {
          struct values
          {
            using type  = T;
            type valmax    = eve::valmax(eve::as_<type>{});
            type valmin    = eve::valmin(eve::as_<type>{});
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
    return [=]<typename T>(eve::as_<T> t, auto& s)
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
    auto const single_test = [=]<typename T>( eve::as_<T> target)                                   \
    {                                                                                               \
      [=]<std::size_t... N>(std::index_sequence<N...>)                                              \
      {                                                                                             \
        ::tts::detail::test::acknowledge(::tts::detail::test                                        \
        {                                                                                           \
            std::string{DESCRIPTION} + " (with T = " + std::string{::tts::typename_<T>} + ")"       \
          , [=]()                                                                                   \
            {                                                                                       \
              std::mt19937::result_type seed(18102008);                                             \
              seed = ::tts::arguments.value_or(seed, "-s", "--seed");                               \
              std::mt19937 gen(seed);                                                               \
                                                                                                    \
              constexpr std::make_index_sequence<sizeof...(N)> size = {};                           \
              auto data = s(eve::as_<T>{}, gen);                                                    \
              auto args = eve::test::make_args(data, size, eve::as_<T>{});                          \
              if( ::tts::verbose_status )                                                           \
              {                                                                                     \
                if(::tts::arguments.is_set("-d","--data"))                                          \
                {                                                                                   \
                  std::cout << "Input data:\n";                                                     \
                  ((std::cout << " [" << ::tts::cyan()                                              \
                                      << ::tts::typename_<decltype(std::get<N>(args))>              \
                                      << ::tts::reset()                                             \
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
      (single_test( eve::as_<Ts>() ),...);                                                          \
    }( TYPES );                                                                                     \
                                                                                                    \
    return true;                                                                                    \
  }} + []                                                                                          \
/**/

#define EVE_TEST_TYPES(DESCRIPTION,TYPES)                                                           \
inline bool const TTS_CAT(register_,TTS_FUNCTION) =  ::eve::test::test_setup{                       \
[](auto tests)                                                                                      \
  {                                                                                                 \
    auto const single_test = [=]<typename T>( eve::as_<T> )                                         \
    {                                                                                               \
      ::tts::detail::test::acknowledge(::tts::detail::test                                          \
      {                                                                                             \
          std::string{DESCRIPTION} + " (with T = " + std::string{::tts::typename_<T>} + ")"         \
        , [=]() {tests(eve::as_<T>{}); }                                                            \
        });                                                                                         \
    };                                                                                              \
                                                                                                    \
    [&]<template<class...> class L,typename... Ts>(L<Ts...>)                                        \
    {                                                                                               \
      (single_test( eve::as_<Ts>() ),...);                                                          \
    }( TYPES );                                                                                     \
                                                                                                    \
    return true;                                                                                    \
  }} + []                                                                                           \
/**/
