<h1 align="center">Dynamic Elevator Counterweight</h1>
<p align="center"><strong>MECHATRONICS | LOAD SENSING | MOTION CONTROL</strong></p>
<p align="center"><a href="https://github.com/Kaveesha229">Kaveesha Gunawardena | Engineering portfolio</a></p>

## Overview

A mechatronics prototype exploring liquid based counterweight adjustment for an elevator model. The controller compares load readings and operates transfer outputs before moving between floor positions.

## Repository guide

<table>
<tr><th>File or folder</th><th>Purpose</th></tr>
<tr><td><a href="to_left_elevator.ino">to_left_elevator.ino</a></td><td>Root controller sketch</td></tr>
<tr><td><a href="IDP/Final/to_left_elevator/to_left_elevator.ino">IDP/Final/to_left_elevator/to_left_elevator.ino</a></td><td>Controller copy inside the development folder</td></tr>
<tr><td><a href="https://github.com/Kaveesha229/Liquid%2Dbased%2Ddynamic%2Dcounterweight%2Dsystem%2Dto%2Doptimize%2Delevator%2Denergy%2Dusage%2Dbased%2Don%2Dload./tree/main/IDP">IDP</a></td><td>Component tests and development sketches</td></tr>
<tr><td><a href="IMDP%20REPORT.pdf">IMDP REPORT.pdf</a></td><td>Project report</td></tr>
</table>

## System overview

Two HX711 interfaces measure the lift and counterweight loads. Relay outputs control liquid transfer, a step and direction interface drives motion, and infrared inputs indicate floor positions. The sketch also contains ultrasonic tank monitoring and separate static and dynamic operating paths.

## Controller connections

<table>
<tr><th>Function</th><th>Pins</th></tr>
<tr><td>Stepper direction, step, enable</td><td>53, 52, 34</td></tr>
<tr><td>Load cell interface 1 data and clock</td><td>45, 44</td></tr>
<tr><td>Load cell interface 2 data and clock</td><td>43, 42</td></tr>
<tr><td>Floor sensors</td><td>51, 50, 49</td></tr>
<tr><td>Floor buttons</td><td>48, 47, 46</td></tr>
<tr><td>Mode input</td><td>32</td></tr>
<tr><td>Bottom, top and middle relays</td><td>37, 38, 39</td></tr>
<tr><td>Ultrasonic trigger and echo</td><td>36, 35</td></tr>
</table>

## Getting started

1. Open the controller sketch on a board supporting the listed pins, such as an Arduino Mega class board.
2. Install a compatible `HX711` library and verify the wiring against the prototype.
3. Calibrate both load cells. The current scale value of 420 is specific to the existing setup.
4. Confirm floor sensor polarity, transfer direction and travel limits before enabling motion.
5. Use Serial Monitor at 9600 baud and test each subsystem separately before the combined sequence.

## Implementation notes

The mode input selects the static or dynamic path. Several transfer and motion loops wait for a sensor condition without a timeout, so they need supervised prototype testing. The code alone does not establish energy savings.

## Evaluation

Compare total energy for static and dynamic operation under the same load and travel conditions, including energy used for liquid transfer. Measured savings should be reported only with the test method and recorded results.

## Project media

Photos and demonstration videos will be added here as the project presentation is updated.

<p align="center"><sub>Practical engineering through building, testing and refinement.</sub></p>
