# SingleFileHardDisks

This is the source code accompanying [1] to solve the for the thermodynamic equilibrium properties (equation of state, transverse density profile) of the single-file hard disks fluid, as described in [1], using the transition matrix approach first proposed in [2].

## :ferris_wheel: Dependencies

The source code is provided as a C++ project and has the following prerequisites
- gcc (tested in gcc 11.2.0) or a compatible compiler.
- [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) library
- Make
- git

## :classical_building: Compilation

The project is provided ready to be compiled under Linux platforms
1. `` git clone  https://github.com/amonterouex/SingleFileHardDisks.git``
2. `` cd SingleFileHardDisks ``
4. Make sure the location of your local Eigen library matches the standard one provided in line
`` EIGEN = /usr/include/eigen3/``
of the Makefile. If not, modify that line to point at the correct Eigen location.
3. `` make ``

## :airplane: Execution

The correct compilation of the source code should produce two executables:

### main_DensityProfile.exe

Given an excess pore size $\epsilon$, a specific pressure value $p$ and a discretization parameter $M$, it computes the corresponding linear density of the system.

If required, it writes and output file density_profile.txt containing information about the transverse density profile in a column-like format, the first column being the values of the $y \in [-\epsilon/2, \epsilon/2]$ direction and the second column being the normalized probability density at that point.


### main_EquationOfState.exe

Given an excess pore size $\epsilon$, a the minimum and maximum values of a certain pressure range, $pmin$ and $pmax$, the number of pressure values to compute inside that range and a discretization parameter $M$, it computes the corresponding linear density for the corresponding pressure range and outputs a file equation_of_state.txt containing information about the equation of estate in a column-like format. The first column corresponding to linear density values and the second column being their corresponding compressibility factor value.

## :chart_with_upwards_trend: Plotting

Two gnuplot scripts are provided to directly plot the output files of both executables:
- plot_DensityProfile -> plots the density profiles information contained in density_profile.txt
- plot_EquationOfState -> plots the equation of state information contained in equation_of_state.txt

To use them, first make sure you have gnuplot installed. Then, run ``gnuplot plot_DensityProfile`` or ``gnuplot plot_EquationOfState``

## :envelope_with_arrow: Contact

If you have trouble compiling or using this software, if you found a bug or if you have an important feature request, you may contact us at <anamontero@unex.es>

## :books: References
[1] Ana M. Montero and A. Santos, Equation of State of Hard-Disk Fluids under Single-File Confinement, 	[arXiv:2212.08932](https://arxiv.org/abs/2212.08932)

[2] D. A. Kofke and A. J. Post, Hard particles in narrow pores. Transfer-matrix solution and the periodic narrow box. J. Chem. Phys., **98**, 4853-486 (1993)
