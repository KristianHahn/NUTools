#include <stdio.h>
#include <iomanip>
#include "uhal/uhal.hpp"
#include "uhal/log/log.hpp"
#include "ttcargs.h"

using namespace uhal;
using namespace std;

void ttc_reset(HwInterface & hw, DevStruct dev);
void ttc_dump(HwInterface & hw, DevStruct dev);
