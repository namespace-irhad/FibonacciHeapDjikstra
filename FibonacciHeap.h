#ifndef FIBONACCIHEAP_H
#define FIBONACCIHEAP_H

#include <iostream>
#include <climits>
#include <cmath>
using namespace std;

template <class T>
class FCvor
{
public:
  T kljuc;
  int stepen;
  int labela;
  FCvor *roditelj;
  FCvor *dijete;
  FCvor *lijeviC;
  FCvor *desniC;
  bool oznaka;

  FCvor(T kljuc)
  {
    this->labela = -1;
    this->kljuc = kljuc;
    this->stepen = 0;
    this->roditelj = NULL;
    this->dijete = NULL;
    this->lijeviC = this;
    this->desniC = this;
    this->oznaka = false;
  }
  void unesiDesno(FCvor *cvor)
  {
    cvor->desniC = this->desniC;
    cvor->lijeviC = this;
    this->desniC->lijeviC = cvor;
    this->desniC = cvor;
  }
};

template <class T>
class FibonacciHeap
{
private:
  int velicina;
  int oznaka_velicina;
  FCvor<T> *min;
  FibonacciHeap *unija(FibonacciHeap *h1, FibonacciHeap *h2);
  void prilagodi();                        // Consolidate Stabla
  void poveziHeap(FCvor<T> *, FCvor<T> *); // Link

public:
  FibonacciHeap();
  ~FibonacciHeap();
  FCvor<T> *unesi(T n);
  FCvor<T> *unesi(T n, int labela);
  void izbrisi(T);          // Brisanje po vrijednosti
  void izbrisi(FCvor<T> *); // Brisanje po cvoru
  void pop();               // Brisanje min cvora

  // Funkcije za umanjenje kljuca
  void umanjiKljuc(FCvor<T> *, T);
  void cut(FCvor<T> *, FCvor<T> *);
  void cascadeCut(FCvor<T> *);

  // Funkcije za ispis
  void print();
  void printMin() { cout << "Min: " << this->min->kljuc << endl; }
  void printVelicina() { cout << "Velicina: " << this->velicina << endl; }
  int getVelicina() { return this->velicina; }
  T getMin() { return this->min->kljuc; }

  // Ostalo
  FibonacciHeap<T> operator+(FibonacciHeap h2) { return *this->unija(this, &h2); }
};

#endif // FIBONACCIHEAP_H
