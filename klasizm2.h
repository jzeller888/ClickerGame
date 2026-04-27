#include<iostream>
#include<vector>
#include<random>
#include <map>
using namespace std;

//plik obslugujacy klase gracza i budynków

class player{
    private:
    // zasoby
    int money, wa, wb, wc;
    //wektor w ktorym trzymam zasoby
    vector<int> skarbiec;

    public:
    
    player(int mo = 1, int wa_ = 1, int wb_ = 1, int wc_ = 1)
        : money(mo), wa(wa_), wb(wb_), wc(wc_){
            skarbiec.push_back(money);
            skarbiec.push_back(wa);
            skarbiec.push_back(wb);
            skarbiec.push_back(wc);
        };

    //obsluga wektora skarbca
    int get_skarbiec(int m){return skarbiec.at(m);};
    void set_skarbiec(int m, int k){skarbiec.at(m) = k;};
    void addn_skarbiec(int m, int k){skarbiec.at(m) += k;};
};


//klasa budynku potem budynki ktore kupuje sie w grze sa opisane klasa ktora dziedziczy po tej

class budynek {
    protected:
    //wskaznik na gracza zeby klasa mogla sie kontaktowac ze skarbcem
    player* player_adres;
    // bonusy do kazdej z walut od budynkow
    int nm, na, nb, nc;
    //wektor w ktorym trzymane sa bonusy
    vector<int> nvec;
    //sprawdzacz czy gracz mial wystarczajco zasobow na ulepszenie
    bool upg_suc;

    public:
    budynek(player* adres_, int nm_, int a_, int b_, int c_)
        : player_adres(adres_), nm(nm_), na(a_), nb(b_), nc(c_), upg_suc(false){
            nvec.push_back(nm);
            nvec.push_back(na);
            nvec.push_back(nb);
            nvec.push_back(nc);
        };

        //obsluga wektora bonusow
    int getn(int m){return nvec.at(m);};
    void setn(int m, int k){nvec.at(m) = k ;};
// ntyp to multiplier danego typu waluty
    //ulepszanie uogulnione // typ : money 0, wala 1, walb 2, walc 3 
    void set_upg_suc(bool wart){upg_suc = wart;};

    // ogólna metoda ulepszania
    virtual void upgrade(int typ1, int ntyp1, int typ2, int ntyp2, vector<int> koszt, int lvl){ 

//sprawdzanie czy gracza stac na ulepszenie
        int notariusz = 0;
        map<int, string> walutnik;
        walutnik[0] = "głosów"; walutnik[1] ="rekrutów do komitetów"; walutnik[2]="rekrutów na szpiegów"; walutnik[3]="rekrutów na podrabiaczy";

        for(int i = 0; i <= 3; i++){
            if (player_adres->get_skarbiec(i) >= koszt.at(i)){
                //cout << i << endl;                 
                cout << "masz wystarczająco " << walutnik[i] << " gratulacje" << endl;
                notariusz += 1;
                //cout << notariusz << endl;
            }else{
                cout << "nie masz biedaku "<< walutnik[i] << " wracaj farmic" << endl;
                break;
        };
        };
        if(notariusz == 4){ //ulepszanie jesli gracz ma wystarczajaco srodkow
            cout << "masz wystarczajaco roznego roadzju pieniedzy, zostaje ulepszone i pobrane ze skarbca" << endl;;
            this->setn(typ1, ntyp1) ; // ulepszanie
            this->setn(typ2, ntyp2); // ulepszanie
            for(int i = 0 ; i <= 3; i++){
                player_adres->addn_skarbiec(i,- koszt.at(i)); //platnosc
                cout << "rodzaju " << i << " zostalo: " << player_adres->get_skarbiec(i) << endl;
            }; // placenie
        };
        if(notariusz == 4){this->set_upg_suc(true);} //ulepszenie sie powiodlo

    };
};





//budynek typu a produkuje walute b (czyli komitet produkuje szpiegow)

class budyneka1 : public budynek{
    private:
    //poziom budynku osobny dla kazdego z buydnkow
    int lvl;

    public:
    budyneka1(player* adres_, int nm_ = 1, int na_ = 1, int nb_ = 1, int nc_ = 1)  
        : budynek(adres_, nm_, na_, nb_, nc_), lvl(1){};
    int get_lvl(){return lvl;}; 
    void up_lvl(){lvl += 1;};
    void set_lvl(int n){lvl = n;};
    
    //ulepszenie
    void upgrade_a(int mon, int wal){
        int lvlt = this->get_lvl();
        vector<int> costa = {lvlt*25, (lvl )*5, 0,0} ;
        int n = lvlt + 1 ;
        cout << "lvl : " << lvlt << endl;;
        upgrade(0, n + mon, 2, n + wal, costa, lvlt); //wybor rodzaju ulepszenia pieniezne lub walutowe
        if(upg_suc){up_lvl();};

    };
}; // budynki a pomagaj zdobywac wal b, b->c, c->a i wszystkie troche siopy tez


//budynek b i c analogiczne


class budynekb1 : public budynek{
    private:
    int lvl;

    public:
    budynekb1(player* adres_, int nm_ = 1, int na_ = 1, int nb_ = 1, int nc_ = 1)  
        : budynek(adres_, nm_, na_, nb_, nc_), lvl(1){};
    int get_lvl(){return lvl;}; 
    void up_lvl(){lvl += 1;};
    void set_lvl(int n){lvl = n;};
    
    //ulepszenie
    void upgrade_b(int mon, int wal){
        int lvlt = this->get_lvl();
        vector<int> costa = {lvlt*25, 0, (lvl )*5,0} ;
        int n = lvlt + 1 ;
        upgrade(0, n + mon, 3, n + wal, costa, lvlt);
        if(upg_suc){up_lvl();};

    };
};

class budynekc1 : public budynek{
    private:
    int lvl;

    public:
    budynekc1(player* adres_, int nm_ = 1, int na_ = 1, int nb_ = 1, int nc_ = 1)  
        : budynek(adres_, nm_, na_, nb_, nc_), lvl(1){};
    int get_lvl(){return lvl;}; 
    void up_lvl(){lvl += 1;};
    void set_lvl(int n){lvl = n;};
    
    //ulepszenie
    void upgrade_c(int mon, int wal){
        int lvlt = this->get_lvl();
        vector<int> costa = {lvlt*25, 0, 0, (lvl )*5} ;
        int n = lvlt + 1 ;
        upgrade(0, n + mon, 1, n + wal, costa, lvlt);
        if(upg_suc){up_lvl();};
    };
};

