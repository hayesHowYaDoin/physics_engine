#include <benchmark/benchmark.h>
#include <physics_engine.hpp>
#include <random>
#include <vector>

using namespace physics::domain;
using namespace physics::units;
using namespace physics::usecases;

// Create a vector of particles with random positions for collision testing
std::vector<Particle<SI>> createRandomParticles(int count) {
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

// Benchmark collision detection for different particle counts to analyze time
// complexity
static void BM_CollisionDetection(benchmark::State &state) {
  const int particle_count = state.range(0);

  for (auto _ : state) {
    // Create particles fresh each iteration to avoid state contamination
    auto particles = createRandomParticles(particle_count);

    // Measure just the collision resolution time
    benchmark::DoNotOptimize(particles);
    resolveCollisions(particles);
    benchmark::DoNotOptimize(particles);
  }

  // Set complexity counter for analysis
  state.SetComplexityN(particle_count);
}

// Test with particle counts that demonstrate O(n²) complexity
BENCHMARK(BM_CollisionDetection)
    ->RangeMultiplier(2)
    ->Range(8, 512)
    ->Complexity(benchmark::oNSquared);

// Benchmark individual collision resolution between two particles
static void BM_SingleCollisionResolution(benchmark::State &state) {
  // Create two particles that are colliding
  auto particle1 = Particle<SI>{
      .mass = mass::kilograms<double>(1.0),
      .radius = length::meters<double>(0.5),
      .position = Vector2D::fromComponents(length::meters<double>(0.0),
                                           length::meters<double>(0.0)),
      .velocity =
          Vector2D::fromComponents(velocity::meters_per_second<double>(1.0),
                                   velocity::meters_per_second<double>(0.0))};

  auto particle2 = Particle<SI>{
      .mass = mass::kilograms<double>(1.0),
      .radius = length::meters<double>(0.5),
      .position = Vector2D::fromComponents(
          length::meters<double>(0.8), // Overlapping with particle1
          length::meters<double>(0.0)),
      .velocity =
          Vector2D::fromComponents(velocity::meters_per_second<double>(-1.0),
                                   velocity::meters_per_second<double>(0.0))};

  for (auto _ : state) {
    // Reset particles to initial colliding state
    particle1.position = Vector2D::fromComponents(length::meters<double>(0.0),
                                                  length::meters<double>(0.0));
    particle2.position = Vector2D::fromComponents(length::meters<double>(0.8),
                                                  length::meters<double>(0.0));

    // Measure single collision resolution
    physics::usecases::__detail::resolveCollisionImpl(particle1, particle2);

    benchmark::DoNotOptimize(particle1);
    benchmark::DoNotOptimize(particle2);
  }
}

BENCHMARK(BM_SingleCollisionResolution);

// Benchmark collision detection with no collisions (worst case for early exit
// optimization)
static void BM_CollisionDetection_NoCollisions(benchmark::State &state) {
  const int particle_count = state.range(0);

  // Create particles that are far apart (no collisions)
  std::vector<Particle<SI>> particles;
  particles.reserve(particle_count);

  for (int i = 0; i < particle_count; ++i) {
    // Space particles far apart in a grid to avoid collisions
    double spacing = 10.0;
    int grid_size = static_cast<int>(std::ceil(std::sqrt(particle_count)));
    double x = (i % grid_size) * spacing;
    double y = (i / grid_size) * spacing;

    Particle<SI> particle{
        .mass = mass::kilograms<double>(1.0),
        .radius = length::meters<double>(0.1),
        .position = Vector2D::fromComponents(length::meters<double>(x),
                                             length::meters<double>(y)),
        .velocity =
            Vector2D::fromComponents(velocity::meters_per_second<double>(0.0),
                                     velocity::meters_per_second<double>(0.0))};
    particles.push_back(std::move(particle));
  }

  for (auto _ : state) {
    resolveCollisions(particles);
    benchmark::DoNotOptimize(particles);
  }

  state.SetComplexityN(particle_count);
}

BENCHMARK(BM_CollisionDetection_NoCollisions)
    ->RangeMultiplier(2)
    ->Range(8, 512)
    ->Complexity(benchmark::oNSquared);