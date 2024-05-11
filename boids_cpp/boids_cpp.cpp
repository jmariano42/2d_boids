#include <SFML/Graphics.hpp>
#include <vector>

#include "boids_cpp.h"
#include "boid.h"

void simulateBoids(std::vector<Boid>& boids, int iterations) {
    for (int i = 0; i < iterations; ++i) {
        for (Boid& boid : boids) {
            float maxV = 5.0f;
            float minV = -5.0f;

            float vx = boid.vx;
            float vy = boid.vy;

            //Seperation calculation
            float seperationVX = 0.0f;
            float seperationVY = 0.0f;

            for (Boid& boidy : boids) {
                if (boidy.x == boid.x && boidy.y == boid.y) continue;

                float dx = boidy.x - boid.x;
                float dy = boidy.y - boid.y;
                float distance = sqrt(dx * dx + dy * dy);

                if (distance > 0 && distance < 25) {
                    if (boidy.x < boid.x) { seperationVX += 0.005f + (boidy.vx * 0.00005f); }
                    if (boidy.x > boid.x) { seperationVX -= 0.005f + (boidy.vx * 0.00005f); }
                    if (boidy.y < boid.y) { seperationVY += 0.005f + (boidy.vy * 0.00005f); }
                    if (boidy.y > boid.y) { seperationVY -= 0.005f + (boidy.vy * 0.00005f); }
                }
            }

            //Alignment calculation
            float alignmentVX = 0.0f;
            float alignmentVY = 0.0f;

            for (Boid& boidy : boids) {
                if (boidy.x == boid.x && boidy.y == boid.y) continue;

                float dx = boidy.x - boid.x;
                float dy = boidy.y - boid.y;
                float distance = sqrt(dx * dx + dy * dy);

                if (distance < 100) {
                    alignmentVX += boidy.vx * 0.000075f + (boidy.vx * 0.00005f);
                    alignmentVY += boidy.vy * 0.000075f + (boidy.vy * 0.00005f);
                }
            }

            //Cohesion calculation
            float cohesionVX = 0.0f;
            float cohesionVY = 0.0f;

            float totalX = 0.0f;
            float totalY = 0.0f;

            float avgX = 0.0f;
            float avgY = 0.0f;

            uint8_t count = 0;

            for (Boid& boidy : boids) {
                if (boidy.x == boid.x && boidy.y == boid.y) continue;

                float dx = boidy.x - boid.x;
                float dy = boidy.y - boid.y;
                float distance = sqrt(dx * dx + dy * dy);

                if (distance < 100)
                {
                    totalX += boidy.x;
                    totalY += boidy.y;
                    count++;
                }
            }

            avgX = totalX / count;
            avgY = totalY / count;

            if (avgX > boid.x) { cohesionVX += 0.005f; }
            if (avgX < boid.x) { cohesionVX -= 0.005f; }
            if (avgY > boid.y) { cohesionVY += 0.005f; }
            if (avgY < boid.y) { cohesionVY -= 0.005f; }

            vx += seperationVX + alignmentVX + cohesionVX;
            vy += seperationVY + alignmentVY + cohesionVY;

            sf::Vector2f newVector;
            newVector.x = vx;
            newVector.y = vy;

            if (vx > maxV) vx = maxV;
            if (vy > maxV) vy = maxV;
            if (vx < minV) vx = minV;
            if (vy < minV) vy = minV;

            if (boid.x < 40) { vx = 1.0f; }
            if (boid.x > 1240) { vx = -1.0f; }
            if (boid.y < 40) { vy = 1.0f; }
            if (boid.y > 680) { vy = -1.0f; }

            boid.setVelocity(vx, vy);
        }
    }

    for (Boid& boid : boids) {
        boid.update();
    }
}

void drawBoids(const std::vector<Boid>& boids, sf::RenderWindow& window) {
	for (const Boid& boid : boids) {
		sf::CircleShape circle(5);
		circle.setPosition(boid.x, boid.y);
		window.draw(circle);
	}
}

int main() {
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Boids Simulation");
    window.setFramerateLimit(60);

    std::vector<Boid> boids;

    float clumpRadius = 300.0f;

    for (int i = 0; i < 100; ++i) {
        float randomX = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * clumpRadius * 2 - clumpRadius + 640;
        float randomY = static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * clumpRadius * 2 - clumpRadius + 360;
        float startingVX = 0.0f;
        float startingVY = 0.0f;

        Boid boid(randomX, randomY, startingVX, startingVY);
        boids.push_back(boid);
    }

    while (window.isOpen()) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        
        simulateBoids(boids, 10);

        window.clear();
        drawBoids(boids, window);
        window.display();
    }

    return 0;
}