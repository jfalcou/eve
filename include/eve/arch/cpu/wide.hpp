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

#include <eve/arch/as_register.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/arch/cpu/base.hpp>
#include <eve/arch/spec.hpp>
#include <eve/concept/memory.hpp>
#include <eve/concept/range.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/detail/function/load.hpp>
#include <eve/detail/function/combine.hpp>
#include <eve/detail/function/compounds.hpp>
#include <eve/detail/function/fill.hpp>
#include <eve/detail/function/make.hpp>

#include <type_traits>
#include <iosfwd>

namespace eve
{
  //================================================================================================
  // Wrapper for SIMD registers holding arithmetic types with compile-time size
  //================================================================================================
  template<typename Type, typename Size, typename ABI>
  struct  EVE_MAY_ALIAS wide
        : detail::wide_cardinal<Size>
        , detail::wide_ops<wide<Type,Size,ABI>>
        , detail::wide_storage<as_register_t<Type, Size, ABI>>
  {
    using card_base     = detail::wide_cardinal<Size>;
    using storage_base  = detail::wide_storage<as_register_t<Type, Size, ABI>>;

    public:
    using value_type    = Type;
    using abi_type      = ABI;
    using storage_type  = typename storage_base::storage_type;
    using size_type     = typename card_base::size_type;

    template<typename T, typename N = expected_cardinal_t<T>> using rebind = wide<T,N>;

    static constexpr auto  static_alignment  = std::min ( sizeof(Type)*Size::value
                                                        , alignof(storage_type)
                                                        );

    //==============================================================================================
    // Constructors
    //==============================================================================================
    EVE_FORCEINLINE wide() noexcept : storage_base{} {}
    EVE_FORCEINLINE wide(wide const& w) noexcept : storage_base(w.storage()) {}
    EVE_FORCEINLINE wide(storage_type const &r) noexcept : storage_base(r) {}

    template<std::input_iterator It>
    EVE_FORCEINLINE explicit  wide(It b, It e) noexcept
                            : storage_base(detail::load(eve::as_<wide>{}, b, e))
    {}

    template<detail::range Range>
    EVE_FORCEINLINE explicit  wide(Range &&r) noexcept requires(!std::same_as<storage_type, Range>)
                            : wide( std::begin(std::forward<Range>(r))
                                  , std::end  (std::forward<Range>(r))
                                  )
    {}

    EVE_FORCEINLINE explicit  wide(simd_compatible_ptr<wide> auto ptr) noexcept
                            : storage_base(detail::load(eve::as_<wide>{}, ptr))
    {}

    EVE_FORCEINLINE explicit  wide(scalar_value auto v)  noexcept
                            : storage_base(detail::make(eve::as_<wide>{}, v))
    {}

    EVE_FORCEINLINE wide( scalar_value auto v0, scalar_value auto v1
                        , scalar_value auto... vs
                        ) noexcept requires( card_base::static_size == 2 + sizeof...(vs) )
                  : storage_base(detail::make(eve::as_<wide>{}, v0, v1, vs...))
    {}

    template<std::invocable<size_type,size_type> Generator>
    EVE_FORCEINLINE wide(Generator &&g) noexcept
                  : storage_base( detail::fill(eve::as_<wide>{}, std::forward<Generator>(g)) )
    {}

    template<typename halfSize>
    EVE_FORCEINLINE wide( wide<Type, halfSize> const &l, wide<Type, halfSize> const &h) noexcept
                    requires( card_base::static_size == 2 * halfSize::value )
                  : storage_base(detail::combine(EVE_CURRENT_API{}, l, h))
    {}

    //==============================================================================================
    // Assignments
    //==============================================================================================
    using detail::wide_ops<wide>::operator=;

    //==============================================================================================
    // array-like interface - only available on wide
    //==============================================================================================
    using detail::wide_ops<wide>::operator[];

    EVE_FORCEINLINE auto  begin()       noexcept { return detail::at_begin(*this); }
    EVE_FORCEINLINE auto  begin() const noexcept { return detail::at_begin(*this); }

    EVE_FORCEINLINE auto  end()        noexcept { return begin() + card_base::static_size; }
    EVE_FORCEINLINE auto  end() const  noexcept { return begin() + card_base::static_size; }

    //===============================================================================================
    // Self-increment/decrement operators
    //==============================================================================================
    EVE_FORCEINLINE wide &operator++()    noexcept  { return detail::self_add(*this, wide{1}); }
    EVE_FORCEINLINE wide &operator--()    noexcept  { return detail::self_sub(*this, wide{1}); }
    EVE_FORCEINLINE wide operator++(int)  noexcept  { auto that(*this); operator++(); return that; }
    EVE_FORCEINLINE wide operator--(int)  noexcept  { auto that(*this); operator--(); return that; }

    //==============================================================================================
    // Bitwise operators
    //==============================================================================================
    friend EVE_FORCEINLINE auto operator~(wide const& v) noexcept
    {
      return detail::self_bitnot(v);
    }

    friend  EVE_FORCEINLINE auto operator&=(wide& w, value auto o) noexcept
                        ->  decltype(detail::self_bitand(w, o))
    {
      return detail::self_bitand(w, o);
    }

    template<scalar_value U,typename M>
    friend EVE_FORCEINLINE    auto operator&(wide const& v, wide<U,M> const& w) noexcept
                          ->  std::decay_t<decltype(std::declval<wide&>() &= w)>
    {
      auto    that  = v;
      return  that &= w;
    }

    friend EVE_FORCEINLINE auto operator&(wide const& v, scalar_value auto w) noexcept
    requires (sizeof(w) == sizeof(Type))
    {
      auto    that  = v;
      return  that &= bit_cast(w, as_<Type>{});
    }

    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator&(S v, wide const& w) noexcept
    requires (sizeof(v) == sizeof(Type))
    {
      auto    u  = bit_cast(w, as_<typename wide::template rebind<S,Size>>());
      return  u &= v;
    }

    friend  EVE_FORCEINLINE auto operator|=(wide& w, value auto o) noexcept
                        ->  decltype(detail::self_bitor(w, o))
    {
      return detail::self_bitor(w, o);
    }

    template<scalar_value U,typename M>
    friend EVE_FORCEINLINE    auto operator|(wide const& v, wide<U,M> const& w) noexcept
                          ->  std::decay_t<decltype(std::declval<wide&>() |= w)>
    {
      wide    that  = v;
      return  that |= w;
    }

    friend EVE_FORCEINLINE auto operator|(wide const& v, scalar_value auto w) noexcept
    requires (sizeof(w) == sizeof(Type))
    {
      auto    that  = v;
      return  that |= bit_cast(w, as_<Type>{});
    }

    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator|(S v, wide const& w) noexcept
    requires (sizeof(v) == sizeof(Type))
    {
      auto    u  = bit_cast(w, as_<typename wide::template rebind<S,Size>>());
      return  u |= v;
    }

    friend  EVE_FORCEINLINE auto operator^=(wide& w, value auto o) noexcept
                        ->  decltype(detail::self_bitxor(w, o))
    {
      return detail::self_bitxor(w, o);
    }

    template<scalar_value U, typename M>
    friend EVE_FORCEINLINE    auto operator^(wide const& v, wide<U,M> const& w) noexcept
                          ->  std::decay_t<decltype(std::declval<wide&>() |= w)>
    {
      auto    that  = v;
      return  that ^= w;
    }

    friend EVE_FORCEINLINE auto operator^(wide const& v, scalar_value auto w) noexcept
    requires (sizeof(w) == sizeof(Type))
    {
      auto    that  = v;
      return  that ^= bit_cast(w, as_<Type>{});
    }

    template<scalar_value S>
    friend EVE_FORCEINLINE auto operator^(S v, wide const& w) noexcept
    requires (sizeof(v) == sizeof(Type))
    {
      auto    u  = bit_cast(w, as_<typename wide::template rebind<S,Size>>());
      return  u ^= v;
    }

    //==============================================================================================
    // Arithmetic operators
    //==============================================================================================
    friend  EVE_FORCEINLINE auto operator+=(wide& w, value auto o) noexcept
                        ->  decltype(detail::self_add(w, o))
    {
      return detail::self_add(w, o);
    }

    friend EVE_FORCEINLINE auto operator+(wide const& v) noexcept { return v; }

    friend EVE_FORCEINLINE auto operator+(wide const& v, wide const& w) noexcept
    {
      auto that = v;
      return that += w;
    }

    friend EVE_FORCEINLINE auto operator+(real_scalar_value auto s, wide const& v) noexcept
    {
      return v + wide(s);
    }

    friend EVE_FORCEINLINE auto operator+(wide const& v, real_scalar_value auto s) noexcept
    {
      return v + wide(s);
    }

    friend  EVE_FORCEINLINE auto operator-=(wide& w, value auto o) noexcept
                        ->  decltype(detail::self_sub(w, o))
    {
      return detail::self_sub(w, o);
    }

    friend EVE_FORCEINLINE auto operator-(wide const& v) noexcept
    {
      return self_negate(v);
    }

    friend EVE_FORCEINLINE auto operator-(wide const& v, wide const& w) noexcept
    {
      auto that = v;
      return that -= w;
    }

    friend EVE_FORCEINLINE auto operator-(real_scalar_value auto s, wide const& v) noexcept
    {
      return wide(s) - v;
    }

    friend EVE_FORCEINLINE auto operator-(wide const& v, real_scalar_value auto s) noexcept
    {
      return v - wide(s);
    }

    friend  EVE_FORCEINLINE auto operator*=(wide& w, value auto o) noexcept
                        ->  decltype(detail::self_mul(w, o))
    {
      return detail::self_mul(w, o);
    }

    friend EVE_FORCEINLINE auto operator*(wide const& v, wide const& w) noexcept
    {
      auto that = v;
      return that *= w;
    }

    friend EVE_FORCEINLINE auto operator*(real_scalar_value auto s, wide const& v) noexcept
    {
      return v * wide(s);
    }

    friend EVE_FORCEINLINE auto operator*(wide const& v, real_scalar_value auto s) noexcept
    {
      return v * wide(s);
    }

    friend  EVE_FORCEINLINE auto operator/=(wide& w, value auto o) noexcept
                        ->  decltype(detail::self_div(w, o))
    {
      return detail::self_div(w, o);
    }

    friend EVE_FORCEINLINE auto operator/(wide const& v, wide const& w) noexcept
    {
      auto that = v;
      return that /= w;
    }

    friend EVE_FORCEINLINE auto operator/(real_scalar_value auto s, wide const& v) noexcept
    {
      return wide(s) / v;
    }

    friend EVE_FORCEINLINE auto operator/(wide const& v, real_scalar_value auto s) noexcept
    {
      return v / wide(s);
    }

    friend  EVE_FORCEINLINE auto operator%=(wide& w, value auto o) noexcept
                        ->  decltype(detail::self_rem(w, o))
    {
      return detail::self_rem(w, o);
    }

    friend EVE_FORCEINLINE  auto operator%(wide const& v, wide const& w) noexcept
                            requires( integral_scalar_value<Type> )
    {
      auto that = v;
      return that %= w;
    }

    friend EVE_FORCEINLINE  auto operator%(integral_scalar_value auto s, wide const& v) noexcept
                            requires( integral_scalar_value<Type> )
    {
      return wide(s) % v;
    }

    friend EVE_FORCEINLINE  auto operator%(wide const& v, integral_scalar_value auto s) noexcept
                            requires( integral_scalar_value<Type> )
    {
      return v % wide(s);
    }

    // TODO
    // >>= <<=

    //==============================================================================================
    // Numerical comparisons
    //==============================================================================================
    friend EVE_FORCEINLINE auto operator<(wide const& v, wide const& w) noexcept
    {
      return detail::self_less(v,w);
    }

    friend EVE_FORCEINLINE auto operator<(wide const& v, scalar_value auto w) noexcept
    {
      return v < wide{w};
    }

    friend EVE_FORCEINLINE auto operator<(scalar_value auto v, wide const& w) noexcept
    {
      return wide{v} < w;
    }

    friend EVE_FORCEINLINE auto operator>(wide const& v, wide const& w) noexcept
    {
      return detail::self_greater(v,w);
    }

    friend EVE_FORCEINLINE auto operator>(wide const& v, scalar_value auto w) noexcept
    {
      return v > wide{w};
    }

    friend EVE_FORCEINLINE auto operator>(scalar_value auto v, wide const& w) noexcept
    {
      return wide{v} > w;
    }

    //==============================================================================================
    // Inserting a logical<wide> into a stream
    //==============================================================================================
    friend std::ostream &operator<<(std::ostream &os, wide const &p)
    {
      constexpr auto sz = sizeof(storage_type)/sizeof(Type);
      auto that = bit_cast( p, as_<std::array<Type,sz>>());

      os << '(' << +that[ 0 ];
      for(size_type i = 1; i != p.size(); ++i) os << ", " << +that[ i ];
      return os << ')';
    }
  };
}
