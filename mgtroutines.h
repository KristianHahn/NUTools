#include <stdio.h>
#include <iomanip>
#include "uhal/uhal.hpp"
#include "uhal/log/log.hpp"
#include "mgtargs.h"

using namespace uhal;
using namespace std;

#define kRX 0
#define kTX 1

#define MODE_LATENCY   0
#define MODE_CAPTURE   1
#define MODE_PLAY1     2
#define MODE_PLAY      3

#define SOURCE_INPUT   0
#define SOURCE_BUFFER  1
#define SOURCE_PATTERN 2
#define SOURCE_ZEROS   3

#define STROBE_DATA    0
#define STROBE_BUFFER  1
#define STROBE_PATTERN 2
#define STROBE_HIGH    3

#define BUFFER_LEN     1000

void mgt_global_reset(HwInterface & hw, DevStruct dev);
void mgt_tx_usr_reset(HwInterface & hw,DevStruct dev);
void mgt_rx_usr_reset(HwInterface & hw,DevStruct dev);
void mgt_tx_polarity(HwInterface & hw,DevStruct dev);
void mgt_rx_polarity(HwInterface & hw,DevStruct dev);
void mgt_rx_lpm(HwInterface & hw,DevStruct dev);
void mgt_reset_crc_counters(HwInterface & hw,DevStruct dev);
void mgt_set_loopback(HwInterface & hw,DevStruct dev);
void mgt_dump(HwInterface & hw,DevStruct dev);
void clearBuffer(HwInterface & hw, int quad, int chan, int bufftype);
void writeBuffer(HwInterface & hw, int quad, int chan, int bufftype, std::vector<uint32_t> & data);
void readBuffer(HwInterface & hw, int quad, int chan, int bufftype, std::vector<uint32_t> & data, int len);
void mgt_play_pattern(HwInterface & hw,DevStruct dev);
void mgt_play_file(HwInterface & hw,DevStruct dev);
void mgt_capture(HwInterface & hw,DevStruct dev);
void mgt_align(HwInterface & hw,DevStruct dev );
