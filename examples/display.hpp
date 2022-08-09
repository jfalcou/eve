//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include <sstream>
#include <vector>
#include <string>

struct display
{
  display(int w, int h) : pixels(h, std::vector<char>(w, ' ')) {}

  void put(char v, int c, int l)
  {
    pixels[l][c] = v;
  }

  void line(int l, char s, char e)
  {
    auto w = pixels[0].size();
    put(e,0,l);
    for(std::size_t i=1;i<w-1;++i) put(s,i,l);
    put(e,w-1,l);
  }

  std::ostringstream& header() { return headers; }
  std::string render() const
  {
    std::ostringstream str;
    str << headers.str();
    for(auto l : pixels)
    {
      for(auto c : l) str << c;
      str << '\n';
    }

    return str.str();
  }

  std::vector<std::vector<char>> pixels;
  std::ostringstream headers;
};
