//================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/polynomial/regular/polynom.hpp>
#include <map>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief representation of sparse polynoms
  //!
  //! **Required header:** `#include <eve/module/polynomial.hpp>`
  //!
  //! eve::polynom and monom are templates structure representing respactivly polynomials with real
  //! or complex floating coefficients (resp polynomials with only one non zero coefficient).
  //! polynomials are internally based on std:vectors of coefficients on the fundamental basis and in
  //! decreasing powers order, but:
  //!
  //!  \f$ \displaystyle p(x) = \sum_0^n p[i]x^{i]\f$
  //!
  //!
  //! @tparam Type  Underlying scalar floating point type
  //!
  //! provided operators and functions are :
  //!
  //! - constructors
  //!    - trivial constructor provides the null polynomial (of degree -1) with no coefficients
  //!    - a constructor from a range of coefficients in decreasing power order
  //!    - a constructor from an initializer list of coefficients in decreasing power order
  //!    - a constructor from a range of elements in increasing power order (with second parameter eve::upward);
  //!
  //! - operators :
  //!     - +,  -, *, /, %, +=, -=, *=, /=, %=, <<, >>
  //!
  //!       binary operators accept mix of polynom, momom, value_type in any order.
  //!       monomial multiplication can be replaced by shift operators
  //!       division and remainder with null second parameter are UB.
  //!
  //!    - operator(): p(x) evaluates the polynomial p at x. x can be a scalar, an simd value or a range of scalar
  //!                  of the underlying type
  //!                  Take care that if a non const range is evaluted,  it is evaluated in place
  //!    - operator[]: p[i] return the coefficient of order i of the polynomial (i.e. of the monomial \f$x^i\f$.
  //!                  In particular 0 if i is not in the range \f$[0, degree(p)]\f$. (This operator is const).
  //!    - operator==: Two polynomials are equal if and only if they have the same degree and the same coefficients.
  //!    - operator!=: Two polynomials are not equal if and only if they do not have the same degree or two coefficients differ.
  //!
  //!@warning : this is a simple polynomial class not fit for big or sparse polynomials,  but for monomials or
  //!           dense polynomials of small degrees (in particular fft is not used for implementing *
  //!           (i.e. polynomial multiplication which could be written as a convolution)
  //!
  //! - friend functions
  //!     - degree returns the polynomial degree, i.e. the greatest power for which the polynomial
  //!       has a non null coefficient (-1 for the null polynomial)
  //!     - valuation returns the polynomial valuation i.e. the lest power for which the polynomial
  //!       has a non null coefficient (-1 for the null polynomial)
  //!     - remquo computes both the quotient and remainder of euclidian division
  //!     - young(n, p0) suppress all coefficients of degree greater than n,  thus giving the regular part
  //!       of the Taylor-Young devlopment of the polynom
  //!     - young_remainder(n, p0) zeroes all the lower n coefficients of p0 : one have
  //!       young(n, p0)+young_remainder(n, p0) == p0.
  //!       concat(p1, p0) if n is the degree of p0, return the polynom \f$x^{n+1}p1+p0\f$.
  //!     - is_null returns true if and only if the polynomial is of degree -1
  //!     - is_constant returns true if and only if the polynomial is of degree less than 1
  //!     - is_monomial returns true if and only if the polynomial has only one non null coef
  //!     - derivative(p, n) computes the nth derivative of p
  //!     - primive(p, n)    computes a primitive of order n of p (the one with valuation greater or equal to n)
  //!
  //================================================================================================


  template<floating_scalar_value Type>
  struct sparse_polynom
  {
    /// Underlying type
    using value_type = Type;
    using sparse_polynom_t  = sparse_polynom<value_type>;
    using data_t     = std::map<int, value_type, std::greater<int>>;
    using pair_t     = typename data_t::value_type;
    using monom_t    = monom<value_type>;
    using polynom_t  = polynom<value_type>;

    // constructors
    sparse_polynom() {}

    sparse_polynom(value_type const & v) : data{{0, v}}{};
    sparse_polynom(std::initializer_list<pair_t> const & c) : data(c) { normalize();}

    template <detail::range R>
    sparse_polynom(R const & r) : data(r.begin(), r.end()) {normalize();}

    sparse_polynom(monom_t const & m) : data{{degree(m), m[0]}} {};
    sparse_polynom(polynom_t const & p) {
      for(int i=0; i <= degree(p); ++i) data[i] = p[i];
      normalize();
    }

    //==============================================================================================
    //== degree and valuation
    //==============================================================================================
    friend inline int degree(sparse_polynom_t const & p) noexcept
    {
      return p.data.empty() ? -1 : p.data.begin()->first;
    }

    friend inline int valuation(sparse_polynom_t const & p) noexcept
    {
      return p.data.empty() ? -1 :p.data.rbegin()->first;
    }

    //==============================================================================================
    //== coefficients but only for reading.
    //== Out of range returns 0
    //==============================================================================================
    auto operator[](int const & i) const noexcept
    {
      auto search = data.find(i);
      return (search != data.end()) ? search->second : zero(as<value_type>());
    }

    //==============================================================================================
    //== evaluation
    //==============================================================================================
    template <floating_value T>
    auto operator()(T const & x) noexcept
    {
      auto s = T(0);
      for (const auto& [i, value] : data) { s+= pow(x, i)*value; }
      return s;
    }

    template <detail::range R>
    friend void tagged_dispatch( eve::tag::polyval_, inplace_type const&
                               , sparse_polynom_t const & p, R & x)  noexcept
    {
      auto eval = [ p ](auto e){
        auto s = zero(as(e));
        for (const auto& [i, value] : p.data) { s+= eve::pow(e, i)*value; }
        return s;
//       return p(e);
      };
      eve::algo::transform_inplace(x, eval);
    }

    template <detail::range R>
    friend  R tagged_dispatch( eve::tag::polyval_, sparse_polynom_t const & p, const R & x)  noexcept
    {
      return p(x);
    }

    template <detail::range R> [[nodiscard]] R operator()(R const & x) const noexcept
    {
      auto px(x);
      auto eval = [ this ](auto e){
        auto s = zero(as(e));
        for (const auto& [i, value] : data) { s+= pow(e, i)*value; }
        return s;
        //    return this->operator()(e);
      };
      eve::algo::transform_inplace(px, eval);
      return px;
    }

//     //==============================================================================================
//     //== derivatives
//     //==============================================================================================

//     friend sparse_polynom_t & tagged_dispatch( eve::tag::derivative_, inplace_type const &, sparse_polynom_t & p) noexcept
//     {
//       value_type n = degree(p);
//       if(n < 0) return p;
//       else if(n <= 1){ p.data.resize(n); return p;}
//       else
//       {
//         auto factors = eve::algo::views::iota_with_step(n, mone(as(n)), n+1);
//         auto mult = [](auto pair) {
//           auto [x, y] = pair;
//           return x *= y;
//         };
//         eve::algo::transform_to(eve::algo::views::zip(p.data, factors), p.data, mult);
//         p.data.resize(n);
//         return p;
//       }
//     }

//     [[nodiscard]] friend sparse_polynom_t tagged_dispatch( eve::tag::derivative_, sparse_polynom_t const & p0) noexcept
//     {
//       auto p = p0;
//       return inplace(derivative)(p);
//     }

//     [[nodiscard]] friend sparse_polynom_t tagged_dispatch( eve::tag::derivative_
//                                                   , sparse_polynom_t const & p0, size_t m) noexcept
//     {
//       auto p = p0;
//       return inplace(derivative)(p, m);
//     }

//     friend sparse_polynom_t tagged_dispatch( eve::tag::derivative_
//                                     , inplace_type const &, sparse_polynom_t & p, size_t m) noexcept
//     {
//       int n = degree(p);
//       if (int(m) > n)  { p.data.resize(0); return p; }
//       else if (int(m) == n) { p.data.resize(1); return p.data[0] = value_type(factorial(m));}
//       else if (m == 0) return p;
//       else if (m == 1) return inplace(derivative)(p);
//       else
//       {
//         auto factors = eve::algo::views::iota_with_step(n, mone(as(n)), n-m+1);
//         data_t f(n-m+1);
//         p.data.resize(n-m+1);
//         eve::algo::copy(factors, f);
//         auto mult = [](auto pair){
//           auto [x, y] = pair;
//           return x *= y;
//         };
//         eve::algo::transform_to(eve::algo::views::zip(p.data, f), p.data, mult);
//         for(size_t i=2; i <= m; ++i)
//         {
//           eve::algo::transform_inplace(f, dec);
//           eve::algo::transform_to(eve::algo::views::zip(p.data, f), p.data, mult);
//         }
//         return p;
//       }
//     }



//     [[nodiscard]] friend auto tagged_dispatch( eve::tag::derivative_, sparse_polynom_t const & p
//                                              , size_t m, eve::callable_all_) noexcept
//     {
//       int n = degree(p);
//       std::vector<sparse_polynom_t> ders(m+1);
//       ders[0] = p;
//       if (m == 0 || n <= 0) return ders;
//       ders[1] = derivative(p);
//       if (m == 1) return ders;
//       value_type nvt = n;
//       auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)), nvt+1);
//       data_t f(n+1);
//       data_t datad(n+1);
//       eve::algo::copy(factors, datad);
//       eve::algo::copy(factors, f);
//       auto mult = [](auto pair) {
//         auto [x, y] = pair;
//         return x *= y;
//       };
//       eve::algo::transform_to(eve::algo::views::zip(datad, p.data), datad, mult);

//       for(size_t i=2; i <= eve::min(size_t(n), m); ++i)
//       {
//         eve::algo::transform_inplace(f, dec);
//         eve::algo::transform_to(eve::algo::views::zip(datad, f), datad, mult);
//         datad.resize(n-i+1);
//         f.resize(n-i+1);
//         ders[i] = sparse_polynom_t(datad);
//       }
//       return ders;
//     }

//     //==============================================================================================
//     //== primitives
//     //==============================================================================================
//     friend sparse_polynom_t & tagged_dispatch( eve::tag::primitive_
//                                       , inplace_type const &, sparse_polynom_t & p) noexcept
//     {
//       int n = degree(p);
//       if(n < 0) return p;
//       else if(n <= 1){ p.data.resize(n); return p;}
//       else
//       {
//         value_type nvt = n+1;
//         auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)), n+1);
//         auto divi = [](auto pair){
//           auto [x, y] = pair;
//           return x /= y;
//         };
//         eve::algo::transform_to(eve::algo::views::zip(p.data, factors), p.data, divi);
//         p.data.resize(n+2);
//         return p;
//       }
//     }

//     [[nodiscard]] friend sparse_polynom_t tagged_dispatch( eve::tag::primitive_
//                                                   , sparse_polynom_t const & p) noexcept
//     {
//       int n = degree(p);
//       if(n < 0) return sparse_polynom_t();
//       else
//       {
//         value_type nvt = n+1;
//         auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)), n+1);
//         data_t datad(n+1);
//         eve::algo::copy(p.data, datad);
//         auto divi = [](auto pair){
//             auto [x, y] = pair;
//             return x /= y;
//         };
//         eve::algo::transform_to(eve::algo::views::zip(datad, factors), datad, divi);
//         datad.resize(n+2);
//         sparse_polynom_t prim(datad);
//         return prim;
//       }
//     }

//     [[nodiscard]] friend sparse_polynom_t tagged_dispatch( eve::tag::primitive_, sparse_polynom_t & p
//                                     , size_t m) noexcept
//     {
//       int n = degree(p);
//       if (m == 0 || n < 0) return p;
//       else if (m == 1u) return primitive(p);
//       else
//       {
//         value_type nvt = n+1;
//         auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)),n+1);
//         data_t f(n+1);
//         data_t datad(n+1);
//         eve::algo::copy(p.data, datad);
//         eve::algo::copy(factors, f);
//         auto divi = [](auto pair)
//           {
//             auto [x, y] = pair;
//             return x /= y;
//           };
//         eve::algo::transform_to(eve::algo::views::zip(datad, f), datad, divi);
//         for(size_t i=2; i <= m; ++i)
//         {
//           eve::algo::transform_inplace(f, inc);
//           eve::algo::transform_to(eve::algo::views::zip(datad, f), datad, divi);
//         }
//         datad.resize(n+m+1);
//         sparse_polynom_t integ(datad);
//         return integ;
//       }
//     }

//     friend sparse_polynom_t tagged_dispatch( eve::tag::primitive_, inplace_type const &
//                                     , sparse_polynom_t & p, size_t m) noexcept
//     {
//       int n = degree(p);
//       if (m == 0 || n < 0) return p;
//       else if (m == 1u) return inplace(primitive)(p);
//       else
//       {
//         value_type nvt = n+1;
//         auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)),n+1);
//         data_t f(n+1);
//         eve::algo::copy(factors, f);
//         auto divi = [](auto pair) {
//           auto [x, y] = pair;
//           return x /= y;
//         };
//         eve::algo::transform_to(eve::algo::views::zip(p.data, f), p.data, divi);
//         for(size_t i=2; i <= m; ++i)
//         {
//           eve::algo::transform_inplace(f, inc);
//           eve::algo::transform_to(eve::algo::views::zip(p.data, f), p.data, divi);
//         }
//         p.data.resize(n+m+1);
//         return p;
//       }
//     }

//     [[nodiscard]] friend auto tagged_dispatch( eve::tag::primitive_
//                                              , sparse_polynom_t const & p, size_t m
//                                              , eve::callable_all_) noexcept
//     {
//       int n = degree(p);
//       std::vector<sparse_polynom_t> prims(m+1);
//       prims[0] = p;
//       if (m == 0 || n <= 0) return prims;
//       prims[1] = primitive(p);
//       if (m == 1) return prims;
//       value_type nvt = n+1;
//       auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)), n+1);
//       data_t f(n+1);
//       data_t datad(n+1);
//       eve::algo::copy(p.data, datad);
//       eve::algo::copy(factors, f);
//       auto divi = [](auto pair) {
//         auto [x, y] = pair;
//         return x /= y;
//       };
//       eve::algo::transform_to(eve::algo::views::zip(datad, f), datad, divi);

//       for(size_t i=2; i <= m; ++i)
//       {
//         eve::algo::transform_inplace(f, inc);
//         eve::algo::transform_to(eve::algo::views::zip(datad, f), datad, divi);
//         prims[i] = sparse_polynom_t(datad);
//         prims[i].data.resize(n+i+1);
//       }
//       return prims;
//     }

//     //==============================================================================================
//     //=== operators
//     //==============================================================================================

//     //==============================================================================================
//     //=== operator+ family
//     //==============================================================================================
//     friend sparse_polynom_t operator+(sparse_polynom_t const & p0, sparse_polynom_t const & p1)
//     {
//       int const n0 = p0.data.size();
//       int const n1 = p1.data.size();
//       int offset = abs(n0-n1);
//       sparse_polynom_t r;
//       r.data.resize(max(n0, n1));
//       auto doit =  [&r, offset](auto const & p0,  auto const & p1) {
//         std::copy(p1.data.begin(), p1.data.end(), r.data.begin()+offset);
//         eve::algo::copy(p1.data, eve::algo::as_range(r.data.begin()+offset, r.data.end()));
//         auto addi = [](auto pair){
//           auto [x, y] = pair;
//           return x+y;
//         };
//         eve::algo::transform_to(eve::algo::views::zip(r.data, p0.data), r.data, addi);
//         r.normalize();
//         return r;
//       };
//       return (n0 > n1) ? doit(p0, p1) : doit(p1, p0);
//     }

//     friend sparse_polynom_t operator+(sparse_polynom_t const & p0, value_type const & v)
//     {
//       if (is_eqz(v)) return p0;
//       else if (degree(p0) < 0) return sparse_polynom_t(v);
//       else
//       {
//         auto r(p0);
//         r.data[degree(r)] += v;
//         r.normalize();
//         return r;
//       }
//     }

//     friend sparse_polynom_t operator+(value_type const & v, sparse_polynom_t const & p0)
//     {
//       return p0+v;
//     }

//     friend sparse_polynom_t operator+(sparse_polynom_t const & p0, monom_t const & m)
//     {
//       auto dm = degree(m);
//       if (dm < 0) return p0;
//       else
//       {
//         auto r(p0);
//         if (dm > degree(p0)) r.data.resize(dm+1);
//         r.data[degree(r)-degree(m)] += m[0];
//         r.normalize();
//         return r;
//       }
//     }

//     friend sparse_polynom_t operator+(monom_t const & m, sparse_polynom_t const & p0)
//     {
//       return p0+m;
//     }

//     template < typename Other>
//     sparse_polynom_t & operator+= (Other const & other)
//     {
//       return *this = *this+other;
//     }

//     //==============================================================================================
//     //=== operator- family
//     //==============================================================================================
//     friend sparse_polynom_t operator-(sparse_polynom_t const & p0)
//     {
//       data_t mp0 = p0.data;
//       eve::algo::transform_inplace(mp0, minus);
//       return sparse_polynom_t(mp0);
//     }

//     template < typename Other>
//     friend sparse_polynom_t operator-(sparse_polynom_t const & p0, Other const & o)
//     {
//       return p0+(-o);
//     }

//     template < typename Other>
//     sparse_polynom_t & operator-= (Other const & other)
//     {
//       return *this = *this-other;
//     }

//     //=== operator* family
//     friend sparse_polynom_t operator*(sparse_polynom_t const & p0, sparse_polynom_t const &  p1)
//     {
//       const size_t p1s = p1.data.size();
//       const size_t size = p0.data.size() + p1s - 1;
//       data_t r(size, value_type(0));
//       auto b = r.begin();
//       for (size_t i = 0; i < p0.data.size(); ++i, ++b) {
//         auto p0i = p0.data[i];
//         auto addit = [p0i](auto p){
//           auto [ripj, p1j] = p;
//           return fam(ripj, p0i, p1j);
//         };
//         auto z = eve::algo::as_range(b, b+p1s);
//         eve::algo::transform_to(eve::algo::views::zip(z, p1.data), z , addit);
//       }
//       return sparse_polynom_t(r);
//     }

//     friend sparse_polynom_t operator*(sparse_polynom_t const & p0, value_type const & f)
//     {
//       auto r(p0);
//       eve::algo::transform_inplace(r.data, [f](auto e){return e*f; });
//       r.normalize();
//       return r;
//     }

//     friend sparse_polynom_t operator*(value_type const & f, sparse_polynom_t const & p0)
//     {
//       auto r(p0);
//       eve::algo::transform_inplace(r.data, [f](auto e){return e*f; });
//       return r;
//     }

//     friend sparse_polynom_t operator*(sparse_polynom_t const & p0, monom_t const & m)
//     {
//       auto d = degree(m);
//       if (d < 0) return sparse_polynom_t();
//       else
//       {
//         sparse_polynom_t r(p0);
//         r = r*m[0];
//         if (d ==  0) return r;
//         r.data.resize(p0.data.size()+d);
//         return r;
//       }
//     }

//     friend sparse_polynom_t operator*(monom_t const & m, sparse_polynom_t const & p0)
//     {
//       return p0*m;
//     }

//     template <typename Other>
//     sparse_polynom_t & operator*= (Other const & other)
//       requires(is_one_of<Other>(detail::types<sparse_polynom_t, monom_t, value_type> {}))
//     {
//       if constexpr(std::same_as<value_type, Other>)
//       {
//         eve::algo::transform_inplace(data, [other](auto e){return e*other; });
//         normalize();
//       }
//       else if  constexpr(std::same_as<monom_t, Other>)
//       {
//         auto deg = degree(other);
//         eve::algo::transform_inplace(data, [other](auto e){return e*other[0]; });
//         if (deg > 0) data.resize(data.size()+deg);
//       }
//       else
//       {
//         return *this = (*this)*other;
//       }
//       return *this;
//     }

//     //==============================================================================================
//     //=== operator/ family and remquo
//     //==============================================================================================
//     friend kumi::tuple<sparse_polynom_t, sparse_polynom_t> remquo(sparse_polynom_t const & p0, sparse_polynom_t const & d)
//     {
//       int const n0 = p0.data.size();
//       int const n1 = d.data.size();
//       if (n1 == -1) return {d, sparse_polynom_t()};
//       if (n1 == 0) {
//         if (is_eqz(d.data[0])) return  {d, sparse_polynom_t()};
//         else return {sparse_polynom_t(), p0*rec(d.data[0])};
//       }
//       if (n0 < n1) return {p0, sparse_polynom_t()};
//       else
//       {
//         sparse_polynom_t r(p0);
//         int i = -1;
//         int deg = n0-n1;
//         sparse_polynom_t q;
//         q.data.resize(deg+1);
//         while (degree(r) >= 0 && degree(r) >= degree(d))
//         {
//           auto t = r.data[0]/d.data[0];
//           q.data[++i] = t;
//           r = r-monom(t, deg)*d;
//           --deg;
//         }

//         return {r, q};
//       }
//     }

//     friend kumi::tuple<sparse_polynom_t, sparse_polynom_t> remquo(sparse_polynom_t const & p0, value_type const & d)
//     {
//       return {sparse_polynom_t(), p0*rec(d)};
//     }

//     friend kumi::tuple<sparse_polynom_t, sparse_polynom_t> remquo(sparse_polynom_t const & p0, monom_t const & d)
//     {
//       auto degd = degree(d);
//       auto degp0= degree(p0);
//       if (degd < 0)           return {sparse_polynom_t(), sparse_polynom_t()};
//       else if (degd == 0)     return {sparse_polynom_t(), p0*rec(d[0])};
//       else if (degd > degree(p0))  return {sparse_polynom_t(d), sparse_polynom_t()};
//       else
//       {
//         auto q(p0);
//         q.data.resize(degp0-degd+1);
//         eve::algo::transform_inplace(q.data, [d](auto e){return e/d[0];});
//         auto r(p0);
//         r.data.resize(degd);
//         eve::algo::copy(eve::algo::as_range(p0.data.begin()+degp0-degd+1, p0.data.end()), r.data);
//         r.normalize();
//         return {r, q};
//       }
//     }

//     template < typename O>
//     friend sparse_polynom_t operator/(sparse_polynom_t const & p0, O const & p1)
//       requires(is_one_of<O>(detail::types<sparse_polynom_t, monom_t, value_type> {}))
//     {
//       if constexpr(std::same_as<O, value_type>)
//       {
//         auto fac =  rec(p1);
//         return (is_not_finite(fac) || is_eqz(fac)) ? sparse_polynom_t() : p0*fac;
//       }
//       else
//       {
//         auto [_, q] = remquo(p0, p1);
//         return q;
//       }
//     }

//     template < typename O>
//     auto operator/= (O const & p1)
//       requires(is_one_of<O>(detail::types<sparse_polynom_t, monom_t, value_type> {}))
//     {
//       return *this = *this/p1;
//     }

//     template < typename O>
//     friend sparse_polynom_t operator%(sparse_polynom_t const & p0, O const & p1)
//       requires(is_one_of<O>(detail::types<sparse_polynom_t, monom_t, value_type> {}))
//     {
//       if constexpr(std::same_as<O, value_type>)
//       {
//         return sparse_polynom_t();
//       }
//       else
//       {
//         auto [r, _] = remquo(p0, p1);
//         return r;
//       }
//     }

//     template < typename O>
//     auto operator%= (O const & p1)
//       requires(is_one_of<O>(detail::types<sparse_polynom_t, monom_t, value_type> {}))
//     {
//       return *this = *this%p1;
//     }

//     //==============================================================================================
//     //=== young and young_remainder
//     //==============================================================================================

//     friend sparse_polynom_t young(int n, sparse_polynom_t const & p0)
//     {
//       auto d = degree(p0);
//       if (n >= d)
//         return p0;
//       else if (n == -1)
//         return sparse_polynom_t();
//       else
//         return sparse_polynom_t(eve::algo::as_range(p0.data.begin()+d-n, p0.data.end()));
//     }

//     friend sparse_polynom_t young_remainder(int n, sparse_polynom_t const & p0)
//     {
//       auto d = degree(p0);
//       if (n > d)
//         return sparse_polynom_t();
//       else if (n == -1)
//         return p0;
//       else
//       {
//         sparse_polynom_t yr(p0);
//         eve::algo::fill(eve::algo::as_range(yr.data.begin()+d-n, yr.data.end()), value_type(0));
//         return yr;
//       }
//     }

//     //==============================================================================================
//     //=== concat
//     //==============================================================================================
//     friend sparse_polynom_t concat(sparse_polynom_t const & p0, sparse_polynom_t const & p1)
//     {
//       auto d = degree(p0);
//       if (d == -1) return p1;
//       else return p0+monom_t(value_type(1), d+1)*p1;
//     }


    //==============================================================================================
    //=== operator ==  and !=
    //==============================================================================================
    friend bool operator==(sparse_polynom_t const & p0, sparse_polynom_t const & p1)
    {
      return p0.data.size() == p1.data.size()
        && std::equal(p0.data.begin(), p0.data.end(), p1.data.begin());
    }

    friend bool operator!=(sparse_polynom_t const & p0, sparse_polynom_t const & p1)
    {
      return p0.data.size() != p1.data.size()
        || !std::equal(p0.data.begin(), p0.data.end(), p1.data.begin());
    }

//     friend bool operator==( monom_t const & p0, sparse_polynom_t const & p1)
//     {
//       return p1 == p0;
//     }

//     friend bool operator!=(sparse_polynom_t const & p0, sparse_polynom_t const & p1)
//     {
//       if(degree(p0) != degree(p1)) return true;
//       return degree(p0-p1) != -1;
//     }

//     friend bool operator!=(sparse_polynom_t const & p0, monom_t const & p1)
//     {
//       return (degree(p0) != degree(p1) || !is_monomial(p0)) ? true : (p0[0] != p1[0]);
//     }

//     friend bool operator!=( monom_t const & p0, sparse_polynom_t const & p1)
//     {
//       return p1 != p0;
//     }

    //==============================================================================================
    //=== predicates
    //==============================================================================================

    friend bool is_null(sparse_polynom_t const & p0)
    {
      return p0.data.empty();
    }

    friend bool is_constant(sparse_polynom_t const & p0)
    {
      return degree(p0) <=  0;
    }

    friend bool is_monomial(sparse_polynom_t const & p0)
    {
      return degree(p0) == valuation(p0);
    }

    //==============================================================================================
    //=== ostream
    //==============================================================================================
    template <class charT, class traits> friend
    inline std::basic_ostream<charT, traits>&
    operator << (std::basic_ostream<charT, traits>& os, const sparse_polynom<value_type>& poly)
    {
      if (poly.data.empty())
        return os << value_type(0);
      else
      {
        for (const auto& [i, value] : poly.data) {
          auto show = false;
          auto neg = is_ltz(value);
          auto z = eve::abs(value);
          if(eve::abs(z) == one(as(z)))
          {
            os << (neg ? "-" : "+");
            show = true;
          }
          else
          {
            if (show) os << std::showpos;
            os << value;
            show = true;
          }
          if (i!=  0) os << "x";
          if (i > 1 ) os << "^" <<  std::noshowpos << i << std::showpos;
        }
      }
      return os << std::noshowpos;
    }

    void normalize()
    {
      std::erase_if (data, [](const auto& item){ auto const & [i, v] = item; return is_eqz(v); });
    }

  private :
    data_t data;
  };
}
