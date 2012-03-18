#ifndef STD_HXX
#define STD_HXX

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <utility>
#include <algorithm>
#include <numeric>
#include <memory>
#include <sstream>
#include <fstream>
#include <functional>
#include <iomanip>
#include <stack>
#include <limits>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <typeinfo>
#include <queue>

using namespace std ;

#include "boost.hxx"

#define DEFINE_MAP(key, value, mapName)                       \
  typedef std::map<key, value> mapName;                       \
  typedef mapName::value_type BOOST_PP_CAT (mapName, Value);  \
  typedef mapName::iterator   BOOST_PP_CAT (mapName, Iter);   \
  typedef mapName::const_iterator BOOST_PP_CAT(mapName, IterC)

#define DEFINE_VEC(key, vecName)                              \
  typedef std::vector<key> vecName;                           \
  typedef vecName::value_type BOOST_PP_CAT (vecName, Value);  \
  typedef vecName::iterator   BOOST_PP_CAT (vecName, Iter);   \
  typedef vecName::const_iterator BOOST_PP_CAT(vecName, IterC)

#define DEFINE_LIST(key, listName)                              \
  typedef std::list<key> listName;                              \
  typedef listName::value_type BOOST_PP_CAT (listName, Value);  \
  typedef listName::iterator   BOOST_PP_CAT (listName, Iter);   \
  typedef listName::const_iterator BOOST_PP_CAT(listName, IterC)

#define DEFINE_SET(key, setName)                              \
  typedef std::set<key> setName;                              \
  typedef setName::value_type BOOST_PP_CAT (setName, Value);  \
  typedef setName::iterator   BOOST_PP_CAT (setName, Iter);   \
  typedef setName::const_iterator BOOST_PP_CAT(setName, IterC)

namespace stl {
  DEFINE_MAP(std::string, std::string, StringMap);
  DEFINE_MAP(int, int, IntMap);
  DEFINE_MAP(int, std::string, IntStringMap);
  DEFINE_MAP(std::string, int, StringIntMap);

  DEFINE_VEC(std::string, StringVector);
  DEFINE_VEC(int, IntVector);
  DEFINE_VEC(double, DoubleVector);
  DEFINE_VEC(float, FloatVector);

  DEFINE_LIST(int, IntList);
  DEFINE_LIST(float, FloatList);
  DEFINE_LIST(double, DoubleList);
  DEFINE_LIST(std::string, StringList);

  DEFINE_SET(int, IntSet);
  DEFINE_SET(float, FloatSet);
  DEFINE_SET(double, DoubleSet);
  DEFINE_SET(std::string, StringSet);
}

#endif
