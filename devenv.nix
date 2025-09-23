{ pkgs, ... }:

{
  packages = with pkgs; [
    cmake
    ninja
    gcc11
    gdb
    valgrind
    pkg-config
  ];

  languages.cplusplus = {
    enable = true;
  };

  languages.javascript = {
    enable = true;
    yarn = {
      enable = true;
      install.enable = true;
    };
  };

  pre-commit.hooks = {
    clang-format.enable = true;
  };

  enterShell = ''
    echo "C++20 Physics Engine Development Environment"
    echo "CMake: $(cmake --version | head -n1)"
    echo "GCC: $(gcc --version | head -n1)"
    echo ""
    echo "Available commands:"
    echo "  cmake -B build -S . -G Ninja  # Configure build"
    echo "  cmake --build build           # Build project"
    echo "  cmake --build build --target test  # Run tests"
  '';
}