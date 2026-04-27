#include <iostream>
#include <fstream>
using namespace std;

#include "klasizm2.h"
#include "random.h"
#include "saver.h"


int main(){

    //wczytywanie stanu gry 
    loader stan("zapis1.txt");
    vector<int> stan_vec_aktual;

    //wczytywanie osiagniec
    loader achiv("achiv_zapis.txt");
    vector<int> achiv_vec;
    achiv_vec = achiv.wczytywanie(); 

    //menu startowe
    cout << "nowa gra-> n , wczytaj -> w, wyjdz -> e" << endl;
    string menu1;
    cin >> menu1;

    if(menu1 == "n"){
        //tworzenie nowego zapisu
        vector<int> stan_vec_new = {0, 0, 0, 0, 0, 0, 0, 0, 2, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 1};

        stan.zapis(stan_vec_new);
        stan_vec_aktual = stan.wczytywanie();
    } 
    else if(menu1 == "w"){
        stan_vec_aktual = stan.wczytywanie();

    } 
    else if(menu1 == "e"){
        return 1;
    }else{cout << "nie rozpoznano literki" << endl;}

    
    // tworzenie gracza i budynkow z zapisu
    player dummy(stan_vec_aktual.at(0),stan_vec_aktual.at(1),stan_vec_aktual.at(2),stan_vec_aktual.at(3));
    budyneka1 dumbuilda(&dummy,stan_vec_aktual.at(8),stan_vec_aktual.at(9),stan_vec_aktual.at(10),stan_vec_aktual.at(11));
    budynekb1 dumbuildb(&dummy,stan_vec_aktual.at(12),stan_vec_aktual.at(13),stan_vec_aktual.at(14),stan_vec_aktual.at(15));
    budynekc1 dumbuildc(&dummy,stan_vec_aktual.at(16),stan_vec_aktual.at(17),stan_vec_aktual.at(18),stan_vec_aktual.at(19));
    dumbuilda.set_lvl(stan_vec_aktual.at(4));
    dumbuildb.set_lvl(stan_vec_aktual.at(5));
    dumbuildc.set_lvl(stan_vec_aktual.at(6));
    int turn_count = stan_vec_aktual.at(7);




    bool game = true; //podtrzymanie petli gry
    string input; //gracz wpisuje w to komendy


    //tworzenie rzeczy do randomeventow
    int sed = 1;
    random_device rd;
    sed = rd();
    randomev rand(sed, 0.2);

    int mo_static, mo_multip;

    int checker = 0; // sprawdzanie czy wyswietlono juz instrukcje i wstep zeby w zerowej rundzie nie wyswieltalo sie bez przerwy

    while(game){

        //sprawdzanie achivmentow
        if(turn_count == 100){
            cout << "wow ethan, great moves, keep it up, im proud of you " << endl;
            cout << "odblokowano osiagniecie !!!!!!!!" << endl;
            cout << "udalo ci sie grac przez 100 rund" << endl;
            achiv_vec.at(2) = 1;
        }; //achivvec ma taka strukture: tury siopa achiv1 achiv2 achiv3
        if(dumbuilda.get_lvl() == 5){
            cout << "osiagniecie osiagniecie !!!!" << endl;
            cout << "udalo ci sie ulpszyc komitet do poziomu 5 kongratulacje" << endl;
            achiv_vec.at(3) = 1;
        };
        if(dummy.get_skarbiec(0) >= 10000){
            cout << "gratulacje sfałszował_ś 10000 głosów wygral_s" << endl;
            cout << "koniec tego dobrego co za duzo frajdy to niezdrowo" << endl;
            cout << "program sie wylacza. baj baj" << endl; 
            achiv_vec.at(4) = 1;
            break;
        };

        if(turn_count == 0 and checker == 0){
            cout << "w grze wcielasz sie w fanatycznego wyborce bardzo niszowego kandydata w wyborach" << endl;
            cout << "ponieważ wiesz że nikt nie lubi twojego kandydata i nikt na niego nie zagłosuje" << endl;
            cout << "to na tobie spoczywa oddpowiedzialność doprowadzenia do jego zwyciestwa" << endl;
            cout << " w tym celu w każdej turze fałszuj głosy, buduj nowe komitety, fabryki sztucznych dowodów tożsamości i korumpuj członków pkw" << endl;
            cout << " gra kończy się kiedy uda ci się zdobyć 10 000 głosów" << endl;
            cout << "instrukcja->h"<< endl; checker =1;
        };



        //poczatek nowej tury
        cout<< "..." <<endl;
        cout << "runda : " << turn_count << endl;
        cout << "graczu komenduj" << endl;
        cin >> input;

        //kolejna tura
        if(input == "y"){
            //sprawdzanie modyfikator z random eventow
            int random_event = rand.random_event();
            if(random_event == 0){mo_static = 0, mo_multip = 1;}
            else if (random_event == 1){
                rand.event();
                mo_static = rand.get_staticz(); 
                mo_multip = rand.get_mult();
                cout << rand.get_ogloszenie() << endl;

            }else{cout << "unknown unknown !!!!" << endl;}
            //liczenie przyrostu walut z random eventow i budynkow
            int tot_money_bonus;
            tot_money_bonus = (dumbuilda.getn(0) + dumbuildb.getn(0)+ dumbuildc.getn(0) + mo_static )*mo_multip;
            dummy.addn_skarbiec(0,tot_money_bonus);

            int tot_wala_bonus = dumbuildc.getn(1);
            dummy.addn_skarbiec(1, tot_wala_bonus);

            int tot_walb_bonus = dumbuilda.getn(2);
            dummy.addn_skarbiec(2, tot_walb_bonus);

            int tot_walc_bonus = dumbuildb.getn(3);
            dummy.addn_skarbiec(3, tot_walc_bonus);
            cout << "przyrost w nastepnej rundzie: głosy: " << tot_money_bonus << " rekruci komitety: " << tot_wala_bonus << " rekruci szpiedzy pkw: " << tot_walb_bonus << " rekruci fałszerzy dowodów: " << tot_walc_bonus << endl;

            turn_count += 1;

            //zapelnianie wektora osiagniec i sprawdzanie czy gracz zdobyl osiagniecia
            if(achiv_vec.size()>1){
                if(turn_count > achiv_vec.at(0)){achiv_vec.at(0) = turn_count;};
            }else if(achiv_vec.size() == 0){achiv_vec.push_back(turn_count);};
            //achiv_vec liczba tur liczba siopy
            if(achiv_vec.size()>1){
                if(dummy.get_skarbiec(0) > achiv_vec.at(1)){achiv_vec.at(1) = dummy.get_skarbiec(0);};
            }else if(achiv_vec.size() == 1){
                achiv_vec.push_back(dummy.get_skarbiec(0));
                achiv_vec.push_back(0);
                achiv_vec.push_back(0);
                achiv_vec.push_back(0);
            };
        }
        //ulepszanie
        else if(input == "ulepsz"){
            cout << "co chcesz zbudować komitet->a, szpieg w pkw ->b czy fabryka podróbek dowodów->c ? e->wyjscie" << endl;;
            int upmo,upwa;
            string budynek, rodzaj;
            cin >> budynek;
            if(budynek == "e"){continue;}
            else if(budynek !="a" and budynek !="b" and budynek != "c"){cout << "nie rozpoznano literki" << endl; continue;}
            else{
                cout << "jaki rodzaj ulepszenia?" << endl;
                cout << "p->wiecej glosow , w->wiecej rekrutów, e->wyjscie" << endl;
                cin >> rodzaj;
                if(rodzaj == "e"){continue;}
                else if(rodzaj !="p" and rodzaj !="w"){cout << "nie rozpoznano literki" << endl; continue;}
                else if(rodzaj == "p"){upmo = 2; upwa = 0;}
                else if(rodzaj == "w"){upmo = 0; upwa = 2;};
                if(budynek == "a"){dumbuilda.upgrade_a(upmo,upwa);}
                else if(budynek == "b"){dumbuildb.upgrade_b(upmo,upwa);}
                else if(budynek == "c"){dumbuildc.upgrade_c(upmo,upwa);}
                else{continue;}
            };
        }
        //wszystkie dane o sytuacji gracza
        else if(input == "status"){
            cout << "oddal_ś tyle głosów : " << dummy.get_skarbiec(0) << endl;
            cout << "masz tylu rekrutów na szpiegów: " << dummy.get_skarbiec(1) << endl;
            cout << "masz tylu rekrutów na fałszerów dowodów: " << dummy.get_skarbiec(2) << endl;
            cout << "masz tylu rekrutów na : " << dummy.get_skarbiec(3) << endl;
            cout << "liczba komitetów: " << dumbuilda.get_lvl() << endl;
            cout << "liczba szpiegów pkw: " << dumbuildb.get_lvl() << endl;
            cout << "liczba fabryk podrobionych dowodów: " << dumbuildc.get_lvl() << endl;
            cout << "teraz jest " << turn_count << " tura " << endl;
        }
        //zapis
        else if(input == "save"){
            vector<int> stan_vec1;
            stan_vec1.push_back(dummy.get_skarbiec(0)); 
            stan_vec1.push_back(dummy.get_skarbiec(1)); 
            stan_vec1.push_back(dummy.get_skarbiec(2)); 
            stan_vec1.push_back(dummy.get_skarbiec(3)); 
            stan_vec1.push_back(dumbuilda.get_lvl());
            stan_vec1.push_back(dumbuildb.get_lvl());
            stan_vec1.push_back(dumbuildc.get_lvl());
            stan_vec1.push_back(turn_count);
            for(int i = 0 ; i <= 3; i++){stan_vec1.push_back(dumbuilda.getn(i));};
            for(int i = 0 ; i <= 3; i++){stan_vec1.push_back(dumbuildb.getn(i));};
            for(int i = 0 ; i <= 3; i++){stan_vec1.push_back(dumbuildc.getn(i));};
            cout << "stan save test " << endl;  
            stan.zapis(stan_vec1);
            cout << "achiva save test : " << endl; //test
            achiv.zapis_achiv(achiv_vec);
            cout << "udalo sie zapisac" << endl; //test 
        }
        //wyjscie
        else if(input == "exit"){
            cout << "czy chcesz zapisac stan gry przed wyjsciem?" << endl;
            cout << "y->tak n->nie" << endl;
            string inpt_ex;
            cin >> inpt_ex;
            if(inpt_ex == "y"){
                vector<int> stan_vec1;
            stan_vec1.push_back(dummy.get_skarbiec(0)); 
            stan_vec1.push_back(dummy.get_skarbiec(1)); 
            stan_vec1.push_back(dummy.get_skarbiec(2)); 
            stan_vec1.push_back(dummy.get_skarbiec(3)); 
            stan_vec1.push_back(dumbuilda.get_lvl());
            stan_vec1.push_back(dumbuildb.get_lvl());
            stan_vec1.push_back(dumbuildc.get_lvl());
            stan_vec1.push_back(turn_count);
            for(int i = 0 ; i <= 3; i++){stan_vec1.push_back(dumbuilda.getn(i));};
            for(int i = 0 ; i <= 3; i++){stan_vec1.push_back(dumbuildb.getn(i));};
            for(int i = 0 ; i <= 3; i++){stan_vec1.push_back(dumbuildc.getn(i));};
            stan.zapis(stan_vec1);
            achiv.zapis_achiv(achiv_vec);
            game = false;
            }
            else if(inpt_ex == "n"){game = false;}
            else{cout << "nie rozpoznano literki " << endl; continue ;}
        }

        //sprawdzanie osiagniec
        else if(input == "achivmenty"){
            cout << "najwieksza rozgrana liczba tur " << achiv_vec.at(0) << endl;
            cout << "najwieksza liczba sfałszowanych głosów " << achiv_vec.at(1) << endl;
            if(achiv_vec.at(2) == 1){
                cout << "osiagniecie : rozegrano 100 rund" << endl;
            }else if(achiv_vec.at(3) == 1){
                cout << "osiagniecie : udalo sie ulepszyc komitet do poziomu 5" << endl;
            }else if(achiv_vec.at(4) == 1){
                cout << "osiagniecie : udalo sie ukonczyc gre" << endl;
            }
        }

        //instrukcja
        else if(input == "h"){
            cout << "nastepna tura -> y" << endl;
            cout << "sklep -> ulepsz" << endl;
            cout << "zapisz -> save" << endl;
            cout << "stan skarbca budynkow itd. -> status" << endl;
            cout << "osiagniecia -> achivmenty" << endl;
            cout << "budowanie komitetów dostarcza nowe głosy na ture oraz rekrutów na szpiegów na ture" << endl;
            cout << "budowanie szpiegów dostarcza nowe głosy na ture oraz rekrutów na fałszerów dowodów osobistych na ture" << endl;
            cout << "budowanie fałszerów dostarcza nowe głosy na ture oraz rekrutów na działaczy w twoich komitetach na ture" << endl;
            cout << "instrukcja -> h" << endl;
            cout << "wyjscie z gry -> exit" << endl;
        }

        else{ cout << "nie rozopoznano polecenia" << endl;}

    }


    return 0;
};


