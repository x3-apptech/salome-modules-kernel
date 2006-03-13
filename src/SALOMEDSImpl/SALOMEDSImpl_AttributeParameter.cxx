// Copyright (C) 2005  OPEN CASCADE, EADS/CCR, LIP6, CEA/DEN,
// CEDRAT, EDF R&D, LEG, PRINCIPIA R&D, BUREAU VERITAS
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either 
// version 2.1 of the License.
// 
// This library is distributed in the hope that it will be useful 
// but WITHOUT ANY WARRANTY; without even the implied warranty of 
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU 
// Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public  
// License along with this library; if not, write to the Free Software 
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
//
// See http://www.salome-platform.org/
//
//  File   : SALOMEDSImpl_AttributeParameter.cxx
//  Author : Sergey RUIN
//  Module : SALOME


#include "SALOMEDSImpl_AttributeParameter.hxx"
#include <Standard_Failure.hxx>

#include <stdio.h>
#include <stdlib.h>
#include <strstream>

using namespace std;



IMPLEMENT_STANDARD_HANDLE( SALOMEDSImpl_AttributeParameter, SALOMEDSImpl_GenericAttribute )
IMPLEMENT_STANDARD_RTTIEXT( SALOMEDSImpl_AttributeParameter, SALOMEDSImpl_GenericAttribute )


// Purpose: Each character in the string is replaced by 3 characters: '%' and hex number 
//          of the character (2 characters)
string convertString(const string& S)
{
  int length = S.size();
  const char *s = S.c_str();
  char *c = new char[3], *buffer = new char[length*3+1];
  buffer[length*3] = (char)0;
  for(int i = 0, pos = 0; i<length; i++, pos+=3) {
    int val = (int)s[i];
    buffer[pos] = '%';
    sprintf(c, "%x", val);
    buffer[pos+1] = c[0]; 
    buffer[pos+2] = c[1];
  }

  string RS(buffer); 
  delete c;
  delete buffer;
  return RS;
}

//Restors a string converted by the function convertString
string restoreString(const string& S)
{
  int length = S.size();
  char *c = new char[3], *buffer = new char[length/3+1];
  buffer[length/3] = (char)0;
  const char *s = S.c_str();
  for(int i = 0, pos = 0; i<length; i+=3, pos++) {
    c[0] = s[i+1];
    c[1] = s[i+2];
    c[2] = (char)0;
    int val = strtol(c, NULL, 16);
    buffer[pos] = (char)val;
  }

  string RS(buffer); 
  delete c;
  delete buffer;
  return RS;
}

//=======================================================================
/*!
 * Function : GetID
 * Purpose  : Returns GUID of the attribute
 */
//=======================================================================
const Standard_GUID& SALOMEDSImpl_AttributeParameter::GetID ()
{
  static Standard_GUID ParemeterID ("BA75F3A1-E40B-46b8-8D24-B1D3C3BB1A8C");
  return ParemeterID;
}   

//=======================================================================
/*!
 * Function : Set
 * Purpose  : Adds an attribute to the label
 */
//=======================================================================
Handle(SALOMEDSImpl_AttributeParameter) SALOMEDSImpl_AttributeParameter::Set (const TDF_Label& L) 
{
  Handle(SALOMEDSImpl_AttributeParameter) A;
  if (!L.FindAttribute(SALOMEDSImpl_AttributeParameter::GetID(), A)) {
    A = new  SALOMEDSImpl_AttributeParameter(); 
    L.AddAttribute(A);
  }

  return A;
}

//=======================================================================
/*!
 * Function : SetInt
 * Purpose  : Associates a integer value with the ID
 */
//=======================================================================
void SALOMEDSImpl_AttributeParameter::SetInt(const string& theID, const int& theValue)
{
  CheckLocked();

  Backup();

  _ints[theID] = theValue;

  SetModifyFlag(); 
}

//=======================================================================
/*!
 * Function : GetInt
 * Purpose  : Returns a int value associated with the given ID
 */
//=======================================================================
int SALOMEDSImpl_AttributeParameter::GetInt(const string& theID)
{
  if(!IsSet(theID, PT_INTEGER)) Standard_Failure::Raise("Invalid ID");
  return _ints[theID];
}

//=======================================================================
/*!
 * Function : SetReal
 * Purpose  : Associates a double value with the ID
 */
//=======================================================================
void SALOMEDSImpl_AttributeParameter::SetReal(const string& theID, const double& theValue)
{
  CheckLocked();

  Backup();

  _reals[theID] = theValue;

  SetModifyFlag(); 
}

//=======================================================================
/*!
 * Function : GetReal
 * Purpose  : Returns a double value associated with the given ID
 */
//=======================================================================
double SALOMEDSImpl_AttributeParameter::GetReal(const string& theID)
{
  if(!IsSet(theID, PT_REAL)) Standard_Failure::Raise("Invalid ID");
  return _reals[theID];
}

//=======================================================================
/*!
 * Function : SetString
 * Purpose  : Associates a string with the ID
 */
//=======================================================================
void SALOMEDSImpl_AttributeParameter::SetString(const string& theID, const string& theValue)
{
  CheckLocked();

  Backup();

  _strings[theID] = theValue;

  SetModifyFlag(); 
}

//=======================================================================
/*!
 * Function : GetString
 * Purpose  : Returns a string associated with the given ID
 */
//=======================================================================
string SALOMEDSImpl_AttributeParameter::GetString(const string& theID)
{
  if(!IsSet(theID, PT_STRING)) Standard_Failure::Raise("Invalid ID");
  return _strings[theID];
}

//=======================================================================
/*!
 * Function : SetBool
 * Purpose  : Associates a bool value with the ID
 */
//=======================================================================
void SALOMEDSImpl_AttributeParameter::SetBool(const string& theID, const bool& theValue)
{
  CheckLocked();

  Backup();

  _bools[theID] = theValue;

  SetModifyFlag(); 
}

//=======================================================================
/*!
 * Function : GetBool
 * Purpose  : Returns a bool value associated with the ID
 */
//=======================================================================
bool SALOMEDSImpl_AttributeParameter::GetBool(const string& theID)
{
  if(!IsSet(theID, PT_BOOLEAN)) Standard_Failure::Raise("Invalid ID");
  return _bools[theID];
}

//=======================================================================
/*!
 * Function : SetRealArray
 * Purpose  : Associates an array of double values with the given ID
 */
//=======================================================================
void SALOMEDSImpl_AttributeParameter::SetRealArray(const string& theID, const vector<double>& theArray)
{
  CheckLocked();

  Backup();

  _realarrays[theID] = theArray;

  SetModifyFlag(); 
}

//=======================================================================
/*!
 * Function : GetRealArray
 * Purpose  : Returns double values associated with the ID
 */
//=======================================================================
vector<double> SALOMEDSImpl_AttributeParameter::GetRealArray(const string& theID)
{
  if(!IsSet(theID, PT_REALARRAY)) Standard_Failure::Raise("Invalid ID");
  return _realarrays[theID];
}
 

//=======================================================================
/*!
 * Function : SetIntArray
 * Purpose  : Associates an array of int values with the given ID
 */
//=======================================================================
void SALOMEDSImpl_AttributeParameter::SetIntArray(const string& theID, const vector<int>& theArray)
{
  CheckLocked();

  Backup();

  _intarrays[theID] = theArray;

  SetModifyFlag(); 
}

//=======================================================================
/*!
 * Function : GetIntArray
 * Purpose  : Returns int values associated with the ID
 */
//=======================================================================
vector<int> SALOMEDSImpl_AttributeParameter::GetIntArray(const string& theID)
{
  if(!IsSet(theID, PT_INTARRAY)) Standard_Failure::Raise("Invalid ID");
  return _intarrays[theID];
}
 

//=======================================================================
/*!
 * Function : SetStrArray
 * Purpose  : Associates an array of string values with the given ID
 */
//=======================================================================
void SALOMEDSImpl_AttributeParameter::SetStrArray(const string& theID, const vector<string>& theArray)
{
  CheckLocked();

  Backup();

  _strarrays[theID] = theArray;

  SetModifyFlag(); 
}

//=======================================================================
/*!
 * Function : GetStrArray
 * Purpose  : Returns string values associated with the ID
 */
//=======================================================================
vector<string> SALOMEDSImpl_AttributeParameter::GetStrArray(const string& theID)
{
  if(!IsSet(theID, PT_STRARRAY)) Standard_Failure::Raise("Invalid ID");
  return _strarrays[theID];
}
 

//=======================================================================
/*!
 * Function : IsSet
 * Purpose  : Returns true if for the ID of given type was assigned \n
 *            a value in the attribute
 */
//=======================================================================
bool SALOMEDSImpl_AttributeParameter::IsSet(const string& theID, const Parameter_Types theType)
{
  switch(theType) {
  case PT_INTEGER: {
    if(_ints.find(theID) != _ints.end()) return true;
    break;
  }
  case PT_REAL: {
    if(_reals.find(theID) != _reals.end()) return true;
    break;
  }
  case PT_BOOLEAN: {
    if(_bools.find(theID) != _bools.end()) return true;
    break;
  }
  case PT_STRING: {
    if(_strings.find(theID) != _strings.end()) return true;
    break;
  }
  case PT_REALARRAY: {
    if(_realarrays.find(theID) != _realarrays.end()) return true;
    break;
  }
  case PT_INTARRAY: {
    if(_intarrays.find(theID) != _intarrays.end()) return true;
    break;
  }
  case PT_STRARRAY: {
    if(_strarrays.find(theID) != _strarrays.end()) return true;
    break;
  }
  default: return false;
  }

  return false;
}

//=======================================================================
/*!
 * Function : RemoveID
 * Purpose  : Removes a parameter with given ID
 */
//=======================================================================
bool SALOMEDSImpl_AttributeParameter::RemoveID(const string& theID, const Parameter_Types theType)
{
  Backup();
  SetModifyFlag(); 

  switch(theType) {
  case PT_INTEGER: {
    if(_ints.erase(theID)) return true;
    break;
  }
  case PT_REAL: {
    if(_reals.erase(theID)) return true;
    break;
  }
  case PT_BOOLEAN: {
    if(_bools.erase(theID)) return true;
    break;
  }
  case PT_STRING: {
    if(_strings.erase(theID)) return true;
    break;
  }
  case PT_REALARRAY: {
    if(_realarrays.erase(theID)) return true;
    break;
  }
  case PT_INTARRAY: {
    if(_intarrays.erase(theID)) return true;
    break;
  }
  case PT_STRARRAY: {
    if(_strarrays.erase(theID)) return true;
    break;
  }
  default: return false;
  }


  return false;
}


//=======================================================================
/*!
 * Function : GetFather
 * Purpose  : Returns a father attribute for this attribute
 */
//=======================================================================
Handle(SALOMEDSImpl_AttributeParameter) SALOMEDSImpl_AttributeParameter::GetFather()
{
  Handle(SALOMEDSImpl_AttributeParameter) aFather;
  TDF_Label L = Label();
  if(L.IsRoot()) return aFather;

  while(!L.IsRoot()) {
    L = L.Father();
    if(L.FindAttribute(SALOMEDSImpl_AttributeParameter::GetID(), aFather)) break; 
  }

  return aFather;
}

//=======================================================================
/*!
 * Function : HasFather
 * Purpose  : Returns True if the attribute has a father attribute
 */
//=======================================================================
bool SALOMEDSImpl_AttributeParameter::HasFather()
{
  TDF_Label L = Label();
  if(L.IsRoot()) return false;
  while(!L.IsRoot()) {
    L = L.Father();
    if(L.IsAttribute(SALOMEDSImpl_AttributeParameter::GetID())) return true; 
  }

  return false;
}

//=======================================================================
/*!
 * Function : IsRoot
 * Purpose  : Returns True is the attribute is highest in an hierachy
 */
//=======================================================================
bool SALOMEDSImpl_AttributeParameter::IsRoot()
{
  return ((HasFather())?false:true);
}           

//=======================================================================
/*!
 * Function : Clear
 * Purpose  : Clears the content of the attribute
 */
//=======================================================================
void SALOMEDSImpl_AttributeParameter::Clear()
{
  Backup();

  _ints.clear();
  _reals.clear();
  _bools.clear();
  _strings.clear();
  _realarrays.clear();
  _intarrays.clear();
  _strarrays.clear();

  SetModifyFlag(); 
}

//=======================================================================
/*!
 * Function : GetIDs
 * Purpose  : Returns an array of all ID's of the given type
 */
//=======================================================================
vector<string> SALOMEDSImpl_AttributeParameter::GetIDs(const Parameter_Types theType)
{
  
  vector<string> anArray;
  int i = 0;

  switch(theType) {
  case PT_INTEGER: {
    if(_ints.size()) {
      anArray.resize(_ints.size());
      for(map<string,int>::const_iterator p = _ints.begin(); p != _ints.end(); p++, i++) 
	anArray[i] =  p->first;
    }
    break;
  }
  case PT_REAL: {
    if(_reals.size()) {
      anArray.resize(_reals.size());
      for(map<string,double>::const_iterator p = _reals.begin(); p != _reals.end(); p++, i++) 
	anArray[i] = p->first;
    }
    break;
  }
  case PT_BOOLEAN: {
    if(_bools.size()) {
      anArray.resize(_bools.size());
      for(map<string,bool>::const_iterator p = _bools.begin(); p != _bools.end(); p++, i++) 
	anArray[i] = p->first;
    }
    break;
  }
  case PT_STRING: {
    if(_strings.size()) {
      anArray.resize(_strings.size());
      for(map<string,string>::const_iterator p = _strings.begin(); p!= _strings.end(); p++) 
	anArray[i] = p->first;
    }
    break;
  }
  case PT_REALARRAY: {
    if(_realarrays.size()) {
      anArray.resize(_realarrays.size());
      for(map< string, vector<double> >::const_iterator p = _realarrays.begin(); p!= _realarrays.end(); p++) 
	anArray[i] = p->first;
    }
    break;
  }
  case PT_INTARRAY: {
    if(_intarrays.size()) {
      anArray.resize(_intarrays.size());
      for(map< string, vector<int> >::const_iterator p = _intarrays.begin(); p!= _intarrays.end(); p++) 
	anArray[i] = p->first;
    }
    break;
  }
  case PT_STRARRAY: {
    if(_strarrays.size()) {
      anArray.resize(_strarrays.size());
      for(map< string, vector<string> >::const_iterator p = _strarrays.begin(); p!= _strarrays.end(); p++) 
	anArray[i] = p->first;
    }
    break;
  }
  default: return anArray;
  }

  return anArray;
}

//=======================================================================
/*!
 * Function : ID
 * Purpose  : Rteurns an GUID of the attribute
 */
//=======================================================================
const Standard_GUID& SALOMEDSImpl_AttributeParameter::ID () const { return GetID(); } 


Handle(TDF_Attribute) SALOMEDSImpl_AttributeParameter::NewEmpty () const
{  
  return new SALOMEDSImpl_AttributeParameter(); 
}

//=======================================================================
/*!
 * Function : Restore
 * Purpose  : Restors the content of the attribute from another
 */
//=======================================================================
void SALOMEDSImpl_AttributeParameter::Restore(const Handle(TDF_Attribute)& with) 
{
  Handle(SALOMEDSImpl_AttributeParameter) A = Handle(SALOMEDSImpl_AttributeParameter)::DownCast (with);
  _ints.clear();
  _reals.clear();
  _bools.clear();
  _strings.clear();
  _realarrays.clear();
  _intarrays.clear();
  _strarrays.clear();
  
  for(map<string,int>::const_iterator p = A->_ints.begin(); p!= A->_ints.end(); p++) _ints[p->first] = p->second;
  for(map<string,double>::const_iterator p = A->_reals.begin(); p!= A->_reals.end(); p++) _reals[p->first] = p->second;
  for(map<string,bool>::const_iterator p = A->_bools.begin(); p!= A->_bools.end(); p++) _bools[p->first] = p->second;
  for(map<string,string>::const_iterator p = A->_strings.begin(); p!= A->_strings.end(); p++) 
    _strings[p->first] = p->second;
  for(map< string,vector<double> >::const_iterator p = A->_realarrays.begin(); p!= A->_realarrays.end(); p++) 
    _realarrays[p->first] = p->second;  
  for(map< string,vector<int> >::const_iterator p = A->_intarrays.begin(); p!= A->_intarrays.end(); p++) 
    _intarrays[p->first] = p->second;  
  for(map< string,vector<string> >::const_iterator p = A->_strarrays.begin(); p!= A->_strarrays.end(); p++) 
    _strarrays[p->first] = p->second; 
}

//=======================================================================
/*!
 * Function : Paste
 * Purpose  : Pastes the content of attribute to another
 */
//=======================================================================
void SALOMEDSImpl_AttributeParameter::Paste (const Handle(TDF_Attribute)& into,
					     const Handle(TDF_RelocationTable)& RT) const
{
  into->Restore(this);
}

//=======================================================================
/*!
 * Function : Save
 * Purpose  : Saves a content of the attribute as a string
 */
//=======================================================================
TCollection_AsciiString SALOMEDSImpl_AttributeParameter::Save() 
{ 
  ostrstream buffer;
  char *tmpBuffer = new char[255];

  buffer << _ints.size() << " ";

  for(map<string,int>::const_iterator p = _ints.begin(); p != _ints.end(); p++) {
    buffer << convertString(p->first) << " " << p->second << " ";
  }

  buffer << _reals.size() << " ";
  for(map<string,double>::const_iterator p =_reals.begin(); p != _reals.end(); p++) {
    sprintf(tmpBuffer, "%.64e", p->second);
    buffer << convertString(p->first) << " " << tmpBuffer << " ";
  }

  buffer << _bools.size() << " ";
  for(map<string,bool>::const_iterator p = _bools.begin(); p != _bools.end(); p++) {
     buffer << convertString(p->first) << " " << p->second << " ";
  }

  buffer << _strings.size() << " ";
  for(map<string,string>::const_iterator p = _strings.begin(); p != _strings.end(); p++) {
    buffer << convertString(p->first) << " " <<  convertString(p->second) << " ";
  }

  buffer << _realarrays.size() << " ";
  for(map< string,vector<double> >::const_iterator p = _realarrays.begin(); p != _realarrays.end(); p++) {
    vector<double> v(p->second);
    sprintf(tmpBuffer, " %s %d ", convertString(p->first).c_str(), v.size());
    buffer << tmpBuffer;
    for(int i = 0; i<v.size(); i++) {
      sprintf(tmpBuffer, " %.64e ", v[i]);
      buffer << tmpBuffer;
    }
  }

  buffer << _intarrays.size() << " ";
  for(map< string,vector<int> >::const_iterator p = _intarrays.begin(); p != _intarrays.end(); p++) {
    vector<int> v(p->second);
    sprintf(tmpBuffer, " %s %d ", convertString(p->first).c_str(), v.size());
    buffer << tmpBuffer;
    for(int i = 0; i<v.size(); i++) {
      sprintf(tmpBuffer, " %d ", v[i]);
      buffer << tmpBuffer;
    }
  }

  buffer << _strarrays.size() << " ";
  for(map< string,vector<string> >::const_iterator p = _strarrays.begin(); p != _strarrays.end(); p++) {
    vector<string> v(p->second);
    sprintf(tmpBuffer, " %s %d ", convertString(p->first).c_str(), v.size());
    buffer << tmpBuffer;
    for(int i = 0; i<v.size(); i++) {
      buffer << " " << convertString(v[i]) << " ";
    }
  }

  delete tmpBuffer;

  TCollection_AsciiString AS((char*)buffer.rdbuf()->str());

  return AS; 
}

//=======================================================================
/*!
 * Function : Load
 * Purpose  : Restores the attribute from the string
 */
//=======================================================================
void SALOMEDSImpl_AttributeParameter::Load(const TCollection_AsciiString& theValue) 
{ 
  Backup();

  _ints.clear();
  _reals.clear();
  _bools.clear();
  _strings.clear();
  _realarrays.clear();
  _intarrays.clear();

  istrstream buffer(theValue.ToCString(), strlen(theValue.ToCString()));

  int size, val, ival;
  double val2;
  string s, id;

  buffer >> size;
  for(int i = 1; i<=size; i++) {
    buffer >> id >> val;
    _ints[restoreString(id)] = val;
  }

  buffer >> size;
  for(int i = 1; i<=size; i++) {
    buffer >> id >> val2;
    _reals[restoreString(id)] = val2;
  }

  buffer >> size;
  for(int i = 1; i<=size; i++) {
    buffer >> id >> val;
    _bools[restoreString(id)] = val;
  }

  buffer >> size;
  for(int i = 1; i<=size; i++) {
    buffer >> id >> s;
    _strings[restoreString(id)] = restoreString(s);
  }
  
  buffer >> size;
  for(int i = 1; i<=size; i++) {
    buffer >> id >> val;
    vector<double> v;
    v.resize(val);
    for(int j = 0; j<val; j++) {
      buffer >> val2;
      v[j] = val2;
    }
    _realarrays[restoreString(id)] = v;
  }

  buffer >> size;
  for(int i = 1; i<=size; i++) {
    buffer >> id >> val;
    vector<int> v;
    v.resize(val);
    for(int j = 0; j<val; j++) {
      buffer >> ival;
      v[j] = ival;
    }
    _intarrays[restoreString(id)] = v;
  }
  
  buffer >> size;
  for(int i = 1; i<=size; i++) {
    buffer >> id >> val;
    vector<string> v;
    v.resize(val);
    for(int j = 0; j<val; j++) {
      buffer >> s;
      v[j] = restoreString(s);
    }
    _strarrays[restoreString(id)] = v;
  }
} 