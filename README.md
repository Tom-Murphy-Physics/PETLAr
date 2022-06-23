# PETLAr

(Positron Emission Tomography (PET) in Liquid Argon (LAr) Time Projection Chambers (TPCs))

## Running The Code

This porject is meant to study the effects of replacing the scintillation material that is traditionally used in PET with a LArTPC.
The code in this repository runs a simulation of the proposed detector. These simulations require GEANT4 and ROOT to run. 
Once those dependencies are setup and this code is downloaded you will need to go into the directory called build.
The next step is to run the command:
```
cmake ..
```
This will create the required cmake files. Now you will need to make the code. This can be done by running the command:
```
make
```
This should make an executable that will run the simulation. The simulation can be run by typing:
```
./PETLAr
```
This should open GEANT4's GUI. To simulate an event type:
```
/run/beamOn
```
and press enter. After a moment this should create some lines that represent the different particles in the detector.
Several shell scripts have been provided in the build directory. These files can be run using:
```
source <file_name>
```
For example the file "do_zit.sh" will iterate over various drift lengths and then do an analysis. 
These analyses are fully automated at this point and can be used as a template should you want to create a new one.

## The Physics
It is probably worth providing some context to the physics of the simulation. PET is a medical imaging technique. Whereby a "tracer" is injected into a patients blood stream to monitor biochemical reactions. These tracers are made of radionuclides attached to a molecule that is used in a certain reaction within the body. This radionuclide will at some point emit a positron and a neutrino via beta plus decay. The neutrino will pass through the body nearly unperturbed. However, the positron will annihilate with a nearby electron. When this happens, the most common result is two photons are emitted. Normally, the initial kinetic energy of the electron and positron are negligible. As a result, the two photons that are produced will be traveling in opposite directions, with the same energy (as seen in the Lab Frame). These photons will each have 511 keV of energy and will usually propagate out of the patient and into a nearby detector. Traditionally segmented crystalline scintillation detectors are used. However, this study looks at replacing those detectors with a LArTPC.

### The Detector 
When this photon enters the detector medium it will collide with one of it's atoms. When this happens an electron will be ejected via Compton scattering and the incident photon will move off in some other direction. These scattering events will continue until either the incident photon deposits all its energy, or more likely it escapes the detector. These scattered electrons will propagate some distance in the detector volume. As they do so they will be excite the neighboring electrons. One of two things will happen to these electrons. Either they will become excited or they will be ionized. If these electrons are excited enough, when they will emit a photon with. These photons are called scintillation photons. These photons can be more easily detected and are produced in quantities great enough that detecting them is feasible. If however, an electrons is ionized, it will propagate some distance all the while interacting with the neighboring atoms. This usually means it will be reabsorbed and not allowed to travel a meaningful distance.


### LArTPCs
Unlike the traditional scintillation material, argon has no valance electrons. Consequently, it will not accept a free floating electron. So the electrons created by the interaction of photons within the detector are free to float around. So, what LArTPCs do is apply a large electric field to these electrons, and drift them to sophisticated electronics that can read out the signal. What this study aims to do is use LArTPCs to gather both charge and light information from the detectors. This could provide higher energy and spatial resolution of where the initial incident photon is in the detector.

### Reconstructing the image
The reason why this is important is because to actually create an image of the body, the two photons that are emitted back to back have to be detected. Once they are detected, a line is drawn between them. A higher resolution means the thinner that line will be and the more accurate it is. To determine where exactly this decay happened one just needs to look at the time when the light was detected. Light moves at a constant speed so if the first photon was detected earlier than the second one, then some simple math can be done to figure out where it happened on that line. When this is done billions of times, an accurate map of the tracer can be made. This tracer is being metabolized so higher concentrations will typically be found in certain parts of the body.

As mentioned before, we need to detect two photons that are traveling back to back. To simplify the math and construction, the detectors are usually built in a ring. However, with traditional detectors, the cost limits the thickness of the ring. However, LArTPCs should reduce costs and allow this ring to be made as thick as a person is long. This would reduce the time it takes to detect the number of photons to create a statistically sound image. This would enable doctors to play all sorts of games adjusting the time, dose, and accuracy to better accommodate their patients.
