//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/eve.hpp>

#include <array>
#include <utility>

namespace eve::algo
{
  namespace detail
  {
    template <std::size_t f, std::size_t l, typename T, std::size_t N, typename Op>
    EVE_FORCEINLINE constexpr T array_reduce_impl(std::array<T, N> const& x, Op op)
    {
      if constexpr ((l - f) == 1) return x[f];
      else
      {
        constexpr std::size_t n = l - f;
        T left_sum  = array_reduce_impl<f, f + n / 2>(x, op);
        T right_sum = array_reduce_impl<f + n / 2, l>(x, op);
        return op(left_sum, right_sum);
      }
    }
  }

  template <typename T, std::size_t N, typename F>
  EVE_FORCEINLINE constexpr auto array_map(std::array<T, N> const& x, F f)
  {
    return [&]<std::size_t ...i>(std::index_sequence<i...>){
      return std::array{ f(x[i]) ... };
    }(std::make_index_sequence<N>{});
  }

  template <typename T, typename U, std::size_t N, typename F>
  EVE_FORCEINLINE constexpr auto array_map(
    std::array<T, N> const& x,
    std::array<U, N> const& y,
    F f)
  {
    return [&]<std::size_t ...i>(std::index_sequence<i...>){
      return std::array{ f(x[i], y[i]) ... };
    }(std::make_index_sequence<N>{});
  }

  template <typename T, std::size_t N, typename Op>
  EVE_FORCEINLINE constexpr T array_reduce(std::array<T, N> x, Op op)
    requires (N >= 1)
  {
    return detail::array_reduce_impl<0, N>(x, op);
  }

  struct
  {
    template <typename T, std::size_t N, typename Op>
    struct cmov_if_lambda
    {
      std::array<T, N>* x;
      Op* op;
      std::size_t* res;

      EVE_FORCEINLINE constexpr void operator()(std::size_t j) const
      {
        if ((*op)((*x)[j])) *res = j;
      }
    };


    template <typename T, std::size_t N, typename Op, std::size_t...i>
    EVE_FORCEINLINE constexpr std::size_t impl(std::array<T, N> x, Op op, std::index_sequence<i...>) const {
      std::size_t res = N;
      cmov_if_lambda<T, N, Op> update_res_if {&x, &op, &res };
      (update_res_if(N - i - 1), ...);
      return res;
    }

    template <typename T, std::size_t N, typename Op, std::size_t...idxs>
    EVE_FORCEINLINE constexpr std::size_t operator()(std::array<T, N> x, Op op) const
    {
      return impl(x, op, std::make_index_sequence<N>{});
    }
  } inline constexpr find_branchless;
}
