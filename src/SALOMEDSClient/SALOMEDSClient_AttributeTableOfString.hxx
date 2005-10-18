//  File   : SALOMEDSClient_AttributeTableOfString.hxx
//  Author : Sergey RUIN
//  Module : SALOME

#ifndef SALOMEDSClient_AttributeTableOfString_HeaderFile
#define SALOMEDSClient_AttributeTableOfString_HeaderFile

#include <vector>
#include <string>
#include "SALOMEDSClient_definitions.hxx" 
#include "SALOMEDSClient_GenericAttribute.hxx" 

class SALOMEDSClient_AttributeTableOfString: public virtual SALOMEDSClient_GenericAttribute
{    
public:

  virtual void SetTitle(const std::string& theTitle) = 0;
  virtual std::string GetTitle() = 0;
  virtual void SetRowTitle(int theIndex, const std::string& theTitle) = 0;
  virtual void SetRowTitles(const std::vector<std::string>& theTitles) = 0;
  virtual std::vector<std::string> GetRowTitles() = 0;
  virtual void SetColumnTitle(int theIndex, const std::string& theTitle) = 0;
  virtual void SetColumnTitles(const std::vector<std::string>& theTitles) = 0;
  virtual std::vector<std::string> GetColumnTitles() = 0; 

  virtual void SetRowUnit(int theIndex, const std::string& theUnit) = 0;
  virtual void SetRowUnits(const std::vector<std::string>& theUnits) = 0;
  virtual std::vector<std::string> GetRowUnits() = 0;

  virtual int GetNbRows() = 0;
  virtual int GetNbColumns() = 0;
  virtual void AddRow(const std::vector<std::string>& theData) = 0;
  virtual void SetRow(int theRow, const std::vector<std::string>& theData) = 0;
  virtual std::vector<std::string> GetRow(int theRow) = 0;
  virtual void AddColumn(const std::vector<std::string>& theData) = 0;
  virtual void SetColumn(int theColumn, const std::vector<std::string>& theData) = 0;
  virtual std::vector<std::string> GetColumn(int theColumn) = 0;
  virtual void PutValue(const std::string& theValue, int theRow, int theColumn) = 0;
  virtual bool HasValue(int theRow, int theColumn) = 0;
  virtual std::string GetValue(int theRow, int theColumn) = 0;

  virtual std::vector<int> GetRowSetIndices(int theRow) = 0;
  virtual void SetNbColumns(int theNbColumns) = 0;

};

#endif