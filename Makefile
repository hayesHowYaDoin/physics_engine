# Physics Engine Command Runner
# This Makefile provides convenient commands for building and running benchmarks

.PHONY: help build build-benchmarks clean test benchmark-all benchmark-collision benchmark-collision-analysis benchmark-single-collision benchmark-step

# Default target - show help
help:
	@echo "Physics Engine Command Runner"
	@echo "============================="
	@echo ""
	@echo "Available commands:"
	@echo "  make build                    - Build the project with tests"
	@echo "  make build-benchmarks         - Build the project with benchmarks enabled"
	@echo "  make clean                    - Clean the build directory"
	@echo "  make test                     - Run all unit tests"
	@echo "  make benchmark-all            - Run all benchmarks"
	@echo "  make benchmark-collision      - Run all collision detection benchmarks"
	@echo "  make benchmark-collision-analysis - Run collision benchmarks with complexity analysis"
	@echo "  make benchmark-single-collision - Run single collision resolution benchmark"
	@echo "  make benchmark-step           - Run step function benchmarks"
	@echo ""

# Build targets
build:
	@echo "Building project with tests..."
	@rm -rf build
	@mkdir -p build
	@cd build && cmake .. -DBUILD_TESTING=ON -DBUILD_BENCHMARKS=OFF
	@cd build && make

build-benchmarks:
	@echo "Building project with benchmarks..."
	@rm -rf build
	@mkdir -p build
	@cd build && cmake .. -DBUILD_BENCHMARKS=ON -DBUILD_TESTING=OFF
	@cd build && make benchmark_physics_engine

clean:
	@echo "Cleaning build directory..."
	@rm -rf build

# Test targets  
test:
	@echo "Building and running all unit tests..."
	@echo "This runs the complete test suite to verify physics engine functionality"
	@rm -rf build
	@mkdir -p build
	@cd build && cmake .. -DBUILD_TESTING=ON -DBUILD_BENCHMARKS=OFF
	@cd build && make test_physics_engine
	@cd build && ./test_physics_engine

# Benchmark targets
benchmark-all: build-benchmarks
	@echo "Running all benchmarks..."
	@cd build && ./benchmark_physics_engine --benchmark_time_unit=ns

benchmark-collision: build-benchmarks
	@echo "Running all collision detection benchmarks..."
	@echo "This tests the O(n²) collision detection algorithm with varying particle counts"
	@cd build && ./benchmark_physics_engine --benchmark_filter="BM_Collision*" --benchmark_time_unit=ns

benchmark-collision-analysis: build-benchmarks
	@echo "Running collision detection benchmarks with complexity analysis..."
	@echo "This demonstrates the O(n²) time complexity of the collision detection algorithm"
	@cd build && ./benchmark_physics_engine --benchmark_filter="BM_CollisionDetection" --benchmark_time_unit=ns

benchmark-single-collision: build-benchmarks
	@echo "Running single collision resolution benchmark..."
	@echo "This measures the performance of resolving a collision between two particles"
	@cd build && ./benchmark_physics_engine --benchmark_filter="BM_SingleCollisionResolution" --benchmark_time_unit=ns

benchmark-step: build-benchmarks
	@echo "Running step function benchmarks..."
	@echo "This measures the performance of the complete simulation step with varying particle counts"
	@cd build && ./benchmark_physics_engine --benchmark_filter="BM_StepFunction" --benchmark_time_unit=ns