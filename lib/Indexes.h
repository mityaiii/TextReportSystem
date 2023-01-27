#pragma once

struct Indexes {
  Indexes(int index_of_beg, int index_of_end, bool important)
    : index_of_beg(index_of_beg), index_of_end(index_of_end), important(important) {}

  int index_of_beg = -1;
  int index_of_end = -1;
  bool important = false;
};