#ifndef DEEPPTR_H
#define DEEPPTR_H

template <class T>

class DeepPtr{

private:

    T* pointer;

public:

    //Costruttore
    DeepPtr(T*);
    DeepPtr(const T*);

    //Costruttore di copia
    DeepPtr(const DeepPtr&);

    //Distruttore
    virtual ~DeepPtr();

    //Operatore di assegnazione
    DeepPtr& operator=(const DeepPtr&);

    //Operatore di deferenziazione
    const T& operator*() const;
    T& operator*();

    //Operatore freccia
    const T* operator->() const;
    T* operator->();

    //Operatori uguale e diverso
    bool operator==(const DeepPtr&) const;
    bool operator!=(const DeepPtr&) const;
};

//Implementazione

//Costruttore
//Forma contratta di if(p) return p->clone(); else return nullptr;
//p->clone() assicura che T* p è stato creato con new e non sarà chiamato delete su di esso
//Il chiamante deve assicurare solo che p sia valido o nullo.
template <class T>
DeepPtr<T>::DeepPtr(T* p) : pointer(p ? p->clone() : nullptr){ }

template <class T>
DeepPtr<T>::DeepPtr(const T* p) : DeepPtr(const_cast<T *>(p)) { }

//Costruttore di copia
//Forma contratta di if(dp.pointer) return dp->clone(); else return nullptr;
//Viene effettuata la copia profonda assegnando a pointer dp.pointer->clone() nel caso dp.pointer sia valido.
template <class T>
DeepPtr<T>::DeepPtr(const DeepPtr& dp) : pointer(dp.pointer ? dp.pointer->clone() : nullptr){ }

//Distruttore
//Elimina profondamente oggetti DeepPtr mediante l'eliminazione dell'oggetto puntato da pointer.
template <class T>
DeepPtr<T>::~DeepPtr(){
    delete pointer;
}

//Operatore di assegnazione
//Controlla che non si stia assegnando un oggetto DeepPtr a sè stesso:
//in tal caso elimina l'oggetto puntato da pointer (per pulire profondamente e non lasciare un oggetto T in memoria)
//e fa puntare pointer a dp->clone() se valido.
//Ritorna la dereferenziazione di this (*this).
template <class T>
DeepPtr<T>& DeepPtr<T>::operator=(const DeepPtr& dp){

    if (*this != dp){

        delete pointer;
        pointer = dp.pointer ? dp.pointer->clone() : nullptr;

    }

  return *this;

}

//Operatore di dereferenziazione e def. const
//Viene ritornata una reference all'oggetto T.
//Questo perchè deepptr deve agire come un puntatore a T, dunque *deepptr deve comportarsi come *pointer.
template <class T>
const T& DeepPtr<T>::operator*() const{
  return *pointer;
}

template <class T>
T& DeepPtr<T>::operator*(){
  return *pointer;
}

//Operatore freccia e freccia const
//Viene ritornato il puntatore all'oggetto T.
//Questo perchè serve ottenere un comportamento del tipo pointer_a_T->attributo_metodo_di_T e
//deepptr deve comportarsi come un puntatore a T intelligente.
template <class T>
const T* DeepPtr<T>::operator->() const{
  return const_cast<const T* const>(pointer);
}

template <class T>
T* DeepPtr<T>::operator->(){
  return pointer;
}

//Operatore uguale
//Ritorna se i puntatori sono uguali.
template <class T>
bool DeepPtr<T>::operator==(const DeepPtr& dp) const{

  if(pointer == dp.pointer){

      return true;

  }else return false;

}

//Operatore diverso
//Ritorna se i puntatori sono diversi
template <class T>
bool DeepPtr<T>::operator!=(const DeepPtr& dp) const{
    if(pointer != dp.pointer){

        return true;

    }else return false;
}

#endif
