#include <iostream>
#include <string>

class Profil{
private:
    std::string nume;
    int an, luna, ziua;
public:
    Profil(std::string nume, int an, int luna, int ziua):nume(nume), an(an), luna(luna), ziua(ziua){}
    void display(int i){
        std::cout<<i<<std::endl;
        std::cout<<nume<<std::endl;
        std::cout<<an<<' ';
        std::cout<<luna<<' ';
        std::cout<<ziua<<std::endl;
    }
    int verific_data_nastere(){
        if(an>=1900 && an<=2021)
            if(luna<=12)
                if(ziua<=30)
                    return 1;
                else return 0;
            else return 0;
        return 0;
                
    }
    int calculare_varsta(int temp_an, int temp_luna, int temp_ziua){
        if(temp_luna>luna)
            return temp_an-an;
        else
            if(temp_luna==luna)
                if(temp_ziua>ziua)
                    return temp_an-an;
                else
                    return temp_an-an-1;
            return temp_an-an-1;
        return temp_an-an-1;
            
    }
    void display_nume(){
        std::cout<<nume<<std::endl;
    }
};

class Post{
private:
    int ID;
    int limit_inf, limit_sup;
    std::string continut;
public:
    Post(){};
    Post(int ID, int limit_inf, int limit_sup, std::string continut):ID(ID), limit_inf(limit_inf), limit_sup(limit_sup), continut(continut){}
    void display_postare(){
        std::cout<<continut<<std::endl;
    }
    int preluare_limit_inf(){
        return limit_inf;
    }
    int preluare_limit_sup(){
        return limit_sup;
    }
    int preluare_id(){
        return ID;
    }
};

class Website{
private:
    Profil **utilizator=nullptr;
    Post **postare=nullptr;
    std::string nume;
    int an, luna, ziua;
    int ID;
    int limit_inf, limit_sup;
    std::string continut;
public:
    Website(){}
    Website(Profil **utilizator, Post **postare):utilizator(utilizator), postare(postare){}
    //postari
    void initializare_postari(int nr_postari){
        postare=new Post*[nr_postari];
    }
    void citire_postari(int nr_postari){
        for(int i=0; i<nr_postari; ++i){
            std::cin>>ID;
            std::cin>>limit_inf>>limit_sup;
            std::cin.ignore();
            std::getline(std::cin, continut);
            *(postare+i)=new Post(ID, limit_inf, limit_sup, continut);
        }
    }
    //profil
    void initializare_profil(int nr_utilizatori){
        utilizator=new Profil*[nr_utilizatori];
    }
    void citire_profil(int nr_utilizatori){
        for(int i=0; i<nr_utilizatori; ++i){
            std::getline(std::cin, nume);
            std::cin>>an;
            std::cin>>luna;
            std::cin>>ziua;
            std::cin.ignore();
            *(utilizator+i)=new Profil(nume, an, luna, ziua);        
        }
    }
    void lista_utilizatori(int nr_utilizatori){
        for(int i=0; i<nr_utilizatori; ++i){
            (*(utilizator+i))->display(i);
        }
    }
    void verificare_data_nastere(int nr_utilizatori){
        for(int i=0; i<nr_utilizatori; ++i){
            if((*(utilizator+i))->verific_data_nastere()==1)
                (*(utilizator+i))->display(i);
            else{
                std::cout<<i<<std::endl;
                std::cout<<"EROARE: Data de nastere introdusa nu e valida"<<std::endl;
            }
        }
    }
    void afisare_varsta(int nr_utilizatori, int temp_an, int temp_luna, int temp_ziua){
        for(int i=0; i<nr_utilizatori; ++i){
            if((*(utilizator+i))->calculare_varsta(temp_an, temp_luna, temp_ziua)>=18){
                (*(utilizator+i))->display_nume();
                std::cout<<(*(utilizator+i))->calculare_varsta(temp_an, temp_luna, temp_ziua)<<std::endl;
            }
        }
    }
    void afisare_perspectiva_0(int nr_postari, int temp_an, int temp_luna, int temp_ziua){
        std::cout<<"News Feed"<<std::endl;
        int k=0;
        for(int i=0; i<nr_postari; ++i){
            if((*(postare+i))->preluare_id()==0){
                (*(utilizator+0))->display_nume();
                (*(postare+0))->display_postare();
                k=0;
            }
            else
                if((*(utilizator+0))->calculare_varsta(temp_an, temp_luna, temp_ziua)>=(*(postare+i))->preluare_limit_inf() && (*(utilizator+0))->calculare_varsta(temp_an, temp_luna, temp_ziua)<=(*(postare+i))->preluare_limit_sup()){
                    (*(utilizator+((*(postare+i)))->preluare_id()))->display_nume();
                    (*(postare+i))->display_postare();
                    k=0;
                }
            k++;
            if(k==nr_postari)
                std::cout<<"No posts for you"<<std::endl;
        }
    }
};

int main(){
    int nr_utilizatori;
    std::cin>>nr_utilizatori;
    std::cin.ignore();
    Website w1;
    w1.initializare_profil(nr_utilizatori);
    w1.citire_profil(nr_utilizatori);
    int test;
    std::cin>>test;
    if(test==1){
        w1.lista_utilizatori(nr_utilizatori);
    }
    if(test==2){
        w1.verificare_data_nastere(nr_utilizatori);
    }
    if(test==3){
        int temp_an, temp_luna, temp_ziua;
        std::cin>>temp_an>>temp_luna>>temp_ziua;
        w1.afisare_varsta(nr_utilizatori, temp_an, temp_luna, temp_ziua);
    }
    if(test==4){
        int temp_an, temp_luna, temp_ziua;
        std::cin>>temp_an>>temp_luna>>temp_ziua;
        std::cin.ignore();
        int nr_postari;
        std::cin>>nr_postari;
        std::cin.ignore();
        w1.initializare_postari(nr_postari);
        w1.citire_postari(nr_postari);
        w1.afisare_perspectiva_0(nr_postari, temp_an, temp_luna, temp_ziua);
    }
}
