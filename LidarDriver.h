#include <iostream>
#include <vector>

using namespace std;
class LidarDriver
{
    private:
    double risoluzione;
    int const buffer_dim = 4;
    vector<double> buffer; //181 * buffer
    
    int scan_index; // numero di scan attuale a cui siamo arrivati
    
    double* mobile; //puntatore mobile
    double* inizio_scansione; //puntatore che punta al primo elemento dell'ultima scansione
    double* eliminatore; //mi serve per tenere traccia di cosa sto eliminando
    
    double* pbi; //puntatore alla prima posizione del buffer
    double* pbf; //puntatore alla prima posizione dopo il buffer
    
    int size;
    
    public:
    
    //costruttori
    LidarDriver (double risoluzione_x); //costruttore completo che DEVE essere usato
    LidarDriver (); //risoluzione = 1  buffer_dim = 0  LANCIARE UN ECCEZIONE
    
    //distruttore
    ~LidarDriver();
    
    // funzioni di modifica
    void new_scan (vector<double> scansione); //analisi di completezza
    void clear_buffer(); //pulizia della storia
    
    //funzioni di interfaccia
    vector<double> get_scan(); //prende ed elimina la scansione piu vecchia
    double get_distance (double gradi);
    
    //per debug
    void get_memory();

    //funzione helper (per << overloading)
    string get_risultato();
};

ostream& operator<<(std::ostream& os, LidarDriver& x);
