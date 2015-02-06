#include "dbscan/dbscan.h"

using namespace clustering;

#include <iostream>
#include <boost/tokenizer.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <boost/lexical_cast.hpp>
int main()
{
//  //DBSCAN::ClusterData cl_d = DBSCAN::gen_cluster_data( 225, 10000 );
//  DBSCAN::ClusterData cl_d = DBSCAN::gen_cluster_data( 2, 5 );
//  cl_d(0, 0) = -1.0;
//  cl_d(0, 1) = 1.0;

//  cl_d(1, 0) = -0.9;
//  cl_d(1, 1) = 0.9;

//  cl_d(2, 0) = 1.0;
//  cl_d(2, 1) = -1.0;

//  cl_d(3, 0) = 0.9;
//  cl_d(3, 1) = -0.9;

//  cl_d(4, 0) = 0.0;
//  cl_d(4, 1) = 0.0;

//  DBSCAN dbs(0.25, 2, 1);

//	dbs.fit( cl_d );

//  std::cout << dbs << std::endl;

  std::ifstream csv_file ("/tmp/2.txt");
  if (!csv_file.is_open()) return 1;
  typedef boost::tokenizer< boost::escaped_list_separator<char> > Tokenizer;

  std::vector<std::string> vec;
  std::string line;

  std::size_t i = 0;

  clustering::DBSCAN::ClusterData cl_d(1000, 2);
  while (getline(csv_file, line))
  {
    Tokenizer tok(line);
    vec.assign(tok.begin(),tok.end());

    cl_d(i, 0) = boost::lexical_cast<double>(vec[0]);
    cl_d(i, 1) = boost::lexical_cast<double>(vec[1]);


    std::cout << i << " " << cl_d(i, 0) << " " << cl_d(i, 1) << std::endl;
    i++;
  }
  csv_file.close();

  DBSCAN dbs(0.01, 10, 1);

  dbs.fit( cl_d );

  std::cout << dbs << std::endl;


	return 0;
}
