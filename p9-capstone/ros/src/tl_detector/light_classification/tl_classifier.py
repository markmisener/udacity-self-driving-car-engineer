from styx_msgs.msg import TrafficLight
import tensorflow as tf
import os
import numpy as np
import rospy
import cv2
from keras.models import load_model

DIR_PATH = os.path.dirname(os.path.realpath(__file__))

class TLClassifier(object):
    def __init__(self):
        self.model = load_model(DIR_PATH + '/tl_detector_model.h5')
        self.light_state = TrafficLight.UNKNOWN
        self.classes = {
            0: TrafficLight.RED,
            1: TrafficLight.YELLOW,
            2: TrafficLight.GREEN,
            4: TrafficLight.UNKNOWN
        }

    def get_classification(self, image):
        """Determines the color of the traffic light in the image

        Args:
            image (cv::Mat): image containing the traffic light

        Returns:
            int: ID of traffic light color (specified in styx_msgs/TrafficLight)

        """
        img_resized = cv2.resize(image, (80, 60))/255.
        img = np.array([img_resized])
        model_predict = self.model.predict(img)
        if model_predict[0][np.argmax(model_predict[0])] > 0.5:
            return self.classes[np.argmax(model_predict[0])]
        return TrafficLight.UNKNOWN
