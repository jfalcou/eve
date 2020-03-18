//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef TEST_PRODUCERS_HPP
#define TEST_PRODUCERS_HPP

#include <eve/function/bit_cast.hpp>
#include <eve/function/next.hpp>
#include <eve/function/clamp.hpp>
#include <tts/tests/exhaustive_range.hpp>
#include <tts/tests/random_range.hpp>
#include <algorithm>
#include <random>

namespace eve
{
  //////////////////////////////////////////////////////////////////////////////////////////////////
  template<typename T>
  struct rng_producer : tts::rng_producer<eve::detail::value_type_t<T>>
  {
    using base_type  = eve::detail::value_type_t<T>;
    using parent = tts::rng_producer<eve::detail::value_type_t<T>>;
    using value_type = T;
    T next() noexcept
    {
      T that;
      std::generate ( tts::detail::begin(that),
                      tts::detail::end(that),
                      [&](){ return this->distribution_(this->generator_); }
                    );
      return that;
    }

    template<typename U, typename V> rng_producer(U mn, V mx) : parent(mn,mx) {}

    template<typename P>
    rng_producer ( P const& src, std::size_t i0, std::size_t i1, std::size_t s)
                  : parent(src,i0,i1,s)
    {}
  };

  //////////////////////////////////////////////////////////////////////
  template<typename T>
  struct exhaustive_producer : tts::exhaustive_producer<eve::detail::value_type_t<T>>
  {
    using base_type  = eve::detail::value_type_t<T>;
    using parent  = tts::exhaustive_producer<base_type>;
    using value_type = T;

    T next() noexcept
    {
      T that( this->current_ );
      this->current_ = eve::next(this->current_, eve::cardinal_v<T>);
      return eve::clamp(that, this->pmi_, this->pmx_);
    }

    template<typename U, typename V>
    exhaustive_producer(U mn, V mx) : parent(mn,mx)
    {
      auto p = tts::detail::begin(this->current_);

      for(std::size_t i=0;i<eve::cardinal_v<T>;++i)
      {
        *p = eve::next(*p,i);
        *p = eve::clamp(*p, this->pmi_, this->pmx_);
        ++p;
      }
    }

    template<typename P>
    exhaustive_producer ( P const& src, std::size_t i0, std::size_t i1, std::size_t s)
                  : parent(src,i0,i1,s)
    {
      this->current_ = eve::next(this->current_,i0);
      this->current_ = eve::clamp(this->current_, this->pmi_, this->pmx_);
    }
  };
}


#endif
