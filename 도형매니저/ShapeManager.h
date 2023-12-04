#include "Shape.h"
class ShapeManager {
	int nShape;
	int capacity;
	Shape** shapes;

public:
	static bool flag;

	explicit ShapeManager(int n);

	~ShapeManager();
	ShapeManager(const ShapeManager&) = default;

	void menu();
	void insert(Shape*);
	void remove(int);
	void draw() const;
 };
