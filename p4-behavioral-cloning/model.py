import cv2
import glob
import pandas as pd
import numpy as np
from keras.optimizers import Adam
from keras.callbacks import ModelCheckpoint
from keras.models import Sequential
from keras.layers import Conv2D, Cropping2D, Dense, Dropout, Flatten, Lambda
from sklearn.model_selection import train_test_split
import matplotlib.image as mpimg

IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_CHANNELS = 160, 320, 3


def flip(image, measurement):
    return np.fliplr(image), -measurement


def load_image(image_file):
    """ Load RGB images from a file

    Args
        image_file (str): name of image file

    """
    if image_file.split('/')[0] == 'IMG':
        image_file = '/opt/carnd_p3/data/{}'.format(image_file)
    return mpimg.imread(image_file.strip())


def load_data(test_size, additional_training_data=False):
    """ Load the data from a directory and split it into
    training and testing datasets.

    Args:
        test_size (float): percentage of data to hold out for testing
    Returns:
        List containing train-test split of inputs. (X_train, X_val,  y_train, y_val)
    """
    header = None
    names = ['center', 'left', 'right', 'steering', 'throttle', 'brake', 'speed']
    data_df = pd.read_csv('/opt/carnd_p3/data/driving_log.csv',
                          header=header, names=names)
    if additional_training_data:
        for filename in glob.glob('training_data/*.csv'):
            tmp_df = pd.read_csv(filename, header=header, names=names)
            data_df = pd.concat([data_df, tmp_df])

    data_df = data_df[(data_df.center != 'center') |
                      (data_df.left != 'left') |
                      (data_df.right != 'right')]
    X = data_df[['center', 'left', 'right']].values
    y = data_df['steering'].values

    return train_test_split(X, y, test_size=test_size)


def build_model(rows, columns, channels):
    """ Create keras sequential model, derived from NVIDIA's architecture
    (https://arxiv.org/pdf/1604.07316v1.pdf), with some minor modifications.

    Args:
        rows (int): the number of rows in the input
        columns (int): the number of columns in the input
        channels (int): the number of channels in the input

    Returns:
        keras sequential model
    """
    model = Sequential()
    model.add(Cropping2D(cropping=((65,20), (0,0)), input_shape=(rows, columns, channels)))
    model.add(Lambda(lambda x: x/127.5 - 1.))
    model.add(Conv2D(24, (5, 5), strides=(2, 2), activation='relu'))
    model.add(Dropout(0.5))
    model.add(Conv2D(36, (5, 5), strides=(2, 2), activation='relu'))
    model.add(Conv2D(48, (5, 5), strides=(2, 2), activation='relu'))
    model.add(Dropout(0.5))
    model.add(Conv2D(64, (3, 3), activation='relu'))
    model.add(Conv2D(64, (3, 3), activation='relu'))
    model.add(Dropout(0.5))
    model.add(Flatten())
    model.add(Dense(100))
    model.add(Dense(50))
    model.add(Dropout(0.5))
    model.add(Dense(10))
    model.add(Dense(1))
    return model


def batch_generator(image_paths, steering_angles, batch_size):
    """
    """
    images = np.empty([batch_size, IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_CHANNELS])
    measurements = np.empty(batch_size)
    while True:
        i = 0
        for index in np.random.permutation(image_paths.shape[0]):
            center, left, right = image_paths[index]
            image = load_image(center)
            measurement = float(steering_angles[index])

            if np.random.rand() < 0.5:
                image, measurement = flip(image, measurement)

            images[i] = image
            measurements[i] = measurement

            i += 1
            if i == batch_size:
                break
        yield images, measurements

def main():
    """Entry point for training the model"""

    # Hyperparameters
    test_size = 0.20
    batch_size = 128
    epochs = 5
    verbose = 1
    additional_training_data = True

    print('Loading data...')
    X_train, X_val, y_train, y_val = load_data(test_size, additional_training_data=additional_training_data)
    print('Building sequential model...')
    model = build_model(IMAGE_HEIGHT, IMAGE_WIDTH, IMAGE_CHANNELS)

    checkpoint = ModelCheckpoint('model_checkpoints/model-{epoch:03d}.h5',
                                 monitor='val_loss',
                                 verbose=0,
                                 save_best_only=True,
                                 mode='auto')

    print('Compiling model...')
    model.compile(loss='mean_squared_error', optimizer=Adam(lr=0.0001))

    print('Training model...')
    history_object = model.fit_generator(batch_generator(X_train, y_train, batch_size),
                                         steps_per_epoch=len(X_train)/batch_size,
                                         validation_data=batch_generator(X_val, y_val, batch_size),
                                         validation_steps=len(X_val)/batch_size,
                                         callbacks=[checkpoint],
                                         epochs=epochs,
                                         verbose=verbose)

    print('Saving model...')
    model.save('model.h5')
    print('Complete!')

if __name__ == '__main__':
    main()
