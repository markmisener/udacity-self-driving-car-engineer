# **Behavioral Cloning**

## Writeup Template

### You can use this file as a template for your writeup if you want to submit it as a markdown file, but feel free to use some other method and submit a pdf if you prefer.

---

**Behavioral Cloning Project**

The goals / steps of this project are the following:
* Use the simulator to collect data of good driving behavior
* Build, a convolution neural network in Keras that predicts steering angles from images
* Train and validate the model with a training and validation set
* Test that the model successfully drives around track one without leaving the road
* Summarize the results with a written report

## Rubric Points
### Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/432/view) individually and describe how I addressed each point in my implementation.  

---
### Files Submitted & Code Quality

#### 1. Submission includes all required files and can be used to run the simulator in autonomous mode

My project includes the following files:
* model.py containing the script to create and train the model
* drive.py for driving the car in autonomous mode
* model.h5 containing a trained convolution neural network
* writeup.md summarizing the results

#### 2. Submission includes functional code
Using the Udacity provided simulator and my drive.py file, the car can be driven autonomously around the track by executing
```sh
python drive.py model.h5
```

#### 3. Submission code is usable and readable

The model.py file contains the code for training and saving the convolution neural network. The file shows the pipeline I used for training and validating the model, and it contains comments to explain how the code works.

### Model Architecture and Training Strategy

#### 1. An appropriate model architecture has been employed

My model consists of a convolution neural network modeled after NVIDIA's (End to End Learning for Self-Driving Cars)[https://images.nvidia.com/content/tegra/automotive/images/2016/solutions/pdf/end-to-end-dl-using-px.pdf].

The model includes RELU layers to introduce nonlinearity (first example: model.py line 98), and the data is normalized in the model using a Keras lambda layer (model.py line 97).

#### 2. Attempts to reduce overfitting in the model

The model contains multiple dropout layers in order to reduce overfitting (first example: model.py lines 99).

The model was trained and validated on different data sets to ensure that the model was not overfitting (model.py function load_data lines 55-82). The model was tested by running it through the simulator and ensuring that the vehicle could stay on the track.

#### 3. Model parameter tuning

The model used an Adam optimizer, so the learning rate was not tuned manually (model.py line 170).

#### 4. Appropriate training data

I used the data provided by Udacity as a starting place for training my model. The model architecture and the given data led to the car drifting off the track at the first sharp turn by the lake. Because of this, I decided it was best to include some additionaly training data focused on recovering from drifting. I captured data of the car recovering from the left and right sides of the road in both the forward and reverse direction on the track.

### Model Architecture and Training Strategy

#### 1. Solution Design Approach

The overall strategy for deriving a model architecture was to build off existing research completed by experts in the field and fine-tune the model to my data.

My first step was to use a convolution neural network model similar to the NVIDIA End to End Learning for Self-Driving Cars. I thought this model might be appropriate because it is a similar use case and was suggested in the course notes.

In order to gauge how well the model was working, I split my image and steering angle data into a training and validation set. I found that my first model had a low mean squared error on the training set but a high mean squared error on the validation set. This implied that the model was overfitting.

To combat the overfitting, I modified the model to include multiple Dropout layers with a keep_prob of 0.5.

Then I captured training data in which the car was driven the reserve direction around the course. Additionally, I included a random augmentation function which randomly selected images in the training set to be flipped horizontally or had the image's brightness adjusted randomly.

The final step was to run the simulator to see how well the car was driving around track one. There were a few spots where the vehicle fell off the track. To improve the driving behavior in these cases, I captured recovery data from both the left and right sides of the track.

At the end of the process, the vehicle is able to drive autonomously around the track without leaving the road.

#### 2. Final Model Architecture

The final model architecture (model.py lines 95-11) consisted of a convolution neural network with the following layers and layer sizes:

- Cropping2D (removing unneeded top/bottom of the image)
- Lambda (normalization of the image)
- Conv2D(24, (5, 5), strides=(2, 2), activation='relu')
- Dropout(0.5)
- Conv2D(36, (5, 5), strides=(2, 2), activation='relu')
- Conv2D(48, (5, 5), strides=(2, 2), activation='relu')
- Dropout(0.5)
- Conv2D(64, (3, 3), activation='relu')
- Conv2D(64, (3, 3), activation='relu')
- Dropout(0.5)
- Flatten()
- Dense(100)
- Dense(50)
- Dropout(0.5)
- Dense(10)
- Dense(1)

#### 3. Creation of the Training Set & Training Process

To capture good driving behavior, I used the data provided by Udacity:

![alt text][image2]

I then recorded the vehicle recovering from the left side and right sides of the road back to center so that the vehicle would learn to correct toward the center of the lane. These images show what a recovery looks:

![alt text][image3]
![alt text][image4]

To augment the data sat, I also flipped images and angles thinking that this would ... For example, here is an image that has then been flipped:

![alt text][image6]
![alt text][image7]
