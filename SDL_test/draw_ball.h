#include "glad/glad.h"


void sphere_entry(int du, int dv) {

	float gu = 3.1415926535 / du, gv = 2.0 * 3.1415926535 / (dv - 1);

	float x, y, z, r;

	glPushMatrix();
#define MAKE_R(z2) sqrt(1.0 - (z2))
#define MAKE_Z(z_step) cos((z_step) *gu)
#define MAKE_Y(x_step,r) (r)*sin((x_step)* gv)
#define MAKE_X(x_step,r) (r)*cos((x_step)* gv)
	// ÇòÌå
	glBegin(GL_QUADS);
	for (int z_step = 0; z_step < du; ++z_step) {
		for (int x_step = 0; x_step < dv; ++x_step) {

			z = MAKE_Z(z_step);
			r = MAKE_R(z * z);
			x = MAKE_X(x_step, r);
			y = MAKE_Y(x_step, r);
			glVertex3f(x, y, z);

			z = MAKE_Z(z_step + 1);
			r = MAKE_R(z * z);
			x = MAKE_X(x_step, r);
			y = MAKE_Y(x_step, r);
			glVertex3f(x, y, z);

			z = MAKE_Z(z_step + 1);
			r = MAKE_R(z * z);
			x = MAKE_X(x_step + 1, r);
			y = MAKE_Y(x_step + 1, r);
			glVertex3f(x, y, z);

			z = MAKE_Z(z_step);
			r = MAKE_R(z * z);
			x = MAKE_X(x_step + 1, r);
			y = MAKE_Y(x_step + 1, r);
			glVertex3f(x, y, z);
		}

	}

	glEnd();
#undef MAKE_Y
#undef MAKE_Z
#undef MAKE_X
#undef MAKE_R
	glPopMatrix();
}