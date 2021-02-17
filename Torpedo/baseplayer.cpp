#include "baseplayer.h"

baseplayer::baseplayer(int areaSize, int shipNum)
{
    _data.areaSize = areaSize;
    for(int i = 0; i < shipNum; i++)
    {
        _data.shipNumForSizes[i] = 1;
    }
    _data.online = false;
    initTable(_gameTable);
    fillShips();
}

Area baseplayer::getField(Coordinate c) const
{
    return _gameTable[c.x][c.y];
}

Ship baseplayer::getShipByID(int ID) const
{
    return _ships[ID-1];
}

void baseplayer::randomTable()
{
    resetTable(_gameTable);
    for (size_t i = 0; i < _ships.size(); i++)
    {
        bool notPlaced = true;
        while (notPlaced)
        {
            int startcolumn = rand() % _data.areaSize;
            int startrow = rand() % _data.areaSize;
            int endrow = startrow;
            int endcolumn = startcolumn;
            int orientation = rand() % 2;
            bool canBePlaced = true;
            if (orientation == 0)
            {
                for (int j = 0; j < _ships[i].size-1; j++)
                {
                    endrow++;
                }
            }
            else
            {
                for (int j = 0; j < _ships[i].size-1; j++)
                {
                    endcolumn++;
                }
            }
            // ellenőrizzük, kilógunk-e a tábláról
            if(endrow > _data.areaSize - 1 || endcolumn > _data.areaSize - 1)
            {
                canBePlaced = false;
            }

            // ellenőrizzük, hogy foglalt-e egy hely
            if(canBePlaced)
                for(int row = startrow; row <= endrow; row++)
                    for(int col = startcolumn; col <= endcolumn; col++)
                        if(_gameTable[row][col].shipID != 0)
                            canBePlaced = false;

            // ha le lehet rakni, akkor elhelyezzük a hajót
            if(canBePlaced)
            {
                for(int row = startrow; row <= endrow; row++)
                {
                    for(int col = startcolumn; col <= endcolumn; col++)
                    {
                        _gameTable[row][col].shipID = _ships[i].ID;
                    }
                }
            notPlaced = false;
            }
        }
    }
}

void baseplayer::initTable(std::vector<std::vector<Area>> &t)
{
    for (int i = 0; i < _data.areaSize; ++i)
    {
        std::vector<Area> tmpVec;
        for (int j = 0; j < _data.areaSize; ++j)
        {
            Area a;
            a.shipID = 0;
            a.isShot = false;
            tmpVec.push_back(a);
        }
        t.push_back(tmpVec);
    }
}

void baseplayer::resetTable(std::vector<std::vector<Area>> &t)
{
    for (int i = 0; i < _data.areaSize; i++)
    {
        for (int j = 0; j < _data.areaSize; j++)
        {
            t[i][j].isShot = false;
            t[i][j].shipID = 0;
        }
    }
}

void baseplayer::fillShips()
{
    int ID = 1;
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < _data.shipNumForSizes[i]; j++)
            {
                Ship s;
                s.ID = ID;
                s.hitPoint = i+2;
                s.size = i+2;
                _ships.push_back(s);
                ID++;
            }
}

void baseplayer::resetShips()
{
    for(size_t i = 0; i < _ships.size(); i++)
    {
        _ships[i].hitPoint = _ships[i].size;
    }
}

void baseplayer::getShot(Coordinate c)
{
    _gameTable[c.x][c.y].isShot = true;
    if(_gameTable[c.x][c.y].shipID)
        _ships[_gameTable[c.x][c.y].shipID-1].hitPoint--;
}

void baseplayer::newField(NewGameData data)
{
    _gameTable.clear();
    _ships.clear();
    _data = data;
    initTable(_gameTable);
    fillShips();
    randomTable();
}

