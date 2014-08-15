// advance example
#include <iostream>     // std::cout
#include <iterator>     // std::distance
#include <list>         // std::list
#include <vector>

using namespace std;

void displayIntList(list<int> & L)
{
    list<int>::iterator I=L.begin();
    while(I!= L.end())
        cout << *I++ << ' ';
    cout << "L size is:"<< L.size() << endl;
}


int main () {

  std::list<int> mylist;
  for (int i=0; i<10; i++)
    mylist.push_back (i*10);

  std::list<int>::iterator first = mylist.begin();

  std::list<int>::iterator last = mylist.end();

  std::cout << "The distance is: " << std::distance(first,--last) << '\n';

  vector<int> intV(10);
  int i;
  for(i = 0; i < intV.size(); i++)
    intV[i] = i;

  intV.insert(intV.end(), 100);

  for(i = 0; i < intV.size(); i++)
    cout << intV[i] << endl;

  vector<int>::iterator I;
  for(I = intV.begin(); I != intV.end(); ++I)
    cout << *I << endl;

  vector<int> newV(20,0);
  newV.swap(intV);
  newV.swap(intV);
  cout<<"after swap intV:"<<endl;
  for(i = 0; i < intV.size(); i++)
    cout << intV[i] << endl;
  for(i = 0; i < newV.size(); i++)
    cout << newV[i] << endl;

  list<int> l1, l2;

  for(int i=0; i<10;i++)
  {
      l1.push_back(2*i);
      l2.push_back(2*i+1);
  }
  displayIntList(l1);
  displayIntList(l2);

  //l1.merge(l2);
  //displayIntList(l1);
  //displayIntList(l2);

  list<int>::iterator iter = l2.begin();
  advance(iter, 4);
  l1.splice(l1.begin(), l2, iter, l2.end());
  displayIntList(l1);
  displayIntList(l2);
  cout<< '\t';
  return 0;
}
