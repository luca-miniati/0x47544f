# 0x47544f - Advanced Poker Solver & Visualization Suite

0x47544f (hex for "GTO") is a high-performance No-Limit Hold'Em solver with real-time visualization capabilities. This project aims to be the most comprehensive open-source poker solving and training tool available.

## Core Features

### Solver Engine
- **Preflop Solver**
  - Small Blind vs Big Blind scenarios
  - Advanced CFR (Counterfactual Regret Minimization) implementation
  - Highly optimized C++ core for maximum performance
  - Support for custom starting stack depths
  - Configurable rake and equity realization adjustments

## Planned Features

### Solver Expansion
- Complete postflop solver implementation

### Visualization Enhancements
- Real-time strategy visualization using modern C++ graphics
- Dynamic range viewers showing:
  - Frequency breakdowns for each action
  - EV (Expected Value) calculations
  - Equity distributions
- Interactive decision trees
- Heat maps for different stack depths
- Customizable color schemes for visualization

## Technical Details

### Architecture
- Modern C++20 implementation
- Optimized card evaluation engine
- Custom memory management
- Efficient game state representation
- Advanced caching mechanisms

### Performance
- Highly optimized lookup tables
- Efficient bit manipulation for card operations
- Smart memory allocation for game trees
- Vectorized operations where possible

## Building & Development

### Prerequisites
- CMake 3.15+
- Modern C++ compiler with C++20 support
- Graphics libraries (coming soon)

### Build Instructions

```
mkdir build
cd build
cmake ..
make
```

## Contributing

We welcome contributions! Whether you're interested in:
- Solver optimizations
- UI/UX improvements
- Documentation
- Testing and validation
- New feature implementation

Please read our contributing guidelines before submitting PRs.

## License

This project is licensed under [LICENSE TBD] - see the LICENSE file for details.

## Acknowledgments

Special thanks to:
- The poker theory community
- Contributors to poker solving algorithms
- Open-source graphics libraries

## Contact

For questions, suggestions, or collaboration opportunities:
- GitHub Issues
- email miniati.l@northeastern.edu or gandhi.mar@northeastern.edu

---

*Note: 0x47544f is currently under active development. Some features mentioned are in progress or planned for future releases.*