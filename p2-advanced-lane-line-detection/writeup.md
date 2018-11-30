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

![camera_undistorted](https://user-images.githubusercontent.com/11286381/49229739-01c97980-f3a3-11e8-8e55-04da919dc15b.png)

### Pipeline (single images)

#### 1. Provide an example of a distortion-corrected image.

After computing the camera calibration an distortion coefficients using the `cv2.calibrateCamera()` function as explained above, I applied the distortion correction to an image as the first step in the image pipeline.

The output of this step looks like this:
![undistorted](https://user-images.githubusercontent.com/11286381/49201283-2c8ce100-f355-11e8-8eae-62797eed24ca.png)

#### 2. Describe how (and identify where in your code) you used color transforms, gradients or other methods to create a thresholded binary image.  Provide an example of a binary image result.

In the `Image layers and masks` section of my notebook, I experimented with various image layers and masks to eyeball which might be included to create the best combined binary image. Below are the results.

**Color channels:**  
I experimented with different color channels/masks to try to isolate the lane lines as much as possible, while attempting to minimize the number of non-lane items. Ultimately the channels I decided to include were the blue channel, white channel, and yellow channel.

![blue_channel](https://user-images.githubusercontent.com/11286381/49201351-7249a980-f355-11e8-8458-c9e37335bfe9.png)
![green_channel](https://user-images.githubusercontent.com/11286381/49201353-7249a980-f355-11e8-970a-66cc17d7299a.png)
![red_channel](https://user-images.githubusercontent.com/11286381/49201366-737ad680-f355-11e8-8c90-6df8bc31e3b4.png)
![white_channel](https://user-images.githubusercontent.com/11286381/49201367-737ad680-f355-11e8-9613-b7fe40cd5595.png)
![yellow_channel](https://user-images.githubusercontent.com/11286381/49201368-737ad680-f355-11e8-9e2f-6eddbb35a4c5.png)

**HSV channels:**  
I converted the image to HSV color space (Hue, Saturation, Value) and again attempted to isolate the lane lanes. The saturation channel appeared to provide the most contrast between the lane lines and the rest of the image.

![hsv_hue_channel](https://user-images.githubusercontent.com/11286381/49201362-72e24000-f355-11e8-953c-be2592367d6b.png)
![hsv_saturation_channel](https://user-images.githubusercontent.com/11286381/49201364-737ad680-f355-11e8-814c-b8a925835ba7.png)
![hsv_value_channel](https://user-images.githubusercontent.com/11286381/49201365-737ad680-f355-11e8-9021-d95543ae7b16.png)

**HLS channels:**  
I also tried isolating the lines by converting the image to HLS color space (Hue, Light, Saturation). The saturation channel was the best in this color space.
![hls_hue_channel](https://user-images.githubusercontent.com/11286381/49201356-7249a980-f355-11e8-8de3-ac7d7235dcde.png)
![hls_light_channel](https://user-images.githubusercontent.com/11286381/49201357-72e24000-f355-11e8-8295-b8ae53b19b05.png)
![hls_saturation_channel](https://user-images.githubusercontent.com/11286381/49201359-72e24000-f355-11e8-9969-43d26f79d919.png)

**Final combined image:**  
I combined the blue, white, yellow, HSV saturation, and HLS saturation channels with a sobelx gradient to create the combined binary image, seen below:
![combined_binary](https://user-images.githubusercontent.com/11286381/49201352-7249a980-f355-11e8-8f91-b50f20af4656.png)

The final code used in the image and video pipelines can be seen in the `get_combined_binary_img()` function in the `Detect lanes in single images` section of the notebook.

#### 3. Describe how (and identify where in your code) you performed a perspective transform and provide an example of a transformed image.

The code for my perspective transform includes a function called `apply_perspective_transform()`, which appears in the `Detect lanes in single images` section of my notebook.  The `apply_perspective_transform()()` function takes in an image (`img`) as the only input, and used hardcoded values for source (`src`) and destination (`dst`) points. I verified that my perspective transform was working as expected by drawing the `src` and `dst` points onto a test image and its warped counterpart to verify that the lines appear parallel in the warped image. In the first image, red points represent the source image and blue points represent the destination.

This resulted in the following source and destination points:

| Source        | Destination   |
|:-------------:|:-------------:|
| 560, 460      | 320, 0        |
| 180, 690      | 320, 720      |
| 1130, 690     | 960, 720      |
| 750, 460      | 960, 0        |

![p_transform_points](https://user-images.githubusercontent.com/11286381/49202811-c73bee80-f35a-11e8-92aa-d3a91a9aded6.png)

![p_transform](https://user-images.githubusercontent.com/11286381/49202813-c73bee80-f35a-11e8-9729-88ca83eea4b7.png)


The final code used in the image and video pipelines can be seen in the `apply_perspective_transform()` function in the `Detect lanes in single images` section of the notebook.


#### 4. Describe how (and identify where in your code) you identified lane-line pixels and fit their positions with a polynomial?

After warping the combined binary image, I used the `fit_polynomial()` function, which fits the lane lines with a
2nd order polynomial, and calls the `find_lane_pixels()` function. The `find_lane_pixels()` function first takes
the bottom half of the image and creates a histogram of the pixels, effectively identifying where the lane lines
start (at the minimum y value).

The function then loops through each "window" of the image, identifies the non-zero pixels, and appends the indices
to a list. If the algorithm identifies non-zero pixels in that window, we set the center of the next window to
that position, which helps give us a jump-start on the next loop.

At this point, we are able to plot the polynomial and windows like so:

![polyfit_img](https://user-images.githubusercontent.com/11286381/49269202-9ae6a780-f418-11e8-9f33-3471ad651ff9.png)

The final code used in the image and video pipelines can be seen in the `find_lane_pixels()` and `fit_polynomial()` functions in the `Detect lanes in single images¶` section of the notebook.

#### 5. Describe how (and identify where in your code) you calculated the radius of curvature of the lane and the position of the vehicle with respect to center.

The `get_radius_and_offset()` function handles calculating the radius and offset.

To calculate the radius, we first fine the curvature of each line individually.

<img width="366" alt="radius_formula" src="https://user-images.githubusercontent.com/11286381/49269107-1ac04200-f418-11e8-8c77-c12cd409772a.png">


After finding the curvature of each line, we simply get the average of the two.
```python
left_curverad =  ((1 + (2*left_fit[0]*720*ym_per_pixel + left_fit[1])**2)**(3/2))/np.abs(2*left_fit[0])
right_curverad =  ((1 + (2*right_fit[0]*720*ym_per_pixel + right_fit[1])**2)**(3/2))/np.abs(2*right_fit[0])
radius = np.mean([left_curverad, right_curverad])
```

To calculate the offset, we calculate the x position of each lane line within the image and subtract
the the center of the lane (which we assume is the location of the camera), after converting pixels to
meters.

```python
left_lane = left_fit[0]*(720*ym_per_pixel)**2 + left_fit[1]*720*ym_per_pixel + left_fit[2]
right_lane = right_fit[0]*(720*ym_per_pixel)**2 + right_fit[1]*720*ym_per_pixel + right_fit[2]
offset = [640*xm_per_pixel - np.mean([left_lane, right_lane]), right_lane-left_lane]
```


The final code used in the image and video pipelines can be seen in the `get_radius_and_offset()` function in the `Detect lanes in single images¶` section of the notebook.

#### 6. Provide an example image of your result plotted back down onto the road such that the lane area is identified clearly.

Here is an image of the projected lane detection:

![lane_detected_img](https://user-images.githubusercontent.com/11286381/49269056-cddc6b80-f417-11e8-84f5-f47e5a43004d.png)

The final code used in the image and video pipelines can be seen in the `draw()` function in the `Detect lanes in single images` section of the notebook.

---

### End to end:

![pipeline_corrected](https://user-images.githubusercontent.com/11286381/49204380-9494f480-f360-11e8-9e69-6b24b1e22b92.png)
![pipeline_binary](https://user-images.githubusercontent.com/11286381/49204379-9494f480-f360-11e8-8c9c-0aae7e71142d.png)
![pipeline_roi](https://user-images.githubusercontent.com/11286381/49204383-9494f480-f360-11e8-99a5-35483b21ee50.png)
![pipeline_binary_warped](https://user-images.githubusercontent.com/11286381/49204378-93fc5e00-f360-11e8-8007-591361c08211.png)
![polyfit_img](https://user-images.githubusercontent.com/11286381/49269202-9ae6a780-f418-11e8-9f33-3471ad651ff9.png)
![pipeline_lane_detection](https://user-images.githubusercontent.com/11286381/49204381-9494f480-f360-11e8-8df8-ccc6f4807912.png)


---

### Pipeline (video)

#### 1. Provide a link to your final video output.  Your pipeline should perform reasonably well on the entire project video (wobbly lines are ok but no catastrophic failures that would cause the car to drive off the road!).

[![screencap](https://img.youtube.com/vi/-ew4mhf7ZQI/0.jpg)](https://www.youtube.com/watch?v=-ew4mhf7ZQI)

Here's a [link to my download my video result](https://github.com/markmisener/udacity-self-driving-car-engineer/blob/master/p2-advanced-lane-line-detection/output_video/lane_detection_video.mp4)

The final code used in the image and video pipelines can be seen in the `image_pipeline()` function in the `Detecting lanes in video` section of the notebook.

---

### Discussion

#### 1. Briefly discuss any problems / issues you faced in your implementation of this project.  Where will your pipeline likely fail?  What could you do to make it more robust?

Because I used smoothing to determine if the image (in the video) should be updated or if we should just use the lane detected in the previous frame, the pipeline will likely fail in conditions where there are more abrupt changes such as sharper turns, vehicle moving between lanes, other obstacles entering the field of view. At this point in my understanding of these types of detections, I am not sure of how to make this more robust.
