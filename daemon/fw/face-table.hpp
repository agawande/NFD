/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * Copyright (C) 2014 Named Data Networking Project
 * See COPYING for copyright and distribution information.
 */

#ifndef NFD_FW_FACE_TABLE_HPP
#define NFD_FW_FACE_TABLE_HPP

#include "face/face.hpp"
#include "core/map-value-iterator.hpp"

namespace nfd
{

class Forwarder;

/** \brief container of all Faces
 */
class FaceTable
{
public:
  explicit
  FaceTable(Forwarder& forwarder);

  void
  add(shared_ptr<Face> face);

  void
  remove(shared_ptr<Face> face);

  shared_ptr<Face>
  get(FaceId id) const;

  size_t
  size() const;

public: // enumeration
  typedef std::map<FaceId, shared_ptr<Face> > FaceMap;

  /** \brief ForwarderIterator for shared_ptr<Face>
   */
  typedef MapValueIterator<FaceMap> const_iterator;

  const_iterator
  begin() const;

  const_iterator
  end() const;

private:
  Forwarder& m_forwarder;
  FaceId m_lastFaceId;
  FaceMap m_faces;
};

inline shared_ptr<Face>
FaceTable::get(FaceId id) const
{
  std::map<FaceId, shared_ptr<Face> >::const_iterator i = m_faces.find(id);
  return (i == m_faces.end()) ? (shared_ptr<Face>()) : (i->second);
}

inline size_t
FaceTable::size() const
{
  return m_faces.size();
}

inline FaceTable::const_iterator
FaceTable::begin() const
{
  return const_iterator(m_faces.begin());
}

inline FaceTable::const_iterator
FaceTable::end() const
{
  return const_iterator(m_faces.end());
}

} // namespace nfd

#endif // NFD_FW_FACE_TABLE_HPP