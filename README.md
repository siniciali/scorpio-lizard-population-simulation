=====================================================================
# Project 2024-25 - Simulation of a Predator-Prey Model with Vibration Detection
# Group 01 - Bruno Siniciali and Samuele Sattar

### Introduction ###

The purpose of this program consists of two main aspects in a "predator-prey" context:

- Simulating the dynamics of animal population evolution.
- Simulating neuronal models related to animal behaviors.

The objective is to simulate the coexistence of lizards and scorpions in an ecosystem.
Scorpions feed on lizards, which feed on cacti.

This will be done at two scales:

- **Population scale**: Simulate the complete life cycles of animals
    (movement, food consumption, predation, reproduction, and death).

- **Individual scale**: Simulate the detection of lizards by scorpions using a specific neuronal model:
    vibrations from lizard movements induce neuronal stimuli in the scorpion, conditioning its orientation towards its prey.

The animals are automatons moving randomly on a two-dimensional toric terrain in search of food.
If a food source is present in their field of vision, they move towards it and consume it.
They have a limited lifespan and die if they run out of food.
They can also reproduce and preys are intelligent enough to try to escape predators.
In the neuronal simulation, lizards emit circular vibration waves that expand around them.
Scorpions are capable of detecting these waves and move towards the source.
Rocks can block the propagation of the wave and scorpions behind rocks are uncapable of percieving any signal.

***
NOTE: when testing the neuronal simulation model, a proper feeding behaviour for scorpions is not implemented,
since the goal of this part of the simulation is to modelize vibrations detection and neuronal stimuli in scorpions.
Therefore, in the "Waves" part of the simulation, the vibration-receptive scorpions will simply chase the lizards in sight
without eating them.
***

### Compilation and Execution ###

This project uses [Cmake](https://cmake.org/) for compilation.

* In QTCreator:
    - Set up the project: open the `src/CmakeLists.txt` file
    - Choose the target to execute by adding or removing "#" from the four specific lines.
    ***
    NOTE: Target Titles (i.e "Main Application, line 83 and 152) are given to improve clearness
    in the choice of the targets to execute.)
    ***

### Main Targets ###

* `application` -> corresponds to the final application, the complete simulation (lines 84-85 and 153-154 in the CMakeLists file).

### Project Structure ###

* Configuration files are accessible via res/app3.Json

### Test Specificity ###

*   For `ColliderTest.cpp`, we had to add the `draw` and `update` functions in the `Body` class
    that inherits from `Collider` for the test to work.

*   For `TargetInSightTest.cpp` to work, you need to return to step 2 of the project because otherwise the `DummyAnimal`
    class is a pure virtual class that cannot be instantiated due to the pure virtual methods present in it.

*   The `envTest`, `chasingTest`, and `animalTest` only work in step 2.

*   The `ppsTest` works well in step 5.

*   The `reproductionTest` works well in step 5 and depends on `app3.json`.

*   The `waveTest` works well in step 5 and depends on `app3.json`.

*   The `neuronalTest` works well in step 5 and depends on `app3.json`.

*   The `FinalApplication` works well in step 5 and depends on `app3.json`.

### Commands ###

The commands for the simulation are provided in a help panel on the left side of the simulation window.

### Design Modifications ###

The project was coded in accordance with the given project instructions (no personal modifications to the suggested design elements).

### Extensions ###

*   The `Waves` section of the program when running `FinalApplication` disposes of new commands to spawn:
    - Rocks with "O"
    - Cacti with "G".
    The help panel had been consequently modified to display these new two functions along with
    the commands to spawn a WaveLizard (W) and a NeuronalScorpion (N).
