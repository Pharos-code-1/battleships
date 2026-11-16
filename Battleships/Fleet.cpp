/***********************************************************************
Bachelor of Software Engineering
Media Design School at Strayer
Auckland
New Zealand
(c) 2026 Media Design School at Strayer
File Name : Fleet.cpp
Description : Fleet class implementation for tracking ships and sunk status
Author : Campbell Roberts
Mail : Campbell.Roberts@mds.ac.nz
**************************************************************************/
#include "Fleet.h"

CFleet::CFleet() : m_pShips(nullptr), m_iShipCount(0)// TF: Constructor // TF: Pointer Initialised
{   
    m_pShips = new SShip[NUMSHIPS];// TF: Dynamic Memory
    m_iShipCount = 0;
    for (int i = 0; i < NUMSHIPS; ++i)
    {
        m_pShips[i].iRow = 0;
        m_pShips[i].iCol = 0;
        m_pShips[i].iLength = 0;
        m_pShips[i].bHorizontal = true;
        m_pShips[i].iHits = 0;
        m_pShips[i].bSunk = false;
    }
}
CFleet::CFleet(const CFleet& _rOther) : m_pShips(nullptr), m_iShipCount(_rOther.m_iShipCount)// TF: Copy Constructor
{
    // own copy of the array so both fleets can be deleted safely
    m_pShips = new SShip[NUMSHIPS];
    for (int i = 0; i < NUMSHIPS; ++i)
    {
        m_pShips[i] = _rOther.m_pShips[i];
    }
}

CFleet::~CFleet()// TF: Destructor
{
    delete[] m_pShips;
    m_pShips = nullptr;
}

void CFleet::AddShipCells(int _iRow, int _iCol, int _iLength, bool _bHorizontal)
{
    if (m_iShipCount < NUMSHIPS)
    {
        m_pShips[m_iShipCount].iRow = _iRow;
        m_pShips[m_iShipCount].iCol = _iCol;
        m_pShips[m_iShipCount].iLength = _iLength;
        m_pShips[m_iShipCount].bHorizontal = _bHorizontal;
        m_pShips[m_iShipCount].iHits = 0;
        m_pShips[m_iShipCount].bSunk = false;
        m_iShipCount++;
    }
}

bool CFleet::RegisterHit(int _iRow, int _iCol)
{
    for (int i = 0; i < NUMSHIPS; ++i)
    {
        for (int j = 0; j < m_pShips[i].iLength; ++j)
        {
            int r = m_pShips[i].iRow;
            int c = m_pShips[i].iCol;

            if (m_pShips[i].bHorizontal)
            {
                c += j;
            }
            else
            {
                r += j;
            }

            if (r == _iRow && c == _iCol)
            {
                int* piHits = &m_pShips[i].iHits;
                ++(*piHits);// TF: Pointer Dereferenced
                if (m_pShips[i].iHits >= m_pShips[i].iLength)
                {
                    m_pShips[i].bSunk = true;
                }
                return m_pShips[i].bSunk;
            }
        }
    }
    return false;
}

int CFleet::GetShipsSunk() const
{
    int iSunkCount = 0;
    for (int i = 0; i < NUMSHIPS; ++i)
    {
        if (m_pShips[i].bSunk)
        {
            iSunkCount++;
        }
    }
    return iSunkCount;
}