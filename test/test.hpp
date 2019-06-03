//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef TEST_TEST_HPP
#define TEST_TEST_HPP

#define TTS_USE_CUSTOM_DRIVER
#include <tts/tts.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <eve/wide.hpp>
#include <algorithm>

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
      return equal<b_t,b_t>{}(l.bits(),r.bits());
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

int main(int argc, const char** argv)
{
  std::cout << "[EVE] - Target: "<< ::tts::type_id<EVE_CURRENT_API>() << " - Build type: ";
  #ifdef NDEBUG
  std::cout << "Release\n";
  #else
  std::cout << "Debug\n";
  #endif

  ::tts::env runtime(argc,argv,std::cout);
  return ::tts::run( runtime, ::tts::detail::suite, 0, 0 );
}

#endif
