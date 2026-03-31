#include <iostream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <thread>
using namespace std;

struct stRedirectionGame
{
    char Key = 0;
    char PrevKey = 0;
    int CountRow = 0;
    int CountCol = 0;
    int PrevRow = 0;
    int PrevCol = 0;
    int Speed = 1;
};

struct stEating
{
    int EatRow = 0;
    int EatCol = 0;
};

struct stWennerGame
{
    bool YouWin = false;
    bool YouLost = false;
};

struct stNodeSnake
{
    int CountRow = 0;
    int CountCol = 0;
    int PrevRow = 0;
    int PrevCol = 0;
};

struct stDiesingGame
{
    char HeadSnake = 'O';
    char NodeSnake = '*';
    char EatingSnake = '&';
    char SpaceMap = ' ';
    char ColMap = '.';
    char RowMap = '-';
};


struct stGameSnak
{
    stRedirectionGame RedirectionGame;
    vector <stNodeSnake> LastOfSnak;
    stEating Eating;
    stDiesingGame DiesingGame;
    stWennerGame WennerGame;
    char** Arr = NULL;
    int SizeRow = 100;
    int SizeCol = 20;
    int Slowing = 101000;
    bool Flag = false;
    bool Erno = false;
    string Buffer;
};

void Sleaping(stGameSnak* GameSnak)
{
    usleep(GameSnak->Slowing);
}

int RandomNumber(int From, int To)
{
    int randNum = rand() % (To - From + 1) + From;
    return randNum;
}

bool StoringMatrix(stGameSnak *GameSnak)
{
    char** NewArr = NULL;
    GameSnak->Arr = new(std::nothrow) char* [GameSnak->SizeCol + 1];
    if (!GameSnak->Arr)
        return true;
    for (int i = 0; i < GameSnak->SizeCol; i++)
    {
        GameSnak->Arr[i] = new(std::nothrow) char[GameSnak->SizeRow + 1];
        if (!GameSnak->Arr[i])
            return true;
        for (int j = 0; j < GameSnak->SizeRow; j++)
            GameSnak->Arr[i][j] = GameSnak->DiesingGame.SpaceMap;
        GameSnak->Arr[i][GameSnak->SizeRow] = '\0';
    }
    GameSnak->Arr[GameSnak->SizeCol] = NULL;
    return false;
}

string PrintTap(int NumberTap)
{
    string Str('\t', NumberTap);
    return Str;
}

string PrintRedirection(char Key)
{
    if (tolower(Key) == 'z')
        return "up";
    else if (tolower(Key) == 's')
        return "down";
    else if (tolower(Key) == 'd')
        return "->";
    else if (tolower(Key) == 'q')
        return "<-";
    return "No moves";
}

void PrintState(stGameSnak* GameSnak)
{
    GameSnak->Buffer += "the Redirection : ";
    GameSnak->Buffer += PrintRedirection(GameSnak->RedirectionGame.Key);
    GameSnak->Buffer += " | ";

    GameSnak->Buffer += "counter col : ";
    GameSnak->Buffer += to_string(GameSnak->RedirectionGame.CountCol);
    GameSnak->Buffer += " | ";

    GameSnak->Buffer += "counter row : "; GameSnak->Buffer += to_string(GameSnak->RedirectionGame.CountRow);
    GameSnak->Buffer += "\n\n";
}
void ReturnCharFavorate(stGameSnak* GameSnak)
{
    GameSnak->Buffer += ' ';
    for (int i = 0; i < GameSnak->SizeRow; i++)
        GameSnak->Buffer += GameSnak->DiesingGame.RowMap;
    GameSnak->Buffer += '\n';
}
void Print(stGameSnak* GameSnak)
{
    if (!GameSnak->Arr)
        return;
    system("clear");
    PrintState(GameSnak);
    GameSnak->Arr[GameSnak->RedirectionGame.PrevCol][GameSnak->RedirectionGame.PrevRow] = GameSnak->DiesingGame.SpaceMap;
    GameSnak->Arr[GameSnak->RedirectionGame.CountCol][GameSnak->RedirectionGame.CountRow] = GameSnak->DiesingGame.HeadSnake;
    GameSnak->Arr[GameSnak->Eating.EatCol][GameSnak->Eating.EatRow] = GameSnak->DiesingGame.EatingSnake;
    for (int i = 0; i < GameSnak->LastOfSnak.size(); i++)
    {
        GameSnak->Arr[GameSnak->LastOfSnak[i].PrevCol][GameSnak->LastOfSnak[i].PrevRow] = GameSnak->DiesingGame.SpaceMap;
        GameSnak->Arr[GameSnak->LastOfSnak[i].CountCol][GameSnak->LastOfSnak[i].CountRow] = GameSnak->DiesingGame.NodeSnake;
    }
    for (int i = 0; i < GameSnak->SizeCol; i++)
    {
        if (!i)
            ReturnCharFavorate(GameSnak);
        GameSnak->Buffer += GameSnak->DiesingGame.ColMap;
        GameSnak->Buffer += GameSnak->Arr[i];
        GameSnak->Buffer += GameSnak->DiesingGame.ColMap;
        GameSnak->Buffer += '\n';
        if ( i == GameSnak->SizeCol - 1)
            ReturnCharFavorate(GameSnak);
    }
    cout << GameSnak->Buffer;
    GameSnak->Buffer.clear();
}

void RedirectionOfSnak(stGameSnak *GameSnak)
{
    GameSnak->RedirectionGame.PrevCol = GameSnak->RedirectionGame.CountCol;
    GameSnak->RedirectionGame.PrevRow = GameSnak->RedirectionGame.CountRow;
    if (tolower(GameSnak->RedirectionGame.Key) == 'w')
    {
        GameSnak->Flag = true;
        GameSnak->RedirectionGame.CountCol -= GameSnak->RedirectionGame.Speed;
        if (GameSnak->RedirectionGame.CountCol < 0)
            GameSnak->RedirectionGame.CountCol = GameSnak->SizeCol - 1;
    }
    else if (tolower(GameSnak->RedirectionGame.Key) == 's')
    {
        GameSnak->Flag = true;
        GameSnak->RedirectionGame.CountCol += GameSnak->RedirectionGame.Speed;
        if (GameSnak->RedirectionGame.CountCol == GameSnak->SizeCol)
            GameSnak->RedirectionGame.CountCol = 0;
    }
    else if (tolower(GameSnak->RedirectionGame.Key) == 'd')
    {
        GameSnak->Flag = true;
        GameSnak->RedirectionGame.CountRow += GameSnak->RedirectionGame.Speed;
        if (GameSnak->RedirectionGame.CountRow == GameSnak->SizeRow)
            GameSnak->RedirectionGame.CountRow = 0;
    }
    else if (tolower(GameSnak->RedirectionGame.Key) == 'a')
    {
        GameSnak->Flag = true;
        GameSnak->RedirectionGame.CountRow -= GameSnak->RedirectionGame.Speed;
        if (GameSnak->RedirectionGame.CountRow < 0)
            GameSnak->RedirectionGame.CountRow = GameSnak->SizeRow - 1;
    }
    GameSnak->RedirectionGame.PrevKey = GameSnak->RedirectionGame.Key;
}

void InitialEating(stGameSnak* GameSnak)
{
    GameSnak->Eating.EatRow = RandomNumber(0, GameSnak->SizeRow - 1);
    GameSnak->Eating.EatCol = RandomNumber(0, GameSnak->SizeCol - 1);
    while (GameSnak->Eating.EatRow == GameSnak->RedirectionGame.CountRow
        && GameSnak->Eating.EatCol == GameSnak->RedirectionGame.CountCol)
    {
        GameSnak->Eating.EatRow = RandomNumber(0, GameSnak->SizeRow - 1);
        GameSnak->Eating.EatCol = RandomNumber(0, GameSnak->SizeCol - 1);
    };
    
}

void DebugMoveLastOfSnak(stGameSnak* GameSnak)
{
    if (GameSnak->Flag)
    {
        GameSnak->Flag = false;
        for (int i = 0; i < GameSnak->LastOfSnak.size(); i++)
        {
            if (!i)
            {
                GameSnak->LastOfSnak[i].PrevCol = GameSnak->LastOfSnak[i].CountCol;
                GameSnak->LastOfSnak[i].PrevRow = GameSnak->LastOfSnak[i].CountRow;
                GameSnak->LastOfSnak[i].CountCol = GameSnak->RedirectionGame.PrevCol;
                GameSnak->LastOfSnak[i].CountRow = GameSnak->RedirectionGame.PrevRow;
            }
            if ((i + 1) < GameSnak->LastOfSnak.size())
            {
                GameSnak->LastOfSnak[i + 1].PrevCol = GameSnak->LastOfSnak[i + 1].CountCol;
                GameSnak->LastOfSnak[i + 1].PrevRow = GameSnak->LastOfSnak[i + 1].CountRow;
                GameSnak->LastOfSnak[i + 1].CountCol = GameSnak->LastOfSnak[i].PrevCol;
                GameSnak->LastOfSnak[i + 1].CountRow = GameSnak->LastOfSnak[i].PrevRow;
            }
        }
    }
}
void AddNodeInLastSnake(stGameSnak* GameSnak)
{
    if (GameSnak->Eating.EatCol == GameSnak->RedirectionGame.CountCol
        && GameSnak->Eating.EatRow == GameSnak->RedirectionGame.CountRow)
    {
        stNodeSnake NodeSnake;
        if (!GameSnak->LastOfSnak.empty())
        {
            NodeSnake.CountCol = GameSnak->LastOfSnak[GameSnak->LastOfSnak.size() - 1].PrevCol;
            NodeSnake.CountRow = GameSnak->LastOfSnak[GameSnak->LastOfSnak.size() - 1].PrevRow;
        }
        else
        {
            NodeSnake.CountCol = GameSnak->RedirectionGame.PrevCol;
            NodeSnake.CountRow = GameSnak->RedirectionGame.PrevRow;
        }
        InitialEating(GameSnak);
        GameSnak->LastOfSnak.push_back(NodeSnake);
    }
}
void PageLost()
{
    cout << "You lost " << endl;
}
bool GameOver(stGameSnak* GameSnak)
{
    if (GameSnak->Arr[GameSnak->RedirectionGame.CountCol]
        [GameSnak->RedirectionGame.CountRow] == GameSnak->DiesingGame.NodeSnake)
    {
        Sleaping(GameSnak);
        system("clear");
        PageLost();
        GameSnak->WennerGame.YouLost = true;
        return (true);
    }
    return (false);
}


void PrintViewGame(stGameSnak* GameSnak)
{
    while (true)
    {
        if (GameSnak->Erno)
            return;
        RedirectionOfSnak(GameSnak);
        AddNodeInLastSnake(GameSnak);
        DebugMoveLastOfSnak(GameSnak);
        Sleaping(GameSnak);
        Print(GameSnak);
        if (GameOver(GameSnak))
            return;
    }
}
void InputGame(stGameSnak* GameSnak)
{
    while (true)
    {
        if (GameSnak->WennerGame.YouLost)
            return;
        string Input;
        if (!getline(cin, Input))
        {
            GameSnak->Erno = true;
            return;
        }
        if (Input.size() > 0)
            GameSnak->RedirectionGame.Key = Input[0];
    }
}

void FreeMap(stGameSnak* GameSnak)
{
    if (!GameSnak->Arr)
        return;
    for (int i = 0; i < GameSnak->SizeCol; i++)
        delete[] GameSnak->Arr[i];
    delete[] GameSnak->Arr;
    GameSnak->Arr = NULL;
}

short StartGame(stGameSnak *GameSnak)
{
    if (StoringMatrix(GameSnak))
    {
        cout << "Error in storing data" << endl;
        return 1;
    }
    InitialEating(GameSnak);
    thread Pthread1(PrintViewGame, GameSnak);
    thread Pthread2(InputGame, GameSnak);
    Pthread1.join();
    Pthread2.join();
    FreeMap(GameSnak);
    return GameSnak->Erno;
}

int main()
{
    char **Arr = NULL;
    stGameSnak GameSnak;
    GameSnak.Buffer.resize((GameSnak.SizeCol * GameSnak.SizeRow) * 2);
    srand(time(0));
    return (StartGame(&GameSnak));
    
}