#include "MyString.h"

using namespace std;

// 비어 있는 MyString() 생성
MyString::MyString()
{
	str_ = nullptr;
	size_ = 0;
}

// 맨 뒤에 널 캐릭터'\0'가 들어 있는 문자열로부터 초기화
MyString::MyString(const char* init)
{
	// 크기(size_) 결정
	// init이 포인터기 때문에 sizeof로 크기를 구하면 8bytes가 나옴
	
	while (init[size_] != '\0')
	{
		size_++;
	}

	// 메모리 할당
	if (size_ > 0)
		str_ = new char[size_];

		// 데이터 복사
		memcpy(str_, init, size_);
}

// MyString의 다른 instance로부터 초기화
MyString::MyString(const MyString& str)
{
	// 기본 복사 생성자는 포인터 주소만 복사하기 때문에 
	// 소멸시 오류 발생
	// 여기서는 새로 메모리를 할당 받아서 복사
	
	if (str.size_ > 0)
	{
		size_ = str.size_;
		str_ = new char[size_];
		memcpy(str_, str.str_, str.size_);
	}
}

MyString::~MyString()
{
	// 메모리 해제
	delete[] str_;
	size_ = 0;
}

bool MyString::IsEmpty()
{
	return Length() == 0;
}

bool MyString::IsEqual(const MyString& str) // 편의상 참조& 사용
{
	// 힌트: str.str_, str.size_ 가능
	if (this->Length() != str.size_)
		return false;

	for (int i = 0; i < this->Length(); i++)
	{
		if (str_[i] != str.str_[i])
			return false;
	}
	return true;
}

int MyString::Length()
{
	return size_;
}

void MyString::Resize(int new_size)
{
	// 메모리 재할당과 원래 갖고 있던 내용 복사
	char* tmp = nullptr;
	tmp = str_;
	str_ = new char[new_size];
	memcpy(str_, tmp, size_);
	size_ = new_size;
}

// 인덱스 start위치의 글자부터 num개의 글자로 새로운 문자열 만들기
MyString MyString::Substr(int start, int num)
{
	// 복사할 인덱스: start, start + 1, ... , start + num - 1
	assert(start + num - 1 < this->size_); // 문제를 단순하게 만들기 위해 가정

	MyString temp;
	temp.Resize(num);

	for (int i = start; i < start + num; i++)
		temp.str_[i - start] = str_[i];

	return temp;
}

MyString MyString::Concat(MyString app_str)
{
	MyString temp; // str2

	// TODO: 
	int new_size = this->Length() + app_str.Length();
	temp.Resize(new_size);

	for (int i = 0; i < new_size; i++)
	{
		char tmp;
		if (i < app_str.Length())
			tmp = this->str_[i];
		else
			tmp = app_str.str_[i - app_str.Length()];
		temp.str_[i] = tmp;
	}

	return temp;
}

MyString MyString::Insert(MyString t, int start)
{
	assert(start >= 0);
	assert(start <= this->Length());
	MyString temp;

	// TODO:
	int new_size = this->Length() + t.Length();
	temp.Resize(new_size);
	int add_count1 = 0, add_count2 = 0;
	bool insert = false;

	for (int i = 0; i < new_size; i++)
	{
		if (i == start)
			insert = true;
		if (add_count2 == t.Length())
			insert = false;

		if (insert)
		{
			temp.str_[i] = t.str_[add_count2];
			add_count2++;
		}
		else
		{
			temp.str_[i] = this->str_[add_count1];
			add_count1++;
		}
	}
	return temp;
}

int MyString::Find(MyString pat)
{
	//TODO:

	if (pat.Length() > this->Length())
		return -1;

	int start_index = 0;
	int pat_index = 0;
	int count = 0;

	for (int i = 0; i < this->Length(); i++)
	{
		if (str_[i] == pat.str_[pat_index])
		{
			if (count == 0) // 첫 번째 값이 같으면
				start_index = i;
			count++;
			pat_index++;
			if (pat.Length() == count)
				return start_index;
		}
		else
		{
			pat_index = 0;
			count = 0;
		}
	}
	return -1;
}

void MyString::Print()
{
	for (int i = 0; i < this->Length(); i++)
		cout << str_[i];
	cout << endl;
}

