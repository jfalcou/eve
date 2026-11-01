//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#pragma once

#include "test.hpp"
#include <eve/module/core.hpp>

//==================================================================================================
// test_load[opts...](...) behaves as eve::load[opts...](...). When the conditional among opts keeps
// at least one lane, it also loads with it wrapped in eve::never_empty and checks that both agree on
// the kept lanes, or on all of them when it has an alternative. With eve::ignore_all and no
// alternative, no lane is specified and it returns zeros.
//==================================================================================================
namespace never_empty_test
{
  template<typename O> constexpr bool is_cx = eve::relative_conditional_expr<O>;

  auto decorate(auto const& f) { return f; }
  auto decorate(auto const& f, auto o, auto... os) { return decorate(f[o], os...); }

  template<typename O> auto wrap(O o)
  {
    if constexpr( is_cx<O> ) return eve::never_empty {o};
    else                     return o;
  }

  template<typename T> void check(T a, T b)
  {
    if constexpr( eve::logical_value<T> ) TTS_EQUAL(a, b);
    else                                  TTS_IEEE_EQUAL(a, b);
  }

  template<typename... Opts> struct load_with
  {
    kumi::tuple<Opts...> opts;

    template<typename O> auto operator[](O o) const
    {
      return load_with<Opts..., O> {kumi::push_back(opts, o)};
    }

    auto cx() const
    {
      return kumi::fold_left([](auto acc, auto o)
                             {
                               if constexpr( is_cx<decltype(o)> ) return o;
                               else                               return acc;
                             },
                             opts,
                             eve::ignore_none);
    }

    template<typename T> T kept(T x) const
    {
      auto c = cx();
      if constexpr( decltype(c)::has_alternative ) return x;
      else                                         return eve::replace_ignored(x, c, eve::zero);
    }

    template<typename... Args> auto operator()(Args... args) const
    {
      auto r = kumi::apply([](auto... o) { return decorate(eve::load, o...); }, opts)(args...);
      using r_t = decltype(r);

      if constexpr( std::same_as<decltype(cx()), eve::ignore_all_> )
      {
        if constexpr( eve::logical_value<r_t> ) return r_t(false);
        else                                    return r_t(0);
      }
      else
      {
        if constexpr( (is_cx<Opts> || ...) )
        {
          if( cx().count(eve::as(r)) != 0 )
          {
            auto n = kumi::apply([](auto... o) { return decorate(eve::load, wrap(o)...); }, opts)(args...);
            check(kept(n), kept(r));
            return n;
          }
        }

        return r;
      }
    }
  };
}

inline constexpr never_empty_test::load_with<> test_load = {};
