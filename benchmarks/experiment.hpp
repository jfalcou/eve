//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef BENCHMARK_BENCH_HPP
#define BENCHMARK_BENCH_HPP

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#include <eve/traits/cardinal.hpp>
#include <algorithm>
#include <numeric>
#include <iostream>
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

  template<typename Type, typename XP, typename Fun, typename... Gens>
  void run(std::string const& name, XP& xp, Fun f, Gens const&... gs)
  {
    xp.run( name + "(" + ::eve::bench::typename_<Type> + ")"
          , f, gs.template build<Type>()...
          );

    if constexpr( eve::cardinal_v<Type> != 1 )
    {
      using card_t = typename eve::cardinal_t<Type>::split_type;
      run<eve::as_wide_t<Type,card_t>>(name, xp, f, gs... );
    }
  }

  struct experiment2
  {
    ankerl::nanobench::Bench bench_;
    std::size_t size_;

    experiment2(std::size_t size) : size_(size)
    {
      bench_.warmup(100).unit("element").performanceCounters(true);

      std::cout << "[EVE] - Target: "<< AS_STRING(EVE_CURRENT_API) << " - Assertions: ";
#ifdef NDEBUG
      std::cout << "Disabled\n";
#else
      std::cout << "Enabled\n";
#endif
    }

    template<typename Fun, typename... Args>
    void run(std::string const& root, Fun fun, Args const&... args)
    {
      using b_t   = decltype( std::declval<Fun>()(std::declval<typename Args::value_type>()...) );
      using out_t = std::conditional_t< std::is_same_v<b_t,bool>, int, b_t>;

      std::vector<out_t> output(size_);

      bench_.batch(size_ * eve::cardinal_v<out_t>);
      bench_.run( root
                , [&]()
                  {
                    for(std::size_t i=0;i<size_;i++)
                      output[i] = fun( args[i]...);
                    ankerl::nanobench::doNotOptimizeAway(output);
                  }
                );
    }

    private:
  };
}

#endif

