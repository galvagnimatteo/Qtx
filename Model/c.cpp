#include "c.h"

template <class T>
//Costruttore di copia (profonda)
C<T>::C(const C& c){

    copy(c.list_begin, this->list_begin, this->list_end);

}

template <class T>
//Distruzione (profonda)
C<T>::~C(){

    destroy(list_begin);

}

template <class T>
//Assegnazione (profonda)
C<T>& C<T>::operator=(const C& list_to_assign) {

    if(this != &list_to_assign) {

        destroy(list_begin); //Libero lo spazio precedentemente occupato dalla lista
        copy(list_to_assign.list_begin, this->list_begin, this->append(list_end)); //Copio profondamente la lista

    }

    return *this;
    //Ritorno una reference a questo oggetto sia se non è stato fatto nulla (non assegno list_to_assign a questa lista se sono la stessa lista) sia se è stata assegnata.
}

template <class T>
//Inserimento in coda
void C<T>::append(const T& info) {

    if(list_end){ //Se la lista non è vuota viene creato un nuovo nodo, fatto puntare da list_end, e fatto puntare dal precedente nodo (vecchio list_end).

        list_end = new node(info, list_end, nullptr);
        list_end->previous->next = list_end;

    }else{ //Se la lista è vuota, list_end e list_begin coincidono e puntano al nuovo nodo aggiunto

        list_begin = list_end = new node(info);

    }
}

template<class T>
int C<T>::size(){

    int counter = 0;

    node* list_scrollable = list_begin;

    while(list_scrollable){

        counter++;

    }

    return counter;

}

template <class T>
C<T>::const_iterator::const_iterator(): list(nullptr), is_past_end(false){ }

template <class T>
//Incremento prefisso
typename C<T>::const_iterator& C<T>::const_iterator::operator++(){

    if(list != nullptr){ //Se lista non vuota controllo che l'iteratore non sia già oltre la lunghezza della lista.

        if(!is_past_end){

            if(list->next != nullptr){ //Se non lo è, controllo di non essere nell'ultimo nodo e avanzo il puntatore

                list = list->next;

            }else{ //Se invece sono nell'ultimo nodo, faccio puntare la lista all'indirizzo logico successivo e cambio la flag in true.

                list = list + 1;
                is_past_end = true;

            }

        }

    }

    return *this;

}

template <class T>
//Incremento postfisso
typename C<T>::const_iterator C<T>::const_iterator::operator++(int){

    const_iterator not_incremented(*this); //Creo un iteratore da non incrementare

    if(list != nullptr){ //Se lista non vuota controllo che l'iteratore non sia già oltre la lunghezza della lista.

        if(!is_past_end){

            if(list->next != nullptr){ //Se non lo è, controllo di non essere nell'ultimo nodo e avanzo il puntatore

                list = list->next;

            }else{ //Se invece sono nell'ultimo nodo, faccio puntare la lista all'indirizzo logico successivo e cambio la flag in true.

                list = list + 1;
                is_past_end = true;

            }
        }
    }

    return not_incremented; //Ritorno l'iteratore non incrementato

}

template <class T>
//Decremento prefisso
typename C<T>::const_iterator& C<T>::const_iterator::operator--(){

    if(list != nullptr){ //Se la lista non è vuota vengono distinti 3 casi:

        if(list->previous == nullptr){ //Se previous è nullptr sono al primo nodo, la lista viene fatta puntare a nullptr.

            list = nullptr;

        }else if(!is_past_end){ //Se non siamo oltre la fine della lista, avviene il decremento "normale" (punto al nodo precedente).

            list = list->previous;

        }else{ //Nell'ultimo caso siamo oltre la fine della lista (is_past_end true) dunque viene decrementato list di uno e settato is_past_end a false.

            list = list-1;
            is_past_end = false;

        }

    }

    return *this;

}

template <class T>
//Decremento postfisso
typename C<T>::const_iterator C<T>::const_iterator::operator--(int){

    const_iterator not_decremented(*this);

    if(list != nullptr){ //Se la lista non è vuota vengono distinti 3 casi:

        if(list->previous == nullptr){ //Se previous è nullptr sono al primo nodo, la lista viene fatta puntare a nullptr.

            list = nullptr;

        }else if(!is_past_end){ //Se non siamo oltre la fine della lista, avviene il decremento "normale" (punto al nodo precedente).

            list = list->previous;

        }else{ //Nell'ultimo caso siamo oltre la fine della lista (is_past_end true) dunque viene decrementato list di uno e settato is_past_end a false.

            list = list-1;
            is_past_end = false;

        }

    }

    return not_decremented; //Similmente all'incremento postfisso, viene ritornato l'iteratore non decrementato

}

template <class T>
bool C<T>::const_iterator::operator==(const const_iterator& iter) const{

    if(list == iter.list){

        return true;

    }else{

        return false;

    }

}

template <class T>
bool C<T>::const_iterator::operator!=(const const_iterator& iter) const{

    if(list != iter.list){

        return true;

    }else{

        return false;

    }

}

template <class T>
//Operator* deve ritornare una reference dell'informazione T contenuta in un nodo della lista.
const T& C<T>::const_iterator::operator*() const{

    return list->info;

}

template <class T>
//Operator-> deve restituire l'indirizzo dell'informazione.
const T* C<T>::const_iterator::operator->() const{

    return &(list->info); //Puntatore a T

}

template <class T>
typename C<T>::const_iterator C<T>::begin() const {

    return const_iterator(list_begin); //Viene ritornato un const_iterator, assegnandogli prima la lista che dovrà iterare che in begin() coincide col puntatore al primo nodo di C<T> (eventualmente nullptr)

}

template <class T>
typename C<T>::const_iterator C<T>::end() const {

    if(!list_end){ //Se list_end è nullo (non punta ad un nodo, lista vuota) viene ritornato un const_iterator con list = nullptr.

        return const_iterator();

    }else{ //Se invece è valido (lista con almeno un nodo) viene ritornato un const_iterator assegnandogli il puntatore successivo a list_end.

        return const_iterator(list_end + 1, true);

    }

}

//---------------------------------------iterator----------------------------------------------------------------

template <class T>
C<T>::iterator::iterator(): list(nullptr), is_past_end(false){ }

template <class T>
//Incremento prefisso
typename C<T>::iterator& C<T>::iterator::operator++(){

    if(list != nullptr){ //Se lista non vuota controllo che l'iteratore non sia già oltre la lunghezza della lista.

        if(!is_past_end){

            if(list->next != nullptr){ //Se non lo è, controllo di non essere nell'ultimo nodo e avanzo il puntatore

                list = list->next;

            }else{ //Se invece sono nell'ultimo nodo, faccio puntare la lista all'indirizzo logico successivo e cambio la flag in true.

                list = list + 1;
                is_past_end = true;

            }

        }

    }

    return *this;

}

template <class T>
//Incremento postfisso
typename C<T>::iterator C<T>::iterator::operator++(int){

    iterator not_incremented(*this); //Creo un iteratore da non incrementare

    if(list != nullptr){ //Se lista non vuota controllo che l'iteratore non sia già oltre la lunghezza della lista.

        if(!is_past_end){

            if(list->next != nullptr){ //Se non lo è, controllo di non essere nell'ultimo nodo e avanzo il puntatore

                list = list->next;

            }else{ //Se invece sono nell'ultimo nodo, faccio puntare la lista all'indirizzo logico successivo e cambio la flag in true.

                list = list + 1;
                is_past_end = true;

            }
        }
    }

    return not_incremented; //Ritorno l'iteratore non incrementato

}

template <class T>
//Decremento prefisso
typename C<T>::iterator& C<T>::iterator::operator--(){

    if(list != nullptr){ //Se la lista non è vuota vengono distinti 3 casi:

        if(list->previous == nullptr){ //Se previous è nullptr sono al primo nodo, la lista viene fatta puntare a nullptr.

            list = nullptr;

        }else if(!is_past_end){ //Se non siamo oltre la fine della lista, avviene il decremento "normale" (punto al nodo precedente).

            list = list->previous;

        }else{ //Nell'ultimo caso siamo oltre la fine della lista (is_past_end true) dunque viene decrementato list di uno e settato is_past_end a false.

            list = list-1;
            is_past_end = false;

        }

    }

    return *this;

}

template <class T>
//Decremento postfisso
typename C<T>::iterator C<T>::iterator::operator--(int){

    iterator not_decremented(*this);

    if(list != nullptr){ //Se la lista non è vuota vengono distinti 3 casi:

        if(list->previous == nullptr){ //Se previous è nullptr sono al primo nodo, la lista viene fatta puntare a nullptr.

            list = nullptr;

        }else if(!is_past_end){ //Se non siamo oltre la fine della lista, avviene il decremento "normale" (punto al nodo precedente).

            list = list->previous;

        }else{ //Nell'ultimo caso siamo oltre la fine della lista (is_past_end true) dunque viene decrementato list di uno e settato is_past_end a false.

            list = list-1;
            is_past_end = false;

        }

    }

    return not_decremented; //Similmente all'incremento postfisso, viene ritornato l'iteratore non decrementato

}

template <class T>
bool C<T>::iterator::operator==(const iterator& iter) const{

    if(list == iter.list){

        return true;

    }else{

        return false;

    }

}

template <class T>
bool C<T>::iterator::operator!=(const iterator& iter) const{

    if(list != iter.list){

        return true;

    }else{

        return false;

    }

}

template <class T>
//Operator* deve ritornare una reference dell'informazione T contenuta in un nodo della lista.
T& C<T>::iterator::operator*() const{

    return list->info;

}

template <class T>
//Operator-> deve restituire l'indirizzo dell'informazione.
T* C<T>::iterator::operator->() const{

    return &(list->info); //Puntatore a T

}

template <class T>
typename C<T>::iterator C<T>::begin(){

    return iterator(list_begin); //Viene ritornato un iterator, assegnandogli prima la lista che dovrà iterare che in begin() coincide col puntatore al primo nodo di C<T> (eventualmente nullptr)

}

template <class T>
typename C<T>::iterator C<T>::end(){

    if(!list_end){ //Se list_end è nullo (non punta ad un nodo, lista vuota) viene ritornato un iterator con list = nullptr.

        return iterator();

    }else{ //Se invece è valido (lista con almeno un nodo) viene ritornato un iterator assegnandogli il puntatore successivo a list_end.

        return iterator(list_end + 1, true);

    }

}























