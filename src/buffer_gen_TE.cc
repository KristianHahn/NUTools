#include <vector>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include <iostream>

using namespace std;


#define BUFFER_LEN     1000
//#define NEVENTS        17
#define NEVENTS        1

vector<string> split(const string& s, char delimiter)
{
  vector<string> tokens;
  string token;
  istringstream ss(s);

  while(getline(ss,token,delimiter)) {
    tokens.push_back(token);
  }

  return tokens;
}

int main(int argc, char ** argv) {

  vector<ifstream*> stubinnerfiles, stubouterfiles;
//   stubinnerfiles.push_back(new ifstream("VMStubs_VMSTE_L1PHIE18n2_04.dat"));
//   stubouterfiles.push_back(new ifstream("VMStubs_VMSTE_L2PHIC17n4_04.dat"));
  stubinnerfiles.push_back(new ifstream(argv[1]));
  stubouterfiles.push_back(new ifstream(argv[2]));
	

  const unsigned int NMODULES = stubinnerfiles.size();
  for(unsigned int ifile=0; ifile<NMODULES; ifile++) { 
    assert(stubinnerfiles[ifile]->is_open() && stubouterfiles[ifile]->is_open());
  }


  const unsigned int nevents = NEVENTS;
  string line;
  vector<uint32_t> rxdata0;
  vector<uint32_t> htmpinner[4];
  vector<uint32_t> htmpouter[4];
  for(unsigned int ifile=0; ifile<NMODULES; ifile++) {
    unsigned int membank=0;

    htmpinner[0].push_back(0x0);
    htmpinner[1].push_back(0x0);
    htmpinner[2].push_back(0x0);
    membank = ((2*ifile+1) << 8);
    htmpinner[3].push_back(0x39000 | membank);

    htmpouter[0].push_back(0x0);
    htmpouter[1].push_back(0x0);
    htmpouter[2].push_back(0x0);
    membank = ((2*ifile+2) << 8);
    htmpouter[3].push_back(0x39000 | membank);
  }
  

  // cache cout defaults
  ios_base::fmtflags oldFlags = cout.flags();
  streamsize         oldPrec  = cout.precision();
  char               oldFill  = cout.fill();

  // fill between prefix and number with 0s
  cout << std::internal << std::setfill('0');

  unsigned int ievt=0;
  vector<unsigned int> ievtinner, ievtouter;
  unsigned int iheadinner=0, iheadouter=0;
  vector<bool> eofinner, eofouter;

  for(unsigned int ifile=0; ifile<NMODULES; ifile++) {
    ievtinner.push_back(0);
    ievtouter.push_back(0);
    eofinner.push_back(false);
    eofouter.push_back(false);
  }

  char fname[256];
  while(ievt < nevents) {
    rxdata0.clear();
    //sprintf(fname, "memfile_TE_%d.dat", ievt);
    //ofstream memfile = ofstream(fname);
    ofstream memfile = ofstream(argv[3]);
    ievt++;

    for(unsigned int ifile=0; ifile<NMODULES; ifile++) {
      unsigned int nstubinner=0;
      while(ievtinner[ifile] <= ievt && !eofinner[ifile]) {
        if(getline(*stubinnerfiles[ifile], line)) {
          if(line.find("Event") != string::npos) {
            ievtinner[ifile]++;
            nstubinner=0;

          } else {
            // Parse the line in the data file
            // For inner stubs, we only need the stub data (last column)
            unsigned long long stubdata = strtoul(split(line,' ').back().c_str(),NULL,0);
            if(nstubinner==0) {  // header word before stub data words to follow
              iheadinner = rxdata0.size();
              rxdata0.push_back(htmpinner[0][ifile]);
              rxdata0.push_back(htmpinner[1][ifile]);
              rxdata0.push_back(htmpinner[2][ifile]);
              rxdata0.push_back(htmpinner[3][ifile]);
            }
            rxdata0.push_back(stubdata & 0xFFFF);
            rxdata0.push_back(stubdata >> 16);
            rxdata0.push_back(nstubinner);
            rxdata0.push_back(0x30000);
            nstubinner++;

            // update header word with number of stubs
            rxdata0[iheadinner+3] = (htmpinner[3][ifile] | nstubinner);
          }
        } else {
          eofinner[ifile] = true;
        }
      }

      unsigned int nstubouter=0;
//      unsigned int nstubouterZ[8] = {0,0,0,0,0,0,0,0};
      unsigned long long nstubouterZ[8] = {0,0,0,0,0,0,0,0};
      while(ievtouter[ifile] <= ievt && !eofouter[ifile]) {
        if(getline(*stubouterfiles[ifile], line)) {
          if(line.find("Event") != string::npos) {
            ievtouter[ifile]++;
            nstubouter=0;
            for(unsigned int k=0; k<8; k++) { nstubouterZ[k]=0; }

          } else {
            // Parse the line in the data file
            // For outer stubs, we need the z-bin slot and the stub data (first and last column, respectively)
            vector<string> tokens = split(line,' ');
            unsigned long long zbin     = strtoul(tokens.front().c_str(),NULL,0);
            unsigned long long stubdata = strtoul(tokens.back().c_str(),NULL,0);
            if(nstubouter==0) {  // header word before stub data words to follow
              iheadouter = rxdata0.size();
              rxdata0.push_back(htmpouter[0][ifile]);
              rxdata0.push_back(htmpouter[1][ifile]);
              rxdata0.push_back(htmpouter[2][ifile]);
              rxdata0.push_back(htmpouter[3][ifile]);
            }
            rxdata0.push_back(stubdata & 0xFFFF);
            rxdata0.push_back(stubdata >> 16);
            rxdata0.push_back((zbin<<8) | (16*zbin+nstubouterZ[zbin]));
            rxdata0.push_back(0x30000);
            nstubouter++;
            nstubouterZ[zbin]++;

            // update header word with number of stubs
            unsigned long long nstubouterZ_word = 0;
            for(unsigned int k=0; k<8; k++) {
              nstubouterZ_word += (nstubouterZ[k]<<(k*5));
            }
            rxdata0[iheadouter]   = ( htmpouter[0][ifile] | (nstubouterZ_word       & 0xFFFF) );
            rxdata0[iheadouter+1] = ( htmpouter[1][ifile] | ((nstubouterZ_word>>16) & 0xFFFF) );
            rxdata0[iheadouter+2] = ( htmpouter[2][ifile] | ((nstubouterZ_word>>32) & 0xFF) );
            rxdata0[iheadouter+3] = ( htmpouter[3][ifile] | nstubouter );
          }
        } else {
          eofouter[ifile] = true;
        }
      }
    }

  for(unsigned int i=0; i<rxdata0.size()/4; i++) {
    cout << std::hex << std::setw(4) << rxdata0[4*i+3];
    cout << " "      << std::setw(4) << rxdata0[4*i+2];
    cout << " "      << std::setw(4) << rxdata0[4*i+1];
    cout << " "      << std::setw(4) << rxdata0[4*i];
    cout << endl;

    memfile << std::hex << rxdata0[4*i]   << std::endl;
    memfile << std::hex << rxdata0[4*i+1] << std::endl;
    memfile << std::hex << rxdata0[4*i+2] << std::endl;
    memfile << std::hex << rxdata0[4*i+3] << std::endl;

  }
  memfile.close();
  // restore cout defaults
  cout.flags(oldFlags);
  cout.precision(oldPrec);
  cout.fill(oldFill);
  }



  //  memfile->write();



}
