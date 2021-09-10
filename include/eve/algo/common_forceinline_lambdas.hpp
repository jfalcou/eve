//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/function/load.hpp>
#include <eve/function/store.hpp>
#include <eve/conditional.hpp>

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
    template<typename Ignore, typename I>
    EVE_FORCEINLINE static auto load(Ignore ignore, I i)
    {
      return eve::load[ignore](i);
    }

    template<typename I> using read_value_type = algo::value_type_t<I>;

    template<typename Ignore, typename V, typename I>
    EVE_FORCEINLINE static auto store(Ignore ignore, V v, I i)
    {
      eve::store[ignore](v, i);
    }
  };
}
