#ifndef DATE_H
#define DATE_H


class Date
{
    //public-Bereich
    public:
        Date();
        virtual ~Date();

        //setter-Methode mit 3 Variablen
        Date(int year, int month, int day);

        //setter-Methode mit 4 Variablen
        Date(int year, int month, int day, int hour);

        //Funktionen, die die Werte des Typs zur�ckgeben
        int year();
        int month();
        int day();
        int hour();

//-------------------------------------------------------------------------------------
///////////////////////Memberfunktionen der Klasse Date////////////////////////////////
//-------------------------------------------------------------------------------------

        //Gibt das Datum aus (dd.mm.yyyy hh:00)
        void printDate();

        //Gibt true zur�ck wenn Schaltjahr, sonst false
        bool isLeapyear();

        //Gibt true zur�ck wenn Ende des Tages erreicht ist, sonst false
        bool endOfDay();

        //Gibt true zur�ck, wenn Ende des Monats erreicht ist, sonst false
        bool endOfMonth();

        //Gibt true zur�ck, wenn Ende das Jahres erreicht ist, sonst false
        bool endOfYear();

        //Funktion die die zeitliche Lage zweier Zeitpunkte zueinander bewertet
        //gibt 0 zur�ck, wenn Daten gleich sind
        //gibt 1 zur�ck, wenn this.date sp�ter liegt
        //gibt -1 zur�ck, wenn this.date fr�her liegt
        int compareToHour(Date cmpDate);

        //Funktion die die zeitliche Lage zweier Zeitpunkte zueinander bewertet
        //gibt 0 zur�ck, wenn Daten gleich sind
        //gibt 1 zur�ck, wenn this.date sp�ter liegt
        //gibt -1 zur�ck, wenn this.date fr�her liegt
        int compareToDay(Date cmpDate);

        //Setzt Date auf die erste Stunde (hour = 0) des n�chsten Tages
        void nextDay();

        //Setzt Date auf die n�chste Stunde
        void nextHour();


    //protected-Bereich
    protected:
    //private-Bereich
    private:
        short year_;
        short month_;
        short day_;
        short hour_;

};

#endif // DATE_H
