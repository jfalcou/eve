//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/memory/align.hpp>
#include <eve/memory/is_aligned.hpp>
#include <eve/memory/is_aligned.hpp>
#include <eve/traits/alignment.hpp>
#include <eve/traits/element_type.hpp>
#include <compare>

namespace eve
{
  template< typename Type
          , std::size_t Alignment = sizeof(Type) * expected_cardinal_v<Type>
          >
  requires(is_power_of_2(Alignment))
  struct aligned_ptr
  {
    using pointer = std::add_pointer_t<Type>;

    template<typename T> using rebind = aligned_ptr<T,Alignment>;

    static constexpr std::size_t alignment() { return Alignment; }

    aligned_ptr() noexcept {}
    aligned_ptr(std::nullptr_t) noexcept : pointer_(nullptr) {}

    aligned_ptr(pointer p) noexcept : pointer_(p)
    {
      EVE_ASSERT(is_aligned<Alignment>(p),(void *)(p) << " is not aligned on " << Alignment << ".");
    }

    auto operator<=>(const aligned_ptr<Type, Alignment>&) const = default;
    template<typename U, std::size_t A>
    aligned_ptr(aligned_ptr<U, A> p) noexcept requires(A >= Alignment)
              : pointer_(static_cast<pointer>(p.get()))
    {}

    template<std::size_t A>
    aligned_ptr(aligned_ptr<void, A> p) noexcept requires(A >= Alignment)
              : pointer_(static_cast<pointer>(p.get()))
    {
    }

    template<typename U, std::size_t A>
    aligned_ptr &operator=(aligned_ptr<U, A> p) noexcept
    requires( (A >= Alignment) && std::convertible_to<U*, pointer> )
    {
      pointer_ = static_cast<pointer>(p.get());
      return *this;
    }

    template<std::size_t A>
    aligned_ptr &operator=(aligned_ptr<void, A> p) noexcept  requires(A >= Alignment)
    {
      pointer_ = static_cast<pointer>(p.get());
      return *this;
    }

    aligned_ptr &operator+=(std::ptrdiff_t o) noexcept
    {
      EVE_ASSERT(is_aligned<Alignment>(pointer_ + o),
                 (void *)(pointer_) << " + " << o << " is not aligned on " << Alignment << ".");

      pointer_ += o;
      return *this;
    }

    aligned_ptr &operator-=(std::ptrdiff_t o) noexcept
    {
      EVE_ASSERT( is_aligned<Alignment>(pointer_ - o)
                , (void *)(pointer_) << " - " << o << " is not aligned on " << Alignment << "."
                );

      pointer_ -= o;
      return *this;
    }

    aligned_ptr &operator++() noexcept requires(Alignment == 1)
    {
      pointer_++;
      return *this;
    }

    aligned_ptr operator++(int) noexcept requires(Alignment == 1)
    {
      aligned_ptr tmp(*this);
      this->      operator++();
      return tmp;
    }

    aligned_ptr &operator--() noexcept requires(Alignment == 1)
    {
      pointer_--;
      return *this;
    }

    aligned_ptr operator--(int) noexcept requires(Alignment == 1)
    {
      aligned_ptr tmp(*this);
      this->      operator--();
      return tmp;
    }

    explicit operator bool() const noexcept { return pointer_ != nullptr; }
    pointer  get() const noexcept { return pointer_; }
    explicit operator pointer() const noexcept { return pointer_; }

    Type const &operator[](std::size_t i) const noexcept { return pointer_[ i ]; }
    Type &      operator[](std::size_t i) noexcept { return pointer_[ i ]; }

    decltype(auto) operator*() const noexcept { return *pointer_; }
    decltype(auto) operator*() noexcept { return *pointer_; }

    decltype(auto) operator-> () const noexcept { return pointer_; }
    decltype(auto) operator-> () noexcept { return pointer_; }

    void swap(aligned_ptr &that) noexcept { std::swap(pointer_, that.pointer_); }

    private:
    pointer pointer_;
  };

  template<std::size_t Alignment>  requires(is_power_of_2(Alignment))
  struct aligned_ptr<void, Alignment>
  {
    using pointer = void *;

    template<typename T> using rebind = aligned_ptr<T,Alignment>;

    static constexpr std::size_t alignment() { return Alignment; }

    aligned_ptr() noexcept {}
    aligned_ptr(std::nullptr_t) noexcept : pointer_(nullptr) {}
    aligned_ptr(pointer p) noexcept : pointer_(p)
    {
      EVE_ASSERT(is_aligned<Alignment>(p),(void *)(p) << " is not aligned on " << Alignment << ".");
    }

    template<typename U, std::size_t A>
    aligned_ptr(aligned_ptr<U, A> p) noexcept
    requires( (A >= Alignment) && std::convertible_to<U*, pointer> )
    {
      pointer_ = p.get();
    }

    template<typename U, std::size_t A>
    aligned_ptr &operator=(aligned_ptr<U, A> p) noexcept
                requires( (A >= Alignment) && std::convertible_to<U*, pointer> )
    {
      pointer_ = p.get();
      return *this;
    }

    aligned_ptr &operator=(pointer p) noexcept
    {
      assert(is_aligned<Alignment>(p));
      pointer_ = p;
      return *this;
    }

    explicit operator bool() const noexcept { return pointer_ != nullptr; }
    pointer  get() const noexcept { return pointer_; }
    void     swap(aligned_ptr &that) noexcept { std::swap(pointer_, that.pointer_); }

  private:
    pointer pointer_;
  };

  template<typename T, std::size_t A> struct element_type<aligned_ptr<T,A>> { using type = T; };
  template<typename T>                struct element_type<aligned_ptr<T>>   { using type = T; };

  template<typename T1, std::size_t A1, typename T2, std::size_t A2>
  bool operator==(aligned_ptr<T1, A1> lhs, aligned_ptr<T2, A2> rhs) noexcept
  {
    return lhs.get() == rhs.get();
  }

  template<typename T, std::size_t A>
  bool operator==(aligned_ptr<T, A> lhs, T* rhs) noexcept
  {
    return lhs.get() == rhs;
  }

  template<typename T, std::size_t A>
  bool operator==(T* lhs, aligned_ptr<T, A> rhs) noexcept
  {
    return rhs.get() == lhs;
  }

  template<typename T, std::size_t A>
  bool operator==(aligned_ptr<T, A> lhs, std::nullptr_t) noexcept
  {
    return lhs.get() == nullptr;
  }

  template<typename T, std::size_t A>
  bool operator==(std::nullptr_t, aligned_ptr<T, A> rhs) noexcept
  {
    return rhs.get() == nullptr;
  }

  template<typename T1, std::size_t A1, typename T2, std::size_t A2>
  bool operator!=(aligned_ptr<T1, A1> lhs, aligned_ptr<T2, A2> rhs) noexcept
  {
    return lhs.get() != rhs.get();
  }

  template<typename T, std::size_t A>
  bool operator!=(aligned_ptr<T, A> lhs, T* rhs) noexcept
  {
    return lhs.get() != rhs;
  }

  template<typename T, std::size_t A>
  bool operator!=(T* lhs, aligned_ptr<T, A> rhs) noexcept
  {
    return rhs.get() != lhs;
  }

  template<typename T, std::size_t A>
  bool operator!=(aligned_ptr<T, A> lhs, std::nullptr_t) noexcept
  {
    return lhs.get() !=nullptr;
  }

  template<typename T, std::size_t A>
  bool operator!=(std::nullptr_t, aligned_ptr<T, A> rhs) noexcept
  {
    return rhs.get()!= nullptr;
  }

  template<typename Type, std::size_t Alignment>
  void swap(aligned_ptr<Type, Alignment> &lhs, aligned_ptr<Type, Alignment> &rhs) noexcept
  {
    lhs.swap(rhs);
  }

  template<typename Type, std::size_t Alignment>
  aligned_ptr<Type, Alignment> operator-(aligned_ptr<Type, Alignment> const &p,
                                         std::ptrdiff_t                      o) noexcept
  {
    auto that = p;
    return that -= o;
  }

  template<typename Type, std::size_t Alignment>
  aligned_ptr<Type, Alignment> operator+(aligned_ptr<Type, Alignment> const &p,
                                         std::ptrdiff_t                      o) noexcept
  {
    auto that = p;
    return that += o;
  }

  template<typename Type, std::size_t Alignment>
  aligned_ptr<Type, Alignment> operator+(std::ptrdiff_t                      o,
                                         aligned_ptr<Type, Alignment> const &p) noexcept
  {
    auto that = p;
    return that += o;
  }

  template<std::size_t Alignment, typename Type>
  aligned_ptr<Type, Alignment> as_aligned(Type *ptr) noexcept
  {
    return {ptr};
  }

  template<typename Type>
  aligned_ptr<Type> as_aligned(Type *ptr) noexcept
  {
    return {ptr};
  }

  template<std::size_t Alignment, typename Type>
  aligned_ptr<Type const, Alignment> as_aligned(Type const *ptr) noexcept
  {
    return {ptr};
  }

  template<typename Type>
  aligned_ptr<Type const> as_aligned(Type const *ptr) noexcept
  {
    return {ptr};
  }

  template<std::size_t A, typename T, std::size_t B>
  constexpr bool is_aligned(aligned_ptr<T, B> const &ptr) noexcept
  {
    if constexpr(A <= B)  return true;
    else                  return is_aligned(ptr.get());
  }

  //================================================================================================
  //  Specialisation for pointer_alignment
  //================================================================================================
  template<typename Type, std::size_t Alignment>
  struct  pointer_alignment<aligned_ptr<Type, Alignment>>
        : std::integral_constant<std::size_t,Alignment>
  {};

  template <typename T, typename Cardinal>
  EVE_FORCEINLINE auto previous_aligned_address(T* p, Cardinal /*width*/) noexcept
  {
    static constexpr std::size_t alignment = Cardinal() * sizeof(T);
    return eve::aligned_ptr<T, alignment>{eve::align(p, eve::under{alignment})};
  }

  template <typename T>
  EVE_FORCEINLINE auto previous_aligned_address(T* p) noexcept
  {
    return previous_aligned_address(p, eve::expected_cardinal<std::remove_cvref_t<T>>{});
  }
}
