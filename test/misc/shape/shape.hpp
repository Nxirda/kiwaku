//==================================================================================================
/**
  KIWAKU - Containers Well Made
  Copyright 2020 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef SHAPE_SHAPE_HPP
#define SHAPE_SHAPE_HPP

#include <kiwaku/shape.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/basic.hpp>

template<int N>
struct nD : std::integral_constant<int,N>
{};

template<typename N>
using up_to = std::make_index_sequence<N::value>;

template<typename Env, typename Shape>
inline void test_0D(Env& runtime, Shape const& sh)
{
  TTS_EQUAL(sh.nbdims() , 0   );
  TTS_EQUAL(sh.numel()  , 0   );
  TTS_EQUAL(sh.count()  , 0   );
  TTS_EQUAL(sh.size()   , 0ULL);

  TTS_EQUAL(sh.end() , sh.begin());
  TTS_EQUAL(sh.data(), nullptr   );
}

template<int N> using int_ = std::integral_constant<int,N>;

template<typename Env, typename Size, typename Shape>
inline void test_nD(Env& runtime, Size const&, Shape const& sh)
{
  TTS_EQUAL(sh.count(), Size::value                           );
  TTS_EQUAL(sh.size() , static_cast<std::size_t>(Size::value) );

  TTS_EQUAL(sh.front(), 3             );
  TTS_EQUAL(sh.back() , 3*Size::value );

  TTS_EQUAL     ( sh.end()  , sh.begin() + Size::value  );
  TTS_NOT_EQUAL ( sh.data() , nullptr                   );
}

#endif
