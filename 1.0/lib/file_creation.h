#ifndef CREATE_HEADER_H
#define CREATE_HEADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Date.h"

using namespace std;


//Funktion, die guckt, ob char ';' ist
bool is_semi(char c);
//Funktion, die guckt, ob char ':' ist
bool is_dp(char c);

//dd in Array einordnen
void sort_dd(long int (&dd_mean)[12], int dd);

//ff in Array einordnen
void sort_ff(long int (&ff_mean)[9], double ff);

//Funktion, um inputDatei für SRJ zu öffnen und lesen
void read_input_file(string input_filename, string &station, ifstream &file_input, Date &date_from,
                     Date &date_to, string &input_wind, string &output_srj);

//Funktion, die Zeile aus Winddatei liest und verarbeitet
void read_line_ff(ifstream &file_in, Date &dummy_date, int &dd, double &ff);

//Abweichung zum langjährigen Mittel ermitteln
void chi_square_test(double (&ff_mean)[9], double (&dd_mean)[12], double (&ff_mean_year)[9], double (&dd_mean_year)[12], long int nr_of_dd, long int nr_of_ff, long int &abw_dd, long int &abw_ff);

//Funktion, um Arrays zu sortieren und normieren
//void norm_sort(double (&abw_dd)[], double (&abw_ff)[], double (&ff_medius)[], Date (&dates)[], int nr_of_years);

//Funktion, die mittlere Werte für ff und dd herausfindet
void get_mean_wind(string &input_wind, long int (&ff_mean)[9], long int (&dd_mean)[12], long int &counter_dd, long int &counter_ff, double &ff_medius, double &avail, Date &date_from, Date &date_to);

#endif // CREATE_HEADER_H
