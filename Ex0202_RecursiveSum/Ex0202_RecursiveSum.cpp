#include <iostream>
#include <cassert>
#include <algorithm> // swap

using namespace std;

// 공간 복잡도: O(1) - n 값에 따라 달라지지 않고 일정하기 때문에
// 시간 복잡도: O(N) - n번 만큼 연산하기 때문에
int Sum(int* arr, int n)
{
	int sum = 0;

	for (int i = 0; i < n; i++)
		sum += arr[i];

	return sum;
}

// 공간 복잡도: O(N) - n의 수만큼 커지기 때문에
// 시간 복잡도: O(N) - n번 만큼 연산하기 때문에
int RecurSum(int* arr, int n)
{
	/* 힌트: 역순으로 더하기 (매개변수에 시작 인덱스를 추가하지 않아도 되기 때문)
	  (1 + 2 + ... 8 + 9 + 10)
	= (1 + 2 + ... 8 + 9) + 10
	= ((1 + 2 + ... 8) + 9) + 10
	= ...
	*/
	if (n == 0)
		return 0;

	return RecurSum(arr, n-1) + arr[n-1];

}

// 그냥 더하기와 재귀함수 구현은 Big-O notation 상 시간 복잡도가 같지만
// 재귀함수를 이용한 구현이 사실상 훨씬 메모리도 많이 필요하고 시간도 더 걸림
// 함수를 호출할 때 더하기 연산보다 훨씬 많은 연산이 필요하고
// 메모리의 stack 영역에 n번 만큼 호출된 함수가 쌓이기 때문에
// stack에 쌓인 것을 frame이라고 하는데 frame에는 함수 호출 후 어디로 돌아가야 하는지에 대한 주소도 저장되어 있다.(x64면 8바이트)

int main()
{
	// Sum vs RecurSum

	int arr[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	int n = sizeof(arr) / sizeof(arr[0]);

	cout << Sum(arr, n) << endl;
	cout << RecurSum(arr, n) << endl;

	return 0;
}
