//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/expected_cardinal.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/kumi.hpp>
#include <eve/forward.hpp>
#include <eve/traits/as_wide.hpp>
#include <cstring>
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

  template<transparent_value Type, typename Cardinal, typename ABI>
  struct as_register<Type, Cardinal, ABI>: as_register<transparent_inner_t<Type>, Cardinal, ABI>
  { };

  template<transparent_value Type, typename Cardinal, typename ABI>
  struct as_logical_register<Type, Cardinal, ABI>: as_logical_register<transparent_inner_t<Type>, Cardinal, ABI>
  { };

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
        : kumi::as_tuple<Type, detail::apply_as_wide<Cardinal>::template type>
  {
  };

  namespace detail
  {
    template<typename Type, typename Cardinal>
    struct  blob
    {
      using is_product_type             = void;
      using cardinal_t                  = expected_cardinal_t<Type>;
      using value_type                  = as_wide_t<Type, cardinal_t>;
      using subvalue_type               = as_wide_t<Type, typename Cardinal::split_type>;
      static constexpr auto replication = Cardinal::value/expected_cardinal_v<Type>;

      std::array<value_type, replication> storage;

      EVE_FORCEINLINE void assign_parts(subvalue_type const& l, subvalue_type const& h)
      {
        std::array<subvalue_type,2> data{l,h};

        auto dst = reinterpret_cast<std::byte*>(this);
        auto src = reinterpret_cast<std::byte*>(data.data());
        std::memcpy(dst, src, sizeof(*this));
      }

      EVE_FORCEINLINE auto slice() const
      {
        std::array<subvalue_type,2> data{};

        auto src = reinterpret_cast<std::byte const*>(this);
        auto dst = reinterpret_cast<std::byte*>(data.data());
        std::memcpy(dst, src, sizeof(*this));

        return data;
      }

      template<std::size_t I>
      friend EVE_FORCEINLINE auto&        get(blob& b) noexcept       { return b.storage[I]; }

      template<std::size_t I>
      friend EVE_FORCEINLINE auto const&  get(blob const& b) noexcept { return b.storage[I]; }

      template<typename Func>
      EVE_FORCEINLINE void for_each(Func f, auto... w)       { kumi::for_each(f, *this, w.storage()...); }

      template<typename Func>
      EVE_FORCEINLINE void for_each(Func f, auto... w) const { kumi::for_each(f, *this, w.storage()...); }

      template<typename Func>
      EVE_FORCEINLINE decltype(auto) apply(Func f)        { return kumi::apply(f,*this); }

      template<typename Func>
      EVE_FORCEINLINE decltype(auto) apply(Func f) const  { return kumi::apply(f,*this); }
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

template<std::size_t I, typename T, typename C>
struct std::tuple_element<I, eve::detail::blob<T,C>>
{
  using type = typename eve::detail::blob<T,C>::value_type;
};

template<typename T, typename C>
struct  std::tuple_size<eve::detail::blob<T,C>>
      : std::integral_constant<std::size_t, eve::detail::blob<T,C>::replication>
{
};
