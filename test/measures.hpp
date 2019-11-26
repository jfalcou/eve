//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef TEST_MEASURES_HPP
#define TEST_MEASURES_HPP

#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/wide.hpp>
#include <algorithm>

namespace tts
{
  template<typename Type,typename Func> auto vectorize(Func f)
  {
    return [=](auto x){ Type that;
                        std::transform( tts::detail::begin(x),tts::detail::end(x),
                                        tts::detail::begin(that),
                                        f
                                      );
                        return that;
                      };
  }
}

namespace tts::ext
{
  template<typename T, typename N, typename ABI, typename EnableIf>
  struct equal<eve::wide<T, N, ABI>, eve::wide<T, N, ABI>, EnableIf>
  {
    using arg_t = eve::wide<T, N, ABI>;
    inline bool operator()(arg_t const &l, arg_t const &r) const
    {
      return std::equal(l.begin(), l.end(), r.begin());
    }
  };

  template<typename T, typename EnableIf>
  struct equal<eve::logical<T>, eve::logical<T>, EnableIf>
  {
    using arg_t = eve::logical<T>;
    inline bool operator()(arg_t const &l, arg_t const &r) const
    {
      using b_t = typename arg_t::bits_type;
      return equal<b_t, b_t>{}(l.bits(), r.bits());
    }
  };

  template<typename T, typename N, typename ABI, typename EnableIf>
  struct ulpdist<eve::wide<T, N, ABI>, eve::wide<T, N, ABI>, EnableIf>
  {
    inline double operator()(eve::wide<T, N, ABI> const &l, eve::wide<T, N, ABI> const &r) const
    {
      double max_ulp = 0;
      for(auto i = 0; i < l.size(); ++i)
        max_ulp = std::max(max_ulp, tts::ulpdist(T(l[ i ]), T(r[ i ])));

      return max_ulp;
    }
  };

  template<typename T, typename N, typename ABI, typename EnableIf>
  struct reldist<eve::wide<T, N, ABI>, eve::wide<T, N, ABI>, EnableIf>
  {
    inline double operator()(eve::wide<T, N, ABI> const &l, eve::wide<T, N, ABI> const &r) const
    {
      double max_rel = 0;
      for(auto i = 0; i < l.size(); ++i)
        max_rel = std::max(max_rel, tts::reldist(T(l[ i ]), T(r[ i ])));

      return max_rel;
    }
  };
}

#endif
