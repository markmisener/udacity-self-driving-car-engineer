**Advanced Lane Finding Project**

The goals / steps of this project are the following:

* Compute the camera calibration matrix and distortion coefficients given a set of chessboard images.
* Apply a distortion correction to raw images.
* Use color transforms, gradients, etc., to create a thresholded binary image.
* Apply a perspective transform to rectify binary image ("birds-eye view").
* Detect lane pixels and fit to find the lane boundary.
* Determine the curvature of the lane and vehicle position with respect to center.
* Warp the detected lane boundaries back onto the original image.
* Output visual display of the lane boundaries and numerical estimation of lane curvature and vehicle position.


## [Rubric](https://review.udacity.com/#!/rubrics/571/view) Points

### Here I will consider the rubric points individually and describe how I addressed each point in my implementation.  

---

### Camera Calibration

#### 1. Briefly state how you computed the camera matrix and distortion coefficients. Provide an example of a distortion corrected calibration image.

The code for this step is contained in the first code cell of the IPython notebook located in `P2.ipynb`.  

I start by preparing the "object points", which correspond to the (x, y, z) coordinates of the chessboard corners. Here I am assuming the chessboard is fixed on the (x, y) plane at z=0, such that the object points are the same for each calibration image.  Thus, `objp` is just a replicated array of coordinates, and `objpoints` will be appended with a copy of it every time I successfully detect all chessboard corners in a test image.  `imgpoints` will be appended with the (x, y) pixel position of each of the corners in the image plane with each successful chessboard detection.  

I then used the output `objpoints` and `imgpoints` to compute the camera calibration and distortion coefficients using the `cv2.calibrateCamera()` function.  I applied this distortion correction to the test image using the `cv2.undistort()` function and obtained this result:

![undistorted](https://user-images.githubusercontent.com/11286381/49201283-2c8ce100-f355-11e8-8eae-62797eed24ca.png)

### Pipeline (single images)

#### 1. Provide an example of a distortion-corrected image.

To demonstrate this step, I will describe how I apply the distortion correction to one of the test images like this one:
![undistorted](https://user-images.githubusercontent.com/11286381/49201283-2c8ce100-f355-11e8-8eae-62797eed24ca.png)

#### 2. Describe how (and identify where in your code) you used color transforms, gradients or other methods to create a thresholded binary image.  Provide an example of a binary image result.

I used a combination of color and gradient thresholds to generate a binary image (thresholding steps at lines # through # in `another_file.py`).  Here's an example of my output for this step.  (note: this is not actually from one of the test images)

**Color channels:**  
![blue_channel](https://user-images.githubusercontent.com/11286381/49201351-7249a980-f355-11e8-8458-c9e37335bfe9.png)
![green_channel](https://user-images.githubusercontent.com/11286381/49201353-7249a980-f355-11e8-970a-66cc17d7299a.png)
![red_channel](https://user-images.githubusercontent.com/11286381/49201366-737ad680-f355-11e8-8c90-6df8bc31e3b4.png)
![white_channel](https://user-images.githubusercontent.com/11286381/49201367-737ad680-f355-11e8-9613-b7fe40cd5595.png)
![yellow_channel](https://user-images.githubusercontent.com/11286381/49201368-737ad680-f355-11e8-9e2f-6eddbb35a4c5.png)

**HSV channels:**  
![hsv_hue_channel](https://user-images.githubusercontent.com/11286381/49201362-72e24000-f355-11e8-953c-be2592367d6b.png)
![hsv_saturation_channel](https://user-images.githubusercontent.com/11286381/49201364-737ad680-f355-11e8-814c-b8a925835ba7.png)
![hsv_value_channel](https://user-images.githubusercontent.com/11286381/49201365-737ad680-f355-11e8-9021-d95543ae7b16.png)

**HLS channels:**  
![hls_hue_channel](https://user-images.githubusercontent.com/11286381/49201356-7249a980-f355-11e8-8de3-ac7d7235dcde.png)
![hls_light_channel](https://user-images.githubusercontent.com/11286381/49201357-72e24000-f355-11e8-8295-b8ae53b19b05.png)
![hls_saturation_channel](https://user-images.githubusercontent.com/11286381/49201359-72e24000-f355-11e8-9969-43d26f79d919.png)

**Final combined image:**  
![combined_binary](https://user-images.githubusercontent.com/11286381/49201352-7249a980-f355-11e8-8f91-b50f20af4656.png)

#### 3. Describe how (and identify where in your code) you performed a perspective transform and provide an example of a transformed image.

The code for my perspective transform includes a function called `apply_perspective_transform()`, which appears in lines 1 through 8 in the file `example.py` (output_images/examples/example.py) (or, for example, in the 3rd code cell of the IPython notebook).  The `apply_perspective_transform()()` function takes as inputs an image (`img`), as well as source (`src`) and destination (`dst`) points.  I chose the hardcode the source and destination points in the following manner:

```python
src = np.float32([[560,460],[180,690],[1130,690],[750,460]])
dst = np.float32([[320,0],[320,720],[960,720],[960,0]])
```

This resulted in the following source and destination points:

| Source        | Destination   |
|:-------------:|:-------------:|
| 560, 460      | 320, 0        |
| 180, 690      | 320, 720      |
| 1130, 690     | 960, 720      |
| 750, 460      | 960, 0        |

I verified that my perspective transform was working as expected by drawing the `src` and `dst` points onto a test image and its warped counterpart to verify that the lines appear parallel in the warped image. In the first image, red points represent the source image and blue points represent the destination.

![p_transform_points](https://user-images.githubusercontent.com/11286381/49202811-c73bee80-f35a-11e8-92aa-d3a91a9aded6.png)
![p_transform](https://user-images.githubusercontent.com/11286381/49202813-c73bee80-f35a-11e8-9729-88ca83eea4b7.png)


#### 4. Describe how (and identify where in your code) you identified lane-line pixels and fit their positions with a polynomial?

Then I did some other stuff and fit my lane lines with a 2nd order polynomial kinda like this:

![pipeline_polyfit](https://user-images.githubusercontent.com/11286381/49204382-9494f480-f360-11e8-8ed0-a8ea26e796c2.png)

#### 5. Describe how (and identify where in your code) you calculated the radius of curvature of the lane and the position of the vehicle with respect to center.

I did this in lines # through # in my code in `my_other_file.py`

#### 6. Provide an example image of your result plotted back down onto the road such that the lane area is identified clearly.

I implemented this step in lines # through # in my code in `yet_another_file.py` in the function `map_lane()`.  Here is an example of my result on a test image:

![pipeline_lane_detection](https://user-images.githubusercontent.com/11286381/49204381-9494f480-f360-11e8-8df8-ccc6f4807912.png)

---

### End to end:
![pipeline_corrected](https://user-images.githubusercontent.com/11286381/49204380-9494f480-f360-11e8-9e69-6b24b1e22b92.png)
![pipeline_binary](https://user-images.githubusercontent.com/11286381/49204379-9494f480-f360-11e8-8c9c-0aae7e71142d.png)
![pipeline_binary_warped](https://user-images.githubusercontent.com/11286381/49204378-93fc5e00-f360-11e8-8007-591361c08211.png)
![pipeline_roi](https://user-images.githubusercontent.com/11286381/49204383-9494f480-f360-11e8-99a5-35483b21ee50.png)
![pipeline_polyfit](https://user-images.githubusercontent.com/11286381/49204382-9494f480-f360-11e8-8ed0-a8ea26e796c2.png)
![pipeline_lane_detection](https://user-images.githubusercontent.com/11286381/49204381-9494f480-f360-11e8-8df8-ccc6f4807912.png)




---

### Pipeline (video)

#### 1. Provide a link to your final video output.  Your pipeline should perform reasonably well on the entire project video (wobbly lines are ok but no catastrophic failures that would cause the car to drive off the road!).

[![screencap](https://img.youtube.com/vi/-ew4mhf7ZQI/0.jpg)](https://www.youtube.com/watch?v=-ew4mhf7ZQI)

Here's a [link to my download my video result](https://github.com/markmisener/udacity-self-driving-car-engineer/blob/master/p2-advanced-lane-line-detection/output_video/lane_tracking.mp4)



---

### Discussion

#### 1. Briefly discuss any problems / issues you faced in your implementation of this project.  Where will your pipeline likely fail?  What could you do to make it more robust?

Here I'll talk about the approach I took, what techniques I used, what worked and why, where the pipeline might fail and how I might improve it if I were going to pursue this project further.  
