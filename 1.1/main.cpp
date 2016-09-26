#include "file_creation.h"
#include "Date.h"
#include "output_latex.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <string>


using namespace std;


int main()
{
    ifstream file_input;
    string input_filename{"S:\\Datenban\\Wetter\\Programme\\srj\\input_srj.txt"};
    Date date_from{};
    Date date_to{};
    string input_wind{};
    string output_path{};
    string stat_id{};
    string station{};
    double coord_n{};
    double coord_e{};
    int stat_h{0};
    double mess_h{0};
    bool latex;

    read_input_file(input_filename, stat_id, station, file_input,
                    coord_n, coord_e, stat_h, mess_h, latex,
                    date_from, date_to, input_wind, output_path);


    Date date_dummy{};
    int nr_of_days{0};
    date_dummy = date_from;
    while(date_dummy.compareToDay(date_to) <= 0)
    {
        nr_of_days++;
        date_dummy.nextDay();
    }

    long int ff_mean[9]{0};
    long int dd_mean[12]{0};
    long int counter_dd{0};
    long int counter_ff{0};
    double ff_medius{0.0};

    {
        double dummy{0.0};
        get_mean_wind(input_wind, ff_mean, dd_mean, counter_dd, counter_ff, ff_medius, dummy, date_from, date_to);
    }
    
    double dd_mean_p[12];
    double ff_mean_p[9];

    for(int i = 0; i<12; i++)
    {
        dd_mean_p[i] = static_cast<double>(dd_mean[i]) / static_cast<double>(counter_dd);
    }
    for(int i = 0; i<9; i++)
    {
        ff_mean_p[i] = static_cast<double>(ff_mean[i]) / static_cast<double>(counter_ff);
    }

    //Verteilung der einzelnen Jahre anschauen
    int nr_of_years {date_to.year()-date_from.year()+1};
    long int abw_dd_years[nr_of_years]{0};
    long int abw_ff_years[nr_of_years]{0};
    double ff_medius_years[nr_of_years]{0.0};
    double avail_years[nr_of_years]{0.0};
    Date dates[nr_of_years];
    Date date_year_from;
    Date date_year_to;
    for(int i = 0; i < (nr_of_years); i++)
    {
        date_year_from = Date(date_from.year()+i, 1, 1, 0);
        date_year_to   = Date(date_from.year()+i, 12, 31, 23);
        if(date_year_to.isLeapyear())
        {
            date_year_to = Date(date_from.year()+i, 12, 30, 23);
        }
        long int dd_year[12]{0};
        long int ff_year[9]{0};
        double dd_year_p[12]{0.0};
        double ff_year_p[9]{0.0};
        long int dd_count{0};
        long int ff_count{0};
        dates[i] = date_year_from;
        get_mean_wind(input_wind, ff_year, dd_year, dd_count, ff_count,
                      ff_medius_years[i], avail_years[i], date_year_from, date_year_to);
        for(int i = 0; i<12; i++)
        {
            dd_year_p[i] = static_cast<double>(dd_year[i]) / static_cast<double>(dd_count);
        }
        for(int i = 0; i<9; i++)
        {
            ff_year_p[i] = static_cast<double>(ff_year[i]) / static_cast<double>(ff_count);
        }
        //Abweichung zum langjährigen Mittel ermitteln
        chi_square_test(ff_mean_p, dd_mean_p, ff_year_p, dd_year_p, dd_count, ff_count, abw_dd_years[i], abw_ff_years[i]);
    }

    //ff_medius_years sind die Jahresdurchschnittswinde drin
    //Abweichungen normieren und sortieren
    double abw_dd_norm[nr_of_years]{0.0};
    double abw_ff_norm[nr_of_years]{0.0};


    long int min_ff{abw_ff_years[0]};
    for(int i = 0; i<nr_of_years; i++)
    {
        for(int j = i+1; j<nr_of_years; j++)
        {
            if(abw_dd_years[j] < abw_dd_years[i])
            {
                long int dummy_dd, dummy_ff;
                double dummy_ff_med;
                Date dummy_date;
                dummy_dd = abw_dd_years[i];
                dummy_ff = abw_ff_years[i];
                dummy_date = dates[i];
                dummy_ff_med = ff_medius_years[i];
                abw_dd_years[i] = abw_dd_years[j];
                abw_ff_years[i] = abw_ff_years[j];
                dates[i] = dates[j];
                ff_medius_years[i] = ff_medius_years[j];
                abw_dd_years[j] = dummy_dd;
                abw_ff_years[j] = dummy_ff;
                dates[j] = dummy_date;
                ff_medius_years[j] = dummy_ff_med;
            }
        }
        if(abw_ff_years[i] < min_ff)
        {
            min_ff = abw_ff_years[i];
        }
        abw_dd_norm[i] = static_cast<double>(abw_dd_years[i]) / static_cast<double>(abw_dd_years[0])*100.0;
    }
    for(int i = 0; i<nr_of_years; i++)
    {
        abw_ff_norm[i] = static_cast<double>(abw_ff_years[i]) / static_cast<double>(min_ff) * 100.0;
    }

    //Ausgabe in Datei bewerkstelligen
    print_txt(output_path, station, nr_of_years, dates, abw_dd_norm, abw_ff_norm,
			  ff_medius_years, avail_years);
    

    
    if(latex)
    {
		//Ausgabe über LaTEX
		print_latex_source(output_path, stat_id, station, date_from.year(),
						   date_to.year(), coord_n, coord_e, stat_h, 
						   mess_h, dates, abw_dd_norm, abw_ff_norm,
						   ff_medius_years, avail_years);

	}

    return 0;
}
