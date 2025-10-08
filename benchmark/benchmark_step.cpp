#include "util.hpp"
#include <benchmark/benchmark.h>
#include <physics_engine.hpp>

using namespace physics::domain;
using namespace physics::units;
using namespace physics::usecases;

// Benchmark the complete step function with varying particle counts
static void BM_StepFunction(benchmark::State &state) {
  const int particle_count = state.range(0);

  // Create a simple rectangular constraint
  auto constraint = Polygon2D<length::meters<double>>(
      {physics::domain::PositionVector2D(length::meters<double>(-20.0),
                                         length::meters<double>(-20.0)),
       physics::domain::PositionVector2D(length::meters<double>(20.0),
                                         length::meters<double>(-20.0)),
       physics::domain::PositionVector2D(length::meters<double>(20.0),
                                         length::meters<double>(20.0)),
       physics::domain::PositionVector2D(length::meters<double>(-20.0),
                                         length::meters<double>(20.0))});

  auto particles = createRandomParticles(particle_count);
  time::seconds<double> timestep(0.016); // 60 FPS timestep

  for (auto _ : state) {
    // Reset particles to avoid accumulating effects across iterations
    auto fresh_particles = createRandomParticles(particle_count);

    benchmark::DoNotOptimize(fresh_particles);
    auto result = step(fresh_particles, constraint, timestep);
    benchmark::DoNotOptimize(result);
  }

  state.SetComplexityN(particle_count);
}

BENCHMARK(BM_StepFunction)
    ->RangeMultiplier(2)
    ->Range(8, 1024)
    ->Complexity(benchmark::oAuto);

// Benchmark step function with multiple substeps
static void BM_StepFunction_MultipleSubsteps(benchmark::State &state) {
  const int particle_count = state.range(0);

  auto constraint = Polygon2D<length::meters<double>>(
      {physics::domain::PositionVector2D(length::meters<double>(-20.0),
                                         length::meters<double>(-20.0)),
       physics::domain::PositionVector2D(length::meters<double>(20.0),
                                         length::meters<double>(-20.0)),
       physics::domain::PositionVector2D(length::meters<double>(20.0),
                                         length::meters<double>(20.0)),
       physics::domain::PositionVector2D(length::meters<double>(-20.0),
                                         length::meters<double>(20.0))});

  time::seconds<double> timestep(0.016);
  uint32_t substeps = 4;

  for (auto _ : state) {
    auto fresh_particles = createRandomParticles(particle_count);

    benchmark::DoNotOptimize(fresh_particles);
    auto result = step(fresh_particles, constraint, timestep, substeps);
    benchmark::DoNotOptimize(result);
  }

  state.SetComplexityN(particle_count);
}

BENCHMARK(BM_StepFunction_MultipleSubsteps)
    ->RangeMultiplier(2)
    ->Range(8, 512)
    ->Complexity(benchmark::oAuto);