#include "LidarDriver.h"
#include <iostream>
#include <vector>
#include <iomanip>

#include <stdexcept>

using namespace std;

LidarDriver::LidarDriver (double risoluzione_x)
{
    risoluzione = risoluzione_x;                //informazioni scelte 
    size = 180/risoluzione+1; //taglia di informazioni che ricevo in base alla risoluzione
    
    scan_index = 0;
    
    //inizializzo i puntatori della memoria
    pbi = new double [size * buffer_dim]; //moltiplicando la taglia delle informazioni che ricevo per buffer non ho buchi in memoria
    mobile = pbi; //puntatore mobile che coincide con pbi
    eliminatore = pbi; //punta all'inizio del vettore in quanto primo dato da eliminare
    inizio_scansione = pbi;
    
    pbf = pbi + (size * buffer_dim); //cast per evitare problemi con indirizzi di memoria salvati come double
}

LidarDriver::LidarDriver()
{
    //setto le variabili di stato a valori predefiniti
    risoluzione = 1;
    
    scan_index = 0;
    
    pbi = nullptr;
    mobile = pbi; //puntatore mobile parte che coincide con pbi
    eliminatore = pbi;
    inizio_scansione = pbi;
    
    pbf = nullptr;
    cout<<"\nNessuna risoluzione angolare fornita, sara' settata ad 1 di default\n";
}

LidarDriver::~LidarDriver()
{
    delete[] pbi;
    pbi = nullptr;
}

void LidarDriver::new_scan(vector<double> scansione)
{
    scan_index++; //salvando una nuova scansione --> scan_index aumenta
    
    //int taglia = scansione.size(); --> numero di letture effettive
    
    if (mobile >= pbf) //condizione di esaurimento dello spazio nel buffer --> ritorno all'inizio del buffer
        mobile = pbi;
    
    inizio_scansione = mobile;
    
    bool slitto = false;
    if (mobile == eliminatore && scan_index!=1) slitto = true; //se siamo al primo giro non deve slittare tutto perche la prima scansione inserita coincide con con la prima allínterno della memoria
    /*sovrascrivendo i dati la prima scansione inserita, se non ho chiamato già get_scan, coincide con la sezione di memoria successiva al puntatore mobile
      se ho già chiamato get_scan allora la memoria successiva al puntatore che inserisce è ancora vuota ed eliminatore punta alla sezione successiva 
      --> non viene slittato se viene chiamato new_scan perche non vale la condizione mobile==eliminatore (mobile si trova più indietro di eliminatore)
    */
    
    for (int i = 0; i<size; i++)
    {
        if (i<scansione.size()) //salvataggio dati dal vettore delle letture nel buffer corrispondente
        {
            *mobile = scansione[i];
            mobile++;
        }
        else //caso salvataggio vettore conclusa ma numero di letture non massime (< size) --> inizializziamo con 0 le rimanenti 
        {
            *mobile = 0;
            mobile++;
        }
    }

    //slitto permette all'eliminatore di restare al passo con mobile quando ricomincia il giro
    //(manca da implementare la capacità di slitto di ripartire da capo nella memoria dopo aver raggiunto pbf)
    if (slitto) eliminatore = mobile; //si riuniscono
    //in questo modo se adesso chiamo get_scan e capace di darmi lúltima sezione dimemoria aggiornata alle ultime modifiche.
}

void LidarDriver::clear_buffer() //devo cancellare tutte le informazioni in memoria
{
    //basta azzerare tutti i puntatori, il programma non avrà più modo di accedere a queste informazioni
    scan_index = 0;
    mobile = pbi;
    eliminatore = pbi;
}

vector<double> LidarDriver::get_scan()
{
    vector<double> risultato; //vettore in cui vado a salvare i dati
    
    if (scan_index > buffer_dim) //il piu vecchio si trova dopo
    {
        double* p = eliminatore;
        
        for (int i = 0; i < size; i++)
        {
            risultato.push_back(*p);
            p++;
        }
    }
    else
    {
        double* p = eliminatore;
        
        for (int i = 0; i < size; i++)
        {
            risultato.push_back(*p);
            p++;
        }
    }

    //eliminazione dell'informazione
    for (int i = 0; i < size; i++)
    {
        *eliminatore = 0; //sovrascrivo a 0 la lettura i-esima del buffer relativo
        eliminatore++; //incremento per puntare alla locazione successiva
    }
    if (eliminatore == pbf) eliminatore = pbi; //eliminazione dell'ultima sezione di memoria comporta che la meno recente sia la prima nel buffer complessivo
            
    return risultato;
}

double LidarDriver::get_distance(double gradi)
{
    if(scan_index != 0) {
        int posizione = gradi/risoluzione;
        double risultato = *(inizio_scansione + posizione);
        return risultato;
    }
    else{
        cout<<"Impossibile eseguire il metodo per mancanza di scansioni salvate in memoria --> ";
        return 0;
    }
}


//overload dell'operatore <<
ostream& operator<<(std::ostream& os, LidarDriver& x)
{
    os << x.get_risultato();
    return os;
}

//funzione helper --> restituisce la stringa usata come output per l'overloading di <<
string LidarDriver::get_risultato()
{
    string risultato = "";
    string app;
    for (int i =0; i<size; i++)
    {
        app = to_string(*(inizio_scansione + i));
        risultato += app + " ";
    }
    return risultato;
}
