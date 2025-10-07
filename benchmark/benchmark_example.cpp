#include <benchmark/benchmark.h>
#include <physics_engine.hpp>

using namespace physics::domain;
using namespace physics::units;

// Benchmark vector creation and basic operations
static void BM_Vector2D_Creation(benchmark::State &state) {
  for (auto _ : state) {
    auto pos = Vector2D::fromComponents(length::meters<double>(1.0),
                                        length::meters<double>(2.0));
    benchmark::DoNotOptimize(pos);
  }
}
BENCHMARK(BM_Vector2D_Creation);

// Benchmark vector addition
static void BM_Vector2D_Addition(benchmark::State &state) {
  auto v1 = Vector2D::fromComponents(length::meters<double>(1.0),
                                     length::meters<double>(2.0));
  auto v2 = Vector2D::fromComponents(length::meters<double>(3.0),
                                     length::meters<double>(4.0));

  for (auto _ : state) {
    auto result = v1 + v2;
    benchmark::DoNotOptimize(result);
  }
}
BENCHMARK(BM_Vector2D_Addition);

// Benchmark vector magnitude calculation
static void BM_Vector2D_Magnitude(benchmark::State &state) {
  auto v = Vector2D::fromComponents(length::meters<double>(3.0),
                                    length::meters<double>(4.0));

  for (auto _ : state) {
    auto magnitude = v.getMagnitude<length::meters<double>>();
    benchmark::DoNotOptimize(magnitude);
  }
}
BENCHMARK(BM_Vector2D_Magnitude);

// Benchmark vector dot product
static void BM_Vector2D_DotProduct(benchmark::State &state) {
  auto v1 = Vector2D::fromComponents(length::meters<double>(1.0),
                                     length::meters<double>(2.0));
  auto v2 = Vector2D::fromComponents(length::meters<double>(3.0),
                                     length::meters<double>(4.0));

  for (auto _ : state) {
    auto dot = v1.dot(v2);
    benchmark::DoNotOptimize(dot);
  }
}
BENCHMARK(BM_Vector2D_DotProduct);

// Benchmark creating vectors from polar coordinates
static void BM_Vector2D_FromPolar(benchmark::State &state) {
  auto angle = angle::radians<double>(1.57); // ~90 degrees
  auto magnitude = length::meters<double>(5.0);

  for (auto _ : state) {
    auto v = Vector2D::fromPolar(angle, magnitude);
    benchmark::DoNotOptimize(v);
  }
}
BENCHMARK(BM_Vector2D_FromPolar);