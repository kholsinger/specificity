#include <cmath>
#include <iostream>
#include <string>

const char* specificity_version = "Specificity v1.1";
const char* about_string = "Specificity v1.1\nKent Holsinger\nkent.holsinger@uconn.edu";

// Default maxima for numbers of species, genera, and families
// in which a parasite can occur
unsigned long n_species  = 1000;
unsigned long n_genera   = 500;
unsigned long n_families = 150;
unsigned long n_orders   = 75;
unsigned long n_classes  = 5;
unsigned long n_phyla    = 5; 

typedef unsigned long IndexValue;

IndexValue host_index(const unsigned host_species, const unsigned host_genera,
                      const unsigned host_families, const unsigned host_orders,
                      const unsigned host_classes, const unsigned host_phyla) 
{
  IndexValue value = 0;
  if (host_phyla > 1) {
    value = host_index(n_species, n_genera, n_families, n_orders, 
                       n_classes, host_phyla-1);
    IndexValue f_index = host_index(host_species, host_genera, host_families,
                                    host_orders, host_classes, 1);
    IndexValue o_index = host_index(host_phyla, host_phyla, host_phyla,
                                    host_phyla, host_phyla, 1);
    value += f_index - o_index + 1;
  } else if (host_classes > 1) {
    value = host_index(n_species, n_genera, n_families, n_orders, 
                       host_classes-1, 1);
    IndexValue f_index = host_index(host_species, host_genera, host_families,
                                    host_orders, 1, 1);
    IndexValue o_index = host_index(host_classes, host_classes, host_classes,
                                    host_classes, 1, 1);
    value += f_index - o_index + 1;
  } else if (host_orders > 1) {
    value = host_index(n_species, n_genera, n_families, host_orders-1, 1, 1);
    IndexValue f_index = host_index(host_species, host_genera, host_families, 
                                    1, 1, 1);
    IndexValue o_index = host_index(host_orders, host_orders, host_orders, 1,
                                    1, 1);
    value += f_index - o_index + 1;
  } else if (host_families > 1) {
    value = host_index(n_species, n_genera, host_families-1, 1, 1, 1);
    IndexValue f_index = host_index(host_species, host_genera, 1, 1, 1, 1);
    IndexValue o_index = host_index(host_families, host_families, 1, 1, 1, 1);
    value += f_index - o_index + 1;
  } else if (host_genera > 1) {
    for (unsigned g = 1; g < host_genera; g++) {
      value += n_species - g + 1;
    }
    value += host_species - host_genera + 1;
    // The approach on the following lines follows the same recursive 
    // logic as above, but is less computationally efficient. It produces
    // identical results.
    //
    // value = host_index(n_species, host_genera-1, 1, 1, 1, 1);
    // IndexValue f_index = host_index(host_species, 1, 1, 1, 1, 1);
    // IndexValue o_index = host_index(host_genera, 1, 1, 1, 1, 1);
    // value += f_index - o_index + 1;
  } else {
    value = host_species;
  }
  return value;
}

int main(int, char**) {
  using namespace std;

  string line;
  
  cout << "Enter number of host species:  ";
  getline(cin, line);
  unsigned species = stoi(line);
  if (species > n_species) {
    printf("Maximum of %lu species allowed!\n", n_species);
    exit(1);
  }
  
  cout << "Enter number of host genera:   ";
  getline(cin, line);
  unsigned genera = stoi(line);
  if (genera > n_genera) {
    printf("Maximum of %lu genera allowed!\n", n_genera);
    exit(1);
  }
  
  cout << "Enter number of host families: ";
  getline(cin, line);
  unsigned families = stoi(line);
  if (families > n_families) {
    printf("Maximum of %lu families allowed!\n", n_families);
    exit(1);
  }

  cout << "Enter number of host orders:   ";
  getline(cin, line);
  unsigned orders = stoi(line);
  if (orders > n_orders) {
    printf("Maximum of %lu orders allowed!\n", n_orders);
    exit(1);
  }

  cout << "Enter number of host classes:  ";
  getline(cin, line);
  unsigned classes = stoi(line);
  if (classes > n_classes) {
    printf("Maximum of %lu classes allowed!\n", n_classes);
    exit(1);
  }

  cout << "Enter number of host phyla:  ";
  getline(cin, line);
  unsigned phyla = stoi(line);
  if (phyla > n_phyla) {
    printf("Maximum of %lu phyla allowed!\n", n_phyla);
    exit(1);
  }

  cout << endl << endl
       << "Number of host species:  " << species << endl
       << "Number of host genera:   " << genera << endl
       << "Number of host families: " << families << endl
       << "Number of host orders:   " << orders << endl
       << "Number of host classes:  " << classes << endl
       << "Number of host phyla:    " << phyla << endl
       << "Specificity index:       " << endl;
  unsigned long rank = host_index(species, genera, families, orders, classes,
                                  phyla);
  cout << "   Rank:                 " << rank << endl
       << "   Index (log10(Rank)):  " << log10(rank) << endl;
}
