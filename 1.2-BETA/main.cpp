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
    long int nightcalms_mean[12]{0};
    long int counter_dd{0};
    long int counter_ff{0};
    long int counter_nc{0};
    double ff_medius{0.0};

    {
        double dummy{0.0};
        get_mean_wind(input_wind, ff_mean, dd_mean, nightcalms_mean,
            counter_dd, counter_ff, counter_nc, ff_medius, dummy,
            date_from, date_to);
    }

    //Parameter für prozentuale Verteilungen
    double dd_mean_p[12];
    double ff_mean_p[9];
    double nc_mean_p[12];

    for(int i = 0; i<12; i++)
    {
        dd_mean_p[i] = static_cast<double>(dd_mean[i]) / static_cast<double>(counter_dd);
    }
    for(int i = 0; i<9; i++)
    {
        ff_mean_p[i] = static_cast<double>(ff_mean[i]) / static_cast<double>(counter_ff);
    }
    for(int i = 0; i<12; i++)
    {
        nc_mean_p[i] = static_cast<double>(nightcalms_mean[i]) / static_cast<double>(counter_nc);
    }

    //Verteilung der einzelnen Jahre anschauen
    int nr_of_years {date_to.year()-date_from.year()+1};
    long int abw_dd_years[nr_of_years]{0};
    long int abw_ff_years[nr_of_years]{0};
    long int abw_nc_years[nr_of_years]{0};
    double ff_medius_years[nr_of_years]{0.0};
    double avail_years[nr_of_years]{0.0};
    Date dates[nr_of_years];
    Date date_year_from;
    Date date_year_to;
    for(int i = 0; i < (nr_of_years); i++)
    {
        date_year_from = Date(date_from.year()+i, 1, 1, 0);
        date_year_to   = Date(date_from.year()+i, 12, 31, 23);
//WTF...wer kommt denn auf sowas?!
//        if(date_year_to.isLeapyear())
//        {
//            date_year_to = Date(date_from.year()+i, 12, 30, 23);
//        }
        long int dd_year[12]{0};
        long int ff_year[9]{0};
        long int nc_year[12]{0};
        double dd_year_p[12]{0.0};
        double ff_year_p[9]{0.0};
        double nc_year_p[12]{0.0};
        long int dd_count{0};
        long int ff_count{0};
        long int nc_count{0};
        dates[i] = date_year_from;
        get_mean_wind(input_wind, ff_year, dd_year, nc_year, dd_count, ff_count,
                      nc_count, ff_medius_years[i], avail_years[i],
                      date_year_from, date_year_to);
        for(int i = 0; i<12; i++)
        {
            dd_year_p[i] = static_cast<double>(dd_year[i]) / static_cast<double>(dd_count);
        }
        for(int i = 0; i<9; i++)
        {
            ff_year_p[i] = static_cast<double>(ff_year[i]) / static_cast<double>(ff_count);
        }
        for(int i = 0; i<12; i++)
        {
            nc_year_p[i] = static_cast<double>(nc_year[i]) / static_cast<double>(nc_count);
        }
        //Abweichung zum langjährigen Mittel ermitteln
        chi_square_test(ff_mean_p, dd_mean_p, nc_mean_p, ff_year_p,
              dd_year_p, nc_year_p, dd_count, ff_count, nc_count,
              abw_dd_years[i], abw_ff_years[i], abw_nc_years[i]);
    }

    //ff_medius_years sind die Jahresdurchschnittswinde drin
    //Abweichungen normieren und sortieren
    double abw_dd_norm[nr_of_years]{0.0};
    double abw_ff_norm[nr_of_years]{0.0};
    double abw_nc_norm[nr_of_years]{0.0};

	//Variable, um Abweichungen zu gewichten -> Ergebnis der SRJ
    double weighted_result[nr_of_years]{0.0};
    //Abweichungen gewichten
    {
		//Hierbei werden die vom DWD vorgeschlagenen Wichtungsfaktoren angesetzt
		//vorgeschlagen in: "Verfahren zu Bestimmung des repräsentativen
		//aus einer vorgegebenen Zeitreihe der Windrichtung und Windgeschwindigkeit
		//an einer Station"
		//Dr. Deutschländer, Dipl.-Met. Hessel
		//Stand: 20.03.2006 (aktueller Stand am 08.07.2016)
		const double weight_dd{0.48};
		const double weight_ff{0.32};
		const double weight_nc{0.2};
		
		//offene Frage: Was wird gewichtet?
		//1.: Die Abweichungen der Jahre selbst   <- aktuell drin
		//2.: Die Platzierung innerhalb der entsprechenden Rangliste
		for(int i = 0; i<nr_of_years; i++)
		{
			weighted_result[i] = weight_dd * abw_dd_years[i] +
			                     weight_ff * abw_ff_years[i] +
			                     weight_nc * abw_nc_years[i];
			cout << abw_dd_years[i] << "   ";
			cout << abw_ff_years[i] << "   ";
			cout << abw_nc_years[i] << "   ";
			cout << weighted_result[i] << "\n";
		}
	}

	//sortieren, und zwar anhand von weighted_result
	long int min_dd{abw_dd_years[0]};
    long int min_ff{abw_ff_years[0]};
    long int min_nc{abw_nc_years[0]};
    for(int i = 0; i<nr_of_years; i++)
    {
        for(int j = i+1; j<nr_of_years; j++)
        {
            if(weighted_result[j] < weighted_result[i])
            {
                long int dummy_dd, dummy_ff, dummy_nc;
                double dummy_ff_med, dummy_wr;
                Date dummy_date;
                
                dummy_dd = abw_dd_years[i];
                dummy_ff = abw_ff_years[i];
                dummy_nc = abw_nc_years[i];
                dummy_date = dates[i];
                dummy_ff_med = ff_medius_years[i];
                dummy_wr = weighted_result[i];
                abw_dd_years[i] = abw_dd_years[j];
                abw_ff_years[i] = abw_ff_years[j];
                abw_nc_years[i] = abw_nc_years[j];
                dates[i] = dates[j];
                ff_medius_years[i] = ff_medius_years[j];
                weighted_result[i] = weighted_result[j];
                abw_dd_years[j] = dummy_dd;
                abw_ff_years[j] = dummy_ff;
                abw_nc_years[j] = dummy_nc;
                dates[j] = dummy_date;
                ff_medius_years[j] = dummy_ff_med;
                weighted_result[j] = dummy_wr;
            }
        }
        if(abw_dd_years[i] < min_dd)
        {
            min_dd = abw_dd_years[i];
        }
        if(abw_ff_years[i] < min_ff)
        {
            min_ff = abw_ff_years[i];
        }
        if(abw_nc_years[i] < min_nc)
        {
            min_nc = abw_nc_years[i];
        }

    }
    //Abweichungen dd, ff, nc normieren
    for(int i = 0; i<nr_of_years; i++)
    {
        abw_dd_norm[i] = static_cast<double>(abw_dd_years[i]) / static_cast<double>(min_dd) * 100.0;
    }
    for(int i = 0; i<nr_of_years; i++)
    {
        abw_ff_norm[i] = static_cast<double>(abw_ff_years[i]) / static_cast<double>(min_ff) * 100.0;
    }
    for(int i = 0; i<nr_of_years; i++)
    {
        abw_nc_norm[i] = static_cast<double>(abw_nc_years[i]) / static_cast<double>(min_nc) * 100.0;
    }
    double min_wr = weighted_result[0];
    for(int i = 0; i<nr_of_years; i++)
    {
        weighted_result[i] = weighted_result[i] / min_wr * 100.0;
    }

    //Ausgabe in Datei bewerkstelligen
    print_txt(output_path, station, nr_of_years, dates, abw_dd_norm, abw_ff_norm,
			  abw_nc_norm, ff_medius_years, weighted_result, avail_years);
    

    
    if(latex)
    {
		//Ausgabe über LaTEX
		print_latex_source(output_path, stat_id, station, date_from.year(),
						   date_to.year(), coord_n, coord_e, stat_h, 
						   mess_h, dates, abw_dd_norm, abw_ff_norm,
						   abw_nc_norm, ff_medius_years, weighted_result, avail_years);

	}

    return 0;
}
