#include <eve/module/core.hpp>
#include <eve/algo/transform.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <vector>

// struct pipo_dont_work{
//   pipo_dont_work(std::vector<float> const & v) :data(v){};

// this do not work because v is const & so the zip cannot be modified
// however it is not good to duplicate v.data to make it work as in the next example
//   auto operator+= (pipo_dont_work const & v){
//     auto addit = [](auto p) {
//       get<0>(p) += get<1>(p);
//       return p;
//     };
//     eve::algo::transform_inplace(eve::algo::views::zip(data, v.data), addit);
//     return *this;
//   }

//   std::vector<float> data;
// };

struct pipo_eve{
  pipo_eve(std::vector<float> const & v) :data(v){};

  auto operator+= (pipo_eve const & v){
    std::vector<float> mv(v.data); //I don't want to duplicate data
    auto addit = [](auto p) {
      get<0>(p) += get<1>(p);
      return p;
    };
    eve::algo::transform_inplace(eve::algo::views::zip(data, mv), addit);
    return *this;
  }

  std::vector<float> data;
};

struct pipo_std{
  pipo_std(std::vector<float> const & v) :data(v){};

  auto operator+= (pipo_std const & v) {
    //no  duplicate data here
    auto addit = [](auto a, auto b) {
      return a += b;
    };
    // std allows to have in place modifications, I think we need something like that
    std::transform(data.begin(), data.end(), v.data.begin(), data.begin(), addit);
    return *this;
  }

  std::vector<float> data;
};

// struct pipo_wished{
//   pipo_wished(std::vector<float> const & v) :data(v){};

//   auto operator+= (pipo_wished const & v) {
//     //no  duplicate data here
//     auto addit = [](auto a, auto b) {
//       return a += b;
//     };
//     // std allows to have in place modifications, I think we need something like that
//     std::transform(data, v.data, data, addit); // const &,  const &,  & (input input output)
//     return *this;
//   }

//   std::vector<float> data;
// };

int main()
{

  std::vector<float> vv {1,  2, -3, 0, 4};
  std::vector<float> ww {5,  21, -2, 0, 4};
  {
    pipo_eve v(vv);
    pipo_eve w(ww);
    v +=  w;

    for(size_t i=0; i < v.data.size(); ++i)
    {
      std::cout << v.data[i] << std::endl;
    }
    return 0;
  }
  {
    pipo_std v(vv);
    pipo_std w(ww);
    v +=  w;

    for(size_t i=0; i < v.data.size(); ++i)
    {
      std::cout << v.data[i] << std::endl;
    }
    return 0;
  }
}
