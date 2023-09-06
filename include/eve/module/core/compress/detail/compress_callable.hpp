//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core/regular/safe.hpp>
#include <eve/module/core/regular/unsafe.hpp>

namespace eve
{

// hack
struct dense_type
{
} inline constexpr dense;
struct sparse_type
{
} inline constexpr sparse;

}

namespace eve::detail
{

template<typename Safety, typename Density, typename CondIn, typename CondOut>
struct compress_callable_settings
{
  static constexpr bool is_safe   = std::same_as<Safety, safe_type>;
  static constexpr bool is_sparse = std::same_as<Density, sparse_type>;

  using safe_t     = Safety;
  using dense_t    = Density;
  using cond_in_t  = CondIn;
  using cond_out_t = CondOut;

  safe_t  safety;
  dense_t density;

  cond_in_t  c_in;
  cond_out_t c_out;

  compress_callable_settings(safe_t, dense_t, cond_in_t c_in, cond_out_t c_out)
      : c_in(c_in)
      , c_out(c_out)
  {}
};

// While we don't have a proper implementation
template<typename Callable, typename... Settings> struct compress_callable : Callable
{
  kumi::tuple<Settings...> settings;

  template<typename Opt> constexpr auto operator[](Opt opt) const
  {
    return compress_callable<Callable, Settings..., Opt> {
      {},
      kumi::push_back(settings, opt)
    };
  }

  EVE_FORCEINLINE auto operator()(auto ...args) const
  {
    static_assert(sizeof...(Settings) >= 1, "safe/unsafe setting is required");
    if constexpr( sizeof...(Settings) == 1 )
    {
      return (*this)(dense)[ignore_none][ignore_none](args...);
    }
    else if constexpr( sizeof...(Settings) == 2 )
    {
      return (*this)[ignore_none][ignore_none](args...);
    }
    else if constexpr( sizeof...(Settings) == 3 ) { return (*this)[get<2>(settings)](args...); }
    else
    {
      auto s0 = get<0>(settings);
      static_assert(std::same_as<decltype(s0), unsafe_type>
                    || std::same_as<decltype(s0), safe_type>);
      auto s1 = get<1>(settings);
      static_assert(std::same_as<decltype(s1), dense_type>
                    || std::same_as<decltype(s1), sparse_type>);

      relative_conditional_expr auto s2 = get<2>(settings);
      relative_conditional_expr auto s3 = get<3>(settings);

      return Callable::operator()(compress_callable_settings(s0, s1, s2, s3), args...);
    }
  }
};

// While we don't have a proper implementation
template<typename Callable, typename... Settings> struct compress_callable_no_density : Callable
{
  kumi::tuple<Settings...> settings;

  template<typename Opt> constexpr auto operator[](Opt opt) const
  {
    return compress_callable_no_density<Callable, Settings..., Opt> {
      {},
      kumi::push_back(settings, opt)
    };
  }

  EVE_FORCEINLINE auto operator()(auto ...args) const
  {
    static_assert(sizeof...(Settings) >= 1, "safe/unsafe setting is required");
    if constexpr( sizeof...(Settings) == 1 )
    {
      return (*this)[ignore_none][ignore_none](args...);
    }
    else if constexpr( sizeof...(Settings) == 2 ) { return (*this)[get<1>(settings)](args...); }
    else
    {
      static_assert(sizeof...(Settings) == 3);
      auto s0 = get<0>(settings);
      static_assert(std::same_as<decltype(s0), unsafe_type>
                    || std::same_as<decltype(s0), safe_type>);

      relative_conditional_expr auto s1 = get<1>(settings);
      relative_conditional_expr auto s2 = get<2>(settings);

      return Callable::operator()(compress_callable_settings(s0, dense, s1, s2), args...);
    }
  }
};

}
