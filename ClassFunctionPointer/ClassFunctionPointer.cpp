// ClassFunctionPointer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

template<class T>
class Dog
{
public:
	Dog();
	~Dog();

	typedef void (*Bark)(int count);
	Bark Barker;
	typedef void(T::* ClassBark)(int count);
	T* object;
	ClassBark ClassBarker;
	void Action();
private:

};

template <typename T> 
Dog<T>::Dog()
{
	object = nullptr;
	Barker = nullptr;
	ClassBarker = nullptr;
}

template <typename T>
Dog<T>::~Dog()
{
}

template <typename T>
void Dog<T>::Action()
{
	if (Barker)
		Barker(1);
	if (object && ClassBarker)
		(object->*ClassBarker)(2);
}

template <typename T>
class Cat
{
public:
	Cat();
	~Cat();

	typedef void(*Bark)(int count);
	Bark Barker;
	typedef void(T::* ClassBark)(int count);
	T* object;
	ClassBark ClassBarker;
	void Action();
private:

};

template <typename T> 
Cat<T>::Cat()
{
	object = nullptr;
	Barker = nullptr;
	ClassBarker = nullptr;
}

template <typename T> 
Cat<T>::~Cat()
{
}

template <typename T>
void Cat<T>::Action()
{
	if (Barker)
		Barker(3);
	if (object && ClassBarker)
		(object->*ClassBarker)(4);
}

class AnimalBehavior
{
public:
	static AnimalBehavior* Instance;
	AnimalBehavior();
	~AnimalBehavior();

	Dog<AnimalBehavior> *aDog;
	Cat<AnimalBehavior> *aCat;
	
	void Action();
	void ClassDogBark(int count);
	void ClassCatBark(int count);
private:

};
//declaration
AnimalBehavior* AnimalBehavior::Instance = nullptr;

void CatBark(int count)
{
	for (int i = 0; i < count; i++)
		std::cout << "Meow\n";
}

void DogBark(int count)
{
	for (int i = 0; i < count; i++)
		std::cout << "Woof\n";
}

AnimalBehavior::AnimalBehavior()
{
	Instance = this;
	aDog = new Dog<AnimalBehavior>();
	aCat = new Cat<AnimalBehavior>();

	aDog->Barker = &DogBark;
	aCat->Barker = &CatBark;
	aDog->object = this; //who is this???
	aCat->object = this;
	aDog->ClassBarker = &AnimalBehavior::ClassDogBark;
	aCat->ClassBarker = &AnimalBehavior::ClassCatBark;
}

AnimalBehavior::~AnimalBehavior()
{
	delete aDog;
	delete aCat;
}

void AnimalBehavior::Action()
{
	aDog->Action();
	aCat->Action();
}

void AnimalBehavior::ClassDogBark(int count)
{
	for (int i = 0; i < count; i++)
		std::cout << "Class Woof\n";
}

void AnimalBehavior::ClassCatBark(int count)
{
	for (int i = 0; i < count; i++)
		std::cout << "Class Meow\n";
}
 
int main(int argc, char** argv)
{
	AnimalBehavior animalAct;
	std::cout << "Who is this? " << animalAct.Instance << "\n";
	animalAct.Action();
}


// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
