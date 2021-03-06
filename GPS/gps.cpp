#include <cstdarg>  // va_*
#include <iostream>
#include <string>
#include <vector>

#include "gps.hpp"

Room gps(const std::string& S, const int N, ...) {
  va_list args;
  va_start(args, N);

  std::vector<int> v;
  v.reserve(N);
  for (int i = 0; i < N; ++i) {
    v.push_back(va_arg(args, int));  // Room is promoted to int in ...
  }
  va_end(args);

  print_text(S);

  for (int i = 0; i < N; ++i) {
    std::cout << i + 1 << ") " << RoomToString(v[i]) << std::endl;
  }

  int tmp;
  std::cin >> tmp;
  if (tmp <= 0 || N < tmp) {
    print_text("To nie był rozsądny wybór...");
    wait_s(2);
    print_text("Udało Ci się zagiąć czasoprzestrzeń!");
    wait_s(2);
    print_text("... w wyniku czego powstała śmiercionośna czarna dziura.");
    return FAIL;
  }

  return static_cast<Room>(v[tmp - 1]);
}
