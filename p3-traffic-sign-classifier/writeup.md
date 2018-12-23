# **Traffic Sign Recognition**

**Build a Traffic Sign Recognition Project**

The goals / steps of this project are the following:
* Load the data set (see below for links to the project data set)
* Explore, summarize and visualize the data set
* Design, train and test a model architecture
* Use the model to make predictions on new images
* Analyze the softmax probabilities of the new images
* Summarize the results with a written report

## Rubric Points
### Here I will consider the [rubric points](https://review.udacity.com/#!/rubrics/481/view) individually and describe how I addressed each point in my implementation.  

---
### Writeup / README

#### 1. Provide a Writeup / README that includes all the rubric points and how you addressed each one. You can submit your writeup as markdown or pdf. You can use this template as a guide for writing the report. The submission includes the project code.

You're reading it! and here is a link to my [project code](https://github.com/markmisener/udacity-self-driving-car-engineer/blob/master/p3-traffic-sign-classifier/Traffic_Sign_Classifier.ipynb)

### Data Set Summary & Exploration

#### 1. Provide a basic summary of the data set. In the code, the analysis should be done using python, numpy and/or pandas methods rather than hardcoding results manually.

I used the the numpy array `shape` attribute and numpy's `unique()` method to calculate summary statistics of the traffic
signs data set:

* The size of training set is 34,799
* The size of the validation set is 4,410
* The size of test set is 12,630
* The shape of a traffic sign image is 32x32
* The number of unique classes/labels in the data set is 43

#### 2. Include an exploratory visualization of the dataset.

Here is an exploratory visualization of the data set. It is a bar chart showing the frequency of each traffic sign in the training data set.

![image](https://user-images.githubusercontent.com/11286381/50388253-5a9be180-06c5-11e9-8d4d-9f7bc628cf37.png)

### Design and Test a Model Architecture

#### 1. Describe how you preprocessed the image data. What techniques were chosen and why did you choose these techniques? Consider including images showing the output of each preprocessing technique. Pre-processing refers to techniques such as converting to grayscale, normalization, etc. (OPTIONAL: As described in the "Stand Out Suggestions" part of the rubric, if you generated additional data for training, describe why you decided to generate additional data, how you generated the data, and provide example images of the additional data. Then describe the characteristics of the augmented training set like number of images in the set, number of images for each class, etc.)

The first preprocessing technique I used was converting the images to grayscale. I then normalized the dataset to have a mean zero and equal variance, as suggested in the project notes. After training, I was able to achieve 93% test accuracy with these techniques, so I did not attempt any additional preprocessing.


#### 2. Describe what your final model architecture looks like including model type, layers, layer sizes, connectivity, etc.) Consider including a diagram and/or table describing the final model.

My final model consisted of the following layers:

| Layer         		    |     Description	        					            |
|:---------------------:|:---------------------------------------------:|
| Input         		    | 32x32x3 RGB image   							            |
| Convolution 5x5     	| 1x1 stride, valid padding, outputs 28x28x6 	  |
| RELU					        |												                        |
| Max pooling	      	  | 2x2 stride, valid padding, outputs 14x14x6 		|
| Convolution 5x5	      | 1x1 stride, valid padding, outputs 10x10x16   |
| RELU					        |												                        |
| Max pooling	      	  | 2x2 stride,  valid padding, outputs 5x5x16 		|
| Fully connected		    | input 400, output 120        									|
| RELU					        |												                        |
| Dropout				        | 50% keep        									            |
| Fully connected		    | input 120, output 84        									|
| RELU					        |												                        |
| Dropout				        | 50% keep        									            |
| Fully connected		    | input 84, output 43        									  |


#### 3. Describe how you trained your model. The discussion can include the type of optimizer, the batch size, number of epochs and any hyperparameters such as learning rate.

To train the model, I used an an Adam optimizer to minimize the cross entropy loss. The hyperparameters used to train the model were:

| Parameter      | Value	 |
|:--------------:|:-------:|
| Epochs         | 150     |
| Batch size     | 128 	   |
| Dropout				 | 0.5		 |
| Learning Rate	 | 0.0001  |


#### 4. Describe the approach taken for finding a solution and getting the validation set accuracy to be at least 0.93. Include in the discussion the results on the training, validation and test sets and where in the code these were calculated. Your approach may have been an iterative process, in which case, outline the steps you took to get to the final solution and why you chose those steps. Perhaps your solution involved an already well known implementation or architecture. In this case, discuss why you think the architecture is suitable for the current problem.

My final model results were:
* training set accuracy of 0.992
* validation set accuracy of 0.944
* test set accuracy of 0.934

If a well known architecture was chosen:
* What architecture was chosen?

To train the model, I used the LeNet architecture.

* Why did you believe it would be relevant to the traffic sign application?

The LeNet architecture performs well on recognition tasks with tens of classes.

* How does the final model's accuracy on the training, validation and test set provide evidence that the model is working well?

Because the training accuracy, validation accuracy, and test accuracy are all high, we see no evidence the model is over or under fitting.

### Test a Model on New Images

#### 1. Choose five German traffic signs found on the web and provide them in the report. For each image, discuss what quality or qualities might be difficult to classify.

Here are five German traffic signs that I found on the web:

![image](https://user-images.githubusercontent.com/11286381/50388257-6c7d8480-06c5-11e9-86f5-d84a66f2951e.png)

Each of these images might be difficult for the model to classify due to:
- These new images don't have a background, as the images in the training set do.
- The speed limit signs are all very similar.

#### 2. Discuss the model's predictions on these new traffic signs and compare the results to predicting on the test set. At a minimum, discuss what the predictions were, the accuracy on these new predictions, and compare the accuracy to the accuracy on the test set (OPTIONAL: Discuss the results in more detail as described in the "Stand Out Suggestions" part of the rubric).

Here are the results of the prediction:

| Image			            | Prediction	        					            |
|:---------------------:|:-----------------------------------------:|
| Children crossing     | Children crossing   				              |
| General Caution       | General Caution     				              |
| Speed limit (120km/h) | Vehicles over 3.5 metric tons prohibited  |
| Speed limit (60km/h)  | Speed limit (60km/h)   				            |
| Stop                  | Stop                 				              |

The model was able to correctly guess 4 of the 5 traffic signs, which gives an accuracy of 80%. This compares favorably to the accuracy on the test set of 93%. Given more images to classify, I imagine the accuracy would end up around the test accuract of 93%.
