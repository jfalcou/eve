//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_ARCH_CPU_LOGICAL_WIDE_HPP_INCLUDED
#define EVE_ARCH_CPU_LOGICAL_WIDE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/arch/cpu/logical.hpp>
#include <type_traits>
#include <iostream>
#include <cstring>

#if defined(EVE_COMP_IS_GNUC)
#  pragma GCC diagnostic push
#  pragma GCC diagnostic ignored "-Wuninitialized"
#  pragma GCC diagnostic ignored "-Wmaybe-uninitialized"
#endif

namespace eve
{
  template<typename Type, typename N, typename ABI>
  struct logical<wide<Type,N,ABI>>
  {
    using parent    = wide<logical<Type>,N>;
    using bits_type = wide<detail::as_integer_t<Type, unsigned>,N>;
    using mask_type = wide<Type,N>;

    using storage_type            = typename parent::storage_type;
    using cardinal_type           = typename parent::cardinal_type;
    using abi_type                = typename parent::abi_type;
    using value_type              = typename parent::value_type;
    using size_type               = typename parent::size_type;
    using reference               = typename parent::reference;
    using const_reference         = typename parent::const_reference;
    using iterator                = typename parent::iterator;
    using const_iterator          = typename parent::const_iterator;
    using reverse_iterator        = typename parent::reverse_iterator;
    using const_reverse_iterator  = typename parent::const_reverse_iterator;
    using target_type             = typename parent::target_type;

    static constexpr std::size_t static_size      = parent::static_size;
    static constexpr std::size_t static_alignment = parent::static_alignment;

    // ---------------------------------------------------------------------------------------------
    // Ctor
    EVE_FORCEINLINE logical() noexcept {}
    EVE_FORCEINLINE logical(storage_type const &r) noexcept : data_(r) {}

    // ---------------------------------------------------------------------------------------------
    // Constructs a wide from a Range
    template<typename Iterator>
    EVE_FORCEINLINE explicit logical( Iterator b,
                                      Iterator e,
                                      std::enable_if_t<detail::is_iterator_v<Iterator>> * = 0) noexcept
        : data_(detail::load(as_<logical>{}, abi_type{}, b, e))
    {
    }

    template<typename Range>
    EVE_FORCEINLINE explicit logical( Range &&r,
                                      std::enable_if_t<detail::is_range_v<Range> &&
                                      !is_vectorized_v<Range> &&
                                      !std::is_same_v<storage_type, Range>> * = 0) noexcept
        : logical(std::begin(std::forward<Range>(r)), std::end(std::forward<Range>(r)))
    {
    }

    // ---------------------------------------------------------------------------------------------
    // Constructs a wide from a pointer
    EVE_FORCEINLINE explicit logical(logical<Type> *ptr) noexcept
        : data_(detail::load(as_<logical>{}, abi_type{}, ptr))
    {
    }

    template<std::size_t Alignment, typename = std::enable_if_t<(Alignment >= static_alignment)>>
    EVE_FORCEINLINE explicit logical(aligned_ptr<logical<Type>, Alignment> ptr) noexcept
        : data_(detail::load(as_<logical>{}, abi_type{}, ptr))
    {
    }

    // ---------------------------------------------------------------------------------------------
    // Constructs a wide from a single value
    template<typename T, typename = std::enable_if_t<std::is_convertible_v<T, logical<Type>>>>
    EVE_FORCEINLINE explicit logical(T const &v) noexcept
        : data_(detail::make(as_<target_type>{}, abi_type{}, v))
    {
    }

    // ---------------------------------------------------------------------------------------------
    // Constructs a wide from a sequence of values
    template< typename T0,
              typename T1,
              typename... Ts,
              bool Converts =   std::is_convertible_v<T0, logical<Type>>
                            &&  std::is_convertible_v<T1, logical<Type>>
                            && (... && std::is_convertible_v<Ts, logical<Type>>),
              typename      = std::enable_if_t<(static_size == 2 + sizeof...(Ts)) && Converts>
            >
    EVE_FORCEINLINE logical(T0 const &v0, T1 const &v1, Ts const &... vs) noexcept
        : data_(detail::make(as_<target_type>{}, abi_type{}, v0, v1, vs...))
    {}

    // ---------------------------------------------------------------------------------------------
    // Constructs a wide with a generator function
    template<typename Generator>
    EVE_FORCEINLINE
    logical(Generator &&g,
            std::enable_if_t<std::is_invocable_v<Generator, size_type, size_type>> * = 0) noexcept
    {
      for(size_type i = 0; i < size(); ++i)
        this->operator[](i) = static_cast<logical<Type>>(std::forward<Generator>(g)(i, static_size));
    }

    // ---------------------------------------------------------------------------------------------
    // Constructs a wide from a pair of sub-wide
    template<typename HalfSize, typename Other>
    EVE_FORCEINLINE logical(logical<wide<Type, HalfSize, Other>> const &l,
                            logical<wide<Type, HalfSize, Other>> const &h,
                            std::enable_if_t<static_size == 2 * HalfSize::value> * = 0)
        : logical(detail::combine(EVE_CURRENT_API{}, l.bits(), h.bits()), from_bits)
    {
    }

    // ---------------------------------------------------------------------------------------------
    // Internal constructors
    template<typename Storage>
    EVE_FORCEINLINE logical(Storage const &s, from_bits_ const &)
    {
      void const *src = reinterpret_cast<detail::alias_t<void const> *>(&s);
      void *      dst = reinterpret_cast<detail::alias_t<void> *>(&data_.storage());
      std::memcpy(dst, src, sizeof(s));
    }

    // ---------------------------------------------------------------------------------------------
    // Assignment
    EVE_FORCEINLINE logical& operator=(bool b)
    {
      return (*this = logical<Type>{b});
    }

    EVE_FORCEINLINE logical &operator=(logical<Type> const& v) noexcept
    {
      data_ = detail::make(as_<target_type>{}, abi_type{}, v);
      return *this;
    }

    template<typename Slice>
    EVE_FORCEINLINE auto slice(Slice const &s) const { return detail::slice(*this, s); }
    EVE_FORCEINLINE auto slice() const { return detail::slice(*this); }

    // ---------------------------------------------------------------------------------------------
    // Raw storage access
    EVE_FORCEINLINE storage_type storage() const noexcept { return data_.storage(); }
    EVE_FORCEINLINE storage_type &storage() noexcept { return data_.storage(); }
    EVE_FORCEINLINE operator storage_type() const noexcept { return data_.storage(); }

    // ---------------------------------------------------------------------------------------------
    // array-like interface
    static EVE_FORCEINLINE constexpr size_type size() noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr size_type max_size() noexcept { return static_size; }
    static EVE_FORCEINLINE constexpr bool      empty() noexcept { return false; }

    // ---------------------------------------------------------------------------------------------
    // alignment interface
    static EVE_FORCEINLINE constexpr size_type alignment() noexcept { return static_alignment; }

    // ---------------------------------------------------------------------------------------------
    // swap
    EVE_FORCEINLINE void swap(logical &rhs) noexcept
    {
      data_.swap(rhs.data_);
    }

    // ---------------------------------------------------------------------------------------------
    // begin() variants
    EVE_FORCEINLINE iterator        begin()       noexcept { return data_.begin(); }
    EVE_FORCEINLINE const_iterator  begin() const noexcept { return data_.begin(); }
    EVE_FORCEINLINE const_iterator cbegin() const noexcept { return data_.cbegin(); }

    EVE_FORCEINLINE reverse_iterator         rbegin()       noexcept  { return data_.rbegin();  }
    EVE_FORCEINLINE const_reverse_iterator   rbegin() const noexcept  { return data_.rbegin();  }
    EVE_FORCEINLINE const_reverse_iterator  crbegin() const noexcept  { return data_.crbegin(); }

    // ---------------------------------------------------------------------------------------------
    // end() variants
    EVE_FORCEINLINE iterator        end()       noexcept { return data_.end(); }
    EVE_FORCEINLINE const_iterator  end() const noexcept { return data_.end(); }
    EVE_FORCEINLINE const_iterator cend() const noexcept { return data_.cend(); }

    EVE_FORCEINLINE reverse_iterator         rend()       noexcept  { return data_.rend();  }
    EVE_FORCEINLINE const_reverse_iterator   rend() const noexcept  { return data_.rend();  }
    EVE_FORCEINLINE const_reverse_iterator  crend() const noexcept  { return data_.crend(); }

    // ---------------------------------------------------------------------------------------------
    // elementwise access
    EVE_FORCEINLINE reference operator[](std::size_t i) noexcept { return data_[ i ]; }
    EVE_FORCEINLINE const_reference operator[](std::size_t i) const noexcept
    {
      return data_[ i ];
    }

    EVE_FORCEINLINE reference back() noexcept { return data_.back(); }
    EVE_FORCEINLINE const_reference back() const noexcept { return data_.back(); }

    EVE_FORCEINLINE reference front() noexcept { return data_.front(); }
    EVE_FORCEINLINE const_reference front() const noexcept { return data_.front(); }

    // ---------------------------------------------------------------------------------------------
    // logical interface
    EVE_FORCEINLINE logical& self()             { return *this; }
    EVE_FORCEINLINE logical const& self() const { return *this; }

    EVE_FORCEINLINE constexpr bits_type bits() const noexcept
    {
      return bitwise_cast<bits_type>( mask() );
    }

    /// Convert a logical to a typed mask value
    EVE_FORCEINLINE constexpr mask_type mask() const noexcept
    {
      return bitwise_cast<mask_type>( self() );
    }

    // ---------------------------------------------------------------------------------------------
    // Not supported operators
    auto operator++()     const = delete;
    auto operator++(int)  const = delete;
    auto operator--()     const = delete;
    auto operator--(int)  const = delete;
    template<typename Other> auto operator+=(Other const &other) = delete;
    template<typename Other> auto operator-=(Other const &other) = delete;
    template<typename Other> auto operator&=(Other const &other)  = delete;
    template<typename Other> auto operator|=(Other const &other) = delete;
    template<typename Other> auto operator^=(Other const &other) = delete;

    private:
    wide<logical<Type>,N> data_;
  };

  /// Stream insertion operator
  template<typename Type, typename N, typename ABI>
  EVE_FORCEINLINE std::ostream &operator<<(std::ostream &os, logical<wide<Type,N,ABI>> const &p)
  {
    os << '(' << p[0];
    for(std::size_t i = 1; i != p.size(); ++i) os << ", " << p[i];
    return os << ')';
  }
}

#if defined(EVE_COMP_IS_GNUC)
#  pragma GCC diagnostic pop
#endif

#endif


