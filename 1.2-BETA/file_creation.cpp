#include "file_creation.h"
#include "Date.h"

#include <iostream>
#include <iomanip>
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

void print_txt(string &output_path, string &station, int &nr_of_years,
			   Date dates[], double abw_dd_norm[], double abw_ff_norm[],
			   double abw_nc_norm[], double ff_medius_years[],
			   double weighted_result[], double avail_years[])
{
	string output_file{};
    output_file = output_path;
    output_file += "srj_";
    output_file += station;
    output_file += ".txt";
    ofstream file_out;
    file_out.open(output_file, ios::out);
    file_out << "Messstation: " << station << "\n\n";
    file_out << "Datum;        Abw. dd;  Abw. ff; Abw. nc;   gew.Erg.  ; mittl. Windgeschw.;Verfügbarkeit\n\n";
    for(int i = 0; i<nr_of_years; i++)
    {
		file_out << setw(2) << setfill('0') << right << dates[i].day() << ".";
		file_out << setw(2) << setfill('0') << right << dates[i].month() << ".";
		file_out << setw(4) << setfill('0') << right << dates[i].year();
		file_out << ";    " << left << setw(7) << setfill(' ') << abw_dd_norm[i];
		file_out << ";    " << left << setw(7) << setfill(' ') << abw_ff_norm[i];
		file_out << ";    " << left << setw(7) << setfill(' ') << abw_nc_norm[i];
		file_out << ";    " << left << setw(7) << setfill(' ') << weighted_result[i];
		file_out << ";    " << left << setw(7) << setfill(' ') << ff_medius_years[i];
		file_out << ";    " << left << setw(7) << setfill(' ') << avail_years[i]*100.0;
		file_out << "\n";
    }
    file_out.close();
	

}

bool leapPeriod(Date &date_start, Date &date_end)
{
	//Zeitraum durchlaufen und guckenm ob 29.02. getroffen wird
	Date date_dummy{date_start};
	while(date_dummy.compareToDay(date_end) < 1)
	{
		//gucken ob 29.02.
		if(date_dummy.month() == 2 && date_dummy.day() == 29)
		{
			return true;
		}
		date_dummy.nextDay();
	}
	return false;
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


void read_input_file(string input_filename, string &stat_id, string &station,
					 ifstream &file_input, double &coord_n, double &coord_e,
					 int &stat_h, double &mess_h, bool &latex, Date &date_from,
					 Date &date_to, string &input_wind, string &output_path)
{
    file_input.open(input_filename, ios::in);
    string dummy_str{};
    short int day_from, month_from, year_from;
    short int day_to, month_to, year_to;
    file_input >> dummy_str >> stat_id >> station;
    file_input >> dummy_str >> coord_n >> coord_e;
    file_input >> dummy_str >> stat_h;
    file_input >> dummy_str >> mess_h;
    file_input >> dummy_str >> dummy_str;
    if(dummy_str.compare("Ja") == 0 || dummy_str.compare("ja") == 0 ||
	   dummy_str.compare("JA") == 0 || dummy_str.compare("1") == 0)
	{
		latex = true;
	}
	else
	{
		latex = false;
	}
    file_input >> dummy_str >> day_from >> month_from >> year_from;
    file_input >> dummy_str >> day_to >> month_to >> year_to;
    file_input >> dummy_str >> input_wind;
    file_input >> dummy_str >> output_path;
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

void chi_square_test(double (&ff_mean)[9], double (&dd_mean)[12], double (&nc_mean)[12],
     double (&ff_mean_year)[9], double (&dd_mean_year)[12], double (&nc_mean_year)[12],
     long int nr_of_dd, long int nr_of_ff, long int nr_of_nc, long int &abw_dd,
     long int &abw_ff, long int &abw_nc)
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
    for(int i = 0; i<12; i++)
    {
        double n; //Einzeljahr
        double n_0; //Mittel
        n = static_cast<double>(nr_of_nc) * nc_mean_year[i];
        n_0 = static_cast<double>(nr_of_nc) * nc_mean[i];
        abw_nc += static_cast<long int>(pow(n - n_0, 2) / n_0);
    }
}

void get_mean_wind(string &input_wind, long int (&ff_mean)[9], long int (&dd_mean)[12],
     long int (&nightcalms_mean)[12], long int &counter_dd, long int &counter_ff,
     long int &counter_nc, double &ff_medius, double &avail, Date &date_from, Date &date_to)
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
            if(dd != 999 && dd != -999 && dd > 0)
            {
				//Windrichtungsdaten tutti -> einsortieren
                sort_dd(dd_mean, dd);
                counter_dd++;
            }
            if(ff != 999 && ff != -999 && ff >= 0.0)
            {
				//Windgeschwindigkeitsdaten tutti -> einsortieren
                ff_medius += ff;
                sort_ff(ff_mean, ff);
                counter_ff++;
            }
            if(ff >= 0.0 && ff <= 3.0 && dd != 999 && dd != -999 && dd > 0 &&
               (date_in.hour() >= 18 || date_in.hour() <= 6))
            {
				//Nacht- und Schwachwindsituation liegt vor -> einsortieren
				sort_dd(nightcalms_mean, dd);
				counter_nc++;
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
    if(leapPeriod(date_from, date_to))
    {
        avail = avail/8784.0;
	}
	else
	{
		avail = avail/8760.0;
	}

    file_in.close();
}
