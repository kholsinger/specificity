#include <cmath>
#include <iostream>
#include <string>

const char* specificity_version = "Specificity v1.0";
const char* about_string = "Specificity v1.0\nKent Holsinger\nkent.holsinger@uconn.edu";

// Default maxima for numbers of species, genera, and families
// in which a parasite can occur
unsigned long n_species  = 1000;
unsigned long n_genera   = 500;
unsigned long n_families = 150;
unsigned long n_orders   = 75;
unsigned long n_classes  = 5;

typedef unsigned long IndexValue;

IndexValue host_index(const int host_species, const int host_genera,
                      const int host_families, const int host_orders,
                      const int host_classes) 
{
  IndexValue value = 0;
  if (host_classes > 1) {
    value = host_index(n_species, n_genera, n_families, n_orders, 
                       host_classes-1);
    IndexValue f_index = host_index(host_species, host_genera, host_families,
                                    host_orders, 1);
    IndexValue o_index = host_index(host_classes, host_classes, host_classes,
                                    host_classes, 1);
    value += f_index - o_index + 1;
  } else if (host_orders > 1) {
    value = host_index(n_species, n_genera, n_families, host_orders-1, 1);
    IndexValue f_index = host_index(host_species, host_genera, host_families, 
                                    1, 1);
    IndexValue o_index = host_index(host_orders, host_orders, host_orders, 1, 1);
    value += f_index - o_index + 1;
  } else if (host_families > 1) {
    value = host_index(n_species, n_genera, host_families-1, 1, 1);
    IndexValue f_index = host_index(host_species, host_genera, 1, 1, 1);
    IndexValue o_index = host_index(host_families, host_families, 1, 1, 1);
    value += f_index - o_index + 1;
  } else if (host_genera > 1) {
    for (int g = 1; g < host_genera; g++) {
      value += n_species - g + 1;
    }
    value += host_species - host_genera + 1;
    // The approach on the following lines follows the same recursive 
    // logic as above, but is less computationally efficient. It produces
    // identical results.
    //
    // value = host_index(n_species, host_genera-1, 1, 1, 1);
    // IndexValue f_index = host_index(host_species, 1, 1, 1, 1);
    // IndexValue o_index = host_index(host_genera, 1, 1, 1, 1);
    // value += f_index - o_index + 1;
  } else {
    value = host_species;
  }
  return value;
}

// inline bool too_big(void) {
//   IndexValue max = UINT_MAX;
//   return (max/n_species/n_genera/n_families/n_orders < 1);
// }

// inline double my_round(const double x) {
//   return floor(x + 0.5);
// }

int main(int ac, char** av) {
  using namespace std;

  string line;
  
  cout << "Enter number of host species:  ";
  getline(cin, line);
  int species = stoi(line);

  cout << "Enter number of host genera:   ";
  getline(cin, line);
  int genera = stoi(line);

  cout << "Enter number of host families: ";
  getline(cin, line);
  int families = stoi(line);

  cout << "Enter number of host orders:   ";
  getline(cin, line);
  int orders = stoi(line);

  cout << "Enter number of host classes:  ";
  getline(cin, line);
  int classes = stoi(line);

  cout << endl << endl
       << "Number of host species:  " << species << endl
       << "Number of host genera:   " << genera << endl
       << "Number of host families: " << families << endl
       << "Number of host orders:   " << orders << endl
       << "Number of host classes:  " << classes << endl << endl
       << "Specificity index:       " << endl;
  unsigned long rank = host_index(species, genera, families, orders, classes);
  cout << "   Rank:                 " << rank << endl
       << "   Index (log10(Rank)):  " << log10(rank) << endl;
}
