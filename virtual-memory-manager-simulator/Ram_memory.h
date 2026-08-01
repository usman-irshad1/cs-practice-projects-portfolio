#pragma once
#include "FileConfiguration.h"
#include <cmath>
#include <iostream>
#include <vector>


using namespace std;

class TLB;

struct Page_frame_node {
  bool dirty_bit;
  bool valid_bit;
  unsigned long long physical_memory;
  Page_frame_node();
  std::vector<Page_frame_node> getFramesState() {
    std::vector<Page_frame_node> state;
    return state;
  }
};

struct Ram_memory {
  vector<vector<char>> memory;
  unsigned long long frames_size;

  Ram_memory(FileConfiguration &config);

  void write(unsigned long long physical, unsigned long long offset, char data);
  char read(unsigned long long physical, unsigned long long offset);
  void display();
};