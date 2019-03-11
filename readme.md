# Udacity Self-Driving Car Engineer Nanodegree

This repository houses my solutions for projects completed as part of Udacity's [Self-driving Car Engineer Nanodegree](https://www.udacity.com/course/self-driving-car-engineer-nanodegree--nd013).


## Projects

### Basic Lane Line Detection
Employ region of interest selection, grayscaling, Gaussian smoothing, Canny Edge Detection and Hough Transform line detection to identify lane lines on the road in an image.

![example](https://user-images.githubusercontent.com/11286381/51013469-73a2f000-1517-11e9-922e-a612674272f1.gif)  
_Simple linearly extrapolated lane detections_


[Rendered notebook](http://nbviewer.jupyter.org/github/markmisener/udacity-self-driving-car-engineer/blob/master/p1-find-lane-lines/P1.ipynb)  
[Project writeup](https://github.com/markmisener/udacity-self-driving-car-engineer/blob/master/p1-find-lane-lines/writeup.md)  
[Source](https://github.com/markmisener/udacity-self-driving-car-engineer/tree/master/p1-find-lane-lines)


### Advanced Lane Line Detection
Find lane markings in images and video using color transformations, gradients, and perspective transformation. Determine the curvature of the lane and the vehicle position with respect to center.

![example](https://user-images.githubusercontent.com/11286381/51013566-093e7f80-1518-11e9-9574-2fdba6eb4f38.gif)  
_Lane detections with curvature and offset_


[Rendered notebook](http://nbviewer.jupyter.org/github/markmisener/udacity-self-driving-car-engineer/blob/master/p2-advanced-lane-line-detection/P2.ipynb)  
[Project writeup](https://github.com/markmisener/udacity-self-driving-car-engineer/blob/master/p2-advanced-lane-line-detection/writeup.md)  
[Source](https://github.com/markmisener/udacity-self-driving-car-engineer/blob/master/p2-advanced-lane-line-detection/)

### Traffic sign classifier
Train and validate a deep learning model using TensorFlow to classify traffic sign images using the German Traffic Sign Dataset.

[Rendered notebook](https://nbviewer.jupyter.org/github/markmisener/udacity-self-driving-car-engineer/blob/master/p3-traffic-sign-classifier/Traffic_Sign_Classifier.ipynb)  
[Project writeup](https://github.com/markmisener/udacity-self-driving-car-engineer/blob/master/p3-traffic-sign-classifier/writeup.md)  
[Source](https://github.com/markmisener/udacity-self-driving-car-engineer/tree/master/p3-traffic-sign-classifier)  

### Behavioral Cloning
Use Udacity's driving simulator to create a dataset to clone driving behavior by training and validating a model using Keras. The model outputs a steering angle to an autonomous vehicle.

![example](https://user-images.githubusercontent.com/11286381/51013753-17d96680-1519-11e9-8edf-ea62b5a30771.gif)  
_Autonomus driving in the simulator_  

[Project writeup](https://github.com/markmisener/udacity-self-driving-car-engineer/blob/master/p4-behavioral-cloning/writeup.md)  
[Source](https://github.com/markmisener/udacity-self-driving-car-engineer/tree/master/p4-behavioral-cloning)

### Extended Kalman Filter
Utilize a Kalman filter, and simulated lidar and radar measurements to track the a bicycle's position and velocity.  

Lidar measurements are red circles, radar measurements are blue circles with an arrow pointing in the direction of the observed angle, and estimation markers are green triangles.

<img width="794" alt="dataset_1" src="https://user-images.githubusercontent.com/11286381/51014070-b1554800-151a-11e9-8690-93b7226af20a.png">  


[Source](https://github.com/markmisener/udacity-self-driving-car-engineer/tree/master/p5-extended-kalman-filters)

### Localization: Particle Filter

A 2 dimensional particle filter in C++. The particle filter is given a map and some initial localization information (analogous to what a GPS would provide). At each time step the filter is also given observation and control data.

[Source](https://github.com/markmisener/udacity-self-driving-car-engineer/tree/master/p6-sparse-particle-filters)
