#include "particle_filter.h"

#include <math.h>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <random>
#include <string>
#include <vector>

#include "helper_functions.h"

using std::string;
using std::vector;

void ParticleFilter::init(double x, double y, double theta, double std[]) {
  num_particles = 500;

  std::default_random_engine gen;
  std::normal_distribution<double> dist_x(x, std[0]);
  std::normal_distribution<double> dist_y(y, std[1]);
  std::normal_distribution<double> dist_theta(theta, std[2]);

  for (int i = 0; i < num_particles; i++){
    Particle p;
    p.id = i;
    p.x = dist_x(gen);
    p.y = dist_y(gen);
    p.theta = dist_theta(gen);
    p.weight = 1.0;
    particles.push_back(p);
  }
  is_initialized = true;
}

void ParticleFilter::prediction(double delta_t, double std_pos[],
                                double velocity, double yaw_rate) {
  double std_x = std_pos[0];
  double std_y = std_pos[1];
  double std_theta = std_pos[2];
  std::default_random_engine gen;
  std::normal_distribution<double> dist_x(0, std_x);
  std::normal_distribution<double> dist_y(0, std_y);
  std::normal_distribution<double> dist_theta(0, std_theta);

  for (int i = 0; i < num_particles; i++) {
  	double theta = particles[i].theta;
    if (fabs(yaw_rate) > 0.000001) {
      particles[i].x += velocity / yaw_rate * (sin(theta + yaw_rate * delta_t) - sin(theta));
      particles[i].y += velocity / yaw_rate * (cos(theta) - cos(theta + yaw_rate * delta_t));
      particles[i].theta += yaw_rate * delta_t;
    } else {
      particles[i].x += velocity * delta_t * cos(theta);
      particles[i].y += velocity * delta_t * sin(theta);
    }
    particles[i].x += dist_x(gen);
    particles[i].y += dist_y(gen);
    particles[i].theta += dist_theta(gen);
  }
}

void ParticleFilter::dataAssociation(vector<LandmarkObs> predicted,
                                     vector<LandmarkObs>& observations) {
  for (int i = 0; i < observations.size(); i++) {
    int observationID;
    double distMin = std::numeric_limits<double>::max();
    for (int j = 0; j < predicted.size(); j++) {
      double distX = observations[i].x - predicted[j].x;
      double distY = observations[i].y - predicted[j].y;
      double distTotal = std::pow(distX, 2) + std::pow(distY, 2);
      if (distTotal < distMin) {
        distMin = distTotal;
        observationID = predicted[j].id;
      }
    }
    observations[i].id = observationID;
  }
}

void ParticleFilter::updateWeights(double sensor_range, double std_landmark[],
                                   const vector<LandmarkObs> &observations,
                                   const Map &map_landmarks) {
  double stdLandmarkRange = std_landmark[0];
  double stdLandmarkBearing = std_landmark[1];

  for (int i = 0; i < num_particles; i++) {
    double x = particles[i].x;
    double y = particles[i].y;
    double theta = particles[i].theta;

    vector<LandmarkObs> inRangeLandmarks;
    for(int j = 0; j < map_landmarks.landmark_list.size(); j++) {
      int landmarkID = map_landmarks.landmark_list[j].id_i;
      double landmarkX = map_landmarks.landmark_list[j].x_f;
      double landmarkY = map_landmarks.landmark_list[j].y_f;
      double landmarkDistX = x - landmarkX;
      double landmarkDistY = y - landmarkY;
      if (std::pow(landmarkDistX, 2) + std::pow(landmarkDistY, 2) <= std::pow(sensor_range, 2)) {
        inRangeLandmarks.push_back(LandmarkObs{landmarkID, landmarkX, landmarkY});
      }
    }

    vector<LandmarkObs> mappedObservations;
    for(int j = 0; j < observations.size(); j++) {
      int observationID = observations[j].id;
      double xx = cos(theta)*observations[j].x - sin(theta)*observations[j].y + x;
      double yy = sin(theta)*observations[j].x + cos(theta)*observations[j].y + y;
      mappedObservations.push_back(LandmarkObs{observationID, xx, yy});
    }

    dataAssociation(inRangeLandmarks, mappedObservations);

    particles[i].weight = 1.0;
    for(int j = 0; j < mappedObservations.size(); j++) {
      double observationX = mappedObservations[j].x;
      double observationY = mappedObservations[j].y;
      double landmarkX;
      double landmarkY;
      int landmarkId = mappedObservations[j].id;

      int k = 0;
      bool found = false;
      while(!found && k < inRangeLandmarks.size()) {
        if (inRangeLandmarks[k].id == landmarkId) {
          found = true;
          landmarkX = inRangeLandmarks[k].x;
          landmarkY = inRangeLandmarks[k].y;
        }
        k++;
      }

      double distX = observationX - landmarkX;
      double distY = observationY - landmarkY;
      double weight = (1/(2*M_PI*std::pow(stdLandmarkRange,2))) * exp(-(std::pow(distX,2)/(2*std::pow(stdLandmarkRange,2)) + (std::pow(distY,2)/(2*std::pow(stdLandmarkBearing,2)))));
      if (weight == 0) {
        particles[i].weight *= 0.000001;
      } else {
        particles[i].weight *= weight;
      }
    }
  }
}

void ParticleFilter::resample() {
  vector<double> weights;
  double maxWeight = std::numeric_limits<double>::min();
  for(int i = 0; i < num_particles; i++) {
    weights.push_back(particles[i].weight);
    if (particles[i].weight > maxWeight) {
      maxWeight = particles[i].weight;
    }
  }

  std::uniform_real_distribution<double> distDouble(0.0, maxWeight);
  std::uniform_int_distribution<int> distInt(0, num_particles - 1);
  std::default_random_engine gen;
  int index = distInt(gen);

  double beta = 0.0;
  vector<Particle> resampledParticles;
  for(int i = 0; i < num_particles; i++) {
    beta += distDouble(gen) * 2.0;
    while(beta > weights[index]) {
      beta -= weights[index];
      index = (index + 1) % num_particles;
    }
    resampledParticles.push_back(particles[index]);
  }
  particles = resampledParticles;
}

void ParticleFilter::SetAssociations(Particle& particle,
                                     const vector<int>& associations,
                                     const vector<double>& sense_x,
                                     const vector<double>& sense_y) {
  particle.associations= associations;
  particle.sense_x = sense_x;
  particle.sense_y = sense_y;
}

string ParticleFilter::getAssociations(Particle best) {
  vector<int> v = best.associations;
  std::stringstream ss;
  copy(v.begin(), v.end(), std::ostream_iterator<int>(ss, " "));
  string s = ss.str();
  s = s.substr(0, s.length()-1);
  return s;
}

string ParticleFilter::getSenseCoord(Particle best, string coord) {
  vector<double> v;

  if (coord == "X") {
    v = best.sense_x;
  } else {
    v = best.sense_y;
  }

  std::stringstream ss;
  copy(v.begin(), v.end(), std::ostream_iterator<float>(ss, " "));
  string s = ss.str();
  s = s.substr(0, s.length()-1);
  return s;
}
