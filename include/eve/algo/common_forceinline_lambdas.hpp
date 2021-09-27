//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/algo/concepts/value_type.hpp>
#include <eve/conditional.hpp>
#include <eve/function/load.hpp>
#include <eve/function/store.hpp>

#include <utility>

namespace eve::algo
{
  template <typename Op>
  struct apply_to_zip_pair
  {
    Op op;

    explicit apply_to_zip_pair(Op op) : op(op) {}

    EVE_FORCEINLINE auto operator()(auto x_y) const
    {
      return op(get<0>(x_y), get<1>(x_y));
    }
  };

  template <typename P>
  struct not_p
  {
    P p;

    explicit not_p(P p) : p(p) {}

    EVE_FORCEINLINE auto operator()(auto ... x) const
    {
      return !p(x ...);
    }
  };

  template <typename Op>
  struct load_and_apply
  {
    Op op;

    explicit load_and_apply(Op op) : op(op) {}

    EVE_FORCEINLINE auto operator()(auto it) const
    {
      return op(eve::load(it));
    }
  };

  template <typename Delegate>
  struct call_single_step
  {
    Delegate* delegate;

    explicit call_single_step(Delegate* delegate) : delegate(delegate) {}

    EVE_FORCEINLINE bool operator()(auto it) const
    {
      return delegate->step(it, eve::ignore_none, eve::index<0>);
    }
  };

  template <typename T>
  struct equal_to
  {
    T v;

    explicit equal_to(T v) : v(v) {}

    EVE_FORCEINLINE auto operator()(auto x) const
    {
      return x == v;
    }
  };

  struct inplace_load_store
  {
    EVE_FORCEINLINE static auto load_it(auto i) { return i; }

    EVE_FORCEINLINE static auto store_it(auto i) { return i; }
  };

  struct to_load_store
  {
    EVE_FORCEINLINE static auto load_it(auto i) { return get<0>(i); }

    EVE_FORCEINLINE static auto store_it(auto i) { return get<1>(i); }
  };
}
