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
    // Default constructor
    //==============================================================================================
    EVE_FORCEINLINE wide() noexcept {}

    //==============================================================================================
    // Constructs a wide from a native SIMD storage
    //==============================================================================================
    EVE_FORCEINLINE wide(storage_type const &r) noexcept : storage_base(r) {}

    //==============================================================================================
    // Constructs a wide from a Range
    //==============================================================================================
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

    //==============================================================================================
    // Constructs a wide from a pointer or an aligned pointer
    //==============================================================================================
    EVE_FORCEINLINE explicit  wide(simd_compatible_ptr<wide> auto ptr) noexcept
                            : storage_base(detail::load(eve::as_<wide>{}, ptr))
    {}

    //==============================================================================================
    // Constructs a wide from a single value
    //==============================================================================================
    EVE_FORCEINLINE explicit  wide(scalar_value auto v)  noexcept
                            : storage_base(detail::make(eve::as_<wide>{}, v))
    {}

    //==============================================================================================
    // Constructs a wide from a sequence of values
    //==============================================================================================
    EVE_FORCEINLINE wide( scalar_value auto v0, scalar_value auto v1
                        , scalar_value auto... vs
                        ) noexcept requires( card_base::static_size == 2 + sizeof...(vs) )
                  : storage_base(detail::make(eve::as_<wide>{}, v0, v1, vs...))
    {}

    //==============================================================================================
    // Constructs a wide with a generator function
    //==============================================================================================
    template<std::invocable<size_type,size_type> Generator>
    EVE_FORCEINLINE wide(Generator &&g) noexcept
                  : storage_base( detail::fill(eve::as_<wide>{}, std::forward<Generator>(g)) )
    {}

    //==============================================================================================
    // Constructs a wide from a pair of sub-wide
    //==============================================================================================
    template<typename halfSize>
    EVE_FORCEINLINE wide( wide<Type, halfSize> const &l
                        , wide<Type, halfSize> const &h
                        ) noexcept
                    requires( card_base::static_size == 2 * halfSize::value )
                  : storage_base(detail::combine(EVE_CURRENT_API{}, l, h))
    {
    }

    using detail::wide_ops<wide>::operator=;
    using detail::wide_ops<wide>::operator[];

    //==============================================================================================
    // begin/end interface
    //==============================================================================================
    EVE_FORCEINLINE auto  begin()       noexcept { return detail::at_begin(*this); }
    EVE_FORCEINLINE auto  begin() const noexcept { return detail::at_begin(*this); }

    EVE_FORCEINLINE auto  end()        noexcept { return begin() + card_base::static_size; }
    EVE_FORCEINLINE auto  end() const  noexcept { return begin() + card_base::static_size; }

    //===============================================================================================
    // Self-increment/decrement operators
    //==============================================================================================
    EVE_FORCEINLINE wide &operator++() noexcept
    {
      return detail::self_add(*this, Type{1});
    }

    EVE_FORCEINLINE wide operator++(int) noexcept
    {
      auto that(*this);
           operator++();
      return that;
    }

    EVE_FORCEINLINE wide &operator--() noexcept
    {
      return detail::self_sub(*this, Type{1});
      return *this;
    }

    EVE_FORCEINLINE wide operator--(int) noexcept
    {
      auto that(*this);
           operator--();
      return that;
    }

    //==============================================================================================
    // Compound operators
    //==============================================================================================
    template<typename Other>
    EVE_FORCEINLINE   auto operator+=(Other const &other) noexcept
                  ->  decltype(detail::self_add(*this, other))
    {
      return detail::self_add(*this, other);
    }

    template<typename Other>
    EVE_FORCEINLINE   auto operator-=(Other const &other) noexcept
                  ->  decltype(detail::self_sub(*this, other))
    {
      return detail::self_sub(*this, other);
    }

    template<typename Other>
    EVE_FORCEINLINE   auto operator*=(Other const &other) noexcept
                  ->  decltype(detail::self_mul(*this, other))
    {
      return detail::self_mul(*this, other);
    }

    template<typename Other>
    EVE_FORCEINLINE   auto operator/=(Other const &other) noexcept
                  ->  decltype(detail::self_div(*this, other))
    {
      return detail::self_div(*this, other);
    }

    template<typename Other>
    EVE_FORCEINLINE   auto operator%=(Other const &other) noexcept
                  ->  decltype(detail::self_rem(*this, other))
    {
      return detail::self_rem(*this, other);
    }

    // TODO
    // >>= <<=

    template<typename Other>
    EVE_FORCEINLINE   auto operator&=(Other const &other) noexcept
                  ->  decltype(detail::self_bitand(*this, other))
    {
      return detail::self_bitand(*this, other);
    }

    template<typename Other>
    EVE_FORCEINLINE   auto operator|=(Other const &other) noexcept
                  ->  decltype(detail::self_bitor(*this, other))
    {
      return detail::self_bitor(*this, other);
    }

    template<typename Other>
    EVE_FORCEINLINE   auto operator^=(Other const &other) noexcept
                  ->  decltype(detail::self_bitxor(*this, other))
    {
      return detail::self_bitxor(*this, other);
    }

    friend std::ostream &operator<<(std::ostream &os, wide const &p)
    {
      constexpr auto sz = sizeof(storage_type)/sizeof(Type);
      auto that = bit_cast( p, as_<std::array<Type,sz>>());

      os << '(' << +that[ 0 ];
      for(size_type i = 1; i != p.size(); ++i) os << ", " << +that[ i ];
      return os << ')';
    }
  };

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE void swap(wide<T, N, ABI> &lhs, wide<T, N, ABI> &rhs) noexcept
  {
    lhs.swap(rhs);
  }
}
