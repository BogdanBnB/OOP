#include <iostream>
#include <string>
#include <iomanip>

class Angajat{
private:
    std::string nume;
    std::string departament;
    std::string tip;
public:
    Angajat(std::string nume, std::string departament, std::string tip):nume(nume), departament(departament), tip(tip){}
    virtual void afisare() = 0;
    virtual float rentabilitate_angajat() = 0;
    std::string get_nume(){
        return this->nume;
    }
    std::string get_departament(){
        return this->departament;
    }
    std::string get_tip(){
        return this->tip;
    }
    virtual float salariu_anual() = 0;
};

class Salariat: public Angajat{
private:
    int norma;
    int vechime;
    float salariu_net;
public:
    Salariat(std::string nume, std::string departament, std::string tip, int norma, int vechime, float salariu_net):Angajat(nume, departament,tip), norma(norma), vechime(vechime), salariu_net(salariu_net){}
    void afisare(){
        std::cout<<get_nume()<<' '<<norma<<' ' <<vechime<<' '<<salariu_net<<std::endl;
    }
    float rentabilitate_angajat(){
        return (norma*(250-20+vechime/3))/(salariu_net*12);
    }
    float salariu_anual(){
        return salariu_net*12;
    }
};

class Colaborator: public Angajat{
private:
    float onorariu;
    float nr_prestari_anuale;
public:
    Colaborator(std::string nume, std::string departament, std::string tip, float onorariu, float nr_prestari_anuale):Angajat(nume, departament, tip), onorariu(onorariu), nr_prestari_anuale(nr_prestari_anuale){}
    void afisare(){
        std::cout<<get_nume()<<' '<<onorariu<<' '<<nr_prestari_anuale<<std::endl;
    }
    float rentabilitate_angajat(){
        return 0;
    }
    float salariu_anual(){
        return onorariu*nr_prestari_anuale;
    }
};

int main(){
    int n;
    std::cin>>n;
    
    std::string tip;
    std::string temp_nume;
    std::string temp_departament;
    int temp_norma;
    int temp_vechime;
    float temp_salariu_net;
    float temp_onorariu;
    float temp_nr_prestari_anuale;
    
    //initializarea
    Angajat ** a=nullptr;
    a=new Angajat*[n];
    //citirea
    for(int i=0; i<n; i++){
        std::cin>>tip;
        if(tip=="salariat"){
            std::cin>>temp_nume;
            std::cin>>temp_departament;
            std::cin>>temp_norma;
            std::cin>>temp_vechime;
            std::cin>>temp_salariu_net;
            *(a+i)=new Salariat(temp_nume, temp_departament, tip, temp_norma, temp_vechime, temp_salariu_net);
        }
        else
            if(tip=="colaborator"){
                std::cin>>temp_nume;
                std::cin>>temp_departament;
                std::cin>>temp_onorariu;
                std::cin>>temp_nr_prestari_anuale;
                *(a+i)=new Colaborator(temp_nume, temp_departament, tip, temp_onorariu, temp_nr_prestari_anuale);
            }
    }
    int test;
    std::cin>>test;
    if(test==1){
        std::cin>>temp_departament;
        for(int i=0; i<n; i++){
            if(temp_departament==(*(a+i))->get_departament())
                (*(a+i))->afisare();
        }
    }
    if(test==2){
        std::cin>>temp_nume;
        for(int i=0;i<n;i++)
            if((*(a+i))->get_nume()==temp_nume)
                if((*(a+i))->get_departament()=="IT")
                    std::cout<<std::fixed<<std::setprecision(2)<<((*(a+i))->salariu_anual())/(1-0.35);
                else
                    std::cout<<std::fixed<<std::setprecision(2)<<((*(a+i))->salariu_anual())/(1-0.45);
                
    }
    if(test==3){
        
        float R1,R2,Max=0;
        std::string angajat_rentabil;

        for(int i=0;i<n;i++){
            if((*(a+i))->get_tip()=="salariat")
                if((*(a+i))->get_departament()=="IT"){
                    R1=((*(a+i))->rentabilitate_angajat())/(1-0.35);
                    if(Max<R1){
                        Max=R1;
                        angajat_rentabil=(*(a+i))->get_nume();
                        
                    }
                }
                else{
                    R2=((*(a+i))->rentabilitate_angajat())/(1-0.45);
                    if(Max<R2){
                        Max=R2;
                        angajat_rentabil=(*(a+i))->get_nume();
                    }
                }
        }
        std::cout<<angajat_rentabil<<std::endl;
    }
    if(test==4){
        int s=0;
        std::cin>>temp_departament;
        for(int i=0; i<n; i++)
            if((*(a+i))->get_departament()==temp_departament)
                if((*(a+i))->get_departament()=="IT")
                    s=s+((*(a+i))->salariu_anual())/(1-0.35);
                else
                    s=s+((*(a+i))->salariu_anual())/(1-0.45);
        std::cout<<s*1.0/2<<std::endl;       
    }
}
