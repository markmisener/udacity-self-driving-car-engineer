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
        """
        Load and initialize the classifier
        """
        self.model = load_model(DIR_PATH + '/model.h5')
        self.model._make_predict_function()
        self.graph = tf.get_default_graph()
        self.light_state = TrafficLight.UNKNOWN
        self.classes_dict = {
            0: TrafficLight.RED,
            1: TrafficLight.YELLOW,
            2: TrafficLight.GREEN,
            4: TrafficLight.UNKNOWN
        }

    def get_classification(self, img):
        """ Determines the color of the traffic light in the image
         Args:
            image (cv::Mat): image containing the traffic light
         Returns:
            int: ID of traffic light color (specified in styx_msgs/TrafficLight)
        """
        img_resized = cv2.resize(img, (80, 60))/255.
        img_resized = np.array([img_resized])

        with self.graph.as_default():
            model_predict = self.model.predict(img_resized)
            if model_predict[0][np.argmax(model_predict[0])] > 0.5:
                self.light_state = self.classes_dict[np.argmax(model_predict[0])]

        return self.light_state
