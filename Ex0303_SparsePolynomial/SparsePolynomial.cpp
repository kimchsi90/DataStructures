#include "SparsePolynomial.h"

#include <iostream>
#include <cassert>
#include <algorithm>
#include <math.h>

using namespace std;

// 새로운 항을 추가할 때 자기 위치를 찾아서 넣어줘야 함

// exp항이 이미 존재하면 거기에 coef를 더해준다.
// 존재하지 않는다면 exp 오름 차순으로 정렬된 상태로 새로 추가한다.
void SparsePolynomial::NewTerm(float coef, int exp)
{
	if (coef == 0.0f) return; // 0이면 추가하지 않음

	if (num_terms_ >= capacity_)
	{
		// capacity 증가 (num_terms는 일단 고정)
		capacity_ = capacity_ > 0 ? capacity_ * 2 : 1; // 2배씩 증가(매번 메모리를 증가 시키는 것은 속도를 느리게 만들기 때문에 미리 여유공간을 잡아 놓는다.
		Term* new_term = new Term[capacity_];
		
		// 원래 가지고 있던 데이터 복사
		memcpy(new_term, terms_, sizeof(Term) * num_terms_);

		// 메모리 교체
		if (terms_) delete[] terms_;
		terms_ = new_term;
	}

	terms_[num_terms_].coef = coef;
	terms_[num_terms_].exp = exp;

	num_terms_++;
}

float SparsePolynomial::Eval(float x)
{
	float temp = 0.0f;

	// TODO:
	for (int i = 0; i < num_terms_; i++)
		temp += terms_[i].coef * pow(x, terms_[i].exp);

	return temp;
}

SparsePolynomial SparsePolynomial::Add(const SparsePolynomial& poly)
{
	// this와 poly의 terms_가 exp의 오름차순으로 정렬되어 있다고 가정
	// 하나의 다항식 안에 exp가 중복되는 term이 없다라고 가정 (한 exp는 하나의 term만 존재)

	// 간단한 방법 (메모리를 더 사용하는 방법)
	// - 1. 최대 exp를 찾는다.
	// - 2. 필요한 크기의 Polynomial을 만든다. (Sparse 아님)
	// - 3. 더하면서 Polynomial에 업데이트 한다. 구조가 고정되어 있어서 쉽다.
	// - 4. Polynomial을 SparsePolynomial로 변환한다.

	SparsePolynomial temp;
	// 1. 간단한 방법
	//int max_exp = max(terms_[num_terms_ - 1].exp, poly.terms_[poly.num_terms_ - 1].exp);

	//float* temp_array = new float[max_exp + 1]{}; // {} 중괄호를 넣으면 모든 동적 배열의 값을 0.0f로 초기화(int의 경우 0)

	//for (int i = 0; i < num_terms_; i++)
	//	temp_array[terms_[i].exp] += terms_[i].coef;
	//for (int j = 0; j < poly.num_terms_; j++)
	//	temp_array[poly.terms_[j].exp] += poly.terms_[j].coef;

	//for (int i = 0; i <= max_exp; i++)
	//{
	//	if (temp_array[i] != 0.0f)
	//		temp.NewTerm(temp_array[i], i);
	//}


	// 2. 시간복잡도를 줄이는 방법
	
	// 1) 더하려는 두 다항식의 index를 1씩 늘려 값을 비교(i만 먼저 탐색하고 그 다음 j를 탐색하는 것이 아니라 조건에 따라 i와 j의 값을 늘려 효율적으로 탐색)
	// 2) 같을 경우 더하여 새로운 다항식의 exp, coef를 만든다.
	// 3) 같지 않을 경우 index를 늘려 exp 값이 같은지 확인한다
	int i = 0, j = 0;
	int a_max_exp = terms_[num_terms_].exp;
	int b_max_exp = poly.terms_[num_terms_].exp;

	while (i < num_terms_ && j < poly.num_terms_)
	{
		float a_exp = terms_[i].exp;
		float b_exp = poly.terms_[j].exp;
		int a_coef = terms_[i].coef;
		int b_coef = poly.terms_[j].coef;

		if (a_exp == b_exp) // 차수가 같으면
		{
			temp.NewTerm(a_coef + b_coef, a_exp);
			i++, j++;
		}
		else if (a_exp > b_exp) // a의 차수가 더 크면
		{
			temp.NewTerm(b_coef, b_exp);
			j++;
		}
		else // (i < j) // b의 차수가 더 크면
		{
			temp.NewTerm(a_coef, b_exp);
			i++;
		}

		if (terms_[i].exp >= a_max_exp)
			for (int k = j + 1; poly.terms_[k].exp <= b_max_exp; k++)
				temp.NewTerm(poly.terms_[k].coef, poly.terms_[k].exp);

		if (poly.terms_[j].exp <= b_max_exp)
			for (int l = i + 1; terms_[l].exp <= a_max_exp; l++)
				temp.NewTerm(terms_[l].coef, terms_[l].exp);

	}

	// TODO:

	return temp;
}

void SparsePolynomial::Print()
{
	bool is_first = true; // 더하기 출력시 확인용

	for (int i = 0; i < num_terms_; i++)
	{
		// 0이 아닌 항들만 골라서 출력할 필요가 없음

		if (!is_first)
			cout << " + "; // 첫 항이 아니라면 사이사이에 더하기 출력

		cout << terms_[i].coef;

		if (terms_[i].exp != 0) cout << "*" << "x^" << terms_[i].exp;

		is_first = false;
	}

	cout << endl;
}
