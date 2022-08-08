//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
*/
//==================================================================================================
#ifndef BENCHMARK_BENCH_HPP
#define BENCHMARK_BENCH_HPP

#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

#include <eve/module/core/regular/load.hpp>
#include <eve/traits/cardinal.hpp>
#include <algorithm>
#include <iostream>
#include <numeric>
#include <type_traits>

// Turn a variadic macro calls into a string containing properly placed commas
#define AS_STRING(...)    AS_STRING_((__VA_ARGS__))
#define AS_STRING__(...)  #__VA_ARGS__
#define AS_STRING_(TXT)   AS_STRING__ TXT

#define AS_UNIQUE3(ID, LINE)  ID##LINE
#define AS_UNIQUE2(ID, LINE)  AS_UNIQUE3(ID, LINE)
#define AS_UNIQUE(ID)         AS_UNIQUE2(ID, __LINE__)

#define EVE_NAME(FUNC) std::string(AS_STRING(FUNC))

namespace eve::bench
{
  template<typename T> struct type_name_
  {
    static constexpr auto value() noexcept
    {
  #if defined(_MSC_VER )
      std::string_view data(__FUNCSIG__);
      auto i = data.find('<') + 1,
        j = data.find(">::value");
      return data.substr(i, j - i);
  #else
      std::string_view data(__PRETTY_FUNCTION__);
      auto i = data.find('=') + 2,
        j = data.find_last_of(']');
      return data.substr(i, j - i);
  #endif
    }
  };

  template<typename T>
  inline auto const typename_ = std::string ( type_name_<T>::value().data()
                                            , type_name_<T>::value().size()
                                            );

  template<typename T0, typename... T> struct types
  {
    static std::string print()
    {
      std::string out = typename_<T0>;
      ((out += ", " + typename_<T>),...);
      return out;
    }
  };
  template<typename T>    struct is_typelist              : std::false_type {};
  template<typename... T> struct is_typelist<types<T...>> : std::true_type  {};

  template<typename T, typename... N> struct replicate
  {
    template<typename I, typename O> using rep = I;
    using type = types< rep<T,N>... >;
  };

  template<typename T>  struct split;

  template<typename T>  requires( eve::scalar_value<T> )
  struct split<T>
  {
    using type = T;
  };

  template<typename T>  requires( eve::simd_value<T> )
  struct split<T>
  {
    using type = as_wide_t<T,typename cardinal_t<T>::split_type>;
  };

  template<typename... T> struct split<types<T...>>
  {
    using type = types< typename split<T>::type... >;
  };

  template<typename T> struct max_cardinal : eve::cardinal<T> {};

  template<typename... T>
  struct  max_cardinal<types<T...>>
        : std::integral_constant<int, std::max({eve::cardinal_v<T>...})>
  {
  };

  template<typename Type, typename XP, typename Fun, typename... Gens>
  void run(std::string const& name, XP& xp, Fun f, Gens const&... gs)
  {
    if constexpr( is_typelist<Type>::value )
    {
      std::string desc = name + "(" + Type::print() +")";
      xp.run( Type{}, desc, f, gs...);

      if constexpr( max_cardinal<Type>::value != 1 )
      {
        run<typename split<Type>::type>(name, xp, f, gs... );
      }
    }
    else
    {
      run<typename replicate<Type,Gens...>::type>(name,xp,f,gs...);
    }
  }

  struct experiment
  {
    ankerl::nanobench::Bench bench_;

    experiment()
    {
      bench_.warmup(1500).unit("element").performanceCounters(true).minEpochIterations(1500);

      std::cout << "[EVE] - Target: "<< AS_STRING(EVE_CURRENT_API) << " - Assertions: ";
#ifdef NDEBUG
      std::cout << "Disabled\n";
#else
      std::cout << "Enabled\n";
#endif
    }

    template<typename... Types, typename Fun, typename... Args>
    void run(types<Types...> const&, std::string const& root, Fun fun, Args const&... args)
    {
      using b_t   = decltype( std::declval<Fun>()(std::declval<Types>()...) );
      using out_t = std::conditional_t< std::is_same_v<b_t,bool>, int, b_t>;

      constexpr auto card_out = eve::cardinal_v<out_t>;
      constexpr auto card_in  = std::max( {card_out, eve::cardinal_v<Types>...} );
      constexpr auto size     = optimal_size<eve::element_type_t<out_t>>;

      bench_.batch(size);

      constexpr std::array<std::ptrdiff_t,sizeof...(Args)> cards  = { eve::cardinal_v<Types>... };

      auto loader = []<typename Tgt>(auto* ptr, as<Tgt> const& )
      {
        if constexpr( simd_value<Tgt> ) return Tgt( eve::as_aligned(ptr, eve::cardinal_t<Tgt>{}) );
        else                            return *ptr;
      };

      bench_.run( root
                , [&]()
                  {
                    std::tuple<eve::element_type_t<Types> const*...> ptrs = { args.data()... };

                    for(std::size_t i=0;i<size;i+=card_in)
                    {
                      auto result = [&]<std::size_t... N>(std::index_sequence<N...> const&)
                      {
                        return fun( loader(std::get<N>(ptrs), eve::as<Types>{})... );
                      }( std::index_sequence_for<Types...>{} );

                      [&]<std::size_t... N>(std::index_sequence<N...> const&)
                      {
                        ((std::get<N>(ptrs) += cards[N]),...);
                      }( std::index_sequence_for<Types...>{} );

                      ankerl::nanobench::doNotOptimizeAway(result);
                    }
                  }
                );
    }
  };
}

#endif
