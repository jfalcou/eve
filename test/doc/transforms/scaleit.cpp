#include <eve/module/complex.hpp>
#include <eve/module/algo.hpp>
#include <eve/module/transforms.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>
#include <vector>


int main()
{
  auto pr = [](auto title, auto v){
    std::cout << title << " = (";
    for(size_t i=0; i < v.size() ; ++i) std::cout << eve::read(v.data()+i) << " ";
    std::cout << ")\n";
  };

  using e_t = float;
  using c_t = eve::complex<e_t>;
  using soa_ct = eve::algo::soa_vector<c_t>;
  using aos_et = std::vector<e_t>;
  using aos_ct = std::vector<c_t>;
  aos_et aosv(4, 1.0f);
  aos_et aosvr(4, 1.0f);
  aos_et aosvi(4, -1.0f);
  aos_ct aosvri(4, c_t(1.0f, -1.0f));
  soa_ct soavri{c_t(1.0f, -1.0f), c_t(1.0f, -1.0f), c_t(1.0f, -1.0f), c_t(1.0f, -1.0f)};
  eve::scaleit(aosv, 2);
  eve::scaleit(aosvr, aosvi, 2);
  eve::scaleit(aosvri, 2);
  eve::scaleit(soavri, 2);
  pr("aosv", aosv);
  pr("aosvr", aosvr);
  pr("aosvi", aosvi);
  pr("aosvri", aosvri); 
    pr("soavri", soavri);
//   std::cout << "true  = " << eve::algo::is_soa_vector_v<soa_t> << std::endl;
//   std::cout << "false = " << eve::algo::is_soa_vector_v<aos_t> << std::endl;
  return 0;
}
