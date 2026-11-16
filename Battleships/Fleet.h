/***********************************************************************
Bachelor of Software Engineering
Media Design School at Strayer
Auckland
New Zealand
(c) 2026 Media Design School at Strayer
File Name : Fleet.h
Description : Fleet class definition for tracking ships and sunk status
Author : Campbell Roberts
Mail : Campbell.Roberts@mds.ac.nz
**************************************************************************/
#pragma once
#include "Constants.h"

struct SShip
{
    int iRow;
    int iCol;
    int iLength;
    bool bHorizontal;
    int iHits;
    bool bSunk;
};

class CFleet// TF: Class
{
private:// TF: Access Specifier
    SShip* m_pShips;
    int m_iShipCount;

public:
    CFleet();
    CFleet(const CFleet& _rOther);
    ~CFleet();
    CFleet& operator=(const CFleet&) = delete;
    void AddShipCells(int _iRow, int _iCol, int _iLength, bool _bHorizontal);
    bool RegisterHit(int _iRow, int _iCol);
    int GetShipsSunk() const;
};