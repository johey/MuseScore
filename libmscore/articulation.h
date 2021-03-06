//=============================================================================
//  MuseScore
//  Music Composition & Notation
//  $Id: articulation.h 5500 2012-03-28 16:28:26Z wschweer $
//
//  Copyright (C) 2002-2011 Werner Schweer
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License version 2
//  as published by the Free Software Foundation and appearing in
//  the file LICENCE.GPL
//=============================================================================

#ifndef __ARTICULATION_H__
#define __ARTICULATION_H__

#include "mscore.h"
#include "symbol.h"
#include "sym.h"

class QPainter;
class ChordRest;

//---------------------------------------------------------
//   ArticulationInfo
//    gives infos about note attributes
//---------------------------------------------------------

enum ArticulationAnchor {
      A_TOP_STAFF,
      A_BOTTOM_STAFF,
      A_CHORD,          // anchor depends on chord direction
      A_TOP_CHORD,      // attribute is alway placed at top of chord
      A_BOTTOM_CHORD,   // attribute is placed at bottom of chord
      };

// flags:
enum { ARTICULATION_SHOW_IN_PITCHED_STAFF = 1, ARTICULATION_SHOW_IN_TABLATURE = 2 };

struct ArticulationInfo {
      SymId upSym;
      SymId downSym;
      QString name;
      QString description;    // translated name
      qreal timeStretch;      // for fermata
      int flags;
      };

//---------------------------------------------------------
//   @@ Articulation
///    articulation marks
//---------------------------------------------------------

class Articulation : public Element {
      Q_OBJECT

      ArticulationType _subtype;
      MScore::Direction _direction;
      QString _channelName;
      ArticulationAnchor _anchor;
      bool _up;

      virtual void draw(QPainter*) const;

   public:
      Articulation(Score*);
      Articulation &operator=(const Articulation&);

      virtual Articulation* clone() const   { return new Articulation(*this); }
      virtual ElementType type() const      { return ARTICULATION; }

      void setSubtype(ArticulationType);
      ArticulationType subtype() const      { return _subtype; }
      void setSubtype(const QString& s);
      QString subtypeName() const;

      virtual void layout();

      virtual void read(const QDomElement&);
      virtual void write(Xml& xml) const;

      virtual void toDefault();
      virtual QLineF dragAnchor() const;

      virtual QVariant getProperty(P_ID propertyId) const;
      virtual bool setProperty(P_ID propertyId, const QVariant&);

      ArticulationType articulationType() const;
      QString subtypeUserName() const;

      virtual QPointF pagePos() const;      ///< position in page coordinates
      virtual QPointF canvasPos() const;

      bool up() const                       { return _up; }
      void setUp(bool val)                  { _up = val;  }
      void setDirection(MScore::Direction d);
      MScore::Direction direction() const   { return _direction; }

      ChordRest* chordRest() const;

      static ArticulationInfo articulationList[];

      ArticulationAnchor anchor() const     { return _anchor;      }
      void setAnchor(ArticulationAnchor v)  { _anchor = v;         }

      QString channelName() const           { return _channelName; }
      void setChannelName(const QString& s) { _channelName = s;    }

      const ArticulationInfo* articulationInfo() const { return &articulationList[articulationType()]; }

      qreal timeStretch() const;

      static QString idx2name(int idx);
      };

#endif

