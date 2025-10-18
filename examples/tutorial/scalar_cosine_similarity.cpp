//! [simd-function]
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/algo.hpp>
#include <iostream>
#include <array>
#include <bit>

//https://www.modular.com/blog/understanding-simd-infinite-complexity-of-trivial-problems

int main()
{
  auto cosine_similarity0 = []<typename T, auto N>(std::array<T, N> const& a, std::array<T, N> const& b){
     using r_t = T;
     r_t sab = r_t(0);
     r_t sa2 = r_t(0);
     r_t sb2 = r_t(0);
     for(std::size_t i=0; i < a.size(); ++i)
     {
       sab = eve::fam(sab, a[i], b[i]);
       sa2 = eve::fam(sa2, a[i], a[i]);
       sb2 = eve::fam(sb2, b[i], b[i]);
     }
     if(eve::is_eqz(sa2)) return eve::one(eve::as(sab));
     else if(eve::is_eqz(sb2)) return  eve::one(eve::as(sab));
     else return sab*eve::rsqrt(sa2*sb2);
  };

  auto cosine_similarity1 = [](auto const& aa, auto const& bb){
    auto sab =  eve::dot(aa, bb);
    if (eve::is_eqz(sab)) return sab;
    auto sa2 =  eve::hypot(aa);
    if(eve::is_eqz(sa2)) return eve::one(eve::as(sab));
    auto sb2 =  eve::hypot(bb);
    if(eve::is_eqz(sb2)) return  eve::one(eve::as(sab));
    return sab/(sa2*sb2);
  };

  auto cosine_similarity2 = [](auto const& aa, auto const& bb){
    auto sab =  eve::dot(aa, bb);
    if (eve::is_eqz(sab)) return sab;
    auto sa2 =  eve::sum_of_squares(aa);
    if(eve::is_eqz(sa2)) return eve::one(eve::as(sab));
    auto sb2 =  eve::sum_of_squares(bb);
    if(eve::is_eqz(sb2)) return  eve::one(eve::as(sab));
    return sab*eve::rsqrt(sa2*sb2);
  };

  auto cosine_similarity3 = [](auto const& aa, auto const& bb){
    auto sab =  eve::dot(aa, bb);
    if (eve::is_eqz(sab)) return sab;
    auto sa2 =  eve::sum_of_squares(aa);
    if(eve::is_eqz(sa2)) return eve::one(eve::as(sab));
    auto sb2 =  eve::sum_of_squares(bb);
    if(eve::is_eqz(sb2)) return  eve::one(eve::as(sab));
    return sab*eve::rsqrt(sa2*sb2);
  };

  using k_t = kumi::result::fill_t<11, double>;
  using a_t = std::array<double, 11>;
  a_t a{5.0,  12.0,  6.0,  7.0, 1.0, 1.0,   1.0,   1.0, 3.0, 0.0, 1.0};
  a_t b{3.0,   1.0,  4.0, -2.0, 2.0, 1.0,   1.0,   1.0, 4.0, 1.0, 2.0};

  k_t ka = std::bit_cast<k_t>(a);
  k_t kb = std::bit_cast<k_t>(b);
  std::cout << "ka " << ka << std::endl;
  std::cout << "kb " << kb << std::endl;
  std::cout <<  "cosine similarity0 = " << cosine_similarity0(a, b) <<  std::endl;
  std::cout <<  "cosine similarity1 = " << cosine_similarity1(ka, kb) <<  std::endl;
  std::cout <<  "cosine similarity2 = " << cosine_similarity2(ka, kb) <<  std::endl;
}
//! [simd-function]
