#include<iostream>
#include<vector>
#include<random>
using namespace std;


//obsluga random eventow w grze

class randomev{ //regulwoanie probabow w glownym
    private:
    int seed; //ziarno generatora liczb lsoowych
    double probab_zajscia; // prawdopodobienstwo zdarzenia 
    mt19937 gen;
    double mult, staticz; // bonusy i debuffy z random eventow
    string ogloszenie; // wiadomosc do gracza o zajsciu zdazrenai

    public:
    randomev(int seed_, double probab_zajscia_)
    : seed(seed_), probab_zajscia(probab_zajscia_), gen(seed_){};

    int get_seed(){return seed;};

    // sprawdzanie czy w danej turze zachodzi random event
    int random_event(){
        vector<double> probaby = {1.0 - probab_zajscia,probab_zajscia};
        discrete_distribution<> dyskretny2(probaby.begin(), probaby.end());
        int dysk2 = dyskretny2(gen);
        return dysk2;
    };

    //losowanie ktory random even zaszedl jesli random event zaszedl
    void event(){
        vector<double> weights = {0.25, 0.25, 0.25, 0.25};
        discrete_distribution<> dyskretny(weights.begin(), weights.end());
        int dysk = dyskretny(gen);
        //cout << "test ma zwrocic 0,1,2,3 : " << dysk << endl;

        if(dysk == 0){ //procentowe zwiekszenie
            mult = 2; staticz = 0;
            ogloszenie = "twoj kandydat napisal bardzo śmiesznego dla ciebie tweeta, co zainspirowało cię do 2x efektywniejszego fałszowania głosów";
        }
        else if(dysk == 1){
            mult = 1; staticz = -50;
            ogloszenie = "establiszment cie zdołował, twoje fałszerstwo stało się mniej wiarygodne, tracisz 50 głosów";
        }
        else if(dysk == 2){
            mult = 1; staticz = 30;
            ogloszenie = "udalo ci sie przekonac ludzi w kolejce do oddania glowsow dostaje 30 glosow";
        }
        else if(dysk == 3){
            mult = 1; staticz = -30;
            ogloszenie = "twoj kandydat potracil zakonnice na przejsciu dla pieszych tracisz 30 glosow";
        }else{cout << "pusto1" << endl;};
    };

    double get_mult(){return this->mult;};
    double get_staticz(){return this->staticz;};
    string get_ogloszenie(){return this->ogloszenie;};


};