#include "file_creation.h"
#include "Date.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

bool is_semi(char c)
{
    return c == ';' ? true : false;
}

bool is_dp(char c)
{
    return c == ':' ? true : false;
}

void sort_dd(long int (&dd_mean)[12], int dd)
{
    if(dd >= 16 && dd <= 45){
        dd_mean[0]++;
    }else if(dd >= 46 && dd <= 75){
        dd_mean[1]++;
    }else if(dd >= 76 && dd <= 105){
        dd_mean[2]++;
    }else if(dd >= 106 && dd <= 135){
        dd_mean[3]++;
    }else if(dd >= 136 && dd <= 165){
        dd_mean[4]++;
    }else if(dd >= 166 && dd <= 195){
        dd_mean[5]++;
    }else if(dd >= 196 && dd <= 225){
        dd_mean[6]++;
    }else if(dd >= 226 && dd <= 255){
        dd_mean[7]++;
    }else if(dd >= 256 && dd <= 285){
        dd_mean[8]++;
    }else if(dd >= 286 && dd <= 315){
        dd_mean[9]++;
    }else if(dd >= 316 && dd <= 345){
        dd_mean[10]++;
    }else if((dd >= 346 && dd <= 360)||(dd >= 1 && dd <= 15)){
        dd_mean[11]++;
    }
}

void sort_ff(long int (&ff_mean)[9], double ff)
{
    if(ff < 1.4){
        ff_mean[0]++;
    }else if(ff <=1.8){
        ff_mean[1]++;
    }else if(ff <=2.3){
        ff_mean[2]++;
    }else if(ff <=3.8){
        ff_mean[3]++;
    }else if(ff <=5.4){
        ff_mean[4]++;
    }else if(ff <=6.9){
        ff_mean[5]++;
    }else if(ff <=8.4){
        ff_mean[6]++;
    }else if(ff <=10.0){
        ff_mean[7]++;
    }else if(ff >10.0){
        ff_mean[8]++;
    }
}


void read_input_file(string input_filename, string &station, ifstream &file_input, Date &date_from,
                     Date &date_to, string &input_wind, string &output_srj)
{
    file_input.open(input_filename, ios::in);
    string dummy_str{};
    short int day_from, month_from, year_from;
    short int day_to, month_to, year_to;
    file_input >> dummy_str >> station;
    file_input >> dummy_str >> day_from >> month_from >> year_from;
    file_input >> dummy_str >> day_to >> month_to >> year_to;
    file_input >> dummy_str >> input_wind;
    file_input >> dummy_str >> output_srj;
    file_input.close();
    date_from = Date(year_from, month_from, day_from, 0);
    date_to = Date(year_to, month_to, day_to, 23);
}

void read_line_ff(ifstream &file_in, Date &dummy_date, int &dd, double &ff)
{
    int year;
    int month;
    int day;
    int hour;
    string date_str{};
    string dd_str{};
    string ff_str{};
    string line_ff;
    int semi_counter {0};

    getline(file_in, line_ff);

    for(auto c : line_ff)
    {
        if(is_semi(c))
        {
            semi_counter++;
        }

        if((semi_counter == 1) && (!is_semi(c)))
        {
            date_str += c;
        }
        if((semi_counter == 4) && (!is_semi(c)))
        {
            ff_str += c;
        }
        if((semi_counter == 5) && (!is_semi(c)))
        {
            dd_str += c;
        }
    }

    dd = stoi(dd_str);
    ff = stod(ff_str);
    year = stoi(date_str.substr(0,4));
    month = stoi(date_str.substr(4,2));
    day = stoi(date_str.substr(6,2));
    hour = stoi(date_str.substr(8,2));
    dummy_date = Date(year, month, day, hour);
}

void chi_square_test(double (&ff_mean)[9], double (&dd_mean)[12], double (&ff_mean_year)[9], double (&dd_mean_year)[12], long int nr_of_dd, long int nr_of_ff, long int &abw_dd, long int &abw_ff)
{
    for(int i = 0; i<12; i++)
    {
        double n; //Einzeljahr
        double n_0; //Mittel
        n = static_cast<double>(nr_of_dd) * dd_mean_year[i];
        n_0 = static_cast<double>(nr_of_dd) * dd_mean[i];
        abw_dd += static_cast<long int>(pow(n - n_0, 2) / n_0);
    }
    for(int i = 0; i<9; i++)
    {
        double n; //Einzeljahr
        double n_0; //Mittel
        n = static_cast<double>(nr_of_ff) * ff_mean_year[i];
        n_0 = static_cast<double>(nr_of_ff) * ff_mean[i];
        abw_ff += static_cast<long int>(pow(n - n_0, 2) / n_0);
    }
}

void get_mean_wind(string &input_wind, long int (&ff_mean)[9], long int (&dd_mean)[12], long int &counter_dd, long int &counter_ff, double &ff_medius, double &avail, Date &date_from, Date &date_to)
{
    ifstream file_in;
    file_in.open(input_wind, ios::in);
    Date date_in;
    string line_in;
    double ff{0.0};
    int dd{0};

    getline(file_in, line_in);
    read_line_ff(file_in, date_in, dd, ff);

    while(date_in.compareToHour(date_to) <= 0)
    {
        if(date_in.compareToHour(date_from) >= 0)
        {
            avail++;
            //liegen in gesuchtem Zeitraum...nice!
            if(dd != 999 && dd > 0)
            {
                sort_dd(dd_mean, dd);
                counter_dd++;
            }
            if(ff != 999 && ff >= 0.0)
            {
                ff_medius += ff;
                sort_ff(ff_mean, ff);
                counter_ff++;
            }
        }
        //Sind noch nicht am Ende unseres Zeitraums angekommen
        if(date_in.compareToHour(date_to) < 0)
        {
            read_line_ff(file_in, date_in, dd, ff);
        }
        //nur da, um Endlosschleife zu vermeiden
        else
        {
            date_in.nextDay();
        }

    }

    ff_medius = ff_medius / static_cast<double>(counter_ff);
    avail = avail/8760.0;

    file_in.close();
}
