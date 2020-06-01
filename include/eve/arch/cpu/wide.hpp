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

#include <eve/arch/spec.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/arch/as_register.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/concept/range.hpp>
#include <eve/detail/base_wide.hpp>
#include <eve/detail/function/compounds.hpp>
#include <eve/detail/function/combine.hpp>
#include <eve/detail/function/lookup.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/detail/function/make.hpp>
#include <eve/detail/function/load.hpp>
#include <eve/detail/function/fill.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/spy.hpp>
#include <eve/detail/abi.hpp>
#include <type_traits>
#include <iterator>
#include <iostream>

#if defined(SPY_COMPILER_IS_GNUC)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wignored-attributes"
#  pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#  pragma GCC diagnostic ignored "-Wuninitialized"
#endif

namespace eve
{
  //================================================================================================
  // Wrapper for SIMD registers holding arithmetic types with compile-time size
  //================================================================================================
  template<typename Type, typename Size, typename ABI>
  struct EVE_MAY_ALIAS wide
  {
    using storage_type           = ::eve::as_register_t<Type, Size, ABI>;
    using cardinal_type          = Size;
    using abi_type               = ABI;
    using value_type             = Type;
    using size_type              = std::ptrdiff_t;
    using reference              = Type &;
    using const_reference        = Type const &;
    using iterator               = Type *;
    using const_iterator         = Type const *;
    using reverse_iterator       = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    using target_type = typename detail::target_type<wide, abi_type>::type;

    static constexpr size_type   static_size = Size::value;
    static constexpr std::size_t static_alignment =
        detail::wide_align<Size, value_type, storage_type, abi_type>::value;

    using iterator_facade = detail::wide_iterator<Type, storage_type, abi_type>;

    template<typename T, typename N = expected_cardinal_t<T>>
    using rebind = wide<T,N>;

    //==============================================================================================
    // Ctor
    //==============================================================================================
    EVE_FORCEINLINE wide() noexcept {}

    EVE_FORCEINLINE wide(storage_type const &r) noexcept
        : data_(r)
    {
    }

    //==============================================================================================
    // Constructs a wide from a Range
    //==============================================================================================
    template<std::input_iterator Iterator>
    EVE_FORCEINLINE explicit wide(Iterator b, Iterator e) noexcept
                  : data_(detail::load(as_<wide>{}, abi_type{}, b, e))
    {
    }

    template<detail::range Range>
    EVE_FORCEINLINE explicit wide(Range &&r) noexcept
          requires( !simd_value<Range> && !std::same_as<storage_type, Range>)
        : wide(std::begin(std::forward<Range>(r)), std::end(std::forward<Range>(r)))
    {
    }

    //==============================================================================================
    // Constructs a wide from a pointer
    //==============================================================================================
    EVE_FORCEINLINE explicit wide(Type const *ptr) noexcept
        : data_(detail::load(as_<wide>{}, abi_type{}, ptr))
    {
    }

    EVE_FORCEINLINE explicit wide(Type *ptr) noexcept
        : data_(detail::load(as_<wide>{}, abi_type{}, ptr))
    {
    }

    template<std::size_t Alignment>
    EVE_FORCEINLINE explicit wide(aligned_ptr<Type const, Alignment> ptr) noexcept
                    requires(Alignment >= static_alignment)
                  : data_(detail::load(as_<wide>{}, abi_type{}, ptr))
    {
    }

    template<std::size_t Alignment>
    EVE_FORCEINLINE explicit wide(aligned_ptr<Type, Alignment> ptr) noexcept
                    requires(Alignment >= static_alignment)
                  : data_(detail::load(as_<wide>{}, abi_type{}, ptr))
    {
    }

    //==============================================================================================
    // Constructs a wide from a single value
    template<typename T>
    EVE_FORCEINLINE explicit  wide(T const &v)  noexcept requires( std::convertible_to<T, Type> )
                            : data_(detail::make(as_<target_type>{}, abi_type{}, v))
    {
    }

    //==============================================================================================
    // Constructs a wide from a sequence of values
    template<typename T0, typename T1, typename... Ts>
    EVE_FORCEINLINE wide(T0 const &v0, T1 const &v1, Ts const &... vs) noexcept
          requires(     std::convertible_to<T0,Type> && std::convertible_to<T0,Type>
                    &&  (... && std::convertible_to<Ts,Type>)
                    &&  (static_size == 2 + sizeof...(Ts))
                  )
        : data_(detail::make(as_<target_type>{}, abi_type{}, v0, v1, vs...))
    {
    }

    //==============================================================================================
    // Constructs a wide with a generator function
    template<typename Generator>
    EVE_FORCEINLINE wide(Generator &&g) noexcept
                    requires( std::invocable<Generator,size_type,size_type>)
                  : data_( detail::fill(as_<wide>{}, abi_type{}, std::forward<Generator>(g)) )
    {}

    //==============================================================================================
    // Constructs a wide from a pair of sub-wide
    template<typename HalfSize>
    EVE_FORCEINLINE wide( wide<Type, HalfSize> const &l
                        , wide<Type, HalfSize> const &h
                        ) noexcept
                    requires( static_size == 2 * HalfSize::value )
                  : data_(detail::combine(EVE_CURRENT_API{}, l, h))
    {
    }

    //==============================================================================================
    // Assign a single value to a wide
    EVE_FORCEINLINE wide &operator=(Type v) noexcept
    {
      data_ = detail::make(as_<target_type>{}, abi_type{}, v);
      return *this;
    }

    //==============================================================================================
    // Raw storage access
    EVE_FORCEINLINE storage_type storage() const noexcept { return data_; }
    EVE_FORCEINLINE storage_type &storage() noexcept { return data_; }

    EVE_FORCEINLINE operator storage_type() const noexcept { return data_; }

    //==============================================================================================
    // array-like interface
    static EVE_FORCEINLINE constexpr size_type size() noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr size_type max_size() noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr bool      empty() noexcept { return false; }

    //==============================================================================================
    // alignment interface
    static EVE_FORCEINLINE constexpr size_type alignment() noexcept { return static_alignment; }

    //==============================================================================================
    // slice interface
    EVE_FORCEINLINE auto slice() const { return detail::slice(*this); }

    template<typename Slice>
    EVE_FORCEINLINE auto slice(Slice const &s) const
    {
      return detail::slice(*this, s);
    }

    //==============================================================================================
    // swap
    EVE_FORCEINLINE void swap(wide &rhs) noexcept
    {
      using std::swap;
      swap(data_, rhs.data_);
    }

    wide &      self() { return *this; }
    wide const &self() const { return *this; }

    //==============================================================================================
    // begin() variants
    EVE_FORCEINLINE iterator begin() noexcept { return iterator_facade::begin(data_); }
    EVE_FORCEINLINE const_iterator begin() const noexcept { return iterator_facade::begin(data_); }

    EVE_FORCEINLINE const_iterator cbegin() const noexcept
    {
      return iterator_facade::begin(static_cast<storage_type const &>(data_));
    }

    EVE_FORCEINLINE reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
    EVE_FORCEINLINE const_reverse_iterator rbegin() const noexcept
    {
      return reverse_iterator(end());
    }
    EVE_FORCEINLINE const_reverse_iterator crbegin() const noexcept
    {
      return const_reverse_iterator(cend());
    }

    //==============================================================================================
    // end() variants
    EVE_FORCEINLINE iterator end() noexcept { return begin() + size(); }
    EVE_FORCEINLINE const_iterator end() const noexcept { return begin() + size(); }
    EVE_FORCEINLINE const_iterator cend() const noexcept { return cbegin() + size(); }

    EVE_FORCEINLINE reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
    EVE_FORCEINLINE const_reverse_iterator rend() const noexcept
    {
      return reverse_iterator(begin());
    }
    EVE_FORCEINLINE const_reverse_iterator crend() const noexcept
    {
      return const_reverse_iterator(cbegin());
    }

    //==============================================================================================
    // Dynamic index lookup
    template<typename Index>
    EVE_FORCEINLINE wide operator[](wide<Index,Size> const& idx) noexcept
    {
      return lookup(*this,idx);
    }

    //==============================================================================================
    // elementwise access
    EVE_FORCEINLINE reference operator[](std::size_t i) noexcept { return begin()[ i ]; }
    EVE_FORCEINLINE const_reference operator[](std::size_t i) const noexcept
    {
      return begin()[ i ];
    }

    EVE_FORCEINLINE reference back() noexcept { return *rbegin(); }
    EVE_FORCEINLINE const_reference back() const noexcept { return *rbegin(); }

    EVE_FORCEINLINE reference front() noexcept { return *begin(); }
    EVE_FORCEINLINE const_reference front() const noexcept { return *begin(); }

    //===============================================================================================
    // Self-increment/decrement operators
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

    //==============================================================================================
    // SIMD register storage
    //==============================================================================================
    private:
    storage_type data_;
  };

  template<typename T, typename N, typename ABI>
  EVE_FORCEINLINE void swap(wide<T, N, ABI> &lhs, wide<T, N, ABI> &rhs) noexcept
  {
    lhs.swap(rhs);
  }

  template<typename T, typename N, typename ABI>
  std::ostream &operator<<(std::ostream &os, wide<T, N, ABI> const &p)
  {
    using size_type = typename wide<T, N, ABI>::size_type;
    T that[ N::value ];
    memcpy(&that[ 0 ], p.begin(), N::value * sizeof(T));

    os << '(' << +that[ 0 ];
    for(size_type i = 1; i != p.size(); ++i) os << ", " << +that[ i ];
    return os << ')';
  }
}

// + - * / & ^ | + infix version made from compounds versions ?
//#include <eve/detail/function/operators.hpp>

#if defined(SPY_COMPILER_IS_GNUC)
#  pragma GCC diagnostic pop
#endif

