#include "FibonacciHeap.h"
#include "FibonacciHeap.cpp"
#include <vector>

using namespace std;

// Samo za testiranje
void dijkstraFibonacci(vector<vector<int>> matrica, int start, int end)
{
  FibonacciHeap<int> heap;
  vector<int> distance(matrica.size(), INT_MAX);
  vector<int> parent(matrica.size(), -1);
  vector<bool> visited(matrica.size(), false);
  distance[start] = 0;
  heap.unesi(start, distance[start]);
  while (heap.getVelicina() != 0)
  {
    int u = heap.getMin();
    heap.pop();
    visited[u] = true;
    for (int i = 0; i < matrica.size(); i++)
    {
      if (matrica[u][i] != 0 && !visited[i])
      {
        if (distance[u] + matrica[u][i] < distance[i])
        {
          distance[i] = distance[u] + matrica[u][i];
          parent[i] = u;
          heap.unesi(i, distance[i]);
        }
      }
    }
  }
  cout << "Udaljenost od " << start << " do " << end << " je " << distance[end] << endl;
  cout << "Put je: ";
  int curr = end;
  while (curr != -1)
  {
    cout << curr << " ";
    curr = parent[curr];
  }
  cout << endl;
}

int main()
{
    /*
    FibonacciHeap<int> A;
    A.unesi(12);
    A.unesi(15);
    A.unesi(5);
    A.unesi(2);
    FCvor<int> *n = A.unesi(8);
    A.unesi(-10);
    A.print(); // -10 2 5 8 12 15

    A.umanjiKljuc(n, 1);
    A.printMin(); // -10
    A.print();    // -10 2 5 1 12 15
    A.pop();      // Izbaci -10
    A.printMin(); // Min je 1
    A.pop();      // Izbaci 1
    A.printMin(); // Min je 2
    A.pop();      // Izbaci 2
    A.printMin(); // Min je 5
    A.pop();      // Izbaci 5
    A.printMin(); // Min je 12
    FCvor<int> *n1 = A.unesi(100);
    A.unesi(20);
    A.printMin(); // Min je 12
    A.umanjiKljuc(n1, 1);
    A.printMin(); // Min je 1
    */
    /*
    FibonacciHeap<int> B;
    B.unesi(23);
    B.unesi(7);
    B.unesi(21);
    B.unesi(3);
    B.unesi(17);
    B.unesi(24);
    B.unesi(18);
    B.unesi(52);
    B.unesi(38);
    B.unesi(30);
    B.unesi(26);
    B.unesi(46);
    FCvor<int> *n = B.unesi(39);
    B.umanjiKljuc(n, 1);
    B.pop();
    B.printMin(); // Min je 3 (nakon izbacivanja 1)
    FibonacciHeap<int> C;
    C.unesi(-5);
    C.unesi(-10);
    C.unesi(-15);
    C.unesi(100);
    // Unija heapova D i C
    FibonacciHeap<int> D = B + C;
    D.printMin(); // Min je -15 iz Heapa C
    */


    vector<vector<int>> graph = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                               {4, 0, 8, 0, 0, 0, 0, 11, 0},
                               {0, 8, 0, 7, 0, 4, 0, 0, 2},
                               {0, 0, 7, 0, 9, 14, 0, 0, 0},
                               {0, 0, 0, 9, 0, 10, 0, 0, 0},
                               {0, 0, 4, 14, 10, 0, 2, 0, 0},
                               {0, 0, 0, 0, 0, 2, 0, 1, 6},
                               {8, 11, 0, 0, 0, 0, 1, 0, 7},
                               {0, 0, 2, 0, 0, 0, 6, 7, 0}};

    dijkstraFibonacci(graph, 0, 6);
    return 0;
}
