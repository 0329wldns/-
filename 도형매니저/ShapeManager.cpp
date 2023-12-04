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
	// cout << "������ �Ҹ�" << '\n';
	for (int i = 0; i < nShape; ++i)
		delete shapes[i];					// shapes�� �ִ� �������� ����
	delete[] shapes;						// �������� ����Ű�� �����͸� ����
}

void ShapeManager::menu()
{
	int user{};
	cout << "------------------------------------------------" << '\n';
	cout << "1. ���� �߰�" << '\n'
		<< "2. ���� ����" << '\n'
		<< "3. ���� �׸���" << '\n'
		<< "4. ����" << '\n';
	cout << "------------------------------------------------" << '\n';
	std::cin >> user;
	if (user > 4 || user < 1) {
		cout << "1~4 ������ ������ �Է����ּ���" << '\n';
	}
	switch (user) {		// ����ڰ� �� �� �ִ� �ൿ�� ����
	case 1:				// 1. ���� �߰�
		cout << "------------------------------------------------" << '\n';
		cout << "1. �ﰢ��" << '\n'
			<< "2. �簢��" << '\n'
			<< "3. ��" << '\n';
		cout << "------------------------------------------------" << '\n';
		cin >> user;
		if (user > 3 || user < 1) {
			cout << "1~3 ������ ������ �Է����ּ���." << '\n';
			break;
		}
		switch (user)
		{
		case 1: {			// 1-1. �ﰢ�� �߰�
			Point p1, p2, p3;
			cout << "------------------------------------------------" << '\n';
			cout << "�� �������� ��ǥ�� �Է��� �ּ���" << '\n';
			cout << "------------------------------------------------" << '\n';
			cin >> p1 >> p2 >> p3;
			insert(new Triangle(p1, p2, p3));
			break;
		}
		case 2: {		// 1-2. �簢�� �߰�
			Point p1, p2;
			cout << "------------------------------------------------" << '\n';
			cout << "�� �������� ��ǥ�� �Է��� �ּ���" << '\n';
			cout << "------------------------------------------------" << '\n';
			cin >> p1 >> p2;
			insert(new Rectangle(p1, p2));
			break;
		}
		case 3: {		// 1-3. �� �߰�
			Point p1;
			double r;
			cout << "------------------------------------------------" << '\n';
			cout << "�߽��� ��ǥ�� �������� ���̸� �Է��� �ּ���" << '\n';
			cout << "------------------------------------------------" << '\n';
			cin >> p1 >> r;
			insert(new Circle(p1, r));
			break;
		}
		default:
			break;
		}
		break;
	case 2:				// 2. ���� ����
		if (!nShape) {	// ������ ������ 0�̸� �����Ұ�
			cout << "������ ������ �����ϴ�." << '\n';
			break;
		}
		cout << "------------------------------------------------" << '\n';
		cout << "1. ������ ��ȣ�� ����" << '\n'
			<< "2. ������ ������ ����" << '\n';
		cout << "------------------------------------------------" << '\n';
		cin >> user;
		if (user > 2 || user < 1) {		// ������� �Է��� ���� ��ȣ�� ������ ��� ���
			cout << "1~2 ������ ������ �Է����ּ���." << '\n';
			break;
		}
		switch (user)
		{
		case 1:			// 2-1. ������ ��ȣ�� ����
			cout << "------------------------------------------------" << '\n';
			cout << "�� ��° ������ �����Ͻðڽ��ϱ�?" << '\n';
			cout << "------------------------------------------------" << '\n';
			cin >> user;
			if (user >= nShape || user < 0) {	// ������� �Է��� ���� ��ȣ�� ������ ��� ���
				cout << "0 ~ " << nShape - 1 << " ������ ������ �Է����ּ���" << '\n';
				break;
			}
			else {
				remove(user);
				cout << user << "��° ���� ����" << '\n';
				break;
			}			// 2-1. ������ ��ȣ�� ���� ��
		case 2:			// 2-2. ������ ������ ����
			cout << "------------------------------------------------" << '\n';
			cout << "1. �ﰢ��" << '\n'
				<< "2. �簢��" << '\n'
				<< "3. ��" << '\n';
			cout << "------------------------------------------------" << '\n';
			cin >> user;
			if (user > 3 || user < 1) {			// ������� �Է��� ���� ��ȣ�� ������ ��� ���
				cout << "1~3 ������ ������ �Է����ּ���." << '\n';
				break;
			}
			switch (user)
			{
			case 1: {	// 2-2-1. ��� �ﰢ�� ����
				int i = 0;
				while (i < nShape) {
					if (dynamic_cast<Triangle*> (shapes[i]) != nullptr) {
						remove(i);
					}
					else i++;
				}
				break;
			}
			case 2: {	// 2-2-2. ��� �簢�� ����
				int i = 0;
				while (i < nShape) {
					if (dynamic_cast<Rectangle*> (shapes[i]) != nullptr) {
						remove(i);
					}
					else i++;
				}
				break;
			}
			case 3: {	// 2-2-3. ��� �� ����
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
	case 3:			// 3. ���� �׸���
		draw();
		break;
	case 4:			// 4. ����
		flag = false;	// ShapeManager�� �ɹ� ���� flag�� ���α׷� ����
		break;
	default:
		break;
	}
}

void ShapeManager::insert(Shape* a)
{
	if (nShape == capacity) {	// ������ ������ ���� �� ���
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
	delete shapes[n];				// �ش� ��ȣ�� ������ ����
	for (int i = 0; i < nShape - n - 1; ++i)	
		shapes[n + i] = shapes[n + i + 1];		// �ش� ��ȣ�� �ڿ� �ִ� ���� �� ĭ�� ����
	nShape--;									// ���� ���� �ϳ� ����
	shapes[nShape] = nullptr;					// ������ ��ȣ�� �ִ� ������ �ʱ�ȭ
}

void ShapeManager::draw() const
{
	cout << "------------------------------------------------" << '\n';
	cout << "�����ϴ� ��� ������ �׸��ϴ�" << '\n';
	cout << "�ִ� " << capacity << "���� ������ ���� �� �ֽ��ϴ�" << '\n';
	cout << "��� " << nShape << "���� ������ �ֽ��ϴ�" << '\n';
	cout << "------------------------------------------------" << '\n' << '\n';

	for (int i = 0; i < nShape; ++i) {
		cout << "[" << i << "]	";
		shapes[i]->draw();
	}
	cout << '\n';

	cout << "------------------------------------------------" << '\n';
	cout << "�׸��⸦ ��Ĩ�ϴ�" << '\n';
	cout << "------------------------------------------------" << '\n' << '\n';
}