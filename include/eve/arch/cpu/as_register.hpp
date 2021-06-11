//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/expected_cardinal.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/forward.hpp>
#include <eve/traits/as_wide.hpp>
#include <array>

namespace eve
{
  template<typename Type, typename Cardinal, typename ABI>
  struct as_register;

  template<typename Type, typename Cardinal, typename ABI>
  struct as_logical_register;

  template<typename Type, typename Cardinal, typename ABI>
  using as_register_t = typename as_register<Type, Cardinal, ABI>::type;

  template<typename Type, typename Cardinal, typename ABI>
  using as_logical_register_t = typename as_logical_register<Type, Cardinal, ABI>::type;

  template<typename Type, typename Cardinal>
  struct as_register<Type, Cardinal, eve::emulated_>
  {
    using type = std::array<Type, Cardinal::value>;
  };

  template<typename Type, typename Cardinal>
  struct as_logical_register<Type, Cardinal, eve::emulated_>
  {
    using type = std::array<logical<Type>, Cardinal::value>;
  };

  //================================================================================================
  // Special case : product_type
  //================================================================================================
  namespace detail
  {
    template<typename Cardinal> struct apply_as_wide
    {
      template<typename T> using type = as_wide<T,Cardinal>;
    };
  }

  template<typename Type, typename Cardinal>
  requires( kumi::product_type<Type> )
  struct  as_register<Type, Cardinal, eve::bundle_>
        : kumi::remap_type<detail::apply_as_wide<Cardinal>::template type, Type>
  {
  };

  namespace detail
  {
    template<typename Type, typename Cardinal> struct blob
    {
      using cardinal_t                  = expected_cardinal_t<Type>;
      static constexpr auto replication = Cardinal::value/cardinal_t::value;

      using value_type                  = as_wide_t<Type, cardinal_t>;
      using subvalue_type               = as_wide_t<Type, typename Cardinal::split_type>;

      std::array<subvalue_type,2>       segments;

      template<std::size_t I> EVE_FORCEINLINE decltype(auto) get() noexcept
      {
        if constexpr(has_aggregated_abi_v<subvalue_type>)
        {
          constexpr auto side = ((2*I)/replication) & 1;
          return segments[side].storage().template get<I>();
        }
        else
        {
          constexpr auto side = I & 1;
          return segments[side];
        }
      }

      template<std::size_t I> EVE_FORCEINLINE decltype(auto) get() const noexcept
      {
        if constexpr(has_aggregated_abi_v<subvalue_type>)
        {
          constexpr auto side = ((2*I)/replication) & 1;
          return segments[side].storage().template get<I>();
        }
        else
        {
          constexpr auto side = I & 1;
          return segments[side];
        }
      }

      template<typename Func> void for_each(Func f)
      {
        [f]<std::size_t... I>(auto& s, std::index_sequence<I...> const&)
        {
          (f(s.template get<I>()), ...);
        }(*this, std::make_index_sequence<replication>{});
      }

      template<typename Func> void for_each(Func f) const
      {
        [f]<std::size_t... I>(auto& s, std::index_sequence<I...> const&)
        {
          (f(s.template get<I>()), ...);
        }(*this, std::make_index_sequence<replication>{});
      }

      template<typename Func, typename Wide> void for_each(Func f, Wide const& w)
      {
        [&w,f]<std::size_t... I>(auto& s, std::index_sequence<I...> const&)
        {
          (f(s.template get<I>(),w.storage().template get<I>()), ...);
        }(*this, std::make_index_sequence<replication>{});
      }

      template<typename Func, typename Wide> void for_each(Func f, Wide const& w) const
      {
        [&w,f]<std::size_t... I>(auto& s, std::index_sequence<I...> const&)
        {
          (f(s.template get<I>(),w.storage().template get<I>()), ...);
        }(*this, std::make_index_sequence<replication>{});
      }

      template<typename Func> decltype(auto) apply(Func f)
      {
        return [f]<std::size_t... I>(auto& s, std::index_sequence<I...> const&)
        {
          return f(s.template get<I>()...);
        }(*this, std::make_index_sequence<replication>{});
      }

      template<typename Func> decltype(auto) apply(Func f) const
      {
        return [f]<std::size_t... I>(auto& s, std::index_sequence<I...> const&)
        {
          return f(s.template get<I>()...);
        }(*this, std::make_index_sequence<replication>{});
      }
    };
  }

  template<typename Type, typename Cardinal>
  struct as_register<Type, Cardinal, eve::aggregated_>
  {
    using type = detail::blob<Type,Cardinal>;
  };

  template<typename Type, typename Cardinal>
  struct as_logical_register<Type, Cardinal, eve::aggregated_>
  {
    using type = detail::blob<logical<Type>,Cardinal>;
  };
}
