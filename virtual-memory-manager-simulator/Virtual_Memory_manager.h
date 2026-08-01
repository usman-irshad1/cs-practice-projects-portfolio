#pragma once
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <json/json.h>
#include "FileConfiguration.h"
#include "TLB_table.h"
#include "Page_frame.h"

using namespace std;

struct Virtual_Memory_manager {
    void Runner(bool flag);
    void SPRINTER(bool flag);
    void SPRINTER_OPT_TLB(bool flag );
    void Walker(bool flag);
   
};
