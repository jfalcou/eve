//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/function/clamp.hpp>
#include <eve/function/nb_values.hpp>
#include <eve/function/next.hpp>
#include <eve/function/prev.hpp>

#include <algorithm>
#include <random>
#include <tts/tests/range.hpp>

#define TTS_RANGE_CHECK(Producer, Ref, New)                                                         \
  do                                                                                                \
  {                                                                                                 \
    if constexpr(std::is_floating_point_v<typename decltype(Producer)::base_type>)                  \
      TTS_ULP_RANGE_CHECK(Producer, Ref, New, 2.0);                                                 \
    else                                                                                            \
      TTS_ULP_RANGE_CHECK(Producer, Ref, New, 0.0);                                                 \
  } while(::tts::detail::is_false())                                                                \
/**/

namespace eve
{
  //////////////////////////////////////////////////////////////////////////////////////////////////
  template<typename T> struct rng_producer : tts::producer<rng_producer<T>>
  {
    using parent     = tts::producer<rng_producer<T>>;
    using base_type  = eve::detail::value_type_t<T>;
    using value_type = T;

    using distribution_type = std::conditional_t<std::is_floating_point_v<base_type>,
                                                 std::uniform_real_distribution<base_type>,
                                                 std::uniform_int_distribution<base_type>>;

    base_type first() const noexcept { return first_; }
    base_type last() const noexcept { return last_; }

    T next() noexcept
    {
      T that{};
      std::generate ( tts::detail::begin(that),
                      tts::detail::end(that),
                      [&](){ return distribution_(generator_); }
                    );
      return that;
    }

    std::size_t size() const noexcept { return size_; }

    template<typename U, typename V>
    rng_producer(U mn, V mx)
        : first_(parent::valmin(static_cast<base_type>(mn)))
        , last_(parent::valmax(static_cast<base_type>(mx)))
        , distribution_(parent::valmin(base_type(mn)), parent::valmax(base_type(mx)))
        , seed_ {std::size_t(this->prng_seed()), std::size_t(0), std::size_t(1), parent::count()}
        , generator_(seed_)
        , size_(parent::count())
    {
    }

    template<typename P>
    rng_producer(P const &src, std::size_t i0, std::size_t i1, std::size_t s)
        : distribution_(src.self().distribution_)
        , seed_ {std::size_t(this->prng_seed()), i0, i1, s}
        , generator_(seed_)
        , size_(src.self().size_)
    {
    }

    private:
    base_type         first_;
    base_type         last_;
    distribution_type distribution_;
    std::seed_seq     seed_;
    std::mt19937      generator_;
    std::size_t       size_;
  };

  //////////////////////////////////////////////////////////////////////
  template<typename T> struct exhaustive_producer : tts::producer<exhaustive_producer<T>>
  {
    using parent     = tts::producer<exhaustive_producer<T>>;
    using base_type  = eve::detail::value_type_t<T>;
    using bit_type   = eve::detail::as_integer_t<base_type, signed>;
    using value_type = T;

    base_type first() const noexcept { return first_; }
    base_type last() const noexcept { return last_; }

    T next() noexcept
    {
      T that(current_);
      current_ = eve::next(current_, eve::cardinal_v<T>);
      return eve::clamp(that, pmi_, pmx_);
    }

    std::size_t size() const noexcept { return size_; }

    template<typename U, typename V>
    exhaustive_producer(U mn, V mx)
        : current_(parent::valmin(static_cast<base_type>(mn)))
        , first_(parent::valmin(static_cast<base_type>(mn)))
        , last_(parent::valmax(static_cast<base_type>(mx)))
        , pmi_(first_)
        , pmx_(eve::prev(last_))
        , size_(eve::nb_values(first_, last_))
    {
      auto p = tts::detail::begin(current_);

      for( std::size_t i = 0; i < eve::cardinal_v<T>; ++i )
      {
        *p = eve::next(*p, i);
        *p = eve::clamp(*p, pmi_, pmx_);
        ++p;
      }
    }

    template<typename P>
    exhaustive_producer(P const &src, std::size_t i0, std::size_t, std::size_t)
        : exhaustive_producer(src.self())
    {
      current_ = eve::next(current_, i0);
      current_ = eve::clamp(current_, pmi_, pmx_);
    }

    private:
    T           current_;
    base_type   first_, last_;
    base_type   pmi_, pmx_;
    std::size_t size_;
  };
}
