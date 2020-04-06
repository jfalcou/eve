//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_CPU_WIDE_HPP_INCLUDED
#define EVE_ARCH_CPU_WIDE_HPP_INCLUDED

#include <eve/arch/spec.hpp>
#include <eve/arch/expected_cardinal.hpp>
#include <eve/arch/as_register.hpp>
#include <eve/detail/base_wide.hpp>
#include <eve/detail/function/combine.hpp>
#include <eve/detail/function/lookup.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/detail/function/make.hpp>
#include <eve/detail/function/load.hpp>
#include <eve/detail/function/fill.hpp>
#include <eve/detail/alias.hpp>
#include <eve/detail/spy.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/sub.hpp>
#include <eve/function/add.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/div.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/bit_xor.hpp>
#include <eve/concept/stdconcepts.hpp>
#include <eve/concept/range.hpp>
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
  // Wrapper for SIMD registers holding arithmetic types with compile-time size
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

    // ---------------------------------------------------------------------------------------------
    // Ctor
    EVE_FORCEINLINE wide() noexcept {}

    EVE_FORCEINLINE wide(storage_type const &r) noexcept
        : data_(r)
    {
    }

    // ---------------------------------------------------------------------------------------------
    // Constructs a wide from a Range
    template<typename Iterator>
    EVE_FORCEINLINE explicit wide(Iterator b, Iterator e) noexcept
                    requires( std::input_iterator<Iterator> )
        : data_(detail::load(as_<wide>{}, abi_type{}, b, e))
    {
    }

    template<typename Range>
    EVE_FORCEINLINE explicit wide(Range &&r) noexcept
          requires( detail::range<Range> && !is_Vectorized_v<Range> && !std::same_as<storage_type, Range>)
        : wide(std::begin(std::forward<Range>(r)), std::end(std::forward<Range>(r)))
    {
    }

    // ---------------------------------------------------------------------------------------------
    // Constructs a wide from a pointer
    EVE_FORCEINLINE explicit wide(Type const *ptr) noexcept
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

    // ---------------------------------------------------------------------------------------------
    // Constructs a wide from a single value
    template<typename T>
    EVE_FORCEINLINE explicit  wide(T const &v)  noexcept requires( std::convertible_to<T, Type> )
                            : data_(detail::make(as_<target_type>{}, abi_type{}, v))
    {
    }

    // ---------------------------------------------------------------------------------------------
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

    // ---------------------------------------------------------------------------------------------
    // Constructs a wide with a generator function
    template<typename Generator>
    EVE_FORCEINLINE wide(Generator &&g) noexcept
                    requires( std::invocable<Generator,size_type,size_type>)
                  : data_( detail::fill(as_<wide>{}, abi_type{}, std::forward<Generator>(g)) )
    {}

    // ---------------------------------------------------------------------------------------------
    // Constructs a wide from a pair of sub-wide
    template<typename HalfSize>
    EVE_FORCEINLINE wide( wide<Type, HalfSize> const &l
                        , wide<Type, HalfSize> const &h
                        ) noexcept
                    requires( static_size == 2 * HalfSize::value )
                  : data_(detail::combine(EVE_CURRENT_API{}, l, h))
    {
    }

    // ---------------------------------------------------------------------------------------------
    // Assign a single value to a wide
    EVE_FORCEINLINE wide &operator=(Type v) noexcept
    {
      data_ = detail::make(as_<target_type>{}, abi_type{}, v);
      return *this;
    }

    // ---------------------------------------------------------------------------------------------
    // Raw storage access
    EVE_FORCEINLINE storage_type storage() const noexcept { return data_; }
    EVE_FORCEINLINE storage_type &storage() noexcept { return data_; }

    EVE_FORCEINLINE operator storage_type() const noexcept { return data_; }

    // ---------------------------------------------------------------------------------------------
    // array-like interface
    static EVE_FORCEINLINE constexpr size_type size() noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr size_type max_size() noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr bool      empty() noexcept { return false; }

    // ---------------------------------------------------------------------------------------------
    // alignment interface
    static EVE_FORCEINLINE constexpr size_type alignment() noexcept { return static_alignment; }

    // ---------------------------------------------------------------------------------------------
    // slice interface
    EVE_FORCEINLINE auto slice() const { return detail::slice(*this); }

    template<typename Slice>
    EVE_FORCEINLINE auto slice(Slice const &s) const
    {
      return detail::slice(*this, s);
    }

    // ---------------------------------------------------------------------------------------------
    // swap
    EVE_FORCEINLINE void swap(wide &rhs) noexcept
    {
      using std::swap;
      swap(data_, rhs.data_);
    }

    wide &      self() { return *this; }
    wide const &self() const { return *this; }

    // ---------------------------------------------------------------------------------------------
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

    // ---------------------------------------------------------------------------------------------
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

    // ---------------------------------------------------------------------------------------------
    // Dynamic index lookup
    template<typename Index>
    EVE_FORCEINLINE wide operator[](wide<Index,Size> const& idx) noexcept
    {
      return lookup(*this,idx);
    }

    // ---------------------------------------------------------------------------------------------
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

    // ---------------------------------------------------------------------------------------------
    // Self-increment/decrement operators
    EVE_FORCEINLINE wide &operator++() noexcept
    {
      *this += Type{1};
      return *this;
    }

    EVE_FORCEINLINE wide operator++(int) noexcept
    {
      auto that(*this);
           operator++();
      return that;
    }

    EVE_FORCEINLINE wide &operator--() noexcept
    {
      *this -= Type{1};
      return *this;
    }

    EVE_FORCEINLINE wide operator--(int) noexcept
    {
      auto that(*this);
           operator--();
      return that;
    }

    // ---------------------------------------------------------------------------------------------
    // Self-assignment operators
    template<typename Other>
    EVE_FORCEINLINE wide &operator+=(Other const &other) noexcept
    {
      *this = eve::add(*this, other);
      return *this;
    }

    template<typename Other>
    EVE_FORCEINLINE wide &operator-=(Other const &other) noexcept
    {
      *this = eve::sub(*this, other);
      return *this;
    }

    template<typename Other>
    EVE_FORCEINLINE wide &operator*=(Other const &other) noexcept
    {
      *this = eve::mul(*this, other);
      return *this;
    }

    template<typename Other>
    EVE_FORCEINLINE wide &operator/=(Other const &other) noexcept
    {
      *this = eve::div(*this, other);
      return *this;
    }

    template<typename Other>
    EVE_FORCEINLINE wide &operator&=(Other const &other) noexcept
    {
      *this = eve::bit_and(*this, other);
      return *this;
    }

    template<typename Other>
    EVE_FORCEINLINE wide &operator|=(Other const &other) noexcept
    {
      *this = eve::bit_or(*this, other);
      return *this;
    }

    template<typename Other>
    EVE_FORCEINLINE wide &operator^=(Other const &other) noexcept
    {
      *this = eve::bit_xor(*this, other);
      return *this;
    }

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

#if defined(SPY_COMPILER_IS_GNUC)
#  pragma GCC diagnostic pop
#endif

#endif
