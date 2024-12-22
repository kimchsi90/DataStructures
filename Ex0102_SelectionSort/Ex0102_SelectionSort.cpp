#include <iostream>
#include <cassert>
#include <fstream>

using namespace std;

struct Element
{
	int key;
	char value;
};

bool CheckSorted(int* arr, int size)
{
	// TODO: 정렬 확인 함수 구현
	for (int i = 0; i < size - 1; i++) {
		if (arr[i] > arr[i + 1]) return false;
	}
	return true;
}

void SwapRef(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void Print(int* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i] << " ";
	cout << endl;
}

void Print(Element* arr, int size)
{
	for (int i = 0; i < size; i++)
		cout << arr[i].key << " ";
	cout << endl;

	for (int i = 0; i < size; i++)
		cout << arr[i].value << " ";
	cout << endl;
}

int main()
{
	// 3개 정렬
	//{
	//	for (int k = 0; k < 3; k++)
	//		for (int j = 0; j < 3; j++)
	//			for (int i = 0; i < 3; i++) {

	//				int arr[3] = { i, j, k };
	//				int size = sizeof(arr) / sizeof(arr[0]);

	//				for (int e = 0; e < size; e++) {
	//					cout << arr[e] << " " << flush;
	//				}

	//				cout << " -> " << flush;

	//				//TODO: 정렬 해보기

	//				for (int i = 0; i < size - 1; i++)
	//				{
	//					for (int j = i + 1; j < size; j++)
	//					{
	//						if (arr[i] > arr[j])
	//						{
	//							// ToDo
	//							// 왜 안 되는지 확인하기
	//							/*int temp = arr[i];
	//							arr[i] = arr[j];
	//							arr[j] = temp;*/

	//							SwapRef(arr[i], arr[j]);
	//						}
	//					}
	//				}

	//				for (int e = 0; e < size; e++) {
	//					cout << arr[e] << " " << flush;
	//				}

	//				cout << boolalpha;
	//				cout << CheckSorted(arr, size); // 정렬 되었나 확인
	//				cout << endl;
	//			}
	//}

	// return 0; // <- 실습용 임시

	// 5개라면? 더 많다면?
	{
		// 8 4 2 8 3
		// TODO: ???

		// 8 3 2 5 1 1 2 5 8 9
		// TODO: ???

		// 100개라면?
	}

	// 가장 작은 수 찾기
	//{
	//	int arr[] = { 8, 3, 2, 5, 1, 1, 2, 5, 8, 9 }; // 임의의 숫자들, 변경 가능
	//	int size = sizeof(arr) / sizeof(arr[0]);

	//	assert(size > 0); // size가 1이상이라고 가정

	//	// TODO:
	//	int min_number = arr[0];
	//	// 값이 1개 이상인 것이 보장이 되기 때문에 min_number에 할당

	//	// min_number를 아주 큰 수로 초기화하고 for문을 index 0부터 도는 방법도 있음

	//	for (int i = 1; i < size; i++)
	//	{
	//		/*if (min_number > arr[i])
	//			min_number = arr[i];*/
	//		min_number = min_number > arr[i] ? arr[i] : min_number;

	//	}

	//	cout << "Minimum number is " << min_number << endl;
	//}

	// 가장 작은 수의 인덱스 찾기
	//{
	//	int arr[] = { 8, 3, 2, 5, 1, 1, 2, 5, 8, 9 };
	//	int size = sizeof(arr) / sizeof(arr[0]);

	//	assert(size > 0); // size가 1이상이라고 가정

	//	// TODO:
	//	int min_index = 0;
	//	for (int i = 0; i < size; i++)
	//	{
	//		min_index = arr[min_index] > arr[i] ? i : min_index;
	//	}

	//	cout << "The index of min is " << min_index << endl;
	//	cout << "Minimum number is " << arr[min_index] << endl;
	//}

	// Selection Sort
	// 힌트: swap()
	{
		int arr[] = { 8, 3, 2, 5, 1, 1, 2, 5, 8, 9 };
		int size = sizeof(arr) / sizeof(arr[0]);
		int min_index;
		for (int i = 0; i < size - 1; i++)
		{
			// TODO:
			min_index = i;
			for (int j = i+1; j < size; j++)
			{
				if (arr[i] > arr[j])
					min_index = i;
			}
			SwapRef(arr[i], arr[min_index]);
			Print(arr, size);

			cout << boolalpha;
			cout << CheckSorted(arr, size);
			cout << endl;
		}
	}

	// 비교 횟수 세보기, 더 효율적인 방법은 없을까?
	// https://en.wikipedia.org/wiki/Sorting_algorithm
	{
		ofstream ofile("log.txt");
		for (int size = 1; size < 1000; size++)
		{
			int count = 0;
			int* arr = new int[size];
			for (int s = 0; s < size; s++) {
				arr[s] = size - s;
			}

			//TODO: count ++;

			//cout << size << ", " << count << endl;
			ofile << size << ", " << count << endl;
			// Print(arr, size);

			delete[] arr;
		}

		ofile.close();
	}

	// [2, 2, 1]
	// [1, 2, 2] // 첫 2가 마지막으로 이동

	// 정렬 후 key 값이 같은 것 끼리의 순서가 유지되면 stable하다고 함
	// stable함도 정렬 알고리즘은 분류하는 기준이 됨
	// key, value로 묶여있는 경우에는 key만 가지고도 정렬할 수 있다
	// 안정성 확인(unstable)
	{
		Element arr[] = { {2, 'a'}, {2, 'b'}, {1, 'c'} };
		int size = sizeof(arr) / sizeof(arr[0]);

		Print(arr, size); // arr이 Element의 배열

		// TODO:

		Print(arr, size); // arr이 Element의 배열
	}
}
