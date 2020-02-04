
#pragma once
#define GLUT_DISABLE_ATEXIT_HACK
#include <gl/glut.h>  


class particle {
	bool is_forever;
	float x, y, z;
	float size_x;
	float size_y;
	float size_z;
	float speed_x;
	float speed_y;
	float speed_z;
	float acc_x;
	float acc_y;
	float acc_z;
	float life;
	float angle;
	unsigned char color[3];
	friend class emitter;
	void draw();
	void show();
public:
	particle();
	particle(float _size_x, float _size_y, float _size_z,
		float _speed_x, float _speed_y, float _speed_z,
		float _acc_x, float _acc_y, float _acc_z,
		float _life, float _angle, unsigned char* _color, bool _is_forever);
};

class emitter {
	float x1, y1, x2, y2 ,z1, z2;
	int speed;
	particle** p;
	particle* (*f)();
public:
	void emit(particle* (init)());
	void update();
	emitter(int _speed, float _x1,float _x2, float _y1, float _y2,float _z1, float _z2);
};
