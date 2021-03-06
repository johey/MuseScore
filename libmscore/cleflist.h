//=============================================================================
//  MuseScore
//  Music Composition & Notation
//  $Id:$
//
//  Copyright (C) 2011 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENCE.GPL
//=============================================================================

#ifndef __CLEFLIST_H__
#define __CLEFLIST_H__

#include "mscore.h"
#include "clef.h"

class Score;

//---------------------------------------------------------
//   ClefList
//---------------------------------------------------------

class ClefList : public QMultiMap<int, ClefTypeList> {
   public:
      ClefList() {}
      ClefTypeList clef(int tick) const;
      void setClef(int tick, ClefTypeList);
      void read(const QDomElement&, Score*);
      };

typedef QMultiMap<int, ClefTypeList>::iterator iClefEvent;
typedef QMultiMap<int, ClefTypeList>::const_iterator ciClefEvent;

#endif

