#include <iostream>
#include <fstream>
#include <vector>
#include<filesystem>
namespace fs = std::filesystem;
using namespace std;

//plik oblusugjacy zapisywanie i wczytywanie


class loader{

    //nazwa pliku z zapisem
    private:
    string plik;

    public:
    loader(string plik_)
    : plik(plik_){};

    //metoda wczytywania

    vector<int> wczytywanie(){

        ifstream stan(this->plik);
        vector<int> stan_vec;

        if(fs::exists(this->plik)){
            if(stan.is_open()){
                int cyferka;
                while(stan >> cyferka){stan_vec.push_back(cyferka);};
                stan.close();
            }
        //else if (!stan.is_open()) {
        //    ofstream new_file(this->plik);}

            else{cout << "nie udalo sie wczytac zapisu" << endl;};}

        else if(!fs::exists(this->plik)){
            ofstream new_file(this->plik);
        }
        return stan_vec; // w stan_vec jest skarbiec0,1,2,3 lvl a,b,c turn_count potem nvece dal kazdegfo z budynkow
    };

    //metoda zapisywania 

    void zapis(vector<int> stan_vec_old){ /// ma dostawac stan_vec i zamieniac go na plik txt
        ofstream new_save(this->plik);
        if(new_save.is_open()){
            for(int i = 0; i <= 19; i++){
                new_save << stan_vec_old.at(i);
                new_save << " ";
            };
        }else{cout << "nie udalo sie otworzyc pliku zapisu" << endl;};

    };

    // metoda zapisywania achivmentow ma byc zaachowana po rozpoczeciu nowej gry

    void zapis_achiv(vector<int> stan_vec_old){ /// tylko cyferke zmienilkem poniewaz juz koncze to chyba nie mas sensu odyfikowac tametej tylko lepiej zrobic nowa porpostu
        ofstream new_save(this->plik);
        if(new_save.is_open()){
            for(int i = 0; i <= 4; i++){
                new_save << stan_vec_old.at(i);
                new_save << " ";
            };
        }else{cout << "nie udalo sie otworzyc pliku zapisu" << endl;};

    };

};