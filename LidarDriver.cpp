#include "LidarDriver.h"
#include <iostream>
#include <vector>
#include <iomanip>
#include <stdexcept>

using namespace std;

LidarDriver::LidarDriver (double risoluzione_x, double buffer_x)
{
    risoluzione = risoluzione_x;                //informazioni scelte
    buffer_dim = buffer_x;                      //prima dell'esecuzione del programma
    
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
    buffer_dim = 0;
    
    scan_index = 0;
    
    pbi = nullptr;
    mobile = pbi; //puntatore mobile parte che coincide con pbi
    eliminatore = pbi;
    inizio_scansione = pbi;
    
    pbf = nullptr;
    
    //nessun dato passato come parametro al costruttore -> lancio un'eccezione
    throw invalid_argument("Non sono stati forniti ne risoluzione ne dimensione del buffer");
}

LidarDriver::~LidarDriver()
{
    delete[] pbi;
    pbi = nullptr;
}

void LidarDriver::new_scan(vector<double> scansione)
{
    scan_index++; //salvando una nuova scansione --> scan_index aumenta
    
    if (mobile >= pbf)//condizione di esaurimento dello spazio nel buffer --> ritorno all'inizio del buffer
            mobile = pbi;
    
    inizio_scansione = mobile;
    
    bool slitto = false;
    if (mobile == eliminatore && scan_index!=1) 
            slitto = true; //se siamo al primo giro non deve slittare tutto perche la prima scansione inserita coincide con con la prima allínterno della memoria
    /*
      sovrascrivendo i dati la prima scansione inserita, se non ho chiamato già get_scan, coincide con la sezione di memoria successiva al puntatore mobile
      se ho già chiamato get_scan() allora la memoria successiva al puntatore che inserisce è ancora vuota ed eliminatore punta alla sezione successiva 
      --> non viene slittato se viene chiamato new_scan() perchè non vale la condizione mobile==eliminatore (mobile si trova più indietro di eliminatore)
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
    //non ha senso settare tutte le locazioni a 0 perchè l'output sarà lo stesso ma la complessità è O(n) rispetto a O(1)
    scan_index = 0;
    mobile = pbi;
    eliminatore = pbi;
}

vector<double> LidarDriver::get_scan()
{
    vector<double> risultato; //vettore in cui vado a salvare i dati
    
    //i due metodi fanno la medesima cosa
    //erano stati scritti eper funzionare nella struttura precedente del programma
    if (scan_index > buffer_dim) //meno recente è nella sezione di memoria dopo l'inizio del buffer complessivo (essendo la prima sezione già sovrascritta)
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
    //eccezione lanciata in caso di mancati dati presenti nel buffer complessivo
    if (scan_index==0) throw invalid_argument("Impossibile eseguire il metodo per mancanza di scansioni salvate in memoria");
    int posizione = gradi/risoluzione;
    double risultato = *(inizio_scansione + posizione);
    return risultato;
}




//------------------------------------------------------------------------
//metodi usati per il debug

//restituisce la stringa usata come output per sovrascrivere lóperatore <<
string LidarDriver::get_risultato()
{
    string risultato = "";
    for (int i =0; i<size; i++)
    {
        string app = to_string(*(inizio_scansione + i));
        risultato += app + " ";
    }
    return risultato;
}

//non restituisce nulla, stampa solo TUTTA la memoria del programma in output.
void LidarDriver::get_memory()
{
    for (int i =0; i<size*buffer_dim; i++) cout<<*(pbi+i)<<" ";
    cout << endl;
}

//restituisc la locazione in memoria a cui puntano i puntatori
void LidarDriver::get_puntatori()
{
    cout<<"mobile = " << mobile << endl;
    cout<<"pbf = " << pbf << endl;
}

//overload dellóperatore <<
ostream& operator<<(std::ostream& os, LidarDriver& x)
{
    os << x.get_risultato();
    return os;
}

