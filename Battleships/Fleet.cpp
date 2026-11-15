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

CFleet::CFleet()
{
    m_iShipCount = 0;
    for (int i = 0; i < NUMSHIPS; ++i)
    {
        m_Ships[i].iRow = 0;
        m_Ships[i].iCol = 0;
        m_Ships[i].iLength = 0;
        m_Ships[i].bHorizontal = true;
        m_Ships[i].iHits = 0;
        m_Ships[i].bSunk = false;
    }
}

void CFleet::AddShipCells(int _iRow, int _iCol, int _iLength, bool _bHorizontal)
{
    if (m_iShipCount < NUMSHIPS)
    {
        m_Ships[m_iShipCount].iRow = _iRow;
        m_Ships[m_iShipCount].iCol = _iCol;
        m_Ships[m_iShipCount].iLength = _iLength;
        m_Ships[m_iShipCount].bHorizontal = _bHorizontal;
        m_Ships[m_iShipCount].iHits = 0;
        m_Ships[m_iShipCount].bSunk = false;
        m_iShipCount++;
    }
}

bool CFleet::RegisterHit(int _iRow, int _iCol)
{
    for (int i = 0; i < NUMSHIPS; ++i)
    {
        for (int j = 0; j < m_Ships[i].iLength; ++j)
        {
            int r = m_Ships[i].iRow;
            int c = m_Ships[i].iCol;

            if (m_Ships[i].bHorizontal)
            {
                c += j;
            }
            else
            {
                r += j;
            }

            if (r == _iRow && c == _iCol)
            {
                m_Ships[i].iHits++;
                if (m_Ships[i].iHits >= m_Ships[i].iLength)
                {
                    m_Ships[i].bSunk = true;
                }
                return m_Ships[i].bSunk;
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
        if (m_Ships[i].bSunk)
        {
            iSunkCount++;
        }
    }
    return iSunkCount;
}