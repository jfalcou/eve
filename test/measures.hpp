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

#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/wide.hpp>
#include <eve/function/store.hpp>
#include <eve/function/all.hpp>

#include <algorithm>

namespace tts
{
  template<typename T,typename Func> auto vectorize(Func f)
  {
    return  [=]<typename X>(X const& x)
            {
              if constexpr( eve::scalar_value<T> )
              {
                T that = f(x);
                return that;
              }
              else
              {
                typename X::value_type in[X::static_size];
                eve::store(x, &in[0]);

                typename T::value_type out[T::static_size];

                for(std::size_t i=0;i<T::static_size;++i)
                  out[i] = f(in[i]);

                return T(&out[0]);
              }
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
      auto check = [&]<std::size_t... I>(std::index_sequence<I...> const&)
      {
        return (true && ... && (l[I] == r[I]));
      };

      return check( std::make_index_sequence<N::value>{});
    }
  };

  template<typename T, typename EnableIf>
  struct equal<eve::logical<T>, eve::logical<T>, EnableIf>
  {
    using arg_t = eve::logical<T>;
    inline bool operator()(arg_t const &l, arg_t const &r) const
    {
      auto check = [&]<std::size_t... I>(std::index_sequence<I...> const&)
      {
        if constexpr(eve::simd_value<T>)
          return (true && ... && (l[I] == r[I]));
        else
          return l == r;
      };

      return check( std::make_index_sequence<eve::cardinal_v<arg_t>>{});
    }
  };

  template<typename T, typename EnableIf>
  struct reldist<eve::logical<T>, eve::logical<T>, EnableIf>
  {
    using arg_t = eve::logical<T>;
    inline double operator()(arg_t const &l, arg_t const &r) const
    {
      return l.value() == r.value() ? 0 : 1;
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

  template<typename T, typename EnableIf>
  struct ulpdist<eve::logical<T>, eve::logical<T>, EnableIf>
  {
    inline double operator()(eve::logical<T> const &l, eve::logical<T> const &r) const
    {
      return eve::all(l==r) ? 0. : std::numeric_limits<double>::infinity();
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
