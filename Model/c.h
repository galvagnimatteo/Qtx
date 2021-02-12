#ifndef C_H
#define C_H

template <class T>

class C {

private:

    class node{

    public:

        T info;
        node* next;
        node* previous;

        node(const T& t, node* n = 0, node* p = 0) : info(t), next(n), previous(p){ } //next di default a 0

    };

    node* list_begin;
    node* list_end;

    static void destroy(node* n){

        if (n != nullptr) {
            destroy(n->next);
            delete n;
        }

    }

    static void copy(node* list_to_copy, node*& first_node, node*& last_node) {

        if (list_to_copy){ //Se la lista non è nullptr, il primo e l'ultimo nodo puntano al primo e unico nodo della lista, creato con l'info di list_to_copy

            first_node = last_node = new node(list_to_copy->info);

            node* list_to_copy_scrollable = list_to_copy->next; //Creata una lista scorribile per non modificare il suo puntatore originale

            //Finchè la lista scorrevole non è nulla, viene aggiunto un nuovo nodo in coda, puntato da last_node, che avrà come previous il vecchio valore di last_node.
            //Una volta creato si risale al nodo precedente (vecchio last_node) e viene fatto puntare next al nuovo last_node.
            //Si prosegue scorrendo la lista.
            while(list_to_copy_scrollable){

                last_node = new node(list_to_copy_scrollable->info, nullptr, last_node);
                last_node->previous->next = last_node;
                list_to_copy_scrollable = list_to_copy_scrollable->next;

            }


        }else{ //Lista nulla

            first_node = last_node = nullptr;

        }
    }

public:

    C();
    C(const C&); //Costruttore di copia
    ~C(); //Distruttore
    C& operator=(const C&); //Operatore di assegnazione

    void append(const T&);
    void appendFront(const T&);
    bool remove(int); //true se riesce, false se no

    class const_iterator{

        friend class C<T>;

    private:

        const_iterator(node* n, bool end = false): list(n), is_past_end(end){ } //Costruttore utile alla creazione di const_iterator con un puntatore a nodo assegnato
                                                                                //Privato perchè chiede nodo* che è annidato (privato) in C

        const node* list; //Lista che itera, const
        bool is_past_end; //Flag che indica se l'iteratore è andato oltre la lunghezza della lista.

    public:

        const_iterator(); //Costruttore

        const_iterator& operator++(); //Operator++ prefisso
        const_iterator operator++(int); //Operator++ postfisso
        const_iterator& operator--(); //Operator-- prefisso
        const_iterator operator--(int); //Operator-- postfisso
        bool operator==(const const_iterator& it) const; //Operator==
        bool operator!=(const const_iterator& cit) const; //Operator!=
        const T& operator*() const; //Operator*
        const T* operator->() const; //Operator&

    };

    class iterator{

        friend class C<T>;

    private:

        iterator(node* n, bool end = false): list(n), is_past_end(end){ } //Costruttore utile alla creazione di iterator con un puntatore a nodo assegnato
                                                                          //Privato perchè chiede nodo* che è annidato (privato) in C

        node* list; //Lista che itera, const
        bool is_past_end; //Flag che indica se l'iteratore è andato oltre la lunghezza della lista.

    public:

        iterator(); //Costruttore

        iterator& operator++(); //Operator++ prefisso
        iterator operator++(int); //Operator++ postfisso
        iterator& operator--(); //Operator-- prefisso
        iterator operator--(int); //Operator-- postfisso
        bool operator==(const iterator& it) const; //Operator==
        bool operator!=(const iterator& cit) const; //Operator!=
        T& operator*() const; //Operator*
        T* operator->() const; //Operator&

    };

    const_iterator begin() const;
    const_iterator end() const;
    iterator begin();
    iterator end();

};

//Implementazione

template <class T>
//Costruttore di copia (profonda)
C<T>::C():list_begin(nullptr), list_end(nullptr){ }

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
void C<T>::append(const T& in) {

    if(list_end){ //Se la lista non è vuota viene creato un nuovo nodo, fatto puntare da list_end, e fatto puntare dal precedente nodo (vecchio list_end).

        list_end = new node(in, nullptr, list_end);
        (list_end->previous)->next = list_end;

    }else{ //Se la lista è vuota, list_end e list_begin coincidono e puntano al nuovo nodo aggiunto

        list_begin = list_end = new node(in);

    }

}

template <class T>
//Inserimento all'inizio della lista
void C<T>::appendFront(const T& in) {

    list_begin = new node(in, list_begin, nullptr); //Nuovo nodo con next = list_begin

    if(list_begin->next == nullptr){ //Se, oltre il nuovo nodo appena creato e assegnato a list_begin, la lista è vuota, list_end coincide con l'unico nodo presente (list_begin)

        list_end = list_begin;

    }else{ //Se invece ci sono altri nodi, viene collegato il primo nodo oltre a list_begin a list_begin.

        (list_begin->next)->previous = list_begin;

    }

}

template <class T>
bool C<T>::remove(int index){

    if(list_begin == nullptr || index < 0) return false; //se lista vuota o index negativo ritorno false.

    node* current = list_begin;

    for (int i = 0; current != nullptr && i < index; i++){

        current = current->next;

    }

    if (current == nullptr) return false; //Se è uscito dal for per current != nullptr falso e non per i<index falso allora index è maggiore della lunghezza della lista

    if (list_begin == current){ //Se current è il nodo in testa alla lista (dunque non ha previous), allora list_begin punta al nodo successivo.

        list_begin = current->next;

    }

    if (current->next != nullptr){ //Se next non è nullptr (ovvero current NON è l'ultimo nodo della lista), allora collego il nodo successivo a current a quello precedente

        current->next->previous = current->previous;

    }

    if (current->previous != nullptr){ //Se current NON è il primo nodo della lista, allora collego il nodo precedente a current al successivo.

        current->previous->next = current->next;

    }

    if(current == list_end){ //Infine, se current è l'ultimo nodo, allora list_end punta al nodo precedente.

        list_end = current->previous;

    }

    delete current;

    return true;

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

#endif
