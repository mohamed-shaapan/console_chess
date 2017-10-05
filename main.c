#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
//Start-------------------------------------------------Declare GLOBAL VARIABLES--------------------------------------------------
//create object PIECE
struct PIECE {
    char displayName[15];
    char type[15];
    char team;
    char enemy;
    int step;
    char status[15];
    //-------------------
    int initialRow; int initialColumn;
    int currentRow; int currentColumn;
    int teamArrayLocation;
    //-------------------
    int nextValidPositions[8][7][2];
};
//create the runtime database (Board)
struct PIECE runTimeDatabase[8][8];//try to rename it to "runTimeChessBoard"
//create list of teammates
struct PIECE whiteTeam[1][16];
struct PIECE blackTeam[1][16];
//create a global object of type BLANK
struct PIECE blankObject;
//game status
char gameType[15];
char gameStatus[15];
char playerOrder[15];
char playerTurn;
int playCount;
//create global variables for move parameters
struct PIECE pieceToMoveVariable;

char pieceToMoveVariableName[15];
char targetBlockVariableName[15];
int fromRowVariable;
int fromColumnVariable;
int toRowVariable;
int toColumnVariable;
//create global variables for move parameters
//Create Global Variables Of Next Valid Promotion Display Name
char nextValidWhiteTeamPromotionDisplayNames[4][8][15];
char nextValidBlackTeamPromotionDisplayNames[4][8][15];
char promotionRank[15];
char promotionDisplayName[15];
//Create Global Variables Of Next Valid Promotion Display Name

//End---------------------------------------------------Declare GLOBAL VARIABLES--------------------------------------------------

//Start----------------------------------------Initialize Piece Next Valid Display Name-------------------------------------------
void initializeWhiteTeamNextValidPromotionDisplayNames(){
    FILE *filePointer;
    filePointer=fopen("Next Valid White Piece Promotion Names.txt","r");
    char obtainedData[15];
    int row;
    for(row=1; row<=4; row+=1){
        //00-dismiss first line
        fgets(obtainedData, 100, (FILE*)filePointer);
        //01-obtain next valid name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(nextValidWhiteTeamPromotionDisplayNames[row-1][0], obtainedData);
        //01-obtain next valid name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(nextValidWhiteTeamPromotionDisplayNames[row-1][1], obtainedData);
        //01-obtain next valid name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(nextValidWhiteTeamPromotionDisplayNames[row-1][2], obtainedData);
        //01-obtain next valid name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(nextValidWhiteTeamPromotionDisplayNames[row-1][3], obtainedData);
        //01-obtain next valid name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(nextValidWhiteTeamPromotionDisplayNames[row-1][4], obtainedData);
        //01-obtain next valid name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(nextValidWhiteTeamPromotionDisplayNames[row-1][5], obtainedData);
        //01-obtain next valid name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(nextValidWhiteTeamPromotionDisplayNames[row-1][6], obtainedData);
        //01-obtain next valid name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(nextValidWhiteTeamPromotionDisplayNames[row-1][7], obtainedData);
    }
    fclose(filePointer);
}
void initializeBlackTeamNextValidPromotionDisplayNames(){
    FILE *filePointer;
    filePointer=fopen("Next Valid Black Piece Promotion Names.txt","r");
    char obtainedData[15];
    int row;
    for(row=1; row<=4; row+=1){
        //00-dismiss first line
        fgets(obtainedData, 100, (FILE*)filePointer);
        //01-obtain next valid name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(nextValidBlackTeamPromotionDisplayNames[row-1][0], obtainedData);
        //01-obtain next valid name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(nextValidBlackTeamPromotionDisplayNames[row-1][1], obtainedData);
        //01-obtain next valid name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(nextValidBlackTeamPromotionDisplayNames[row-1][2], obtainedData);
        //01-obtain next valid name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(nextValidBlackTeamPromotionDisplayNames[row-1][3], obtainedData);
        //01-obtain next valid name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(nextValidBlackTeamPromotionDisplayNames[row-1][4], obtainedData);
        //01-obtain next valid name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(nextValidBlackTeamPromotionDisplayNames[row-1][5], obtainedData);
        //01-obtain next valid name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(nextValidBlackTeamPromotionDisplayNames[row-1][6], obtainedData);
        //01-obtain next valid name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(nextValidBlackTeamPromotionDisplayNames[row-1][7], obtainedData);
    }
    fclose(filePointer);
}
//Start----------------------------------------Initialize Piece Next Valid Display Name-------------------------------------------

//Start------------------------------------------------Initialize Move Parameters-------------------------------------------------
void initializeMoveParameters(){
    pieceToMoveVariable=blankObject;
    strcpy(pieceToMoveVariableName, "VOID");
    strcpy(targetBlockVariableName, "VOID");
    fromRowVariable=-1;
    fromColumnVariable=-1;
    toRowVariable=-1;
    toColumnVariable=-1;
}
//End--------------------------------------------------Initialize Move Parameters-------------------------------------------------

//Start-----------------------------------------Initialize White Team Array-------------------------------------------------------
void initializeWhiteTeamArray(){
    FILE *filePointer;
    filePointer=fopen("WhiteTeamAttributes.txt","r");
    char obtainedData[15];
    int pieceId;
    for(pieceId=1; pieceId<=16; pieceId+=1){
        //00-dismiss first line
        fgets(obtainedData, 100, (FILE*)filePointer);
        //01-obtain display name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(whiteTeam[0][pieceId-1].displayName, obtainedData);
        //02-obtain piece type
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(whiteTeam[0][pieceId-1].type, obtainedData);
        //03-obtain team identifier
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        whiteTeam[0][pieceId-1].team=obtainedData[0];
        //04-obtain enemy identifier
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        whiteTeam[0][pieceId-1].enemy=obtainedData[0];
        //05-obtain piece step
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        whiteTeam[0][pieceId-1].step=atoi(obtainedData);
        //06-obtain duty status
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(whiteTeam[0][pieceId-1].status, obtainedData);
        //07-obtain initial row
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        whiteTeam[0][pieceId-1].initialRow=atoi(obtainedData);
        //08-obtain initial column
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        whiteTeam[0][pieceId-1].initialColumn=atoi(obtainedData);
        //09-obtain current row
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        whiteTeam[0][pieceId-1].currentRow=atoi(obtainedData);
        //10-obtain current column
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        whiteTeam[0][pieceId-1].currentColumn=atoi(obtainedData);
        //11-obtain location in team array
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        whiteTeam[0][pieceId-1].teamArrayLocation=atoi(obtainedData);
        //12-set next valid possible positions
        setPieceNextValidPositions(whiteTeam[0][pieceId-1], whiteTeam[0][pieceId-1].nextValidPositions);
    }
    fclose(filePointer);
}
//End-------------------------------------------Initialize White Team Array-------------------------------------------------------

//Start-----------------------------------------Initialize Black Team Array-------------------------------------------------------
void initializeBlackTeamArray(){
    FILE *filePointer;
    filePointer=fopen("BlackTeamAttributes.txt","r");
    char obtainedData[15];
    int pieceId;
    for(pieceId=1; pieceId<=16; pieceId+=1){
        //00-dismiss first line
        fgets(obtainedData, 100, (FILE*)filePointer);
        //01-obtain display name
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(blackTeam[0][pieceId-1].displayName, obtainedData);
        //02-obtain piece type
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(blackTeam[0][pieceId-1].type, obtainedData);
        //03-obtain team identifier
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        blackTeam[0][pieceId-1].team=obtainedData[0];
        //04-obtain enemy identifier
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        blackTeam[0][pieceId-1].enemy=obtainedData[0];
        //05-obtain piece step
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        blackTeam[0][pieceId-1].step=atoi(obtainedData);
        //06-obtain duty status
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        strcpy(blackTeam[0][pieceId-1].status, obtainedData);
        //07-obtain initial row
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        blackTeam[0][pieceId-1].initialRow=atoi(obtainedData);
        //08-obtain initial column
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        blackTeam[0][pieceId-1].initialColumn=atoi(obtainedData);
        //09-obtain current row
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        blackTeam[0][pieceId-1].currentRow=atoi(obtainedData);
        //10-obtain current column
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        blackTeam[0][pieceId-1].currentColumn=atoi(obtainedData);
        //11-obtain location in team array
        fgets(obtainedData, 100, (FILE*)filePointer);
        strtok(obtainedData, "\n");
        blackTeam[0][pieceId-1].teamArrayLocation=atoi(obtainedData);
        //12-set next valid possible positions
        setPieceNextValidPositions(blackTeam[0][pieceId-1], blackTeam[0][pieceId-1].nextValidPositions);
    }
    fclose(filePointer);
}
//End-------------------------------------------Initialize Black Team Array-------------------------------------------------------

//Start-----------------------------------------Initialize Blank Object-----------------------------------------------------------
void initializeBlankObject(){
    //initialize blank object
    strcpy(blankObject.displayName, "000");
    strcpy(blankObject.type, "BLANK");
    blankObject.team='V';
    blankObject.enemy='V';
    strcpy(blankObject.status, "VOID");
    blankObject.step=0;
    blankObject.initialRow=-1;
    blankObject.initialColumn=-1;
    blankObject.currentRow=-1;
    blankObject.currentColumn=-1;
    blankObject.teamArrayLocation=-1;
    //set next valid moves for blank object
    int r;
    for(r=1; r<=8; r+=1){
        int c;
        for(c=1; c<=7; c+=1){
            blankObject.nextValidPositions[r-1][c-1][0]=-1;
            blankObject.nextValidPositions[r-1][c-1][1]=-1;
        }
    }
}
//End-------------------------------------------Initialize Blank Object-----------------------------------------------------------

//Start-------------------------------------Place White Pieces On Board-----------------------------------------------------------
void placeWhiteTeamOnBoard(){
    int pieceId;
    for(pieceId=1; pieceId<=16; pieceId+=1){
        int cr=whiteTeam[0][pieceId-1].currentRow;
        int cc=whiteTeam[0][pieceId-1].currentColumn;
        runTimeDatabase[cr][cc]=whiteTeam[0][pieceId-1];
    }
}
//End-------------------------------------Place White Pieces On Board-------------------------------------------------------------

//Start-------------------------------------Place Black Pieces On Board-----------------------------------------------------------
void placeBlackTeamOnBoard(){
    int pieceId;
    for(pieceId=1; pieceId<=16; pieceId+=1){
        int cr=blackTeam[0][pieceId-1].currentRow;
        int cc=blackTeam[0][pieceId-1].currentColumn;
        runTimeDatabase[cr][cc]=blackTeam[0][pieceId-1];
    }
}
//End---------------------------------------Place Black Pieces On Board-----------------------------------------------------------

//Start-------------------------------------Fill Board with Blank Objects---------------------------------------------------------
void fillBoardWithBlankObjects(){
    int row;
    for(row=1; row<=8; row+=1){
        int column;
        for(column=1; column<=8; column+=1){
            runTimeDatabase[row-1][column-1]=blankObject;
        }
    }
}
//End---------------------------------------Fill Board with Blank Objects---------------------------------------------------------

//Start------------------------------------------------Initialize New Game--------------------------------------------------------
void initializeNewGame(){
    //00-initialize blank object
    initializeBlankObject();
    //01-initialize white team
    initializeWhiteTeamArray();
    //02-initialize black team
    initializeBlackTeamArray();
    //04-place pieces on board
    fillBoardWithBlankObjects();
    placeWhiteTeamOnBoard();
    placeBlackTeamOnBoard();
    //set game status to ON GOING
    strcpy(gameStatus, "ON GOING");
    playerTurn='W';
    playCount=0;
    initializeMoveParameters();
    //initialize next valid promotion names
    initializeWhiteTeamNextValidPromotionDisplayNames();
    initializeBlackTeamNextValidPromotionDisplayNames();
    strcpy(promotionRank, "VOID");
    strcpy(promotionDisplayName, "VOID");
    //initialize undo files
    FILE *filePointer;
    filePointer = fopen( "Saved Game Progress Arrays For Undo.bin" , "w" );
    FILE *filePointer2;
    filePointer2=fopen("Saved Game Progress Misc For Undo.txt" ,"w");
    fclose(filePointer);
    fclose(filePointer2);
}
//End--------------------------------------------------Initialize New Game--------------------------------------------------------


//Start---------------------------------------------------Dispaly Chess Board-------------------------------------------------
void displayBoard(){
    printf("\n--------------------------------------------\n\n");
    char columnNames[10][10]={"   ", " a "," b ", " c ", " d ", " e ", " f ", " g ", " h ", "   "};
    char rowNames[10][10]={" ", "8","7", "6", "5", "4", "3", "2", "1", " "};
    //display column names
    int lp;
    printf(" ");
    for(lp=1; lp<=10; lp+=1){
        printf(" %s", columnNames[lp-1]);
    }
    //looping
    int loop1;
    for(loop1=1; loop1<=8; loop1+=1){
        printf("\n\n  ");
        printf("%s  ", rowNames[loop1]);
        int loop2;
        for(loop2=1; loop2<=8; loop2+=1){
            printf(" %s", runTimeDatabase[loop1-1][loop2-1].displayName);
        }
        printf("   %s", rowNames[loop1]);
    }
    //display column name
    int lp2;
    printf("\n\n ");
    for(lp2=1; lp2<=10; lp2+=1){
        printf(" %s", columnNames[lp2-1]);
    }
    printf("\n\n--------------------------------------------");
}
//End-----------------------------------------------------Dispaly Chess Board-------------------------------------------------------

//Start-------------------------------------------Display Dead Pieces---------------------------------------------------------------
void displayDeadPieces(){
    printf("\n--------------------------------------------");
    printf("\nDead White Pieces :\n");
    int a;
    for(a=1; a<=16; a+=1){
        if(strcmp(whiteTeam[0][a-1].status, "DEAD")==0){
            printf("%s\t", whiteTeam[0][a-1].displayName);
        }
    }
    printf("\nDead Black Pieces :\n");
    int b;
    for(b=1; b<=16; b+=1){
        if(strcmp(blackTeam[0][b-1].status, "DEAD")==0){
            printf("%s\t", blackTeam[0][b-1].displayName);
        }
    }
    printf("\n--------------------------------------------");
}
//End---------------------------------------------Display Dead Pieces---------------------------------------------------------------

//Start-------------------------------------------------------display Opening Message-----------------------------------------------------------
void displayOpeningMessage(){
    FILE *filePointer;
    filePointer=fopen("Opening Message.txt", "r");
    char tmpTxt[255];
    while(!feof(filePointer)){
        fgets(tmpTxt, 255, (FILE*)filePointer);
        strtok(tmpTxt, "\n");
        printf("\n%s", tmpTxt);
    }
}
//End---------------------------------------------------------display Opening Message-----------------------------------------------------------

//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************

//Start-----------------------------------Set Next Valid Positions for Piece-------------General Piece------------------------------
void setPieceNextValidPositions(struct PIECE pieceToModify, int arrayToModify[8][7][2]){
//this function sets the next possible positions of a piece
//assuming that only this piece is on the board and next valid locations can be out board limits 8*8
    //get piece info
    int r=pieceToModify.currentRow;
    int c=pieceToModify.currentColumn;
    char t[15]; strcpy(t, pieceToModify.type);
    //---------------------------------------------------------------------
    if(strcmp(t, "KING")==0){
        setKingNextPossibleMoves(arrayToModify,r,c);
    }
    if(strcmp(t, "QUEEN")==0){
        setQueenNextPossibleMoves(arrayToModify,r,c);
    }
    if(strcmp(t, "BISHOP")==0){
        setBishopNextPossbileMoves(arrayToModify,r,c);
    }
    if(strcmp(t, "KNIGHT")==0){
        setKnightNextPossbileMoves(arrayToModify,r,c);
    }
    if(strcmp(t, "ROOK")==0){
        setRookNextPossibleMoves(arrayToModify,r,c);
    }
    if(strcmp(t, "PAWN")==0){
        setPawnNextPossibleMoves(pieceToModify,arrayToModify,r,c);
    }
}
//End-------------------------------------Set Next Valid Positions for Piece-------------General Piece------------------------------

//Start-----------------------------------Set Next Valid Positions for Piece------------Specific Piece------------------------------
//set king next valid moves
void setKingNextPossibleMoves(int arrayToModify[8][7][2] ,int r, int c){
    //nullify the entire array
    nullifyNextValidPositionsArray(arrayToModify);
    //set next valid positions
    setUpPositions(arrayToModify,r,c,1);
    setDownPositions(arrayToModify,r,c,1);
    setRightPositions(arrayToModify,r,c,1);
    setLeftPositions(arrayToModify,r,c,1);
    setD1Positions(arrayToModify,r,c,1);
    setD2Positions(arrayToModify,r,c,1);
    setD3Positions(arrayToModify,r,c,1);
    setD4Positions(arrayToModify,r,c,1);
}
//set queen next valid moves
void setQueenNextPossibleMoves(int arrayToModify[8][7][2] ,int r, int c){
    //nullify the entire array
    nullifyNextValidPositionsArray(arrayToModify);
    //set next valid positions
    setUpPositions(arrayToModify,r,c,7);
    setDownPositions(arrayToModify,r,c,7);
    setRightPositions(arrayToModify,r,c,7);
    setLeftPositions(arrayToModify,r,c,7);
    setD1Positions(arrayToModify,r,c,7);
    setD2Positions(arrayToModify,r,c,7);
    setD3Positions(arrayToModify,r,c,7);
    setD4Positions(arrayToModify,r,c,7);
}
//set next possible moves for the bishop
void setBishopNextPossbileMoves(int arrayToModify[8][7][2] ,int r, int c){
    //nullify the entire array
    nullifyNextValidPositionsArray(arrayToModify);
    //set next valid positions
    setD1Positions(arrayToModify,r,c,7);
    setD2Positions(arrayToModify,r,c,7);
    setD3Positions(arrayToModify,r,c,7);
    setD4Positions(arrayToModify,r,c,7);
}
//set next possible moves for the knight
void setKnightNextPossbileMoves(int arrayToModify[8][7][2] ,int r, int c){
    //0- nullify the entire array
    nullifyNextValidPositionsArray(arrayToModify);
    //set next valid positions
    setKNPositions(arrayToModify,r,c);
}
//set the next possible moves for the rook
void setRookNextPossibleMoves(int arrayToModify[8][7][2] ,int r, int c){
    //0-nullify the entire array
    nullifyNextValidPositionsArray(arrayToModify);
    //set next valid position
    setUpPositions(arrayToModify,r,c,7);
    setDownPositions(arrayToModify,r,c,7);
    setRightPositions(arrayToModify,r,c,7);
    setLeftPositions(arrayToModify,r,c,7);
}
//set the next possible moves for the Pawn
void setPawnNextPossibleMoves(struct PIECE pieceToModify, int arrayToModify[8][7][2] ,int r, int c){
    //00- nullify the entire array
    nullifyNextValidPositionsArray(arrayToModify);
    //White Pawn
    if(pieceToModify.team=='W'){
        //01- attack
        if(runTimeDatabase[r-1][c+1].team==pieceToModify.enemy){
            setD1Positions(arrayToModify,r,c,1);
        }
        if(runTimeDatabase[r-1][c-1].team==pieceToModify.enemy){
            setD4Positions(arrayToModify,r,c,1);
        }
        //02- Moves
        if((r==pieceToModify.initialRow)&&(c==pieceToModify.initialColumn)){
            setUpPositions(arrayToModify,r,c,2);
        }
        if((r!=pieceToModify.initialRow)||(c!=pieceToModify.initialColumn)){
            setUpPositions(arrayToModify,r,c,1);
        }
    }else{
    //Black Pawn
        //01- attack
        if(runTimeDatabase[r+1][c+1].team==pieceToModify.enemy){
            setD2Positions(arrayToModify,r,c,1);
        }
        if(runTimeDatabase[r+1][c-1].team==pieceToModify.enemy){
            setD3Positions(arrayToModify,r,c,1);
        }
        //02- Moves
        if((r==pieceToModify.initialRow)&&(c==pieceToModify.initialColumn)){
            setDownPositions(arrayToModify,r,c,2);
        }
        if((r!=pieceToModify.initialRow)||(c!=pieceToModify.initialColumn)){
            setDownPositions(arrayToModify,r,c,1);
        }
    }
}
//End-------------------------------------Set Next Valid Positions for Piece------------Specific Piece------------------------------


//Start------------------Set Next Valid Positions for Piece------------Specific Direction & Piece-----------------------------------
//create up positions
void setUpPositions(int arrayToModify[8][7][2] ,int r, int c, int s){
    //r: current row, c: current column, s: step, d: direction
    int loop;
    for(loop=1; loop<=s; loop+=1){
        if(r-loop<0){
            break;
        }
        arrayToModify[0][loop-1][0]=r-loop;
        arrayToModify[0][loop-1][1]=c;
    }
}
//create down positions
void setDownPositions(int arrayToModify[8][7][2] ,int r, int c, int s){
    //r: current row, c: current column, s: step, d: direction
    int loop;
    for(loop=1; loop<=s; loop+=1){
        if(r+loop>7){
            break;
        }
        arrayToModify[1][loop-1][0]=r+loop;
        arrayToModify[1][loop-1][1]=c;
    }
}
//create right positions
void setRightPositions(int arrayToModify[8][7][2] ,int r, int c, int s){
    //r: current row, c: current column, s: step, d: direction
    int loop;
    for(loop=1; loop<=s; loop+=1){
        if(c+loop>7){
            break;
        }
        arrayToModify[2][loop-1][0]=r;
        arrayToModify[2][loop-1][1]=c+loop;
    }
}
//create left positions
void setLeftPositions(int arrayToModify[8][7][2] ,int r, int c, int s){
    //r: current row, c: current column, s: step, d: direction
    int loop;
    for(loop=1; loop<=s; loop+=1){
        if(c-loop<0){
            break;
        }
        arrayToModify[3][loop-1][0]=r;
        arrayToModify[3][loop-1][1]=c-loop;
    }
}
//create D1 positions
void setD1Positions(int arrayToModify[8][7][2] ,int r, int c, int s){
    //r: current row, c: current column, s: step, d: direction
    int loop;
    for(loop=1; loop<=s; loop+=1){
        if((r-loop<0)||(c+loop>7)){
            break;
        }
        arrayToModify[4][loop-1][0]=r-loop;
        arrayToModify[4][loop-1][1]=c+loop;
    }
}
//create D2 positions
void setD2Positions(int arrayToModify[8][7][2] ,int r, int c, int s){
    //r: current row, c: current column, s: step, d: direction
    int loop;
    for(loop=1; loop<=s; loop+=1){
        if((r+loop>7)||(c+loop>7)){
            break;
        }
        arrayToModify[5][loop-1][0]=r+loop;
        arrayToModify[5][loop-1][1]=c+loop;
    }
}
//create D3 positions
void setD3Positions(int arrayToModify[8][7][2] ,int r, int c, int s){
    //r: current row, c: current column, s: step, d: direction
    int loop;
    for(loop=1; loop<=s; loop+=1){
        if((r+loop>7)||(c-loop<0)){
            break;
        }
        arrayToModify[6][loop-1][0]=r+loop;
        arrayToModify[6][loop-1][1]=c-loop;
    }
}
//create D4 positions
void setD4Positions(int arrayToModify[8][7][2] ,int r, int c, int s){
    //r: current row, c: current column, s: step, d: direction
    int loop;
    for(loop=1; loop<=s; loop+=1){
        if((r-loop<0)||(c-loop<0)){
            break;
        }
        arrayToModify[7][loop-1][0]=r-loop;
        arrayToModify[7][loop-1][1]=c-loop;
    }
}
//create knight positions
void setKNPositions(int arrayToModify[8][7][2],int r, int c){
    //1st possible move
    arrayToModify[0][0][0]=r-2;
    arrayToModify[0][0][1]=c+1;
    //2nd possible move
    arrayToModify[1][0][0]=r+2;
    arrayToModify[1][0][1]=c+1;
    //3rd possible move
    arrayToModify[2][0][0]=r+2;
    arrayToModify[2][0][1]=c-1;
    //4th possible move
    arrayToModify[3][0][0]=r-2;
    arrayToModify[3][0][1]=c-1;
    //5th possible move
    arrayToModify[4][0][0]=r-1;
    arrayToModify[4][0][1]=c+2;
    //6th possible move
    arrayToModify[5][0][0]=r+1;
    arrayToModify[5][0][1]=c+2;
    //7th possible move
    arrayToModify[6][0][0]=r+1;
    arrayToModify[6][0][1]=c-2;
    //8th possible move
    arrayToModify[7][0][0]=r-1;
    arrayToModify[7][0][1]=c-2;
}
//End--------------------Set Next Valid Positions for Piece------------Specific Direction & Piece-----------------------------------

//start-------------------------------Nullify Next Valid Positions Array---------Specific Array-------------------------------------
void nullifyNextValidPositionsArray(int arraToModify[8][7][2]){
    int row;
    for(row=1; row<=8; row+=1){
        int column;
        for(column=1; column<=7; column+=1){
            arraToModify[row-1][column-1][0]=-1;
            arraToModify[row-1][column-1][1]=-1;
        }
    }
}
//End---------------------------------Nullify Next Valid Positions Array---------Specific Array-------------------------------------

void displayNextValidPositions(struct PIECE pieceToTest){
    int row;
    for(row=1; row<=8; row+=1){
        int column;
        for(column=1; column<=7; column+=1){
            int nvr=pieceToTest.nextValidPositions[row-1][column-1][0];
            int nvc=pieceToTest.nextValidPositions[row-1][column-1][1];
            printf("\n(R,C)=%d,%d", nvr,nvc);
        }
    }
}


//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************

//Start-------------------------Investigate Is King In Danger-----------All Directions--------------------------------
int investigateIsKingInDanger(char kingTeam){
//this function takes the location of a king
//this function returns 1 if that king is in danger (check!) and returns 0 if not

    //01-obtain king current row and column
    int kcr; int kcc;
    if(kingTeam=='W'){
        kcr=whiteTeam[0][0].currentRow;
        kcc=whiteTeam[0][0].currentColumn;
    }
    if(kingTeam=='B'){
        kcr=blackTeam[0][0].currentRow;
        kcc=blackTeam[0][0].currentColumn;
    }
    //check danger from every direction
    if(isUpDangerous(kcr,kcc)==1){
        return 1;
    }
    if(isDownDangerous(kcr,kcc)==1){
        return 1;
    }
    if(isRightDangerous(kcr,kcc)==1){
        return 1;
    }
    if(isLeftDangerous(kcr,kcc)==1){
        return 1;
    }
    if(isD1Dangerous(kcr,kcc)==1){
        return 1;
    }
    if(isD2Dangerous(kcr,kcc)==1){
        return 1;
    }
    if(isD3Dangerous(kcr,kcc)==1){
        return 1;
    }
    if(isD4Dangerous(kcr,kcc)==1){
        return 1;
    }
    if(isKn1Dangerous(kcr,kcc)==1){
        return 1;
    }
    if(isKn2Dangerous(kcr,kcc)==1){
        return 1;
    }
    if(isKn3Dangerous(kcr,kcc)==1){
        return 1;
    }
    if(isKn4Dangerous(kcr,kcc)==1){
        return 1;
    }
    if(isKn5Dangerous(kcr,kcc)==1){
        return 1;
    }
    if(isKn6Dangerous(kcr,kcc)==1){
        return 1;
    }
    if(isKn7Dangerous(kcr,kcc)==1){
        return 1;
    }
    if(isKn8Dangerous(kcr,kcc)==1){
        return 1;
    }
    return 0;
}
//End---------------------------Investigate Is King In Danger-----------All Directions--------------------------------

//Start-------------------------Investigate Is King In Danger-----------Specific Direction----------------------------
//Test Up Dangers
int isUpDangerous(int kcr, int kcc){
    //kcr: king current row, kcc: king current column
    char ourEnemy=runTimeDatabase[kcr][kcc].enemy;
    char ourTeam=runTimeDatabase[kcr][kcc].team;
    int a;
    for(a=1; a<=7; a+=1){
        //if target block out of board dimensions break
        if((kcr-a)<0){
            break;
        }
        //tbtm: target block team, tbtp: target block type
        char tbtm=runTimeDatabase[kcr-a][kcc].team;
        char tbtp[15]; strcpy(tbtp, runTimeDatabase[kcr-a][kcc].type);
        if(tbtm==ourEnemy){
            if((a==1)&&(strcmp(tbtp, "KING")==0)){
                return 1;
            }
            if((strcmp(tbtp, "QUEEN")==0)||(strcmp(tbtp, "ROOK")==0)){
                return 1;
            }
            return 0;
        }
        if(tbtm=='V'){
            continue;
        }
        if(tbtm==ourTeam){
            return 0;
        }
    }
    return 0;
}
//Test Down Dangers
int isDownDangerous(int kcr, int kcc){
    //kcr: king current row, kcc: king current column
    char ourEnemy=runTimeDatabase[kcr][kcc].enemy;
    char ourTeam=runTimeDatabase[kcr][kcc].team;
    int a;
    for(a=1; a<=7; a+=1){
        //if target block out of board dimensions break
        if((kcr+a)>7){
            break;
        }
        //tbtm: target block team, tbtp: target block type
        char tbtm=runTimeDatabase[kcr+a][kcc].team;
        char tbtp[15]; strcpy(tbtp, runTimeDatabase[kcr+a][kcc].type);
        if(tbtm==ourEnemy){
            if((a==1)&&(strcmp(tbtp, "KING")==0)){
                return 1;
            }
            if((strcmp(tbtp, "QUEEN")==0)||(strcmp(tbtp, "ROOK")==0)){
                return 1;
            }
            return 0;
        }
        if(tbtm=='V'){
            continue;
        }
        if(tbtm==ourTeam){
            return 0;
        }
    }
    return 0;
}
//Test Right Dangers
int isRightDangerous(int kcr, int kcc){
    //kcr: king current row, kcc: king current column
    char ourEnemy=runTimeDatabase[kcr][kcc].enemy;
    char ourTeam=runTimeDatabase[kcr][kcc].team;
    int a;
    for(a=1; a<=7; a+=1){
        //if target block out of board dimensions break
        if((kcc+a)>7){
            break;
        }
        //tbtm: target block team, tbtp: target block type
        char tbtm=runTimeDatabase[kcr][kcc+a].team;
        char tbtp[15]; strcpy(tbtp, runTimeDatabase[kcr][kcc+a].type);
        if(tbtm==ourEnemy){
            if((a==1)&&(strcmp(tbtp, "KING")==0)){
                return 1;
            }
            if((strcmp(tbtp, "QUEEN")==0)||(strcmp(tbtp, "ROOK")==0)){
                return 1;
            }
            return 0;
        }
        if(tbtm=='V'){
            continue;
        }
        if(tbtm==ourTeam){
            return 0;
        }
    }
    return 0;
}
//Test Left Dangers
int isLeftDangerous(int kcr, int kcc){
    //kcr: king current row, kcc: king current column
    char ourEnemy=runTimeDatabase[kcr][kcc].enemy;
    char ourTeam=runTimeDatabase[kcr][kcc].team;
    int a;
    for(a=1; a<=7; a+=1){
        //if target block out of board dimensions break
        if((kcc-a)<0){
            break;
        }
        //tbtm: target block team, tbtp: target block type
        char tbtm=runTimeDatabase[kcr][kcc-a].team;
        char tbtp[15]; strcpy(tbtp, runTimeDatabase[kcr][kcc-a].type);
        if(tbtm==ourEnemy){
            if((a==1)&&(strcmp(tbtp, "KING")==0)){
                return 1;
            }
            if((strcmp(tbtp, "QUEEN")==0)||(strcmp(tbtp, "ROOK")==0)){
                return 1;
            }
            return 0;
        }
        if(tbtm=='V'){
            continue;
        }
        if(tbtm==ourTeam){
            return 0;
        }
    }
    return 0;
}
//Test D1 Dangers
int isD1Dangerous(int kcr, int kcc){
    //kcr: king current row, kcc: king current column
    char ourEnemy=runTimeDatabase[kcr][kcc].enemy;
    char ourTeam=runTimeDatabase[kcr][kcc].team;
    int a;
    for(a=1; a<=7; a+=1){
        //if target block out of board dimensions break
        if(((kcr-a)<0)||((kcc+a)>7)){
            break;
        }
        //tbtm: target block team, tbtp: target block type
        char tbtm=runTimeDatabase[kcr-a][kcc+a].team;
        char tbtp[15]; strcpy(tbtp, runTimeDatabase[kcr-a][kcc+a].type);
        if(tbtm==ourEnemy){
            if((a==1)&&(strcmp(tbtp, "KING")==0)){
                return 1;
            }
            if((a==1)&&(strcmp(tbtp, "PAWN")==0)&&(tbtm=='B')){
                return 1;
            }
            if((strcmp(tbtp, "QUEEN")==0)||(strcmp(tbtp, "BISHOP")==0)){
                return 1;
            }
            return 0;
        }
        if(tbtm=='V'){
            continue;
        }
        if(tbtm==ourTeam){
            return 0;
        }
    }
    return 0;
}
//Test D2 Dangers
int isD2Dangerous(int kcr, int kcc){
    //kcr: king current row, kcc: king current column
    char ourEnemy=runTimeDatabase[kcr][kcc].enemy;
    char ourTeam=runTimeDatabase[kcr][kcc].team;
    int a;
    for(a=1; a<=7; a+=1){
        //if target block out of board dimensions break
        if(((kcr+a)>7)||((kcc+a)>7)){
            break;
        }
        //tbtm: target block team, tbtp: target block type
        char tbtm=runTimeDatabase[kcr+a][kcc+a].team;
        char tbtp[15]; strcpy(tbtp, runTimeDatabase[kcr+a][kcc+a].type);
        if(tbtm==ourEnemy){
            if((a==1)&&(strcmp(tbtp, "KING")==0)){
                return 1;
            }
            if((a==1)&&(strcmp(tbtp, "PAWN")==0)&&(tbtm=='W')){
                return 1;
            }
            if((strcmp(tbtp, "QUEEN")==0)||(strcmp(tbtp, "BISHOP")==0)){
                return 1;
            }
            return 0;
        }
        if(tbtm=='V'){
            continue;
        }
        if(tbtm==ourTeam){
            return 0;
        }
    }
    return 0;
}
//Test D3 Dangers
int isD3Dangerous(int kcr, int kcc){
    //kcr: king current row, kcc: king current column
    char ourEnemy=runTimeDatabase[kcr][kcc].enemy;
    char ourTeam=runTimeDatabase[kcr][kcc].team;
    int a;
    for(a=1; a<=7; a+=1){
        //if target block out of board dimensions break
        if(((kcr+a)>7)||((kcc-a)<0)){
            break;
        }
        //tbtm: target block team, tbtp: target block type
        char tbtm=runTimeDatabase[kcr+a][kcc-a].team;
        char tbtp[15]; strcpy(tbtp, runTimeDatabase[kcr+a][kcc-a].type);
        if(tbtm==ourEnemy){
            if((a==1)&&(strcmp(tbtp, "KING")==0)){
                return 1;
            }
            if((a==1)&&(strcmp(tbtp, "PAWN")==0)&&(tbtm=='W')){
                return 1;
            }
            if((strcmp(tbtp, "QUEEN")==0)||(strcmp(tbtp, "BISHOP")==0)){
                return 1;
            }
            return 0;
        }
        if(tbtm=='V'){
            continue;
        }
        if(tbtm==ourTeam){
            return 0;
        }
    }
    return 0;
}
//Test D4 Dangers
int isD4Dangerous(int kcr, int kcc){
    //kcr: king current row, kcc: king current column
    char ourEnemy=runTimeDatabase[kcr][kcc].enemy;
    char ourTeam=runTimeDatabase[kcr][kcc].team;
    int a;
    for(a=1; a<=7; a+=1){
        //if target block out of board dimensions break
        if(((kcr-a)<0)||((kcc-a)<0)){
            break;
        }
        //tbtm: target block team, tbtp: target block type
        char tbtm=runTimeDatabase[kcr-a][kcc-a].team;
        char tbtp[15]; strcpy(tbtp, runTimeDatabase[kcr-a][kcc-a].type);
        if(tbtm==ourEnemy){
            if((a==1)&&(strcmp(tbtp, "KING")==0)){
                return 1;
            }
            if((a==1)&&(strcmp(tbtp, "PAWN")==0)&&(tbtm=='B')){
                return 1;
            }
            if((strcmp(tbtp, "QUEEN")==0)||(strcmp(tbtp, "BISHOP")==0)){
                return 1;
            }
            return 0;
        }
        if(tbtm=='V'){
            continue;
        }
        if(tbtm==ourTeam){
            return 0;
        }
    }
    return 0;
}
//Test Kn1 Dangers
int isKn1Dangerous(int kcr, int kcc){
    //if target block out of board dimensions break
    if(((kcr-2)<0)||((kcc+1)>7)){
        return 0;
    }
    //simplify data
    char myEnemy=runTimeDatabase[kcr][kcc].enemy;
    char targetBlockTeam=runTimeDatabase[kcr-2][kcc+1].team;
    char targetBlockType[15]; strcpy(targetBlockType, runTimeDatabase[kcr-2][kcc+1].type);
    //get cases to test
    int case1=(targetBlockTeam==myEnemy);
    int case2=(strcmp(targetBlockType, "KNIGHT")==0);
    if(case1&&case2){
        return 1;
    }
    return 0;
}
//Test Kn2 Dangers
int isKn2Dangerous(int kcr, int kcc){
    //if target block out of board dimensions break
    if(((kcr+2)>7)||((kcc+1)>7)){
        return 0;
    }
    //simplify data
    char myEnemy=runTimeDatabase[kcr][kcc].enemy;
    char targetBlockTeam=runTimeDatabase[kcr+2][kcc+1].team;
    char targetBlockType[15]; strcpy(targetBlockType, runTimeDatabase[kcr+2][kcc+1].type);
    //get cases to test
    int case1=(targetBlockTeam==myEnemy);
    int case2=(strcmp(targetBlockType, "KNIGHT")==0);
    if(case1&&case2){
        return 1;
    }
    return 0;
}
//Test Kn3 Dangers
int isKn3Dangerous(int kcr, int kcc){
    //if target block out of board dimensions break
    if(((kcr+2)>7)||((kcc-1)<0)){
        return 0;
    }
    //simplify data
    char myEnemy=runTimeDatabase[kcr][kcc].enemy;
    char targetBlockTeam=runTimeDatabase[kcr+2][kcc-1].team;
    char targetBlockType[15]; strcpy(targetBlockType, runTimeDatabase[kcr+2][kcc-1].type);
    //get cases to test
    int case1=(targetBlockTeam==myEnemy);
    int case2=(strcmp(targetBlockType, "KNIGHT")==0);
    if(case1&&case2){
        return 1;
    }
    return 0;
}
//Test Kn4 Dangers
int isKn4Dangerous(int kcr, int kcc){
    //if target block out of board dimensions break
    if(((kcr-2)<0)||((kcc-1)<0)){
        return 0;
    }
    //simplify data
    char myEnemy=runTimeDatabase[kcr][kcc].enemy;
    char targetBlockTeam=runTimeDatabase[kcr-2][kcc-1].team;
    char targetBlockType[15]; strcpy(targetBlockType, runTimeDatabase[kcr-2][kcc-1].type);
    //get cases to test
    int case1=(targetBlockTeam==myEnemy);
    int case2=(strcmp(targetBlockType, "KNIGHT")==0);
    if(case1&&case2){
        return 1;
    }
    return 0;
}
//Test Kn5 Dangers
int isKn5Dangerous(int kcr, int kcc){
    //if target block out of board dimensions break
    if(((kcr-1)<0)||((kcc+2)>7)){
        return 0;
    }
    //simplify data
    char myEnemy=runTimeDatabase[kcr][kcc].enemy;
    char targetBlockTeam=runTimeDatabase[kcr-1][kcc+2].team;
    char targetBlockType[15]; strcpy(targetBlockType, runTimeDatabase[kcr-1][kcc+2].type);
    //get cases to test
    int case1=(targetBlockTeam==myEnemy);
    int case2=(strcmp(targetBlockType, "KNIGHT")==0);
    if(case1&&case2){
        return 1;
    }
    return 0;
}
//Test Kn6 Dangers
int isKn6Dangerous(int kcr, int kcc){
    //if target block out of board dimensions break
    if(((kcr+1)>7)||((kcc+2)>7)){
        return 0;
    }
    //simplify data
    char myEnemy=runTimeDatabase[kcr][kcc].enemy;
    char targetBlockTeam=runTimeDatabase[kcr+1][kcc+2].team;
    char targetBlockType[15]; strcpy(targetBlockType, runTimeDatabase[kcr+1][kcc+2].type);
    //get cases to test
    int case1=(targetBlockTeam==myEnemy);
    int case2=(strcmp(targetBlockType, "KNIGHT")==0);
    if(case1&&case2){
        return 1;
    }
    return 0;
}
//Test Kn7 Dangers
int isKn7Dangerous(int kcr, int kcc){
    //if target block out of board dimensions break
    if(((kcr+1)>7)||((kcc-2)<0)){
        return 0;
    }
    //simplify data
    char myEnemy=runTimeDatabase[kcr][kcc].enemy;
    char targetBlockTeam=runTimeDatabase[kcr+1][kcc-2].team;
    char targetBlockType[15]; strcpy(targetBlockType, runTimeDatabase[kcr+1][kcc-2].type);
    //get cases to test
    int case1=(targetBlockTeam==myEnemy);
    int case2=(strcmp(targetBlockType, "KNIGHT")==0);
    if(case1&&case2){
        return 1;
    }
    return 0;
}
//Test Kn8 Dangers
int isKn8Dangerous(int kcr, int kcc){
    //if target block out of board dimensions break
    if(((kcr-1)<0)||((kcc-2)<0)){
        return 0;
    }
    //simplify data
    char myEnemy=runTimeDatabase[kcr][kcc].enemy;
    char targetBlockTeam=runTimeDatabase[kcr-1][kcc-2].team;
    char targetBlockType[15]; strcpy(targetBlockType, runTimeDatabase[kcr-1][kcc-2].type);
    //get cases to test
    int case1=(targetBlockTeam==myEnemy);
    int case2=(strcmp(targetBlockType, "KNIGHT")==0);
    if(case1&&case2){
        return 1;
    }
    return 0;
}
//End---------------------------Investigate Is King In Danger-----------Specific Direction----------------------------





//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************

//Start--------------------------------------------Apply Player Move----------------------------------------------------------
void applyPlayerMove(int cr, int cc, int tr, int tc){
//cr: current row, cc: current column, tr: target row, tc: target column
//this function moves a piece from block[cr][cc] to block[tr][tc]

    //01-Kill Piece in Target Block, and update its team array info
    killPieceInApplyMove(tr,tc);
    //02-Move Piece to the Target Block and Update its Team Array Info
    movePieceInApplyMove(cr,cc,tr,tc);
    //03-fill current block with blank object
    fillBlockWithBlankObject(cr,cc);
}
//End----------------------------------------------Apply Player Move----------------------------------------------------------

//Start----------------------------------------------Undo Test Move-----------------------------------------------------------
void undoTestMove(int ir, int ic, int fr, int fc, struct PIECE removedPiece){
    //01-return moved piece to its original block
    applyPlayerMove(fr,fc,ir,ic);
    //02-return removed/killed piece to its previous location
    revivePieceInUndoMove(fr,fc,removedPiece);
}
//End------------------------------------------------Undo Test Move-----------------------------------------------------------

//Start--------------------------------------Kill Piece in a Specific Block---------------------------------------------------
void killPieceInApplyMove(int tr, int tc){
    //obtain piece location in team array
    int location=runTimeDatabase[tr][tc].teamArrayLocation;
    //01- target block is occupied with white piece
    if(runTimeDatabase[tr][tc].team=='W'){
        strcpy(whiteTeam[0][location].status, "DEAD");
    }
    //02- target block is occupied with black piece
    if(runTimeDatabase[tr][tc].team=='B'){
        strcpy(blackTeam[0][location].status, "DEAD");
    }
}
//End----------------------------------------Kill Piece in a Specific Block---------------------------------------------------

//Start-----------------------------------------------Move Piece To a Block---------------------------------------------------
void movePieceInApplyMove(int cr, int cc, int tr, int tc){
    //obtain piece team & Team Location
    char pieceTeam=runTimeDatabase[cr][cc].team;
    int location=runTimeDatabase[cr][cc].teamArrayLocation;
    //01-fill target block with current block attributes
    runTimeDatabase[tr][tc]=runTimeDatabase[cr][cc];
    runTimeDatabase[tr][tc].currentRow=tr;
    runTimeDatabase[tr][tc].currentColumn=tc;
    //02-set next valid positions for the moved object
    setPieceNextValidPositions(runTimeDatabase[tr][tc], runTimeDatabase[tr][tc].nextValidPositions);
    //03-update team database
    if(pieceTeam=='W'){
        whiteTeam[0][location]=runTimeDatabase[tr][tc];
    }
    if(pieceTeam=='B'){
        blackTeam[0][location]=runTimeDatabase[tr][tc];
    }
}
//End-------------------------------------------------Move Piece To a Block---------------------------------------------------

//Start----------------------------------------Fill Block with Blank Object---------------------------------------------------
void fillBlockWithBlankObject(int r,int c){
    runTimeDatabase[r][c]=blankObject;
    runTimeDatabase[r][c].currentRow=r;
    runTimeDatabase[r][c].currentColumn=c;
}
//End------------------------------------------Fill Block with Blank Object---------------------------------------------------

//Start----------------------------------Revive Piece to Its Previous Block---------------------------------------------------
void revivePieceInUndoMove(int r, int c, struct PIECE removedPiece){
    //return removed piece to its position
    runTimeDatabase[r][c]=removedPiece;
    //obtain piece location in team array
    int location=removedPiece.teamArrayLocation;
    //01- target block is occupied with white piece
    if(removedPiece.team=='W'){
        strcpy(whiteTeam[0][location].status, "Active");
    }
    //02- target block is occupied with black piece
    if(removedPiece.team=='B'){
        strcpy(blackTeam[0][location].status, "Active");
    }
}
//End------------------------------------Revive Piece to Its Previous Block---------------------------------------------------


//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************

//Start----------------------------------------Investigate Target Block Validity--------------------------------------------
int investigateTargetBlockValidity(int cr, int cc, int tr, int tc){
//cr: current row, cc: current column, tr: Target Row, tc: Target Column
//row and column values must be actual C-Array values 0,1,2,3,4,...

    //01-test that target block is within board limits
    if((tr<0)||(tr>7)||(tc<0)||(tc>7)){
        return 0;
    }
    //02-test if entered move direction is valid (up down left right d1 d2 d3 d4 kn1 kn2 kn3 kn4 kn5 kn6 kn7 kn8
    if(investigateMoveDirectionValidity(cr,cc,tr,tc)==0){
        return 0;
    }
    //03-test target block if occupied by teammate
    if(runTimeDatabase[tr][tc].team==runTimeDatabase[cr][cc].team){
        return 0;
    }
    //if moving piece is pawn
    if((strcmp(runTimeDatabase[cr][cc].type, "PAWN")==0)&&(runTimeDatabase[tr][tc].team==runTimeDatabase[cr][cc].enemy)){
        //for white pawn
        if((runTimeDatabase[cr][cc].team=='W')&&(isPieceMovingInUpDirection(cr,cc,tr,tc)==1)){
            return 0;
        }
        //for black pawn
        if((runTimeDatabase[cr][cc].team=='B')&&(isPieceMovingInDownDirection(cr,cc,tr,tc)==1)){
            return 0;
        }
    }
    //04-test there's nothing in between the two blocks
    if(investigateNothingInBetween(cr,cc,tr,tc)==0){
        return 0;
    }
    return 1;
}
//End------------------------------------------Investigate Target Block Validity--------------------------------------------

//Start---------------------------------Investigate Move Direction Validity--------------General Case-----------------------
int investigateMoveDirectionValidity(int cr, int cc, int tr, int tc){
//for example (up down left right d1 d2 d3 d4 kn1 kn2 kn3 kn4) are valid moves
//else is not valid
    //for up move
    if(isPieceMovingInUpDirection(cr,cc,tr,tc)==1){
        return 1;
    }
    //for down move
    if(isPieceMovingInDownDirection(cr,cc,tr,tc)==1){
        return 1;
    }
    //for right move
    if(isPieceMovingInRightDirection(cr,cc,tr,tc)==1){
        return 1;
    }
    //for left move
    if(isPieceMovingInLeftDirection(cr,cc,tr,tc)==1){
        return 1;
    }
    //for diagonal1 move
    if(isPieceMovingInD1Direction(cr,cc,tr,tc)==1){
        return 1;
    }
    //for diagonal2 move
    if(isPieceMovingInD2Direction(cr,cc,tr,tc)==1){
        return 1;
    }
    //for diagonal3 move
    if(isPieceMovingInD3Direction(cr,cc,tr,tc)==1){
        return 1;
    }
    //for diagonal4 move
    if(isPieceMovingInD4Direction(cr,cc,tr,tc)==1){
        return 1;
    }
    if(isPieceMovingInKnightDirection(cr,cc,tr,tc)==1){
        return 1;
    }
    return 0;
}
//End-----------------------------------Investigate Move Direction Validity--------------General Case-----------------------

//Start-----------------------Investigate There's Nothing In Between Two Blocks------------General Case---------------------
int investigateNothingInBetween(int cr, int cc, int tr, int tc){
//cr: current row, cc: current column, tr: Target Row, tc: Target Column
//row and column values must be actual C-Array values 0,1,2,3,4,...
//this function takes two blocks and tells if there any piece in between
    //for up move
    if(isPieceMovingInUpDirection(cr,cc,tr,tc)==1){
        return nothingInBetweenUp(cr,cc,tr,tc);
    }
    //for down move
    if(isPieceMovingInDownDirection(cr,cc,tr,tc)==1){
        return nothingInBetweenDown(cr,cc,tr,tc);
    }
    //for right move
    if(isPieceMovingInRightDirection(cr,cc,tr,tc)==1){
        return nothingInBetweenRight(cr,cc,tr,tc);
    }
    //for left move
    if(isPieceMovingInLeftDirection(cr,cc,tr,tc)==1){
        return nothingInBetweenLeft(cr,cc,tr,tc);
    }
    //for diagonal1 move
    if(isPieceMovingInD1Direction(cr,cc,tr,tc)==1){
        return nothingInBetweenD1(cr,cc,tr,tc);
    }
    //for diagonal2 move
    if(isPieceMovingInD2Direction(cr,cc,tr,tc)==1){
        return nothingInBetweenD2(cr,cc,tr,tc);
    }
    //for diagonal3 move
    if(isPieceMovingInD3Direction(cr,cc,tr,tc)==1){
        return nothingInBetweenD3(cr,cc,tr,tc);
    }
    //for diagonal4 move
    if(isPieceMovingInD4Direction(cr,cc,tr,tc)==1){
        return nothingInBetweenD4(cr,cc,tr,tc);
    }
    //for knight moves
    if(isPieceMovingInKnightDirection(cr,cc,tr,tc)==1){
        return 1;
    }
    return 0;
}
//End-------------------------Investigate There's Nothing In Between Two Blocks------------General Case---------------------

//Start-----------------------Investigate There's Nothing In Between Two Blocks------------Specific Case--------------------
//test there's nothing in between up
int nothingInBetweenUp(int cr, int cc, int tr, int tc){
    int loop;
    for(loop=tr+1; loop<=cr-1; loop+=1){
        if(runTimeDatabase[loop][cc].team!='V'){
            return 0;
        }
    }
    return 1;
}
//test there's nothing in between down
int nothingInBetweenDown(int cr, int cc, int tr, int tc){
    int loop;
    for(loop=cr+1; loop<=tr-1; loop+=1){
        if(runTimeDatabase[loop][cc].team!='V'){
            return 0;
        }
    }
    return 1;
}
//test there's nothing in between right
int nothingInBetweenRight(int cr, int cc, int tr, int tc){
    int loop;
    for(loop=cc+1; loop<=tc-1; loop+=1){
        if(runTimeDatabase[cr][loop].team!='V'){
            return 0;
        }
    }
    return 1;
}
//test there's nothing in between left
int nothingInBetweenLeft(int cr, int cc, int tr, int tc){
    int loop;
    for(loop=tc+1; loop<=cc-1; loop+=1){
        if(runTimeDatabase[cr][loop].team!='V'){
            return 0;
        }
    }
    return 1;
}
//test there's nothing in between d1
int nothingInBetweenD1(int cr, int cc, int tr, int tc){
    int rowLoop;
    int columnLoop=tc-1;
    for(rowLoop=tr+1; rowLoop<=cr-1; rowLoop+=1){
        if(runTimeDatabase[rowLoop][columnLoop].team!='V'){
            return 0;
        }
        columnLoop-=1;
    }
    return 1;
}
//test there's nothing in between d2
int nothingInBetweenD2(int cr, int cc, int tr, int tc){
    int rowLoop;
    int columnLoop=cc+1;
    for(rowLoop=cr+1; rowLoop<=tr-1; rowLoop+=1){
        if(runTimeDatabase[rowLoop][columnLoop].team!='V'){
            return 0;
        }
        columnLoop+=1;
    }
    return 1;
}
//test there's nothing in between d3
int nothingInBetweenD3(int cr, int cc, int tr, int tc){
    int rowLoop;
    int columnLoop=cc-1;
    for(rowLoop=cr+1; rowLoop<=tr-1; rowLoop+=1){
        if(runTimeDatabase[rowLoop][columnLoop].team!='V'){
            return 0;
        }
        columnLoop-=1;
    }
    return 1;
}
//test there's nothing in between d3
int nothingInBetweenD4(int cr, int cc, int tr, int tc){
    int rowLoop;
    int columnLoop=tc+1;
    for(rowLoop=tr+1; rowLoop<=cr-1; rowLoop+=1){
        if(runTimeDatabase[rowLoop][columnLoop].team!='V'){
            return 0;
        }
        columnLoop+=1;
    }
    return 1;
}
//Start-----------------------Investigate There's Nothing In Between Two Blocks------------Specific Case--------------------

//Start---------------------------------------------Get Piece Moving Direction----------------------------------------------
//is piece moving up
int isPieceMovingInUpDirection(int cr, int cc, int tr, int tc){
    if((cc==tc)&&(cr>tr)){
        return 1;
    }
    return 0;
}
//is piece moving down
int isPieceMovingInDownDirection(int cr, int cc, int tr, int tc){
    if((cc==tc)&&(tr>cr)){
        return 1;
    }
    return 0;
}
//is piece moving right
int isPieceMovingInRightDirection(int cr, int cc, int tr, int tc){
    if((cr==tr)&&(tc>cc)){
        return 1;
    }
    return 0;
}
//is piece moving left
int isPieceMovingInLeftDirection(int cr, int cc, int tr, int tc){
    if((cr==tr)&&(tc<cc)){
        return 1;
    }
    return 0;
}
//is piece moving in direction d1
int isPieceMovingInD1Direction(int cr, int cc, int tr, int tc){
    int loop;
    for(loop=1; loop<=7; loop+=1){
        if((tr==cr-loop)&&(tc==cc+loop)){
            return 1;
        }
    }
    return 0;
}
//is piece moving in direction d2
int isPieceMovingInD2Direction(int cr, int cc, int tr, int tc){
    int loop;
    for(loop=1; loop<=7; loop+=1){
        if((tr==cr+loop)&&(tc==cc+loop)){
            return 1;
        }
    }
    return 0;
}
//is piece moving in direction d3
int isPieceMovingInD3Direction(int cr, int cc, int tr, int tc){
    int loop;
    for(loop=1; loop<=7; loop+=1){
        if((tr==cr+loop)&&(tc==cc-loop)){
            return 1;
        }
    }
    return 0;
}
//is piece moving in direction d4
int isPieceMovingInD4Direction(int cr, int cc, int tr, int tc){
    int loop;
    for(loop=1; loop<=7; loop+=1){
        if((tr==cr-loop)&&(tc==cc-loop)){
            return 1;
        }
    }
    return 0;
}
//is piece moving knight direction
int isPieceMovingInKnightDirection(int cr, int cc, int tr, int tc){
    if((tr==cr-2)&&(tc==cc+1)){
        return 1;
    }
    if((tr==cr+2)&&(tc==cc+1)){
        return 1;
    }
    if((tr==cr+2)&&(tc==cc-1)){
        return 1;
    }
    if((tr==cr-2)&&(tc==cc-1)){
        return 1;
    }
    if((tr==cr-1)&&(tc==cc+2)){
        return 1;
    }
    if((tr==cr+1)&&(tc==cc+2)){
        return 1;
    }
    if((tr==cr+1)&&(tc==cc-2)){
        return 1;
    }
    if((tr==cr-1)&&(tc==cc-2)){
        return 1;
    }
}
//Start---------------------------------------------Get Piece Moving Direction----------------------------------------------


//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//Start-------------------------------Investigate Move Match-------------------------------------------------------------
int investigateIsEnteredMoveMatchPieceAnyNextValidPosition(int cr, int cc, int tr, int tc){
    int a;
    for(a=1; a<=8; a+=1){
        int b;
        for(b=1; b<=7; b+=1){
            int nvr=runTimeDatabase[cr][cc].nextValidPositions[a-1][b-1][0];
            int nvc=runTimeDatabase[cr][cc].nextValidPositions[a-1][b-1][1];
            if((tr==nvr)&&(tc==nvc)){
                return 1;
            }
        }
    }
    return 0;
}
//End---------------------------------Investigate Move Match-------------------------------------------------------------


//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************

//Start----------------------Investigate Does This Move Render My King In Danger--------------------------------------------
int investigateDoesThisMoveRenderMyKingInDanger(int cr, int cc, int tr, int tc){
    char teamToTest=runTimeDatabase[cr][cc].team;
    //create temporary piece (piece to remove from board)
    struct PIECE tmpPiece;
    tmpPiece=runTimeDatabase[tr][tc];
    //01-Apply Test Move
    applyPlayerMove(cr,cc,tr,tc);
    //02-Investigate Is King In Danger
    if(investigateIsKingInDanger(teamToTest)==1){
        //03-Undo Test Move
        undoTestMove(cr,cc,tr,tc,tmpPiece);
        return 1;
    }
    //03-Undo Test Move
    undoTestMove(cr,cc,tr,tc,tmpPiece);
    return 0;
}
//End------------------------Investigate Does This Move Render My King In Danger--------------------------------------------



//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************


//Start-------------------------------Investigate Move Validity-------------------------------------------------------------
int investigateMoveValidity(int cr, int cc, int tr, int tc){
    //00-set piece next valid positions
    setPieceNextValidPositions(runTimeDatabase[cr][cc], runTimeDatabase[cr][cc].nextValidPositions);
    if(runTimeDatabase[cr][cc].team=='W'){
        whiteTeam[0][runTimeDatabase[cr][cc].teamArrayLocation]=runTimeDatabase[cr][cc];
    }
    if(runTimeDatabase[cr][cc].team=='B'){
        blackTeam[0][runTimeDatabase[cr][cc].teamArrayLocation]=runTimeDatabase[cr][cc];
    }
    //01- Investigate Target Block Validity
    if(investigateTargetBlockValidity(cr,cc,tr,tc)==0){
        return 0;
    }
    //02- Investigate Is Entered Move Matches Any of the Next Moves of This Piece
    if(investigateIsEnteredMoveMatchPieceAnyNextValidPosition(cr,cc,tr,tc)==0){
        return 0;
    }
    //03- Investigate Does This Move Render My King In Danger
    if(investigateDoesThisMoveRenderMyKingInDanger(cr,cc,tr,tc)==1){
        return 0;
    }
    return 1;
}
//End---------------------------------Investigate Move Validity-------------------------------------------------------------


//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************


//Start-------------------------Investigate No Next Valid Move for All Teammates--------Any Team------------------------------------
int investigateNoNextValidMoveForAllTeammates(char teamToTest){
//this function takes a team's identifier
//this function test 1- there's no next valid move for king 2- there's no next valid move for all other teammates
//this function returns 1 if no next valid move found,and 0 if a valid move found

    if(teamToTest=='W'){
        return investigateNoNextValidMoveForAllWhitePieces();
    }
    if(teamToTest=='B'){
        return investigateNoNextValidMoveForAllBlackPieces();
    }
}
//End---------------------------Investigate No Next Valid Move for All Teammates--------Any Team------------------------------------

//Start-------------------------Investigate No Next Valid Move for All Teammates--------White Team----------------------------------
int investigateNoNextValidMoveForAllWhitePieces(){
    //try every piece move
    int pieceId;
    for(pieceId=1; pieceId<=16; pieceId+=1){
        //if piece is killed move over to the next piece
        if(strcmp(whiteTeam[0][pieceId-1].status, "DEAD")==0){
            continue;
        }
        //obtain piece current position on board
        int cr; int cc;
        cr=whiteTeam[0][pieceId-1].currentRow;
        cc=whiteTeam[0][pieceId-1].currentColumn;
        //loop over its next valid positions
        int row;
        for(row=1; row<=8; row+=1){
            int column;
            for(column=1; column<=7; column+=1){
                //obtain next valid position
                int tr=whiteTeam[0][pieceId-1].nextValidPositions[row-1][column-1][0];
                int tc=whiteTeam[0][pieceId-1].nextValidPositions[row-1][column-1][1];
                //Investigate Move Validity
                if(investigateMoveValidity(cr,cc,tr,tc)==1){
                    return 0;
                }
            //end looping over columns
            }
        //end looping over rows
        }
    //end looping over pieces
    }
    return 1;
}
//End---------------------------Investigate No Next Valid Move for All Teammates--------White Team----------------------------------

//Start-------------------------Investigate No Next Valid Move for All Teammates--------Black Team----------------------------------
int investigateNoNextValidMoveForAllBlackPieces(){
    //try every piece move
    int pieceId;
    for(pieceId=1; pieceId<=16; pieceId+=1){
        //if piece is killed move over to the next piece
        if(strcmp(blackTeam[0][pieceId-1].status, "DEAD")==0){
            continue;
        }
        //obtain piece current position on board
        int cr; int cc;
        cr=blackTeam[0][pieceId-1].currentRow;
        cc=blackTeam[0][pieceId-1].currentColumn;
        //loop over its next valid positions
        int row;
        for(row=1; row<=8; row+=1){
            int column;
            for(column=1; column<=7; column+=1){
                //obtain next valid position
                int tr=blackTeam[0][pieceId-1].nextValidPositions[row-1][column-1][0];
                int tc=blackTeam[0][pieceId-1].nextValidPositions[row-1][column-1][1];
                //Investigate Move Validity
                if(investigateMoveValidity(cr,cc,tr,tc)==1){
                    return 0;
                }
            //end looping over columns
            }
        //end looping over rows
        }
    //end looping over pieces
    }
    return 1;
}
//End---------------------------Investigate No Next Valid Move for All Teammates--------Black Team----------------------------------


//Start------------------------------------------Investigate Checkmate-------------------------------------------------
int investigateCheckmate(char teamToTest){
//this function takes the team identifier
//this function investigate to see if the team's king is dead or not (checkmate)
//if dead (checkmate) it returns 1, if not it returns 0

    //01-check to see if the king is in dangerous position
    if(investigateIsKingInDanger(teamToTest)==0){
        return 0;
    }
    //02- check to see there's no next valid move for the king
    //&03- check to see if there's no next valid move for other team mates
    if(investigateNoNextValidMoveForAllTeammates(teamToTest)==0){
        return 0;
    }
    return 1;
}
//End--------------------------------------------Investigate Checkmate-------------------------------------------------

//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************


//Start------------------------------------------Investigate Stalemate-------------------------------------------------
int investigateStalemate(char teamToTest){
//this function takes the team identifier
//this function investigate to see if there's no next move for this team (Draw Case)
//if yes it returns 1 if no it returns 0

    //01-check to see if the king is in dangerous position
    if(investigateIsKingInDanger(teamToTest)==1){
        return 0;
    }
    //02- check to see there's no next valid move for the king
    //&03- check to see if there's no next valid move for other team mates
    if(investigateNoNextValidMoveForAllTeammates(teamToTest)==0){
        return 0;
    }

    return 1;
}
//End--------------------------------------------Investigate Stalemate-------------------------------------------------

//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************

//Start---------------------------------------Find Next Valid Piece Display Name--------------------------------------------------
void findNextValidPieceDisplayName(char pieceTeam, char pieceType[15]){
    //obtain promotion type row location in next valid
    int promotionTypeRow;
    if(strcmp(pieceType, "QUEEN")==0){promotionTypeRow=0;}
    if(strcmp(pieceType, "BISHOP")==0){promotionTypeRow=1;}
    if(strcmp(pieceType, "KNIGHT")==0){promotionTypeRow=2;}
    if(strcmp(pieceType, "ROOK")==0){promotionTypeRow=3;}
    //find next valid name
    //for white team
    if(pieceTeam=='W'){
        int matchesFound=0;
        int arrayPointer=0;
        int loop;
        for(loop=1; loop<=16; loop+=1){
            if(strcmp(whiteTeam[0][loop-1].type, pieceType)==0){
                matchesFound+=1;
                strcpy(promotionDisplayName, nextValidWhiteTeamPromotionDisplayNames[promotionTypeRow][arrayPointer]);
                if((matchesFound==1)&&(!(strcmp(pieceType,"QUEEN")==0))){
                    continue;
                }
                arrayPointer+=1;
            }
        }
    }
    //for black team
    if(pieceTeam=='B'){
        int matchesFound=0;
        int arrayPointer=0;
        int loop;
        for(loop=1; loop<=16; loop+=1){
            if(strcmp(blackTeam[0][loop-1].type, pieceType)==0){
                matchesFound+=1;
                strcpy(promotionDisplayName, nextValidBlackTeamPromotionDisplayNames[promotionTypeRow][arrayPointer]);
                if((matchesFound==1)&&(!(strcmp(pieceType,"QUEEN")==0))){
                    continue;
                }
                arrayPointer+=1;
            }
        }
    }
}
//End-----------------------------------------Find Next Valid Piece Display Name--------------------------------------------------

//Start--------------------------------------------Obtain Promotion Rank From Player----------------------------------------------
void obtainPromotionRankFromPlayer(){
    short validRankObtained=0;
    while(validRankObtained==0){
        //get player input
        printf("\n[Promotion Ranks : Queen - Bishop - Knight - Rook]\n");
        printf("\nEnter Promotion Rank For the Pawn : ");
        gets(promotionRank);
        //convert input to upper case
        strcpy(promotionRank, strupr(promotionRank));
        //test rank validity
        int validCase1=(strcmp(promotionRank, "QUEEN")==0);
        int validCase2=(strcmp(promotionRank, "BISHOP")==0);
        int validCase3=(strcmp(promotionRank, "KNIGHT")==0);
        int validCase4=(strcmp(promotionRank, "ROOK")==0);
        if(validCase1||validCase2||validCase3||validCase4){
            validRankObtained=1;
        }else{
            printf("\nPlease Enter A Valid Promotion Rank!");
        }
    }
}
//End----------------------------------------------Obtain Promotion Rank From Player----------------------------------------------

//Start-----------------------------------------------Promote Pawn Order Execution------------------------------------------------
void promotePawnOrderExecution(int r, int c){
    //00-simplify data
    char pieceTeam=runTimeDatabase[r][c].team;
    int pieceTeamLocation=runTimeDatabase[r][c].teamArrayLocation;
    //Display Notification Message
    printf("\n--------------------------------------------");
    printf("\n\tYour Pawn Is Now Eligible for Promotion\n");
    //01- obtain promotion rank from player
    obtainPromotionRankFromPlayer();
    findNextValidPieceDisplayName(pieceTeam, promotionRank);
    int pieceStep=7;
    if(strcmp(promotionRank, "KNIGHT")==0){pieceStep=-1;}
    //assign attributes
    strcpy(runTimeDatabase[r][c].displayName, promotionDisplayName);
    strcpy(runTimeDatabase[r][c].type, promotionRank);
    runTimeDatabase[r][c].step=pieceStep;
    setPieceNextValidPositions(runTimeDatabase[r][c], runTimeDatabase[r][c].nextValidPositions);
    //update team array info
    if(pieceTeam=='W'){
        whiteTeam[0][pieceTeamLocation]=runTimeDatabase[r][c];
    }
    if(pieceTeam=='B'){
        blackTeam[0][pieceTeamLocation]=runTimeDatabase[r][c];
    }
}
//End-------------------------------------------------Promote Pawn Order Execution------------------------------------------------

//Start--------------------------------------------------Investigate Pawn Promotion-------------------------------------------
void investigatePawnPromotion(int r, int c){
    if(strcmp(runTimeDatabase[r][c].type, "PAWN")==0){
        if((runTimeDatabase[r][c].team=='W')&&(r==0)){
            system("cls");
            displayBoard();
            promotePawnOrderExecution(r,c);
        }
        if((runTimeDatabase[r][c].team=='B')&&(r==7)){
            system("cls");
            displayBoard();
            promotePawnOrderExecution(r,c);
        }
    }
}
//End----------------------------------------------------Investigate Pawn Promotion-------------------------------------------


//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************



//Start------------------------------------------obtain move parameters from user----------------------------------------------------
void obtainMoveParametersFromUser(){
        printf("\nEnter Piece Name : ");
        gets(pieceToMoveVariableName);
        printf("\nEnter Target Block ID : ");
        gets(targetBlockVariableName);
}
//End--------------------------------------------obtain move parameters from user----------------------------------------------------

//Start--------------------------------------translate user input into valid parameters----------------------------------------------
int getTargetBlockColumnId(char targetBlock[15]){
    //cac: columnAsCharacter
    char cac=targetBlock[0];
    cac=toupper(cac);
    if(cac=='A'){return 0;}
    if(cac=='B'){return 1;}
    if(cac=='C'){return 2;}
    if(cac=='D'){return 3;}
    if(cac=='E'){return 4;}
    if(cac=='F'){return 5;}
    if(cac=='G'){return 6;}
    if(cac=='H'){return 7;}
}
int getTargetBlockRowId(char targetBlock[15]){
    int rowDisplayId=(targetBlock[1]-'0');
    if(rowDisplayId==8){return 0;}
    if(rowDisplayId==7){return 1;}
    if(rowDisplayId==6){return 2;}
    if(rowDisplayId==5){return 3;}
    if(rowDisplayId==4){return 4;}
    if(rowDisplayId==3){return 5;}
    if(rowDisplayId==2){return 6;}
    if(rowDisplayId==1){return 7;}
}
struct PIECE searchForPieceInfo(char pieceDisplayName[15]){
    //case-1-piece is from white team
    int loop;
    for(loop=1; loop<=16; loop+=1){
        if(strcmp(whiteTeam[0][loop-1].displayName, pieceDisplayName)==0){
            return whiteTeam[0][loop-1];
        }
    }
    //case-1-piece is from black team
    int loop2;
    for(loop2=1; loop2<=16; loop2+=1){
        if(strcmp(blackTeam[0][loop2-1].displayName, pieceDisplayName)==0){
            return blackTeam[0][loop2-1];
        }
    }
    return blankObject;
}
void translateUserInputIntoValidParameters(){
    //identify piece to move
    pieceToMoveVariable=searchForPieceInfo(pieceToMoveVariableName);
    //identify from and to blocks
    fromRowVariable=pieceToMoveVariable.currentRow;
    fromColumnVariable=pieceToMoveVariable.currentColumn;
    toRowVariable=getTargetBlockRowId(targetBlockVariableName);
    toColumnVariable=getTargetBlockColumnId(targetBlockVariableName);
}
//End----------------------------------------translate user input into valid parameters----------------------------------------------

//Start-----------------------------------------------Execute Move Piece Order-------------------------------------------------------
void movePieceOrderProcessing(){
    //01-Obtain move order from user
    int correctMoveEntered=0;
    while(correctMoveEntered==0){
        //01-obtain move parameters from user
        obtainMoveParametersFromUser();
        //02-translate user input into valid parameters
        translateUserInputIntoValidParameters();
        //make sure its the right player turn
        if(runTimeDatabase[fromRowVariable][fromColumnVariable].team!=playerTurn){
            printf("\nPlease Take Your Turn! It's %c Team Turn To Play.", playerTurn);
            continue;
        }
        //03-update piece next valid positions
        setPieceNextValidPositions(pieceToMoveVariable, pieceToMoveVariable.nextValidPositions);
        //04-investigate move validity
        if(investigateMoveValidity(fromRowVariable,fromColumnVariable,toRowVariable,toColumnVariable)==1){
            correctMoveEntered=1;
        }
        else{
            printf("\nPlease Enter a Valid Move");
        }
    }
    //02-apply move
    applyPlayerMove(fromRowVariable,fromColumnVariable,toRowVariable,toColumnVariable);
    //03-Check pawn promotion
    investigatePawnPromotion(toRowVariable,toColumnVariable);
    //03-investigate opponent checkmate
    if(investigateCheckmate(pieceToMoveVariable.enemy)==1){
        strcpy(gameStatus, "Checkmate");
    //04-investigate stalemate
    }else if(investigateStalemate(pieceToMoveVariable.enemy)==1){
        strcpy(gameStatus, "Stalemate");
    //05-investigate is enemy's king in danger
    }else if(investigateIsKingInDanger(pieceToMoveVariable.enemy)==1){
        printf("\nCheck!");
    }
    playerTurn=pieceToMoveVariable.enemy;
}
//End-------------------------------------------------Execute Move Piece Order-------------------------------------------------------



//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************
//**********************************************************************************************************************************

//Start-------------------------------------------------Save Game Progress------------------------------------------------------
void saveGameProgress(){
    //01-Save Main Arrays
    FILE *filePointer;
    filePointer = fopen( "Saved Arrays.bin" , "w" );
    fwrite(runTimeDatabase , sizeof(struct PIECE) , 64 , filePointer);
    fwrite(whiteTeam , sizeof(struct PIECE) , 16 , filePointer);
    fwrite(blackTeam , sizeof(struct PIECE) , 16 , filePointer);
    fclose(filePointer);
    //02-save white & black team roasters
    FILE *filePointer2;
    filePointer2=fopen("Saved Misc Variables.txt" ,"w");
    fprintf(filePointer2, "%s\n", gameStatus);
    fprintf(filePointer2, "%c\n", playerTurn);
    fprintf(filePointer2, "%d\n", playCount);
    fclose(filePointer2);
}
//End---------------------------------------------------Save Game Progress------------------------------------------------------

//Start-------------------------------------------------Load Last Game Progress--------------------------------------------------
void loadGameProgress(){
    //01-load Main Arrays
    FILE *filePointer;
    filePointer = fopen( "Saved Arrays.bin" , "r" );
    fread(runTimeDatabase , sizeof(struct PIECE) , 64 , filePointer);
    fread(whiteTeam , sizeof(struct PIECE) , 16 , filePointer);
    fread(blackTeam , sizeof(struct PIECE) , 16 , filePointer);
    fclose(filePointer);
    //02-load vital variables
    FILE *filePointer2;
    char tmpTxt[100];
    filePointer2=fopen("Saved Misc Variables.txt" ,"r");
    //get game status
    fgets(tmpTxt, 100, (FILE*)filePointer2);
    strtok(tmpTxt, "\n");
    strcpy(gameStatus, tmpTxt);
    //get player turn
    fgets(tmpTxt, 100, (FILE*)filePointer2);
    strtok(tmpTxt, "\n");
    playerTurn=tmpTxt[0];
    //get player count
    fgets(tmpTxt, 100, (FILE*)filePointer2);
    strtok(tmpTxt, "\n");
    playCount=atoi(tmpTxt);
    //close file
    fclose(filePointer2);
    //initialize stuff
    initializeBlankObject();
    initializeMoveParameters();
    //initialize promotion variables
    initializeWhiteTeamNextValidPromotionDisplayNames();
    initializeBlackTeamNextValidPromotionDisplayNames();
    strcpy(promotionRank, "VOID");
    strcpy(promotionDisplayName, "VOID");
}
//End---------------------------------------------------Load Last Game Progress--------------------------------------------------

//Start-------------------------------------Obtain Order to Execute From Player---------------------------------------------------
void obtainOrderToExecuteFromPlayer(){
    printf("\n--------------------------------------------");
    printf("\n[Move: move piece]\n[Save: save and exit]\n[Exit: exit without saving]\n[Undo: undo]");
    printf("\n--------------------------------------------");
    short validOrderObtained=0;
    while(validOrderObtained==0){
        printf("\nEnter an Order to execute : ");
        gets(playerOrder);
        strcpy(playerOrder, strupr(playerOrder));
        //create test cases
        int testCase1=(strcmp(playerOrder, "MOVE")==0);
        int testCase2=(strcmp(playerOrder, "SAVE")==0);
        int testCase3=(strcmp(playerOrder, "EXIT")==0);
        int testCase4=(strcmp(playerOrder, "UNDO")==0);
        //validate test cases
        if(testCase1||testCase2||testCase3||testCase4){
            validOrderObtained=1;
        }else{
            printf("\nPlease Enter a Valid Order!");
        }
    }
}
//End---------------------------------------Obtain Order to Execute From Player---------------------------------------------------

//Start-------------------------------------Obtain Game Type from Player (New Game or Load Progress)--------------------------------
void obtainGameTypeFromUser(){
    printf("\n---------------------------------------------------------------------------\n");
    printf("\n\t\t    >> New :   Start New Game");
    printf("\n");
    printf("\n\t\t    >> Load:   Load Previous Progress");
    printf("\n\n---------------------------------------------------------------------------");
    short validOrderObtained=0;
    while(validOrderObtained==0){
        printf("\nEnter Game Type : ");
        gets(gameType);
        strcpy(gameType, strupr(gameType));
        //create test cases
        int testCase1=(strcmp(gameType, "NEW")==0);
        int testCase2=(strcmp(gameType, "LOAD")==0);
        //validate test cases
        if(testCase1||testCase2){
            validOrderObtained=1;
        }else{
            printf("\nPlease Enter a Valid Game Type!");
        }
    }
}
//Start-------------------------------------Obtain Game Type from Player (New Game or Load Progress)--------------------------------

//Start----------------------------------------------Main Game Body-----------------------------------------------------------------
void runChessGame(){
    //00-display opening message
    displayOpeningMessage();
    //01-Obtain Game Type From User (New Game or Load Previous Progress)
    obtainGameTypeFromUser();
    //02-Initialize Game
    if(strcmp(gameType, "NEW")==0){
        initializeNewGame();
    }
    if(strcmp(gameType, "LOAD")==0){
        loadGameProgress();
    }
    //03-Run Game
    while(strcmp(gameStatus, "ON GOING")==0){
        //flush display and show the board
        system("cls");
        displayBoard();
        displayDeadPieces();
        //00-Obtain Order to execute from user
        obtainOrderToExecuteFromPlayer();
        int testCase1=(strcmp(playerOrder, "MOVE")==0);
        int testCase2=(strcmp(playerOrder, "SAVE")==0);
        int testCase3=(strcmp(playerOrder, "EXIT")==0);
        int testCase4=(strcmp(playerOrder, "UNDO")==0);
        //01-Move Player
        if(testCase1){
            system("cls");
            displayBoard();
            displayDeadPieces();
            printf("\n--------------------------------------------");
            printf("\n\t    %c Team Turn To Play", playerTurn);
            printf("\n--------------------------------------------\n");
            movePieceOrderProcessing();
            playCount+=1;
            saveLastMove();
        }
        if(testCase2){
            saveGameProgress();
            strcpy(gameStatus, "Exit");
        }
        if(testCase3){
            strcpy(gameStatus, "Exit");
        }
        if(testCase4){
            undoLastMove();
        }
    }
    system("cls");
    displayBoard();
    displayDeadPieces();
    if(strcmp(gameStatus, "Stalemate")==0){
        printf("\n--------------------------------------------");
        printf("\nIt's a Stalemate!");
        printf("\nGame Ended with a Draw");
        printf("\n--------------------------------------------");
    }
    if(strcmp(gameStatus, "Checkmate")==0){
        printf("\n--------------------------------------------");
        printf("\nCheckmate Team %c!", pieceToMoveVariable.enemy);
        printf("\nTeam %c is the WINNER.", pieceToMoveVariable.team);
        printf("\n--------------------------------------------");
    }
}
//End------------------------------------------------Main Game Body-----------------------------------------------------------------


//Start------------------------------------------------Main Game Body-------------------------------------------------------------
void main(){

    runChessGame();

}
//End--------------------------------------------------Main Game Body-------------------------------------------------------------

//Start-----------------------------------------------display object attributes-------------------------------------------------
void displayPieceAttributes(int r, int c){
    struct PIECE tmpObject;
    tmpObject=runTimeDatabase[r][c];
    //
    printf("\nDisplay Name : %s", tmpObject.displayName);
    printf("\nType : %s", tmpObject.type);
    printf("\nTeam : %c", tmpObject.team);
    printf("\nEnemy : %c", tmpObject.enemy);
    printf("\nStatus : %s", tmpObject.status);
    printf("\nCurrent Row : %d", tmpObject.currentRow);
    printf("\nCurrent Column : %d", tmpObject.currentColumn);
    printf("\nStep : %d", tmpObject.step);
    printf("\nTeam Location : %d", tmpObject.teamArrayLocation);
}
//End-------------------------------------------------display object attributes-------------------------------------------------


//Start--------------------------------------------------Undo Last Move---------------------------------------------------------
void undoLastMove(){
    //open files
    FILE *filePointer;
    filePointer = fopen( "Saved Game Progress Arrays For Undo.bin" , "r" );
    FILE *filePointer2;
    filePointer2=fopen("Saved Game Progress Misc For Undo.txt" ,"r");
    //undo first move
    if(playCount==1){
        initializeNewGame();
    }
    //01-create tmp variables
    struct PIECE tmpBoard[8][8];
    struct PIECE tmpWhiteTeam[1][16];
    struct PIECE tmpBlackTeam[1][16];
    char tmpText[100];
    //loop over files
    int movePointer;
    for(movePointer=1; movePointer<playCount; movePointer+=1){
        if(movePointer!=(playCount-1)){
            //saved arrays
            fread(tmpBoard , sizeof(struct PIECE) , 64 , filePointer);
            fread(tmpWhiteTeam , sizeof(struct PIECE) , 16 , filePointer);
            fread(tmpBlackTeam , sizeof(struct PIECE) , 16 , filePointer);
            //saved misc
            fgets(tmpText, 100, (FILE*)filePointer2);
            fgets(tmpText, 100, (FILE*)filePointer2);
            fgets(tmpText, 100, (FILE*)filePointer2);
        }else{
            //01-load Main Arrays
            fread(runTimeDatabase , sizeof(struct PIECE) , 64 , filePointer);
            fread(whiteTeam , sizeof(struct PIECE) , 16 , filePointer);
            fread(blackTeam , sizeof(struct PIECE) , 16 , filePointer);
            //02-load vital variables
            //get game status
            fgets(tmpText, 100, (FILE*)filePointer2);
            strtok(tmpText, "\n");
            strcpy(gameStatus, tmpText);
            //get player turn
            fgets(tmpText, 100, (FILE*)filePointer2);
            strtok(tmpText, "\n");
            playerTurn=tmpText[0];
            //get player count
            fgets(tmpText, 100, (FILE*)filePointer2);
            strtok(tmpText, "\n");
            playCount=atoi(tmpText);
            //initialize stuff
            initializeBlankObject();
            initializeMoveParameters();
            //initialize promotion variables
            initializeWhiteTeamNextValidPromotionDisplayNames();
            initializeBlackTeamNextValidPromotionDisplayNames();
            strcpy(promotionRank, "VOID");
            strcpy(promotionDisplayName, "VOID");
        }
    }
    //close files
    fclose(filePointer);
    fclose(filePointer2);

}
//Start--------------------------------------------------Undo Last Move---------------------------------------------------------

//Start-------------------------------------------------Save Game Progress------------------------------------------------------
void saveLastMove(){
    FILE *filePointer;
    filePointer = fopen( "Saved Game Progress Arrays For Undo.bin" , "r+" );
    FILE *filePointer2;
    filePointer2=fopen("Saved Game Progress Misc For Undo.txt" ,"r+");
    //loop over the files to get to the writing point
    //01-create tmp variables
    struct PIECE tmpBoard[8][8];
    struct PIECE tmpWhiteTeam[1][16];
    struct PIECE tmpBlackTeam[1][16];
    char tmpText[100];
    int playCount2=playCount+1;
    if(playCount==1){playCount2=playCount;}
    //loop over files
    int movePointer;
    for(movePointer=1; movePointer<playCount2; movePointer+=1){
            //saved arrays
            fread(tmpBoard , sizeof(struct PIECE) , 64 , filePointer);
            fread(tmpWhiteTeam , sizeof(struct PIECE) , 16 , filePointer);
            fread(tmpBlackTeam , sizeof(struct PIECE) , 16 , filePointer);
            //saved misc
            fgets(tmpText, 100, (FILE*)filePointer2);
            fgets(tmpText, 100, (FILE*)filePointer2);
            fgets(tmpText, 100, (FILE*)filePointer2);
    }
    //01-save main arrays
    fwrite(runTimeDatabase , sizeof(struct PIECE) , 64 , filePointer);
    fwrite(whiteTeam , sizeof(struct PIECE) , 16 , filePointer);
    fwrite(blackTeam , sizeof(struct PIECE) , 16 , filePointer);
    fclose(filePointer);
    //02-save white & black team roasters
    fprintf(filePointer2, "%s\n", gameStatus);
    fprintf(filePointer2, "%c\n", playerTurn);
    fprintf(filePointer2, "%d\n", playCount);
    fclose(filePointer2);
}
//End---------------------------------------------------Save Game Progress------------------------------------------------------
