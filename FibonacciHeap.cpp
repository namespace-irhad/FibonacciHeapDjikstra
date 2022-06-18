#include "FibonacciHeap.h"

template <class T>
FibonacciHeap<T>::FibonacciHeap()
{
  velicina = 0;
  min = NULL;
  oznaka_velicina = 0;
}

template <class T>
FibonacciHeap<T>::~FibonacciHeap()
{
  // while (velicina)
  //   pop();
  return;
}

template <class T>
FibonacciHeap<T> *FibonacciHeap<T>::unija(FibonacciHeap *h1, FibonacciHeap *h2)
{
  // Kreiranje novog heap-a
  FibonacciHeap *h = new FibonacciHeap();

  h->min = h1->min;
  // Povezivanje liste korijena od h2 na listu korijena h
  if (h->min != NULL && h2->min != NULL)
  {
    h->min->desniC->lijeviC = h2->min->lijeviC;
    h2->min->lijeviC->desniC = h->min->desniC;
    h->min->desniC = h2->min;
    h2->min->lijeviC = h->min;
  }
  if (h1->min == NULL || (h2->min != NULL && h2->min->kljuc < h1->min->kljuc))
  {
    h->min = h2->min;
  }
  h->velicina = h1->velicina + h2->velicina;
  h->oznaka_velicina = h1->oznaka_velicina + h2->oznaka_velicina;

  // Brisanje heap-ova (nije potrebno)
  // delete h1;
  // delete h2;

  return h;
}

template <class T>
FCvor<T> *FibonacciHeap<T>::unesi(T kljuc)
{
  // Novi cvor sa pocetnim vrijednostima i kljucem kljuc
  FCvor<T> *noviCvor = new FCvor<T>(kljuc);
  if (min == NULL)
  {
    // Pocetni heap je prazan
    min = noviCvor->lijeviC = noviCvor->desniC = noviCvor;
    velicina++;
    return noviCvor;
  }
  // Dodavanje u listu korijena (konstatno dodavanje)
  min->unesiDesno(noviCvor);
  if (noviCvor->kljuc < min->kljuc)
    min = noviCvor;

  velicina++;
  return noviCvor;
}

template <class T>
void FibonacciHeap<T>::izbrisi(T kljuc)
{
  FCvor<T> *cvor = min;
  // Pretrazivanje po vrijednosti i brisanje ukoliko se nadje
  while (cvor != NULL)
  {
    if (cvor->kljuc == kljuc)
    {
      if (cvor == min)
        min = cvor->desniC;

      cvor->lijeviC->desniC = cvor->desniC;
      cvor->desniC->lijeviC = cvor->lijeviC;
      velicina--;
      break;
    }
    cvor = cvor->desniC;
  }
}

template <class T>
void FibonacciHeap<T>::izbrisi(FCvor<T> *cvor)
{
  // MIN vrijednost zavisi od tipa
  umanjiKljuc(cvor, INT_MIN);
  pop();
}

template <class T>
void FibonacciHeap<T>::cut(FCvor<T> *x, FCvor<T> *y)
{
  if (x == NULL || y == NULL)
  {
    return;
  }
  // 1) Ukloni x iz liste dijece y
  if (x->desniC == x)
  {
    y->dijete = NULL;
  }
  else
  {
    x->desniC->lijeviC = x->lijeviC;
    x->lijeviC->desniC = x->desniC;
    if (y->dijete == x)
    {
      y->dijete = x->desniC;
    }
  }
  y->stepen--;
  // 2) Dodaj x u listu cvorova min
  min->unesiDesno(x);
  // 3) Postavi x->roditelj = NULL
  x->roditelj = NULL;
  // 4) Postavi x->oznaka = false
  x->oznaka = false;
  oznaka_velicina--;
}

template <class T>
void FibonacciHeap<T>::cascadeCut(FCvor<T> *cvor)
{
  if (cvor == NULL)
    return;

  // 1) Postaviti cvorRoditelj da je roditelj cvora iz parametra
  FCvor<T> *cvorRoditelj = cvor->roditelj;
  // 2) Ako cvorRoditelj != NULL i cvorRoditelj->oznaka == false, postavi da je oznacen
  if (cvorRoditelj != NULL)
  {
    if (!cvor->oznaka)
    {
      cvor->oznaka = true;
      oznaka_velicina++;
    }
    else
    {
      // 3) Ako je cvor oznacen vrsimo kaskadno brisanje kao sto je navedeno u radu
      cut(cvor, cvorRoditelj);
      cascadeCut(cvorRoditelj);
    }
  }
}

template <class T>
void FibonacciHeap<T>::umanjiKljuc(FCvor<T> *cvor, T noviKljuc)
{
  if (cvor == NULL || noviKljuc > cvor->kljuc)
    return;

  // Postavljanje nove vrijednosti za cvor i ukoliko je manji vrsi se pomjeranje i kaskadno brisanje ukoliko je roditelj oznacen
  cvor->kljuc = noviKljuc;
  FCvor<T> *cvorRoditelj = cvor->roditelj;
  if (cvorRoditelj != NULL && cvor->kljuc < cvorRoditelj->kljuc)
  {
    cut(cvor, cvorRoditelj);
    cascadeCut(cvorRoditelj);
  }
  if (cvor->kljuc < min->kljuc)
    min = cvor;
}

// Povezivanje heap-a sa istim stepenom
template <class T>
void FibonacciHeap<T>::poveziHeap(FCvor<T> *x, FCvor<T> *y)
{
  // Izbaci x iz liste korijena heap-a
  x->lijeviC->desniC = x->desniC;
  x->desniC->lijeviC = x->lijeviC;
  // Ukoliko je jedini u listi korijena
  if (y->desniC == y)
    min = y;
  // Dodaj y kao dijete x, povecati stepen
  x->lijeviC = x;
  x->desniC = x;
  x->roditelj = y;
  if (y->dijete == NULL)
    y->dijete = x;
  x->desniC = y->dijete;
  x->lijeviC = (y->dijete)->lijeviC;
  (y->dijete->lijeviC)->desniC = x;
  y->dijete->lijeviC = x;
  if (x->kljuc < y->dijete->kljuc)
    y->dijete = x;
  y->stepen++;

  y->oznaka = false;
}
// O(logn)
template <class T>
void FibonacciHeap<T>::prilagodi()
{
  // Pravljenje liste korijena velicine maksimalnog stepena i postavljamo sve vrijednosti na NULL
  // float maxStepen = (log(velicina)) / (log(2));
  int maxStepen = floor(log(double(velicina)) / log(double(1 + sqrt(double(5))) / 2)); // ili velicina ?
  FCvor<T> **A = new FCvor<T> *[maxStepen + 1];
  for (int i = 0; i <= maxStepen; i++)
    A[i] = NULL;

  int currStepen;
  FCvor<T> *trenutni = min;
  FCvor<T> *sljedeci = trenutni;
  // Za svaki cvor u listi korijena preuzimamo i povezujemo sa cvorom iz A ukoliko ima isti istepen
  do
  {
    sljedeci = sljedeci->desniC;
    currStepen = trenutni->stepen;
    while (A[currStepen] != NULL)
    {
      FCvor<T> *y = A[currStepen];
      // Roditelj treba imati manji kljuc od cvora y
      if (trenutni->kljuc > y->kljuc)
      {
        // Zamijeni cvorove
        FCvor<T> *temp = trenutni;
        trenutni = y;
        y = temp;
      }
      if (y == min)
        min = trenutni;
      // cout << "Povezivanje: " << trenutni->kljuc << " i " << y->kljuc << endl;
      poveziHeap(y, trenutni);
      if (trenutni->desniC == trenutni)
        min = trenutni;
      A[currStepen] = NULL;
      currStepen = currStepen + 1;
    }
    // Postavljamo cvor u listu korijena
    A[currStepen] = trenutni;
    trenutni = trenutni->desniC;
  } while (trenutni != min);

  // Nakon povezivanja heap-a sa istim stepenom, ponovo postavi min
  min = NULL;
  for (int j = 0; j <= maxStepen; j++)
  {
    // Prolaz kroz sve cvorove u listi korijena i poredjenje kljuca
    if (A[j] != NULL)
    {
      A[j]->lijeviC = A[j];
      A[j]->desniC = A[j];
      if (min != NULL)
      {
        (min->lijeviC)->desniC = A[j];
        A[j]->desniC = min;
        A[j]->lijeviC = min->lijeviC;
        min->lijeviC = A[j];
        if (A[j]->kljuc < min->kljuc)
          min = A[j];
      }
      else
        min = A[j];
      if (min == NULL)
        min = A[j];
      else if (A[j]->kljuc < min->kljuc)
        min = A[j];
    }
  }
  delete[] A;
}

template <class T>
void FibonacciHeap<T>::pop()
{
  if (min == NULL)
    return;

  FCvor<T> *currMin = min;
  FCvor<T> *sljedeci = currMin;
  FCvor<T> *temp;
  FCvor<T> *x = NULL;
  if (currMin->dijete != NULL)
    x = currMin->dijete;
  if (x != NULL)
  {
    // Prolazimo kroz dijecu cvora min
    sljedeci = x;
    do
    {
      temp = x->desniC;
      // Postavi dijete u listu korijena (nalazi se sa desne strane minimuma)
      min->lijeviC->desniC = x;
      x->desniC = min;
      x->lijeviC = min->lijeviC;
      min->lijeviC = x;
      // Provjeri jel kljuc cvora manji
      if (x->kljuc < min->kljuc)
        min = x;
      // Ukloni roditelja jer je izbacen minimum
      x->roditelj = NULL;
      x = temp;
    } while (temp != sljedeci);
  }

  // Brisanje minimuma iz liste korijena
  currMin->lijeviC->desniC = currMin->desniC;
  currMin->desniC->lijeviC = currMin->lijeviC;
  min = currMin->desniC;
  // Ukoliko je lista prazna, min je NULL
  if (currMin == currMin->desniC && currMin->dijete == NULL)
    min = NULL;
  else
  {
    // Ukoliko nije vrsi se prilagodjavanje heap-a i pronalazi se novi minimum
    min = currMin->desniC;
    prilagodi();
  }
  velicina--;
}

// Print funckije (printanje liste korijena)
template <class T>
void FibonacciHeap<T>::print()
{
  FCvor<T> *trenutni = min;
  if (trenutni == NULL)
    return;

  while (trenutni != NULL)
  {
    cout << trenutni->kljuc << " -> ";
    trenutni = trenutni->desniC;

    if (trenutni == min)
      break;
  }
  cout << endl;
}
// Samo za Dijkstrin algoritam
template <class T>
FCvor<T> *FibonacciHeap<T>::unesi(T n, int labela)
{
  FCvor<T> *noviCvor = new FCvor<T>(n);
  noviCvor->labela = labela;
  if (min == NULL)
  {
    // Pocetni heap je prazan
    min = noviCvor->lijeviC = noviCvor->desniC = noviCvor;
    velicina++;
    return noviCvor;
  }
  // Dodavanje u listu korijena (konstantno dodavanje)
  min->unesiDesno(noviCvor);
  if (noviCvor->kljuc < min->kljuc)
    min = noviCvor;

  velicina++;
  return noviCvor;
}
