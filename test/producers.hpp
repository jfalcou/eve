//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef TEST_PRODUCERS_HPP
#define TEST_PRODUCERS_HPP

#include <eve/function/bitwise_cast.hpp>
#include <eve/function/nb_values.hpp>
#include <eve/function/next.hpp>
#include <eve/function/min.hpp>
#include <eve/constant/valmax.hpp>
#include <algorithm>
#include <random>

namespace eve
{
  template<typename T>
  struct rng_producer : tts::producer<rng_producer<T>>
  {
    using base_type  = eve::detail::value_type_t<T>;
    using value_type = T;

    using distribution_type = std::conditional_t< std::is_floating_point_v<base_type>
                                                , std::uniform_real_distribution<base_type>
                                                , std::uniform_int_distribution<base_type>
                                                >;
    T next()
    {
      T that;
      std::generate ( tts::detail::begin(that),
                      tts::detail::end(that),
                      [&](){ return distribution_(generator_); }
                    );
      return that;
    }

    std::size_t size() const { return size_; }

    static auto max() { return eve::Valmax<T>(); }

    template<typename V1, typename V2>
    static auto compare(V1 const& v1, V2 const& v2) { return eve::min(v1,v2); }

    template<typename U, typename V>
    rng_producer(U mn, V mx)
                : distribution_(mn,mx)
                , seed_{std::size_t(this->prng_seed()), std::size_t(0), std::size_t(1), this->count()}
                , generator_(seed_)
                , size_(this->count())
    {
    }

    template<typename P>
    rng_producer ( P const& src, std::size_t i, std::size_t p, std::size_t s)
                  : distribution_(src.self().distribution_)
                  , seed_{std::size_t(this->prng_seed()),i,p,s}
                  , generator_(seed_)
                  , size_(src.self().size_)
    {}

    private:
    distribution_type distribution_;
    std::seed_seq     seed_;
    std::mt19937      generator_;
    std::size_t       size_;
  };


  template<typename T>
  struct exhaustive_producer : tts::producer<exhaustive_producer<T>>
  {
    using base_type  = eve::detail::value_type_t<T>;
    using bit_type   = eve::detail::as_integer_t<base_type,signed>;
    using value_type = T;

    template<typename V1, typename V2>
    static auto compare(V1 const& v1, V2 const& v2) { return eve::min(v1,v2); }

    T next()
    {
      T that( current_ );
      current_ = eve::next(current_);

      return that;
    }

    static auto max() { return eve::Valmax<T>(); }

    std::size_t size() const { return size_; }

    template<typename U, typename V>
    exhaustive_producer(U mn, V mx)
                : current_( T(mn) )
                , size_ ( eve::nb_values(base_type(mn),base_type(mx)) )
    {
    }

    template<typename P>
    exhaustive_producer ( P const& src, std::size_t i, std::size_t p, std::size_t)
                  : exhaustive_producer(src.self())
    {
      current_ = eve::next(current_,i*p);
    }

    private:
    T           current_;
    std::size_t size_;
  };
}

#endif
