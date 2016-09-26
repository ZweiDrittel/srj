#include "output_latex.h"
#include "Date.h"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

void print_latex_source(string &output_path, string stat_id, string station,
						int year_from, int year_to, double coord_n, 
						double coord_e, int stat_h, double mess_h,
						Date dates[], double abw_dd[],
						double abw_ff[], double mittel_ff[], double verf[])
{
	string output_file{};
    output_file = output_path;
    output_file += "srj_";
    output_file += station;
    output_file += ".tex";
    ofstream file_out;
    file_out.open(output_file, ios::out);
    
    //LaTEX-File aufsetzen, welches übersetzte werden kann
    //Ab hier den LaTEX-Header
    file_out << "\\documentclass[paper=a4, fontsize=12pt,DIV=12]{scrartcl}\n";
    file_out << "\\usepackage[utf8]{inputenc}\n";
    file_out << "\\usepackage[onehalfspacing]{setspace}\n";
    file_out << "\\usepackage[ngerman]{babel}\n";
    file_out << "\\usepackage{lmodern}\n";
    file_out << "\\usepackage[T1]{fontenc}\n";
    file_out << "\\usepackage{textcomp}\n\n";
    file_out << "% Mathematik\n";
    file_out << "\\usepackage{amsmath}\n";
    file_out << "\\usepackage{amssymb}\n\n";
    file_out << "% erweiterte Optionen\n";
    file_out << "\\usepackage{array}\n\n";
    file_out << "% Advanced features for clever quotations\n";
    file_out << "\\usepackage[babel, german=quotes]{csquotes}\n\n";
    file_out << "% Einheiten\n";
    file_out << "\\usepackage{siunitx}\n";
    file_out << "\\sisetup{\n";
    file_out << "   mode = math, detect-family, detect-weight,	\n";
    file_out << "   exponent-product = \\cdot,\n";
    file_out << "   number-unit-separator=\\text{\\,},\n";
    file_out << "   output-decimal-marker={,},\n";
    file_out << "}\n\n";
    file_out << "\\usepackage{float}\n\n";
    file_out << "\\usepackage{setspace}\n\n";
    file_out << "%Seriefenüberschrift\n";
    file_out << "\\usepackage{placeins}\n";
    file_out << "\\usepackage[svgnames]{xcolor}\n";
    file_out << "\\usepackage{paralist}\n";
    file_out << "\\usepackage{stmaryrd}\n";
    file_out << "\\usepackage{txfonts}\n";
    file_out << "\\usepackage{rotating}\n\n";
    file_out << "\\newcommand{\\cor}{\\hspace{1,5mm} \\widehat{=} \\hspace{1,5mm}}\n\n";
    file_out << "%für Kopf-/Fußzeilen\n";
    file_out << "\\usepackage{scrpage2}\n";
    file_out << "\\pagestyle{scrheadings}\n";
    file_out << "\\clearscrheadfoot\n";
    file_out << "%für das Einbinden von Grafiken\n";
    file_out << "\\usepackage{graphicx}\n";
    file_out << "\\usepackage{subfigure}\n\n";
    file_out << "%Für Tabellen\n";
    file_out << "\\usepackage{tabularx}\n";
    file_out << "\\usepackage{multirow}\n";
    file_out << "\\usepackage{multicol}\n\n";
    file_out << "%Kein Einrücken nach Zeilenumbruch\n";
    file_out << "\\setlength{\\parindent}{0pt}\n\n";
    file_out << "%Abstand zwischen Tabelle und Überschrift verändern\n";
    file_out << "\\setlength\\abovecaptionskip{15pt}\n";
    file_out << "\\setlength\\belowcaptionskip{15pt}\n\n\n";
    //Hier gehts los
    file_out << "\\begin{document}\n\n";
    file_out << "\\renewcommand{\\headheight}{2.5cm}\n";
    file_out << "\\ohead{\n";
    file_out << "   \\includegraphics[width=6cm]{S:/User/Ra/DiesDas/Unterlagen/Logo/Logo.jpg}\\\\\n";
    file_out << "   \\today\n";
    file_out << "}\n\n";
    file_out << "\\section*{Bestimmung des repräsentativen Jahres}\n";
    file_out << "Für eine ausgewählte Messstation wird auf Basis einer "\
				"mehrjährigen Stunden-Zeitreihe ein repräsentatives Jahr"\
				" für die Verwendung in Immissionsprognosen ermittelt. "\
				"Die Bestimmung erfolgt als Summe der Fehlerquadrate von"\
				" Windrichtung (12 Sektoren und Windstille) und Windgeschwindigkeit"\
				" (9 Klassen). Es wird das Jahr ausgewählt, welches primär"\
				" bezüglich der Windrichtungsverteilung und sekundär bezüglich"\
				" der Windgeschwindigkeit die niedrigste Abweichungssumme aufweist.\\\\\n\n";
	file_out << "\\begin{tabular}{ll}\n";
	file_out << "\\textbf{Station:}       &  \\textbf{"<<stat_id<<" "<<station<<"}                 \\\\\n";
	file_out << "Betreiber:              &  Deutscher Wetterdienst, DWD               \\\\\n";
	file_out << "Datenquelle:            &  Deutscher Wetterdienst, DWD               \\\\\n";
	file_out << "Bezugszeitraum:         &  "<<year_from<<" - "<<year_to<<"                               \\\\\n";
	file_out << "Koordinaten:            &  N "<<coord_n<<"$^\\circ$\\quad E "<<coord_e<<"$^\\circ$   \\\\\n";
	file_out << "Stationshöhe:         &  "<<stat_h<<"\\,m\\,ü\\,NN                                \\\\\n";
	file_out << "Messhöhe:             &  "<<mess_h<<"\\,m                                       \\\\\n";
	file_out << "Ermitteltes repr. Jahr: &  "<<dates[0].year()<<"                                      \\\\\n";
	file_out << "\\end{tabular}\n";
	file_out << "\\\\\n\n";
	file_out << "Das Abweichungsmaß $\\textbf{A}_\\textbf{n}$ von den mittleren"\
				" Verhältnissen wird durch einen \\textbf{$\\chi^2$}-Test"\
				" ermittelt und ist je Jahr für den ausgewählten Parameter"\
				" darstellbar als:\\\\\n";
	file_out << "\\begin{equation*}\n";
	file_out << "A_n=\\sum_i\\frac{\\left(p_{n,i}-p_{m,i}\\right)^2}{p_{m,i}}\n";
	file_out << "\\end{equation*}\n\n";
	file_out << "\\begin{tabular}{p{1cm}p{.8cm}l}\n";
	file_out << "mit  &  $p_x$  &  Häufigkeit je Sektor/Klasse          "\
				"                        \\\\\n";
	file_out << "     &  $n$    &  Einzeljahr                           "\
				"                        \\\\\n";
	file_out << "     &  $m$    &  aus langjährigem Mittel errechneter "\
				"Erwartungswert           \\\\\n";
	file_out << "     &  $i$    &  Windrichtungssektor (12) oder "\
				"Windgeschwindigkeitsklasse (9) \\\\\n";
	file_out << "\\end{tabular}\n";
	file_out << "\\\\\n\n";
	file_out << "Die nachfolgende Tabelle zeigt die Reihenfolge der"\
				" Einzeljahre mit getrennter Sortierung je Parameter "\
				"(Windrichtung und Windgeschwindigkeit) nach aufsteigendem"\
				" Wert des (auf den kleinsten Wert mit 100) normierten "\
				"Abweichungsmaßes. Die Repräsentativität der Einzeljahre"\
				" gilt als umso größer, je geringer die Abweichung vom "\
				"Mittel ist. Der Windrichtung wird bei der Auswahl die "\
				"Priorität eingeräumt. Die Jahresmittelwerte der "\
				"Windgeschwindigkeit sind in $\\text{ms}^{-1}$ angegeben;"\
				" das langjährige Mittel beträgt $";
	double ff_med_ges{0};
	for(int i = 0; i<=year_to-year_from; i++)
	{
		ff_med_ges += mittel_ff[i];
	}
	ff_med_ges /= year_to-year_from+1;
	file_out << setprecision(1) << fixed << ff_med_ges;
	file_out << "\\,\\text{ms}^{-1}$.\\\\\n\n";
	file_out << "\\newpage\n";
	file_out << "\\clearscrheadfoot\n";
	file_out << "\\renewcommand{\\headheight}{2cm}\n";
	file_out << "\\ohead{\n";
	file_out << "   \\includegraphics[width=6cm]{S:/User/Ra/DiesDas/Unterlagen/Logo/Logo.jpg}\n";
	file_out << "   }\n\n";
	file_out << "\\begin{table}[!htb]\n";
	file_out << "   \\renewcommand{\\arraystretch}{1.4}\n";
	file_out << "   \\centering\n";
	file_out << "   \\caption{Zusammenfassung der Auswertung der Messwerte"\
				" aller betrachteten Einzeljahre im Vergleich zum langjährigen Mittel}\n";
	file_out << "   \\begin{tabular}{|c|c|c|c|c|}\n";
	file_out << "   \\hline\n";
	file_out << "   \\multirow{2}{*}{Jahr}\n";
	file_out << "      &  Windrichtung  &  \\multicolumn{2}{c|}{Windgeschwindigkeit}"\
				"  &  \\multirow{2}{*}{Datenverfügbarkeit [\\%]} \\\\\n";
	file_out << "      \\cline{2-4}\n";
	file_out << "      &  Abweichung  &  Abweichung  &  Mittelwert [$\\text{ms}^{-1}$] & \\\\\n";
	file_out << "   \\hline\n";
	file_out << "   \\textbf{"<<dates[0].year()<<"} & \\textbf{"<< setprecision(0) << fixed <<abw_dd[0]<<"}"\
				" & \\textbf{"<<abw_ff[0]<<"} & \\textbf{"<< setprecision(2) << fixed <<mittel_ff[0]<<"}"\
				" & \\textbf{"<<verf[0]*100.0<<"} \\\\\n";
	file_out << "   \\hline\n";
	for(int i = 1; i <= year_to-year_from; i++)
	{
		file_out << "   "<<dates[i].year()<<" & "<< setprecision(0) << fixed <<abw_dd[i]
				 << " & "<<abw_ff[i]<<" & "<< setprecision(2) << fixed <<mittel_ff[i]
				 << " & "<<verf[i]*100.0<<" \\\\\n";
		file_out << "   \\hline\n";
	}
	file_out << "   \\end{tabular}\n";
	file_out << "\\end{table}\n\n";
	file_out << "\\end{document}";
    
    file_out.close();


	string buff_file{};
    buff_file = "pdflatex "+output_file;
    const char * exec = buff_file.c_str();
    system(exec);
    
    buff_file = "move srj_"+station+".pdf "+output_path;
    exec = buff_file.c_str();
    system(exec);
    
    buff_file = "del srj_"+station+".aux";
    exec = buff_file.c_str();
    system(exec);
    
    buff_file = "del srj_"+station+".log";
    exec = buff_file.c_str();
    system(exec);
    
}
