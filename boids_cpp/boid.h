#include <cmath>

class Boid {
public:
	float x, y;
	float vx, vy;

	Boid(float x = 0, float y = 0, float vx = 0, float vy = 0)
		: x(x), y(y), vx(vx), vy(vy) {}

	void update() {
		x += vx;
		y += vy;
	}

	void setVelocity(float vx, float vy) {
		this->vx = vx;
		this->vy = vy;
	}
};