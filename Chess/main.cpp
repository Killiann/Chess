#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <fstream>
#include "ChessPiece.h"
#include "Console.h"

typedef unsigned _int8 LITTLE;
const LITTLE bs = 8; //board size
const LITTLE tileWidth = 100;
const LITTLE boardFontSize = 23;
sf::Font boardFont;
sf::Color tile1Colour = sf::Color::White;
sf::Color tile2Colour(117, 36, 219);

int main()
{   
    int grid[bs][bs] = {};
    int availableMoves[bs][bs] = {};
    int pieceGrid[bs][bs] = {};
    int pieceTypeGrid[bs][bs] = {
        {2,3,4,5,6,4,3,2},
        {1,1,1,1,1,1,1,1},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {1,1,1,1,1,1,1,1},
        {2,3,4,5,6,4,3,2}
    };

    //setup pieceGrid
    for (LITTLE x = 0; x < bs; ++x)
        for (LITTLE y = 0; y < bs; ++y)
            pieceGrid[x][y] = -1;

    bool isClicking = false;
    bool hasSelected = false;
    bool showMouseHover = false;

    sf::Vector2f clickedSquare = sf::Vector2f(-1, -1);
        
    std::vector<ChessPiece *> pieces;
    int selectedPieceId = -1;

    //drawable
    sf::Texture piecesTexture;
    std::vector<sf::Text> boardText;
    std::vector<sf::RectangleShape> boardSquares;
    sf::RectangleShape mouseHoverSquare;
    sf::RectangleShape selectedSquare;

    //console setup
    Console console(bs * tileWidth, 0, &piecesTexture, &boardFont, "Moves: ");

    //pieces storage?
    std::vector<Pawn> pawns;
    pawns.reserve(16);
    std::vector<Rook> rooks;
    rooks.reserve(20);
    std::vector<Bishop> bishops;
    bishops.reserve(20);
    std::vector<Knight> knights;
    knights.reserve(20);
    std::vector<Queen> queens;
    queens.reserve(16);
    std::vector<King> kings;
    kings.reserve(2);
#pragma region setup;
    
    //setup window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "Chess");    
    
    //load font
    if (!boardFont.loadFromFile("Roboto-Black.ttf")) {
        std::cout << "error loading font.";
    }   

    //load texture
    if (!piecesTexture.loadFromFile("spritesheet.png")) {
        std::cout << "error loading pieces spritesheet";
    }    
    piecesTexture.setSmooth(true);

    //mouse hover
    mouseHoverSquare.setSize(sf::Vector2f(tileWidth, tileWidth));
    mouseHoverSquare.setOutlineColor(sf::Color(252, 113, 86));
    mouseHoverSquare.setOutlineThickness(3);
    mouseHoverSquare.setFillColor(sf::Color::Transparent);

    selectedSquare.setPosition(sf::Vector2f(-1, -1));
    selectedSquare.setSize(sf::Vector2f(tileWidth, tileWidth));
    selectedSquare.setFillColor(sf::Color(217, 194, 74));    

    //setup board shapes
    for (LITTLE x = 0; x < bs; ++x) {
        for (LITTLE y = 0; y < bs; ++y) {
            sf::RectangleShape boardSquare(sf::Vector2f(tileWidth, tileWidth));
            boardSquare.setPosition(x * tileWidth, y * tileWidth);
            if(x % 2 == y % 2) boardSquare.setFillColor(tile1Colour);
            else boardSquare.setFillColor(tile2Colour);
            boardSquares.push_back(boardSquare);
        }
    }

    //setup board text
    int count = 0;
    for (char ch = 'a'; ch < ('a' + bs); ++ch) {
        sf::Text col;
        sf::Text row;
        col.setFont(boardFont);
        row.setFont(boardFont);
        col.setCharacterSize(boardFontSize);
        row.setCharacterSize(boardFontSize);
        col.setString(ch);
        row.setString(std::to_string(count + 1));
        if (ch % 2 == 0) {
            col.setFillColor(tile2Colour);
            row.setFillColor(tile1Colour);
        }
        else {
            col.setFillColor(tile1Colour);
            row.setFillColor(tile2Colour);
        }
        col.setPosition(sf::Vector2f((count * tileWidth) + 80, (bs - 1) * tileWidth + 70));
        row.setPosition(sf::Vector2f(5, (count * tileWidth) + 5));
        boardText.push_back(col);
        boardText.push_back(row);
        count++;
    }        

    //setup pieces 
    ChessPiece* newPiece;
    for (int y = 0; y < bs; ++y)
        for (int x = 0; x < bs; ++x) {
            bool isWhite = false;
            if (y > bs / 2) isWhite = true;
            switch (pieceTypeGrid[y][x]) {
            case 1 :
                pawns.emplace_back((int)pieces.size(), x, y, isWhite, &piecesTexture, &console);
                newPiece = &(pawns.back());
                pieceGrid[y][x] = (int)pieces.size();
                pieces.push_back(newPiece);
                break;
            case 2:
                rooks.emplace_back((int)pieces.size(), x, y, isWhite, &piecesTexture, &console);
                newPiece = &(rooks.back());
                pieceGrid[y][x] = (int)pieces.size();
                pieces.push_back(newPiece);
                break;
            case 3:
                knights.emplace_back((int)pieces.size(), x, y, isWhite, &piecesTexture, &console);
                newPiece = &(knights.back());
                pieceGrid[y][x] = (int)pieces.size();
                pieces.push_back(newPiece);
                break;
            case 4:
                bishops.emplace_back((int)pieces.size(), x, y, isWhite, &piecesTexture, &console);
                newPiece = &(bishops.back());
                pieceGrid[y][x] = (int)pieces.size();
                pieces.push_back(newPiece);
                break;
            case 5:
                queens.emplace_back((int)pieces.size(), x, y, isWhite, &piecesTexture, &console);
                newPiece = &(queens.back());
                pieceGrid[y][x] = (int)pieces.size();
                pieces.push_back(newPiece);
                break;
            case 6:
                kings.emplace_back((int)pieces.size(), x, y, isWhite, &piecesTexture, &console);
                newPiece = &(kings.back());
                pieceGrid[y][x] = (int)pieces.size();
                pieces.push_back(newPiece);
                break;            
            }
        }

#pragma endregion

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(220,220,220));

#pragma region update

        //check mouse position
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        if ((mousePos.x > 0 && mousePos.x < bs * tileWidth) &&
            (mousePos.y > 0 && mousePos.y < bs * tileWidth)) {
            showMouseHover = true;
            mouseHoverSquare.setPosition(sf::Vector2f((int)(mousePos.x / tileWidth) * tileWidth, (int)(mousePos.y / tileWidth) * tileWidth));

            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                        isClicking = true;
                        clickedSquare = sf::Vector2f((int)(mousePos.x / tileWidth), (int)(mousePos.y / tileWidth));                    
                }
            }
            else if (event.type == sf::Event::MouseButtonReleased) {
                if (event.mouseButton.button == sf::Mouse::Left && isClicking &&
                    (clickedSquare == sf::Vector2f((int)(mousePos.x / tileWidth), (int)(mousePos.y / tileWidth)))){
                    if (sf::Vector2f(selectedSquare.getPosition().x / tileWidth, selectedSquare.getPosition().y / tileWidth) != clickedSquare) {
                        
                        int currentId = -1;
                        //check that didn't click on available move
                        bool isAvailableSquare = false;
                        for(LITTLE y = 0; y < bs; ++y)
                            for(LITTLE x = 0; x < bs; ++x)
                                if (availableMoves[(int)clickedSquare.y][(int)clickedSquare.x] != 0) isAvailableSquare = true;

                        if (!isAvailableSquare) {
                            hasSelected = true;
                            selectedSquare.setPosition(sf::Vector2f(clickedSquare.x * tileWidth, clickedSquare.y * tileWidth));

                            //show possible moves
                            currentId = pieceGrid[(int)selectedSquare.getPosition().y / tileWidth][(int)selectedSquare.getPosition().x / tileWidth];

                            if (currentId == -1 || selectedPieceId != -1) { //reset available moves
                                selectedPieceId = -1;
                                for (LITTLE y = 0; y < bs; ++y)
                                    for (LITTLE x = 0; x < bs; ++x)
                                        availableMoves[y][x] = 0;
                            }
                            if (currentId != -1) {
                                pieces[currentId]->showMoves(pieceGrid, availableMoves);
                                selectedPieceId = currentId;
                            }
                        }
                        else {
                            pieces[selectedPieceId]->move((int)clickedSquare.x, (int)clickedSquare.y, pieceGrid, pieces);  
                            for (LITTLE y = 0; y < bs; ++y)
                                for (LITTLE x = 0; x < bs; ++x)
                                    availableMoves[y][x] = 0;
                            selectedPieceId = -1;
                            hasSelected = false;
                        }
                        isClicking = false;
                    }
                }
            }
        }
        else showMouseHover = false;        

#pragma endregion
#pragma region draw

        //draw board
        for (auto s : boardSquares)
            window.draw(s);

        for (auto t : boardText)
             window.draw(t);        
        
        if(showMouseHover)
            window.draw(mouseHoverSquare);

        if (hasSelected)
            window.draw(selectedSquare);

        //draw pieces
        for (ChessPiece* p : pieces)
            p->draw(window);

        //draw available moves        
        if(hasSelected)
            for(int y=0;y<bs;++y)
                for(int x=0;x<bs; ++x)
                    if (availableMoves[y][x] == 1) {
                        sf::RectangleShape rect(sf::Vector2f(tileWidth, tileWidth));
                        rect.setPosition(sf::Vector2f(x * tileWidth, y * tileWidth));
                        rect.setFillColor(sf::Color(93,240,135,130));
                        window.draw(rect);
                    }

        //draw message console        
        console.Draw(window);

        window.display();
    }

#pragma endregion

    return 0;
}
