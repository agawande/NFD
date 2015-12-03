/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (c) 2014-2015,  Regents of the University of California,
 *                           Arizona Board of Regents,
 *                           Colorado State University,
 *                           University Pierre & Marie Curie, Sorbonne University,
 *                           Washington University in St. Louis,
 *                           Beijing Institute of Technology,
 *                           The University of Memphis.
 *
 * This file is part of NFD (Named Data Networking Forwarding Daemon).
 * See AUTHORS.md for complete list of NFD authors and contributors.
 *
 * NFD is free software: you can redistribute it and/or modify it under the terms
 * of the GNU General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * NFD is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE.  See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * NFD, e.g., in COPYING.md file.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef NFD_TESTS_DAEMON_FACE_DUMMY_FACE_HPP
#define NFD_TESTS_DAEMON_FACE_DUMMY_FACE_HPP

#include "face/face.hpp"

namespace nfd {
namespace tests {

/** \brief a Face for unit testing
 */
class DummyFace : public Face
{
public:
  explicit
  DummyFace(const std::string& remoteUri = "dummy://", const std::string& localUri = "dummy://",
            bool isLocal = false)
    : Face(FaceUri(remoteUri), FaceUri(localUri), isLocal)
  {
  }

  void
  sendInterest(const Interest& interest) DECL_OVERRIDE
  {
    this->emitSignal(onSendInterest, interest);
    m_sentInterests.push_back(interest);
    this->afterSend();
  }

  void
  sendData(const Data& data) DECL_OVERRIDE
  {
    this->emitSignal(onSendData, data);
    m_sentDatas.push_back(data);
    this->afterSend();
  }

  void
  close() DECL_OVERRIDE
  {
    this->fail("close");
  }

  void
  receiveInterest(const Interest& interest)
  {
    this->emitSignal(onReceiveInterest, interest);
  }

  void
  receiveData(const Data& data)
  {
    this->emitSignal(onReceiveData, data);
  }

  signal::Signal<DummyFace> afterSend;

public:
  std::vector<Interest> m_sentInterests;
  std::vector<Data> m_sentDatas;
};

class DummyLocalFace : public DummyFace
{
public:
  explicit
  DummyLocalFace(const std::string& remoteUri = "dummy://", const std::string& localUri = "dummy://")
    : DummyFace(remoteUri, localUri, true)
  {
  }
};

} // namespace tests
} // namespace nfd

#endif // NFD_TESTS_DAEMON_FACE_DUMMY_FACE_HPP
