//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

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

  template <typename T, std::size_t N, typename Op>
  EVE_FORCEINLINE constexpr std::size_t find_branchless(std::array<T, N> x, Op op) {
    return [&]<std::size_t ...i> ( std::index_sequence<i...> ) {
      std::size_t res = N;
      auto update_res_if = [&](std::size_t j) mutable {
        if (op(x[j])) res = j;  // should generate cmov
      };
      (update_res_if(N - i - 1), ...);
      return res;
    }(std::make_index_sequence<N>{});
  }

}
