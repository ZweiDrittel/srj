#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//Variablen::::

//count_missing: Anzahl der Datenlücken in Rohdatensatz (365-Tages-Zeitraum)
//error_count_dd(/_ff) stellen die fehlerhaften Werte für dd bzw. ff dar

//dd_mean[12] bzw. ff_mean[9]: Häufigkeit der Sektor-/binwerte in Prozent/100
//für den Zeitraum date_from - date_to

//deviations[][] gibt die Summe der quadratischen Abweichung der Sektoren/Klassen
//an. deviations[][0] für dd, deviations[][1] für ff




//Datentyp Date gibt ein Datum an
typedef struct Date{

    int day;
    int month;
    int year;
    int hour;

} Date;

//Datentyp Time für Zeit in Stunden und Minuten
typedef struct Time{

    int hour;
    int minute;

} Time;

//Zeit im Format hh:mm ausgeben
void printtime(Time time){

    printf("%02d.%02d\n", time.hour, time.minute);

}

//Funktion, um Datum mit Werten zu belegen
Date newDate(int hour, int day, int month, int year){

    Date date;
    date.hour = hour;
    date.day = day;
    date.month = month;
    date.year = year;
    return date;

}

//Funktion um Lage zweier Daten zueinander zu vergleichen
//gibt 0 zurück, wenn Daten gleich
//gibt 1 zurück, wenn date1 früher liegt als date2
//gibt -1 zurück, wenn date2 früher liegt als date1
int cmpDates(Date date1, Date date2){

    if(date1.year == date2.year){
        if(date1.month == date2.month){
            if(date1.day == date2.day){
                if(date1.hour == date2.hour){

                    return 0;

                }else if(date1.hour < date2.hour){

                    return 1;

                }else{

                    return -1;

                }

            }else if(date1.day < date2.day){

                return 1;

            }else{

                return -1;

            }
        }else if(date1.month < date2.month){

            return 1;

        }else{

            return -1;

        }
    }else if(date1.year < date2.year){

        return 1;

    }else{

        return -1;

    }

}

//Datum im Format dd.mm.yyyy hh:mm ausgeben
void printDate(Date date){

    printf("%02d.%02d.%4d %02d:00\n", date.day, date.month, date.year, date.hour);

}

//Funktion zur überprüfung ob Jahr Schaltjahr ist
//gibt 0 zurück, wenn kein Schaltjahr, bei Schaltjahr 1
int isLeapyear(int year){

    if(year % 4 == 0){

        if(year % 100 == 0){

            if(year % 400 == 0){
                return 1;
            }else{
                return 0;
            }

        }else{
            return 1;
        }

    }else{
        return 0;
    }

}

//Funktion zur Überprüfung, ob Tag am Ende des Monats liegt
//gibt 0 zurück wenn nicht, 1 wenn schon
int endOfMonth(Date date){

    if((date.day == 31) && (date.month == 1 || date.month == 3 || date.month == 5 ||
        date.month == 7 || date.month == 8 || date.month == 10 || date.month == 12)){

        return 1;

    }else if((date.day == 30) && (date.month == 4 || date.month == 6 || date.month == 9 ||
        date.month == 11)){

        return 1;

    }else if((date.day == 28) && (date.month == 2) && !isLeapyear(date.year)){

        return 1;

    }else if((date.day == 29) && (date.month == 2) && isLeapyear(date.year)){

        return 1;

    }else{

        return 0;

    }

}

//Funktion zur Überprüfung, ob Tag am Ende des Jahres liegt
//gibt 0 zurück wenn nicht, 1 wenn schon
int endOfYear(Date date){

    if(endOfMonth(date) && date.month == 12){

        return 1;

    }else{

        return 0;

    }

}

//Funktion zur Überprüfung ob die beiden Tage auf die Stunde gleich sind
//gibt 0 zurück wenn nicht gleich, 1 wenn gleich
int sameHour(Date date1, Date date2){

    if(date1.hour == date2.hour && date1.day == date2.day &&
       date1.month == date2.month && date1.year == date2.year){

        return 1;

    }else{

        return 0;

    }

}

//Funktion zur Überprüfung ob die beiden Tage gleich sind
//gibt 0 zurück wenn nicht gleich, 1 wenn gleich
int sameDay(Date date1, Date date2){

    if(date1.day == date2.day && date1.month == date2.month &&
       date1.year == date2.year){

        return 1;

    }else{

        return 0;

    }

}

//Funktion zur Rückgabe des darauffolgenden Tages
Date nextDay(Date date){

    Date nextDate;
    nextDate.hour = date.hour;

    if(endOfMonth(date)){
        if(endOfYear(date)){

            nextDate.day = 1;
            nextDate.month = 1;
            nextDate.year = date.year + 1;

        }else{

            nextDate.day = 1;
            nextDate.month = date.month + 1;
            nextDate.year = date.year;

        }
    }else{

        nextDate.day = date.day + 1;
        nextDate.month = date.month;
        nextDate.year = date.year;

    }

    return nextDate;

}

//Funktion zur Rückgabe der darauffolgenden Stunde
Date nextHour(Date date){

    Date nextHour;

    if(date.hour == 23){
        nextHour = nextDay(date);
        nextHour.hour = 0;
    }else{
        nextHour = date;
        nextHour.hour = nextHour.hour+1;
    }
    return nextHour;
}

//Funktion zur Rückgabe der vorigen Stunde
Date lastHour(Date date){

    Date lastHour;

    if(date.hour == 0){
        lastHour = date;
        lastHour.hour = 23;
        if(lastHour.day > 1){
            lastHour.day = lastHour.day-1;
        }else{
            if(lastHour.month > 1){
                lastHour.month = lastHour.month-1;
                if(lastHour.month == 1 || lastHour.month == 3
                   || lastHour.month == 5 || lastHour.month == 7
                   || lastHour.month == 8 || lastHour.month == 10){

                    lastHour.day = 31;
                }else if(lastHour.month == 2){
                    if(isLeapyear(lastHour.year) == 1){
                        lastHour.day = 29;
                    }else{
                        lastHour.day = 28;
                    }
                }else if(lastHour.month == 4 || lastHour.month == 6
                         || lastHour.month == 9 || lastHour.month == 11){

                    lastHour.day = 30;
                }
            }else{
                lastHour.month = 12;
                lastHour.day = 31;
                lastHour.year = lastHour.year-1;
            }
        }
    }else{
        lastHour = date;
        lastHour.hour = lastHour.hour-1;
    }

    return lastHour;
}

////////////////////////////////MAIN/////////////////////////////////////////////
int main(void){

  //Einlesen der Randbedingungen
    //Variablen zum Einlesen aus Inputdatei erstellen
    FILE *fp_in;
    FILE *fp_out;
    FILE *fp_out2;
    char file_output[100];
    char file_output_year[100];
    char file_input[100];
    Date date_from;
    Date date_to;

    //Input-Datei Einlesen
    fp_in = fopen("input_srj.txt", "r");

    fscanf(fp_in, "%*s %d %d %d %*s %d %d %d", &date_from.day, &date_from.month,
                                               &date_from.year, &date_to.day,
                                               &date_to.month, &date_to.year);
    date_from.hour = 0;
    date_to.hour = 23;
    fscanf(fp_in, "%*s %s", file_input);
    fscanf(fp_in, "%*s %s", file_output);
    fscanf(fp_in, "%*s %s", file_output_year);

    fclose(fp_in);

    printf("Inputparameter eingelesen\n");
  //Einlesen von Inputparametern beendet

/////////////////////////////WORK DATA///////////////////////////////////////////

  //Input-Datei einlesen
    //benötigte Variablen

    //gucken wieviele Inputtage
    int nr_of_days = 1;
    Date runDay;

    runDay = date_from;

    while(!sameDay(runDay, date_to)){

        runDay = nextDay(runDay);

        nr_of_days++;

    }
    //nr_of_days ist nun die Anzahl der einzulesenden Tage


    //Variablen zum Einlesen von Input-Datei
    int hour_in;
    int day_in;
    int month_in;
    int year_in;
    int dd_in;
    float ff_in;
    Date date_in;

    //erste Zeile verwerfen
    fp_in = fopen(file_input, "r");
    fscanf(fp_in, "%*s %*s %*s %*s %*s");
    //erste "richtige" Zeile einlesen
    fscanf(fp_in, "%*5s %4d %2d %2d %2d %*s %*s %*s %f %*1s %d %*s",
           &year_in, &month_in, &day_in, &hour_in, &ff_in, &dd_in);
    date_in = newDate(hour_in, day_in, month_in, year_in);

    while(cmpDates(date_in, date_from) == 1){

        fscanf(fp_in, "%*5s %4d %2d %2d %2d %*s %*s %*s %f %*1s %d %*s",
               &year_in, &month_in, &day_in, &hour_in, &ff_in, &dd_in);
        date_in = newDate(hour_in, day_in, month_in, year_in);

    }
    printf("Anfang des Untersuchungszeitraum identifiziert als: ");
    printDate(date_in);
    printf("Eingegebener Anfang des Untersuchungszeitraums: ");
    printDate(date_from);
/////////////////////////////////////////////////////////////////////////////////
    //Programmabbruch, wenn date_from nicht in InputDatei
    if(cmpDates(date_in, date_from) == -1){

        printf("Beginn des Untersuchungszeitraums nicht in Datei...\n");
        return 1;

    }

    //Mittelwerte über Betrachtungszeitraum berechnen (dd und ff)
    long count_values;
    long count_ges = 0;
    long ff_sum = 0.0;
    double dd_mean[12];
    double ff_mean[9];
    long i;
    Date date_expected;

    for(i = 0; i<12; i++){
        dd_mean[i] = (long)0;
    }
    for(i = 0; i<9; i++){
        ff_mean[i] = (long)0;
    }

    date_expected = date_from;

    while(cmpDates(date_expected, date_to) >= 0){

        if(cmpDates(date_expected, date_in) == 0){

            if(ff_in >= 0.0){
                count_ges++;
                ff_sum = ff_sum + ff_in;

                if(ff_in < 1.4){
                    ff_mean[0] = ff_mean[0]+1;
                }else if(ff_in <=1.8){
                    ff_mean[1] = ff_mean[1]+1;
                }else if(ff_in <=2.3){
                    ff_mean[2] = ff_mean[2]+1;
                }else if(ff_in <=3.8){
                    ff_mean[3] = ff_mean[3]+1;
                }else if(ff_in <=5.4){
                    ff_mean[4] = ff_mean[4]+1;
                }else if(ff_in <=6.9){
                    ff_mean[5] = ff_mean[5]+1;
                }else if(ff_in <=8.4){
                    ff_mean[6] = ff_mean[6]+1;
                }else if(ff_in <=10.0){
                    ff_mean[7] = ff_mean[7]+1;
                }else if(ff_in >10.0){
                    ff_mean[8] = ff_mean[8]+1;
                }

            }

            if(dd_in >= 16 && dd_in <= 45){
                dd_mean[0] = dd_mean[0]+1;
            }else if(dd_in >= 46 && dd_in <= 75){
                dd_mean[1] = dd_mean[1]+1;
            }else if(dd_in >= 76 && dd_in <= 105){
                dd_mean[2] = dd_mean[2]+1;
            }else if(dd_in >= 106 && dd_in <= 135){
                dd_mean[3] = dd_mean[3]+1;
            }else if(dd_in >= 136 && dd_in <= 165){
                dd_mean[4] = dd_mean[4]+1;
            }else if(dd_in >= 166 && dd_in <= 195){
                dd_mean[5] = dd_mean[5]+1;
            }else if(dd_in >= 196 && dd_in <= 225){
                dd_mean[6] = dd_mean[6]+1;
            }else if(dd_in >= 226 && dd_in <= 255){
                dd_mean[7] = dd_mean[7]+1;
            }else if(dd_in >= 256 && dd_in <= 285){
                dd_mean[8] = dd_mean[8]+1;
            }else if(dd_in >= 286 && dd_in <= 315){
                dd_mean[9] = dd_mean[9]+1;
            }else if(dd_in >= 316 && dd_in <= 345){
                dd_mean[10] = dd_mean[10]+1;
            }else if((dd_in >= 346 && dd_in <= 360)||(dd_in >= 1 && dd_in <= 15)){
                dd_mean[11] = dd_mean[11]+1;
            }

            fscanf(fp_in, "%*5s %4d %2d %2d %2d %*s %*s %*s %f %*1s %d %*s",
                   &year_in, &month_in, &day_in, &hour_in, &ff_in, &dd_in);
            date_in = newDate(hour_in, day_in, month_in, year_in);
        }

        //um aus Schleife zu kommen, wenn am Ende des Zeitraums
        if(cmpDates(date_expected, date_to) == 0){
            date_in = newDate(hour_in, day_in, month_in, year_in+1);
        }

        date_expected = nextHour(date_expected);

    }

    fclose(fp_in);

    //prozentuale Häufigkeit dd und ff über die Jahre ermitteln
    count_values = 0;
    for(i=0;i<12;i++){
        count_values = count_values + dd_mean[i];
    }
    for(i=0;i<12;i++){
        dd_mean[i] = dd_mean[i]/count_values;
    }

    count_values = 0;
    for(i=0;i<9;i++){
        count_values = count_values + ff_mean[i];
    }
    for(i=0;i<9;i++){
        ff_mean[i] = ff_mean[i]/count_values;
    }

/////////////////////////////////////////////////////////////////////////////////
    //Inputdatei erneut öffnen und lesen...Speicherprobleme
    int dd[8760];
    float ff[8760];
    double dd_val[12];
    double ff_val[9];
    double dd_val_periods[(date_to.year-date_from.year+1)*365+10][12];
    double ff_val_periods[(date_to.year-date_from.year+1)*365+10][9];
    long count_missing[(date_to.year-date_from.year+1)*365+10];
    double ff_mean_time[(date_to.year-date_from.year+1)*365+10];
    double ff_sum_time;
    long dd_count;
    long ff_count;
    int error_count_dd;
    int error_count_ff;
    Date date_start;
    int go_on = 1;
    long count_period=0;

    for(i=0;i<(date_to.year-date_from.year+1)*365+9;i++){
        count_missing[i] = 0;
    }

    date_start = date_from;

    printf("\n******************************************************\n");
    printf("Beginne, Abweichungen aller Zeitraume zu ermitteln...\n");
    printf("******************************************************\n");

    while(go_on == 1){

        date_expected = date_start;

        error_count_dd = 0;
        error_count_ff = 0;

        //Zeiger auf Starttag setzen
        //erste Zeile verwerfen
        fp_in = fopen(file_input, "r");
        fscanf(fp_in, "%*s %*s %*s %*s %*s");
        //erste "richtige" Zeile einlesen
        fscanf(fp_in, "%*5s %4d %2d %2d %2d %*s %*s %*s %f %*1s %d %*s",
               &year_in, &month_in, &day_in, &hour_in, &ff_in, &dd_in);
        date_in = newDate(hour_in, day_in, month_in, year_in);

        while(cmpDates(date_in, date_start) == 1){

            fscanf(fp_in, "%*5s %4d %2d %2d %2d %*s %*s %*s %f %*1s %d %*s",
                   &year_in, &month_in, &day_in, &hour_in, &ff_in, &dd_in);
            date_in = newDate(hour_in, day_in, month_in, year_in);

        }
        printf("\nBerechne Zeitraum ab: \n");
        printDate(date_in);

        //ab hier einlesen der Daten
        for(i = 0; i<8760; i++){

            //Winddaten in Array schreiben
            //gucken, ob date_in date_exp entspricht
            if(cmpDates(date_expected, date_in) == 0){
                if(dd_in < 0 || dd_in > 360){
                    error_count_dd = error_count_dd+1;
                    dd[i] = 999;
                }else{
                    dd[i] = dd_in;
                }
                if(ff_in < 0.0 || ff_in > 900.0){
                    error_count_ff = error_count_ff+1;
                    ff[i] = 999.0;
                }else{
                    ff[i] = ff_in;
                }

                fscanf(fp_in, "%*5s %4d %2d %2d %2d %*s %*s %*s %f %*1s %d %*s",
                       &year_in, &month_in, &day_in, &hour_in, &ff_in, &dd_in);
                date_in = newDate(hour_in, day_in, month_in, year_in);

            }else if(cmpDates(date_expected, date_in) == 1){

                dd[i] = 999;
                ff[i] = 999.0;
                count_missing[count_period] = count_missing[count_period]+1;

            }

            date_expected = nextHour(date_expected);


            //Abbruch, wenn date_to erreicht wird
            if(cmpDates(date_expected, date_to) <= 0){
                go_on = 0;
            }

        }

        //Häufigkeiten für Sektoren/Klassen berechnen
        for(i=0;i<12;i++){
            dd_val[i]=0.0;
        }
        for(i=0;i<9;i++){
            ff_val[i]=0.0;
        }
        dd_count = 0;
        ff_count = 0;
        ff_sum_time = 0;

        for(i=0;i<8760;i++){

            if(dd[i] != 999){

                dd_count = dd_count+1;

                if(dd[i] >= 16 && dd[i] <= 45){
                    dd_val[0] = dd_val[0]+1;
                }else if(dd[i] >= 46 && dd[i] <= 75){
                    dd_val[1] = dd_val[1]+1;
                }else if(dd[i] >= 76 && dd[i] <= 105){
                    dd_val[2] = dd_val[2]+1;
                }else if(dd[i] >= 106 && dd[i] <= 135){
                    dd_val[3] = dd_val[3]+1;
                }else if(dd[i] >= 136 && dd[i] <= 165){
                    dd_val[4] = dd_val[4]+1;
                }else if(dd[i] >= 166 && dd[i] <= 195){
                    dd_val[5] = dd_val[5]+1;
                }else if(dd[i] >= 196 && dd[i] <= 225){
                    dd_val[6] = dd_val[6]+1;
                }else if(dd[i] >= 226 && dd[i] <= 255){
                    dd_val[7] = dd_val[7]+1;
                }else if(dd[i] >= 256 && dd[i] <= 285){
                    dd_val[8] = dd_val[8]+1;
                }else if(dd[i] >= 286 && dd[i] <= 315){
                    dd_val[9] = dd_val[9]+1;
                }else if(dd[i] >= 316 && dd[i] <= 345){
                    dd_val[10] = dd_val[10]+1;
                }else if((dd[i] >= 346 && dd[i] <= 360)||(dd[i] >= 1 && dd[i] <= 15)){
                    dd_val[11] = dd_val[11]+1;
                }
            }
            if(ff[i] != 999){

                ff_count = ff_count+1;

                ff_sum_time = ff_sum_time + ff[i];

                if(ff[i] < 1.4){
                    ff_val[0] = ff_val[0]+1;
                }else if(ff[i] <=1.8){
                    ff_val[1] = ff_val[1]+1;
                }else if(ff[i] <=2.3){
                    ff_val[2] = ff_val[2]+1;
                }else if(ff[i] <=3.8){
                    ff_val[3] = ff_val[3]+1;
                }else if(ff[i] <=5.4){
                    ff_val[4] = ff_val[4]+1;
                }else if(ff[i] <=6.9){
                    ff_val[5] = ff_val[5]+1;
                }else if(ff[i] <=8.4){
                    ff_val[6] = ff_val[6]+1;
                }else if(ff[i] <=10.0){
                    ff_val[7] = ff_val[7]+1;
                }else if(ff[i] >10.0){
                    ff_val[8] = ff_val[8]+1;
                }
            }

        }
        //Häufigkeit prozentual
        ff_mean_time[count_period] = ff_sum_time/ff_count;
        for(i=0;i<9;i++){
            ff_val[i] = ff_val[i]/ff_count;
        }
        for(i=0;i<12;i++){
            dd_val[i] = dd_val[i]/dd_count;
        }
        //dd_val/ff_val in großem Array speichern
        for(i=0;i<12;i++){
            dd_val_periods[count_period][i] = dd_val[i];
        }
        for(i=0;i<9;i++){
            ff_val_periods[count_period][i] = ff_val[i];
        }

        fclose(fp_in);

        date_start = nextDay(date_start);
        date_start.hour = 0;
        count_period++;

    }

/////////////////////////////////////////////////////////////////////////////////
    //quadratische Abweichung zum langjährigen Mittel berechnen
    double deviations[count_period][2];
    double deviations_year[date_to.year-date_from.year][2];
    double dev_dd;
    double dev_ff;
    long j;

    for(i=0;i<count_period;i++){

        dev_dd = 0.0;
        dev_ff = 0.0;

        for(j=0;j<12;j++){
            dev_dd = dev_dd + pow((dd_mean[j]-dd_val_periods[i][j]),2);
        }
        for(j=0;j<9;j++){
            dev_ff = dev_ff + pow((ff_mean[j]-ff_val_periods[i][j]),2);
        }
        deviations[i][0] = dev_dd;
        deviations[i][1] = dev_ff;

    }

/////////////////////////////////////////////////////////////////////////////////
    //Abweichungen sind hier berechnet
    //jetzt Minimum finden und sortieren/normieren
    double min_dd;
    double min_ff;
    double double_dummy;
    long long_dummy;
    Date date_dummy;
    long min_dd_i;

    printf("\n************************************************************************\n");
    printf("Abweichungen zum langjaehrigen Mittel normieren, sortieren und ausgeben\n");
    printf("**************************************************************************\n\n");

    Date dates_periods[count_period];
    dates_periods[0] = date_from;
    for(i=0;i<count_period-1;i++){
        dates_periods[i+1] = nextDay(dates_periods[i]);
    }


    min_ff = deviations[0][1];
    for(i=1;i<count_period;i++){
        if(deviations[i][1] < min_ff){
            min_ff = deviations[i][1];
        }
    }

    for(j=0;j<count_period;j++){

        //Minimale dd_abw finden
        min_dd = deviations[j][0];
        min_dd_i = j;
        for(i=j+1;i<count_period;i++){

            if(deviations[i][0] < min_dd){
                min_dd = deviations[i][0];
                min_dd_i = i;
            }

        }
        //Arrays umsortieren
        date_dummy = dates_periods[min_dd_i];
        dates_periods[min_dd_i] = dates_periods[j];
        dates_periods[j] = date_dummy;

        long_dummy = count_missing[min_dd_i];
        count_missing[min_dd_i] = count_missing[j];
        count_missing[j] = long_dummy;

        double_dummy = ff_mean_time[min_dd_i];
        ff_mean_time[min_dd_i] = ff_mean_time[j];
        ff_mean_time[j] = double_dummy;

        double_dummy = deviations[min_dd_i][0];
        deviations[min_dd_i][0] = deviations[j][0];
        deviations[j][0] = double_dummy;

        double_dummy = deviations[min_dd_i][1];
        deviations[min_dd_i][1] = deviations[j][1];
        deviations[j][1] = double_dummy;

    }

    min_dd = deviations[0][0];

    //Abweichungen normieren
    j = 0;
    for(i=0;i<count_period;i++){

        if(dates_periods[i].day == 1 && dates_periods[i].month == 1 && dates_periods[i].hour == 0){
            deviations_year[j][0] = deviations[i][0];
            deviations_year[j][1] = deviations[i][1];
            j++;
        }

        deviations[i][0] = deviations[i][0]/min_dd*100.;
        deviations[i][1] = deviations[i][1]/min_ff*100.;

    }

    min_dd = deviations_year[0][0];
    min_ff = deviations_year[0][1];
    for(i=0; i<(date_to.year-date_from.year); i++){
        if(deviations_year[i][1] < min_ff){
            min_ff = deviations_year[i][1];
        }
    }

    for(i=0; i<(date_to.year-date_from.year); i++){
        deviations_year[i][0] = deviations_year[i][0]/min_dd*100.;
        deviations_year[i][1] = deviations_year[i][1]/min_ff*100.;
    }

    fp_out = fopen(file_output, "w");
    fp_out2 = fopen(file_output_year, "w");

    fprintf(fp_out,"Beginn Datum; Abweichung dd; Abweichung ff; mittlere Windgeschw.; Verfügbarkeit\n");
    fprintf(fp_out2,"Beginn Datum; Abweichung dd; Abweichung ff; mittlere Windgeschw.; Verfügbarkeit\n");
    j = 0;
    for(i=0;i<count_period;i++){
        fprintf(fp_out,"%02d.%02d.%04d %02d:00 %8.2f %8.2f %7.3f %6.2f\n",dates_periods[i].day, dates_periods[i].month, dates_periods[i].year, dates_periods[i].hour, deviations[i][0],deviations[i][1],ff_mean_time[i],((8760.-count_missing[i])/8760.)*100.);
        if(dates_periods[i].day == 1 && dates_periods[i].month == 1 && dates_periods[i].hour == 0){
            fprintf(fp_out2,"%02d.%02d.%04d %02d:00 %8.2f %8.2f %7.3f %6.2f\n",dates_periods[i].day, dates_periods[i].month, dates_periods[i].year, dates_periods[i].hour, deviations_year[j][0],deviations_year[j][1],ff_mean_time[i],((8760.-count_missing[i])/8760.)*100.);
            j++;
        }
    }

    fclose(fp_out);
    fclose(fp_out2);

    return 0;

}
