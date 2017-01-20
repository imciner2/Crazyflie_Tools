# Crazyflie Trackable Marker Frame

This trackable frame is based off of the original design done by Ben Landry and Pete Florence from the MIT CSAIL Lab.
The frame is described here: http://groups.csail.mit.edu/robotics-center/public_papers/Landry15.pdf, with the original CAD files here: https://github.com/peteflorence/crazyflie-CAD.


## Modifications

The frame here has been modified in 2 ways:
 * The marker holder lengths were modified to all be different lengths (originally 2 were the same length)
 * The side struts were reinforced by making the material thicker and wider.

## Part Analysis

Analysis of this part was done assuming it is printed by Shapeways, using the Strong & Flexible Plastic material.
The data about the material used can be found here: https://www.shapeways.com/rrstatic/material_docs/mds-strongflex.pdf

The results of that analysis is as follows:
| Property | Value    | Units  |
| -------- | -------- | ------ |
| Mass     | 1.38e-3  | kg     |
| Ixx      | 1.572e-6 | kg*m^2 |
| Iyy      | 1.874e-6 | kg*m^2 |
| Izz      | 3.445e-6 | kg*m^2 |

 
## Files
 * MassProperties-cg.pdf - Contains the mass & Moment of Inertia calculated for this part in units of grams and centimeters
 * Massproperties-kgm.pdf - Contains the mass & Moment of Inertia calculated for this part in units of kilograms and meters
 * PartRendering.pdf - A rendering of the part showing the output axis system
 * TrackableFrame-Version-01.SLDPRT - The SolidWorks file for the frame
 * TrackableFrame-Version-01.STL - STL version of the 3D model