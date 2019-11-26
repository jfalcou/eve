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
      step_++;
      T that;
      std::generate ( tts::detail::begin(that),
                      tts::detail::end(that),
                      [&](){ return distribution_(generator_); }
                    );
      return that;
    }

    std::size_t size() const { return size_; }

    template<typename U>
    rng_producer(U mn, U mx)
                : generator_(this->prng_seed())
                , distribution_(mn,mx)
                , size_(this->count()), step_(0)
    {
    }

    private:
    distribution_type distribution_;
    std::mt19937      generator_;
    std::size_t       size_, step_;
  };
}

#endif
