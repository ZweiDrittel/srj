#ifndef LATEX_H
#define LATEX_H

#include "Date.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

void print_latex_source(string &output_path, string stat_id, string station,
						int year_from, int year_to, double coord_n, 
						double coord_e, int stat_h, double mess_h,
						Date dates[], double abw_dd[],
						double abw_ff[], double abw_nc[], double mittel_ff[],
						double weighted_result[], double verf[]);

#endif // LATEX_H
