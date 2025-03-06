#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>

class PlatitorTaxe{
private:
    std::string tip_entitate;
    std::string nume;
    int suma_bani;
    int suma_netaxabila;
public:
    PlatitorTaxe(std::string tip_entitate, std::string nume, int suma_bani, int suma_netaxabila):tip_entitate(tip_entitate), nume(nume), suma_bani(suma_bani), suma_netaxabila(suma_netaxabila){}
    
    std::string get_tip_entitate(){
        return this->tip_entitate;
    }
    std::string get_nume(){
        return this->nume;
    }
    float get_suma_bani(){
        return this->suma_bani;
    }
    float get_suma_netaxabila(){
        return this->suma_netaxabila;
    }
};

class PersoanaFizica:public PlatitorTaxe{
public:
    PersoanaFizica(std::string tip_entitate, std::string nume, int suma_bani, int suma_netaxabila):PlatitorTaxe(tip_entitate,nume,suma_bani,suma_netaxabila){}
};

class Firma:public PlatitorTaxe{
public:
    Firma(std::string tip_entitate, std::string nume, int suma_bani, int suma_netaxabila):PlatitorTaxe(tip_entitate,nume,suma_bani,suma_netaxabila){}
};

class AgentieAdministrareFiscala{
private:
    std::vector<PlatitorTaxe*> vec_p;
public:
    void add_entity(PlatitorTaxe* p_entitati){
        vec_p.push_back(p_entitati);
    }
    void afisare(){
        for(int i=0; i<vec_p.size(); i++){
            std::cout<<vec_p[i]->get_nume()<<std::endl<<vec_p[i]->get_suma_bani()<<std::endl;
        }
    }
    void taxe_baza(int procent_taxe_persoanafizica, int procent_taxe_firma){
        for(int i=0; i<vec_p.size(); i++)
            if(vec_p[i]->get_tip_entitate()=="Persoana Fizica"){
                int valoare_taxa=(vec_p[i]->get_suma_bani()-vec_p[i]->get_suma_netaxabila())*(procent_taxe_persoanafizica)/100;
                std::cout<<vec_p[i]->get_nume()<<std::endl<<valoare_taxa<<std::endl;
            }
            else
                if(vec_p[i]->get_tip_entitate()=="Firma"){
                    int valoare_taxa=(vec_p[i]->get_suma_bani()-vec_p[i]->get_suma_netaxabila())*(procent_taxe_firma)/100;
                    std::cout<<vec_p[i]->get_nume()<<std::endl<<valoare_taxa<<std::endl;
                }
    }
    void procent_venituri_netaxabile(){
        int verific=0;
        for(int i=0; i<vec_p.size(); ++i){
            if(vec_p[i]->get_suma_netaxabila() > 0.2*(vec_p[i]->get_suma_bani())){
                std::cout<<vec_p[i]->get_nume()<<std::endl<<std::fixed<<std::setprecision(2)<<((vec_p[i]->get_suma_netaxabila()/vec_p[i]->get_suma_bani())*100)<<std::endl;
                verific=1;
            }
        }
        if(verific==0)
            std::cout<<"Nicio potentiala frauda detectata"<<std::endl;
    }
    void taxe_totale(int procent_taxe_persoanafizica, int procent_taxe_firma){
        float venit_taxabil;
        float taxa;
        float taxa_totala=0;
        for(int i=0; i<vec_p.size(); ++i){
            venit_taxabil = vec_p[i]->get_suma_bani()-vec_p[i]->get_suma_netaxabila();
            if(vec_p[i]->get_tip_entitate()=="Persoana Fizica"){
                if(venit_taxabil > 300000){
                    taxa=300000*procent_taxe_persoanafizica/100+((venit_taxabil-300000)*2*procent_taxe_persoanafizica/100);
                    std::cout<<vec_p[i]->get_nume()<<std::endl<<std::fixed<<std::setprecision(2)<<taxa<<std::endl;
                }
                else
                    if(venit_taxabil < 300000){
                        taxa=venit_taxabil*procent_taxe_persoanafizica/100;
                        std::cout<<vec_p[i]->get_nume()<<std::endl<<std::fixed<<std::setprecision(2)<<taxa<<std::endl;
                    }
            }
            else
                if(vec_p[i]->get_tip_entitate()=="Firma"){
                    if(venit_taxabil > 300000){
                        taxa=(vec_p[i]->get_suma_bani()-vec_p[i]->get_suma_netaxabila())*(procent_taxe_firma+19)/100;
                        std::cout<<vec_p[i]->get_nume()<<std::endl<<std::fixed<<std::setprecision(2)<<taxa<<std::endl;
                    }
                    else{
                        if(venit_taxabil < 300000){
                            taxa=(vec_p[i]->get_suma_bani()-vec_p[i]->get_suma_netaxabila())*procent_taxe_firma/100;
                            std::cout<<vec_p[i]->get_nume()<<std::endl<<std::fixed<<std::setprecision(2)<<taxa<<std::endl;
                        }
                    }
                }
            taxa_totala=taxa_totala+taxa;
        }
        std::cout<<taxa_totala<<std::endl; 
    }
        
};


int main(){
    int test;
    int nr_entitati;
    std::string temp_tip_entitate;
    std::string temp_nume;
    float temp_suma_bani;
    float temp_suma_netaxabila;
    
    std::cin>>test;
    std::cin>>nr_entitati;
    std::cin.ignore();
    
    AgentieAdministrareFiscala anaf;
    
    
    for(int i=0; i<nr_entitati; ++i){
        std::getline(std::cin, temp_tip_entitate);
        std::getline(std::cin, temp_nume);
        std::cin>>temp_suma_bani;
        std::cin>>temp_suma_netaxabila;
        std::cin.ignore();
        if(temp_tip_entitate=="Persoana Fizica")
           anaf.add_entity(new PersoanaFizica(temp_tip_entitate, temp_nume, temp_suma_bani, temp_suma_netaxabila));
        else
            if(temp_tip_entitate=="Firma")
               anaf.add_entity(new Firma(temp_tip_entitate, temp_nume, temp_suma_bani, temp_suma_netaxabila));
    }
    
    if(test==1){
        anaf.afisare();
    }
    if(test==2){
        int procent_taxe_persoanafizica;
        int procent_taxe_firma;
        std::cin>>procent_taxe_persoanafizica;
        std::cin>>procent_taxe_firma;
        anaf.taxe_baza(procent_taxe_persoanafizica, procent_taxe_firma);
    }
    if(test==3){
        anaf.procent_venituri_netaxabile();
    }
    if(test==4){
        //firma TVA = 19%
        int procent_taxe_persoanafizica;
        int procent_taxe_firma;
        std::cin>>procent_taxe_persoanafizica;
        std::cin>>procent_taxe_firma;
        anaf.taxe_totale(procent_taxe_persoanafizica, procent_taxe_firma);
    }
    
   
}
