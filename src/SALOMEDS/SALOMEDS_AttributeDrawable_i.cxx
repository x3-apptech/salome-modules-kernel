// Copyright (C) 2007-2020  CEA/DEN, EDF R&D, OPEN CASCADE
//
// Copyright (C) 2003-2007  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
// CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
//
// See http://www.salome-platform.org/ or email : webmaster.salome@opencascade.com
//

//  File   : SALOMEDS_AttributeDrawable_i.cxx
//  Author : Sergey RUIN
//  Module : SALOME
//
#include "SALOMEDS_AttributeDrawable_i.hxx"
#include "SALOMEDS.hxx"

CORBA::Boolean SALOMEDS_AttributeDrawable_i::IsDrawable()
{
  SALOMEDS::Locker lock;
  return (dynamic_cast<SALOMEDSImpl_AttributeDrawable*>(_impl)->IsDrawable() == 1);
}

void SALOMEDS_AttributeDrawable_i::SetDrawable(CORBA::Boolean value)
{
  SALOMEDS::Locker lock;
  CheckLocked();
  dynamic_cast<SALOMEDSImpl_AttributeDrawable*>(_impl)->SetDrawable(value);
}
