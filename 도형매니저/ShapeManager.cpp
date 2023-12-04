#include <iostream>
#include "Point.h"
#include "Circle.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "ShapeManager.h"
using namespace std;

bool ShapeManager::flag = true;

ShapeManager::ShapeManager(int n)
{
	nShape = 0;
	capacity = n;
	shapes = new Shape* [capacity];
}

ShapeManager::~ShapeManager()
{
	// cout << "도형들 소멸" << '\n';
	for (int i = 0; i < nShape; ++i)
		delete shapes[i];					// shapes에 있는 도형들을 정리
	delete[] shapes;						// 도형들을 가리키던 포인터를 정리
}

void ShapeManager::menu()
{
	int user{};
	cout << "------------------------------------------------" << '\n';
	cout << "1. 도형 추가" << '\n'
		<< "2. 도형 삭제" << '\n'
		<< "3. 도형 그리기" << '\n'
		<< "4. 종료" << '\n';
	cout << "------------------------------------------------" << '\n';
	std::cin >> user;
	if (user > 4 || user < 1) {
		cout << "1~4 사이의 정수를 입력해주세요" << '\n';
	}
	switch (user) {		// 사용자가 할 수 있는 행동을 구분
	case 1:				// 1. 도형 추가
		cout << "------------------------------------------------" << '\n';
		cout << "1. 삼각형" << '\n'
			<< "2. 사각형" << '\n'
			<< "3. 원" << '\n';
		cout << "------------------------------------------------" << '\n';
		cin >> user;
		if (user > 3 || user < 1) {
			cout << "1~3 사이의 정수를 입력해주세요." << '\n';
			break;
		}
		switch (user)
		{
		case 1: {			// 1-1. 삼각형 추가
			Point p1, p2, p3;
			cout << "------------------------------------------------" << '\n';
			cout << "세 꼭짓점의 좌표를 입력해 주세요" << '\n';
			cout << "------------------------------------------------" << '\n';
			cin >> p1 >> p2 >> p3;
			insert(new Triangle(p1, p2, p3));
			break;
		}
		case 2: {		// 1-2. 사각형 추가
			Point p1, p2;
			cout << "------------------------------------------------" << '\n';
			cout << "두 꼭짓점의 좌표를 입력해 주세요" << '\n';
			cout << "------------------------------------------------" << '\n';
			cin >> p1 >> p2;
			insert(new Rectangle(p1, p2));
			break;
		}
		case 3: {		// 1-3. 원 추가
			Point p1;
			double r;
			cout << "------------------------------------------------" << '\n';
			cout << "중심의 좌표와 반지름의 길이를 입력해 주세요" << '\n';
			cout << "------------------------------------------------" << '\n';
			cin >> p1 >> r;
			insert(new Circle(p1, r));
			break;
		}
		default:
			break;
		}
		break;
	case 2:				// 2. 도형 삭제
		if (!nShape) {	// 도형의 개수가 0이면 삭제불가
			cout << "삭제할 도형이 없습니다." << '\n';
			break;
		}
		cout << "------------------------------------------------" << '\n';
		cout << "1. 도형의 번호로 삭제" << '\n'
			<< "2. 도형의 종류로 삭제" << '\n';
		cout << "------------------------------------------------" << '\n';
		cin >> user;
		if (user > 2 || user < 1) {		// 사용자의 입력이 도형 번호의 범위를 벗어난 경우
			cout << "1~2 사이의 정수를 입력해주세요." << '\n';
			break;
		}
		switch (user)
		{
		case 1:			// 2-1. 도형의 번호로 삭제
			cout << "------------------------------------------------" << '\n';
			cout << "몇 번째 도형을 삭제하시겠습니까?" << '\n';
			cout << "------------------------------------------------" << '\n';
			cin >> user;
			if (user >= nShape || user < 0) {	// 사용자의 입력이 도형 번호의 범위를 벗어난 경우
				cout << "0 ~ " << nShape - 1 << " 사이의 정수를 입력해주세요" << '\n';
				break;
			}
			else {
				remove(user);
				cout << user << "번째 도형 삭제" << '\n';
				break;
			}			// 2-1. 도형의 번호로 삭제 끝
		case 2:			// 2-2. 도형의 종류로 삭제
			cout << "------------------------------------------------" << '\n';
			cout << "1. 삼각형" << '\n'
				<< "2. 사각형" << '\n'
				<< "3. 원" << '\n';
			cout << "------------------------------------------------" << '\n';
			cin >> user;
			if (user > 3 || user < 1) {			// 사용자의 입력이 도형 번호의 범위를 벗어난 경우
				cout << "1~3 사이의 정수를 입력해주세요." << '\n';
				break;
			}
			switch (user)
			{
			case 1: {	// 2-2-1. 모든 삼각형 삭제
				int i = 0;
				while (i < nShape) {
					if (dynamic_cast<Triangle*> (shapes[i]) != nullptr) {
						remove(i);
					}
					else i++;
				}
				break;
			}
			case 2: {	// 2-2-2. 모든 사각형 삭제
				int i = 0;
				while (i < nShape) {
					if (dynamic_cast<Rectangle*> (shapes[i]) != nullptr) {
						remove(i);
					}
					else i++;
				}
				break;
			}
			case 3: {	// 2-2-3. 모든 원 삭제
				int i = 0;
				while (i < nShape) {
					if (dynamic_cast<Circle*> (shapes[i]) != nullptr) {
						remove(i);
					}
					else i++;
				}
				break;
			}
			default:
				break;
			}
			break;
		}
		break;
	case 3:			// 3. 도형 그리기
		draw();
		break;
	case 4:			// 4. 종료
		flag = false;	// ShapeManager의 맴버 변수 flag로 프로그램 종료
		break;
	default:
		break;
	}
}

void ShapeManager::insert(Shape* a)
{
	if (nShape == capacity) {	// 도형의 개수가 가득 찬 경우
		Shape** temp = new Shape* [capacity];
		memcpy(temp, shapes, sizeof(Shape*) * nShape);
		delete[] shapes;
		capacity++;
		shapes = new Shape* [capacity];
		memcpy(shapes, temp, sizeof(Shape*) * nShape);
	}
		shapes[nShape] = a;
		nShape++;
}

void ShapeManager::remove(int n)
{
	delete shapes[n];				// 해당 번호의 도형을 삭제
	for (int i = 0; i < nShape - n - 1; ++i)	
		shapes[n + i] = shapes[n + i + 1];		// 해당 번호의 뒤에 있는 도형 한 칸씩 당기기
	nShape--;									// 도형 개수 하나 감소
	shapes[nShape] = nullptr;					// 마지막 번호에 있던 포인터 초기화
}

void ShapeManager::draw() const
{
	cout << "------------------------------------------------" << '\n';
	cout << "관리하는 모든 도형을 그립니다" << '\n';
	cout << "최대 " << capacity << "개의 도형을 담을 수 있습니다" << '\n';
	cout << "모두 " << nShape << "개의 도형이 있습니다" << '\n';
	cout << "------------------------------------------------" << '\n' << '\n';

	for (int i = 0; i < nShape; ++i) {
		cout << "[" << i << "]	";
		shapes[i]->draw();
	}
	cout << '\n';

	cout << "------------------------------------------------" << '\n';
	cout << "그리기를 마칩니다" << '\n';
	cout << "------------------------------------------------" << '\n' << '\n';
}