#include <iostream>
using namespace std;

void bubbleSort(int arr[], int size)
{
  for (int i = 0; i < size ; i++)
  {
    for (int j = 0; j < size-1 ; j++)
    {
      if (arr[j] > arr[j + 1])
      {
        // swap
        int tmp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = tmp;
      }
    }
  }
//int index=0;
//for (int j = 1; j < size ; j++)
//    {
//      if (arr[index] > arr[j])
//      {
//        int tmp = arr[j];
//        arr[j] = arr[j + 1];
//        arr[j + 1] = tmp;
//        index=j;
//      }
//	  }
//	  for (int i = 0; i < 10; i++)
//  {
//    cout << arr[i] << " ";
//  }
}

int main()
{
  int arr[10] = {23, 56, 72, 46, 16, 33, 29, 42, 59, 41};
  for (int i = 0; i < 10; i++)
  {
    cout << arr[i] << " ";
  }
  cout<<endl;
  bubbleSort(arr, 10);
  for (int i = 0; i < 10; i++)
  {
    cout << arr[i] << " ";
  }
}
