#include "dbscan/dbscan.h"

using namespace clustering;

#include <iostream>
#include <boost/tokenizer.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <boost/lexical_cast.hpp>

int main(int argc, char* argv[])
{
  if (argc == 1)
  {
    // Legacy test
    std::cout << "Running legacy test, 10000 random points with 225 features each" << std::endl;
    DBSCAN::ClusterData cl_d = DBSCAN::gen_cluster_data( 225, 10000 );
    DBSCAN dbs(0.1, 5, 1);
    dbs.fit( cl_d );
    std::cout << dbs << std::endl;
  }
  else if (argc == 2)
  {
    // New demo (read max 2 cols of the input csv file)
    std::ifstream csv_file (argv[1]);
    if (!csv_file.is_open()) return 1;
    std::string line;
    size_t rows = 0;
    while (std::getline(csv_file, line)) rows++;
    std::cout << "Number of rows " << rows << std::endl;
    csv_file.clear();
    csv_file.seekg(0);

    typedef boost::tokenizer< boost::escaped_list_separator<char> > Tokenizer;
    std::vector<std::string> vec;

    clustering::DBSCAN::ClusterData cl_d(rows, 2);
    for (std::size_t i = 0; i < rows && std::getline(csv_file, line); i++)
    {
      Tokenizer tok(line);
      vec.assign(tok.begin(),tok.end());
      cl_d(i, 0) = boost::lexical_cast<double>(vec[0]);
      cl_d(i, 1) = boost::lexical_cast<double>(vec[1]);
    }
    csv_file.close();

    DBSCAN dbs(0.01, 10, 1);

    dbs.fit( cl_d );

    std::cout << dbs << std::endl;
    return 0;
  }

	return 0;
}
