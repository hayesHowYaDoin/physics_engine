#include "util.hpp"
#include <physics_engine.hpp>
#include <random>

// Create a vector of particles with random positions for collision testing
std::vector<physics::usecases::Particle<physics::units::SI>>
createRandomParticles(int count) {
  using namespace physics::domain;
  using namespace physics::usecases;
  using namespace physics::units;

  std::vector<Particle<SI>> particles;
  particles.reserve(count);

  std::random_device rd;
  std::mt19937 gen(42); // Fixed seed for reproducible benchmarks
  std::uniform_real_distribution<double> pos_dist(-10.0, 10.0);
  std::uniform_real_distribution<double> vel_dist(-5.0, 5.0);
  std::uniform_real_distribution<double> mass_dist(0.5, 2.0);
  std::uniform_real_distribution<double> radius_dist(0.1, 0.5);

  for (int i = 0; i < count; ++i) {
    Particle<SI> particle{
        .mass = mass::kilograms<double>(mass_dist(gen)),
        .radius = length::meters<double>(radius_dist(gen)),
        .position =
            Vector2D::fromComponents(length::meters<double>(pos_dist(gen)),
                                     length::meters<double>(pos_dist(gen))),
        .velocity = Vector2D::fromComponents(
            velocity::meters_per_second<double>(vel_dist(gen)),
            velocity::meters_per_second<double>(vel_dist(gen)))};
    particles.push_back(std::move(particle));
  }

  return particles;
}