/*
 * Copyright (c) 2014, Skybotix AG, Switzerland (info@skybotix.com)
 * Copyright (c) 2014, Autonomous Systems Lab, ETH Zurich, Switzerland
 *
 * All rights reserved.
 *
 * Redistribution and non-commercial use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  Redistributions of source code must retain the above copyright notice, this
 *  list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright notice, this
 *  list of conditions and the following disclaimer in the documentation and/or
 *  other materials provided with the distribution.
 *
 *  Neither the name of the {organization} nor the names of its
 *  contributors may be used to endorse or promote products derived from
 *  this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#ifndef VISENSOR_API_HPP_
#define VISENSOR_API_HPP_

#include <visensor/visensor_config.hpp>

#include <string>
#include <vector>
#include <stdint.h>
#include <boost/function.hpp>

#include <visensor/visensor_datatypes.hpp>
#include <visensor/visensor_constants.hpp>

namespace visensor {

class DSO_EXPORT ViSensorDriver {

 public:
  typedef boost::shared_ptr<ViSensorDriver> Ptr;

  ViSensorDriver();
  ~ViSensorDriver();

  //get list of all ViSensors connected to the network
  void getAutoDiscoveryDeviceList(ViDeviceList &hostname_list);

  //init using autodiscovery (first sensor that responded, returns its ip)
  std::string init();

  //connect to specific host/ip address
  void init(std::string host_ip);

  void startSensor(visensor::SensorId::SensorId sensor_id, uint32_t rate =
                       CAMERA_FREQUENCY);
  void stopSensor(visensor::SensorId::SensorId sensor_id);
  void setSensorConfigParam(visensor::SensorId::SensorId sensor_id, const std::string cmd,
                            int value);

  void startAllCameras(uint32_t rate = CAMERA_FREQUENCY);
  void setCameraCallback(boost::function<void(ViFrame::Ptr, ViErrorCode)> callback);

  void startAllCorners();
  void setCornerCallback(boost::function<void(ViCorner::Ptr, ViErrorCode)> callback);

  void startAllImus(uint32_t rate = IMU_FREQUENCY);
  void setImuCallback(boost::function<void(ViImuMsg::Ptr, ViErrorCode)> callback);

  void startAllExternalTriggers(uint32_t rate);
  void setExternalTriggerCallback(boost::function<void(ViExternalTriggerMsg::Ptr)> callback);
  void setExternalTriggerConfig(const ViExternalTriggerConfig config);

  void startAllDenseMatchers();
  void setDenseMatcherCallback(boost::function<void(ViFrame::Ptr, ViErrorCode)> callback);

  // is called with synchronized images and corresponding corners
  void setFramesCornersCallback(boost::function<void(ViFrame::Ptr, ViCorner::Ptr)> callback);

  std::vector<SensorId::SensorId> getListOfSensorIDs() const;
  std::vector<SensorId::SensorId> getListOfCameraIDs() const;
  std::vector<SensorId::SensorId> getListOfDenseIDs() const;
  std::vector<SensorId::SensorId> getListOfCornerIDs() const;
  std::vector<SensorId::SensorId> getListOfImuIDs() const;
  std::vector<SensorId::SensorId> getListOfTriggerIDs() const;
  uint32_t getFpgaId() const;

  //slot 0 holds the factory calibration (and can't be overwritten using the public API, use the calibration tool instead)
  bool getCameraCalibration(SensorId::SensorId cam_id, ViCameraCalibration& calib, int slot_id=0) const;
  bool setCameraCalibration(SensorId::SensorId cam_id, const ViCameraCalibration calib, int slot_id=1) const;
  bool setCameraFactoryCalibration(SensorId::SensorId cam_id, const ViCameraCalibration calib) const;
  void setCameraCalibrationSlot(int slot_id);
  int getCameraCalibrationSlot();

  //serial port bridge
  void sendSerialData(ViSerialData::Ptr data) const;
  void setSerialCallback(boost::function<void(ViSerialData::Ptr)> callback);
  void setSerialDelimiter(const char serial_id, const std::string delimiter) const;
  void setSerialBaudrate(const char serial_id, const unsigned int baudrate) const;

  //file transfer
  void downloadFile(std::string local_path, std::string remote_path);
  void uploadFile(std::string local_path, std::string remote_path);

 private:
  class Impl;
  Impl* pImpl_;

 public:
  //private API access
  Impl* getPrivateApiAccess() { return pImpl_; }
};
}  //namespace visensor

#endif /* VISENSOR_API_HPP_ */
