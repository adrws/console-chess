#include <iostream>
#include <string>
#include <cmath>
#include <array>

#pragma GCC diagnostic ignored "-Wreturn-type"

using namespace std;

enum class ranks {A,B,C,D,E,F,G,H,None};
enum class colors {White,Black};
enum class piece_names {Pawn,Rook,Bishop,Knight,Queen,King};

class chess_piece {
    public:
        piece_names mType;
        colors mColor;

    chess_piece (piece_names type, colors color) {
        mType = type;
        mColor = color;
    }

};

class chess_square {
    public:
        ranks mRank;
        int mFile;
        chess_piece* mOccupant;
    
        chess_square() : mRank(ranks::None), mFile(0), mOccupant(nullptr) {};

        chess_square (ranks rank, int file, chess_piece* occupant) {
            mRank = rank;
            mFile = file;
            mOccupant = occupant;
        }

        void board_info () {
            array<string,8> rank_to_string = {"A","B","C","D","E","F","G","H"};
            array<string,7> type_to_string = {"Pawn","Rook","Bishop","Knight","Queen","King"};
            array<string,2> color_to_string = {"White","Black"};
            int _rank  = static_cast<int>(mRank);
            int _file  = mFile;
            int _type;
            int _color;

            if (mOccupant != nullptr) {
                _type = static_cast<int>(mOccupant->mType);
                _color = static_cast<int>(mOccupant->mColor);

                cout << "\n\n" << rank_to_string[_rank] << ++_file;
                cout << "\nOccupant: " << type_to_string[_type];
                cout << "\nColor: " << color_to_string[_color]; 
            } else {
                cout << "\n\n" << rank_to_string[_rank] << ++_file;
                cout << "\nOccupant: None";
            }
   
}

};

bool pawn_algo(array<array<chess_square,8>,8>& board, int c_rank, int c_file, int f_rank, int f_file) {
    if (board[f_rank][f_file].mOccupant == nullptr) {
        if ((f_rank == c_rank) && (f_file == c_file + 1)) {return true;}
        else {return false;}
    }
    else if (board[f_rank][f_file].mOccupant != nullptr) {
        if (
            (board[f_rank][f_file].mOccupant->mColor != board[c_rank][c_file].mOccupant->mColor) && 
            (f_file == c_file + 1) && (f_rank == (c_rank + 1 || c_rank - 1))
        ) {return true; }
        else {return false;}
    }
}

bool knight_algo(array<array<chess_square,8>,8>& board, int c_rank, int c_file, int f_rank, int f_file) {
    int delta_rank = abs(f_rank - c_rank);
    int delta_file = abs(f_file - c_file);
    int knight_move = delta_rank * delta_file;

    if (knight_move == 2) {
        if (board[f_rank][f_file].mOccupant != nullptr) {
            if (board[f_rank][f_file].mOccupant->mColor == board[c_rank][c_file].mOccupant->mColor) {return false;}
            else if (board[f_rank][f_file].mOccupant->mColor != board[c_rank][c_file].mOccupant->mColor) {return true;}
        }
        else {return true;}   
    }
    else {return false;}
    
}

bool rook_algo(array<array<chess_square,8>,8>& board, int c_rank, int c_file, int f_rank, int f_file) {
    int left_limit = 0;
    int right_limit = 7;
    int up_limit = 7;
    int down_limit = 0;
    enum class directions {Left, Right, Up, Down};
    directions direction;

    if ((f_rank > c_rank) && (c_file == f_file)) {direction = directions::Right;}
    else if ((f_rank < c_rank) && (c_file == f_file)) {direction = directions::Left;}
    else if ((f_file > c_file) && (c_rank == f_rank)) {direction = directions::Up;}
    else if ((f_file < c_file) && (c_rank == f_rank)) {direction = directions::Down;}
    else {return false;}

    if (direction == directions::Right) {
        for (int i = c_rank + 1; i <= 7; i++) {
            if (board[i][c_file].mOccupant != nullptr) {
                if (board[i][c_file].mOccupant->mColor == board[c_rank][c_file].mOccupant->mColor) {right_limit = i - 1; break;}
                else {right_limit = i; break;}
            }
            if (i == 7) {right_limit = 7; break;}
        }
    }
    else if (direction == directions::Left) {
        for (int i = c_rank - 1; i >= 0; i--) {
            if (board[i][c_file].mOccupant != nullptr) {
                if (board[i][c_file].mOccupant->mColor == board[c_rank][c_file].mOccupant->mColor) {left_limit = i - 1; break;}
                else {left_limit = i; break;}
            }
            if (i == 0) {left_limit = 0; break;}
        }
    }
    else if (direction == directions::Up) {
        for (int i = c_file + 1; i <= 7; i++) {
            if (board[c_rank][i].mOccupant != nullptr) {
                if (board[c_rank][i].mOccupant->mColor == board[c_rank][c_file].mOccupant->mColor) {up_limit = i - 1; break;}
                else {up_limit = i; break;} 
            }
            if (i == 7) {up_limit = 7; break;}
        }
    }
    else if (direction == directions::Down) {
        for (int i = c_file - 1; i >= 0; i--) {
            if (board[c_rank][i].mOccupant != nullptr) {
                if (board[c_rank][i].mOccupant->mColor == board[c_rank][c_file].mOccupant->mColor) {down_limit = i - 1; break;}
                else {down_limit = i; break;} 
            }
            if (i == 0) {down_limit = 0; break;}
        }
    }

    
    if ((direction == directions::Right) && (f_rank <= right_limit) && (c_file == f_file)) {return true;}
    else if ((direction == directions::Left) && (f_rank >= left_limit) && (c_file == f_file)) {return true;}
    else if ((direction == directions::Up) && (f_file <= up_limit) && (c_rank == f_rank)) {return true;}
    else if ((direction == directions::Down) && (f_file >= down_limit) && (c_rank == f_rank)) {return true;}
    else {return false;}
}

bool bishop_algo(array<array<chess_square,8>,8>& board, int c_rank, int c_file, int f_rank, int f_file) {
    int delta_r = fabs(f_rank-c_rank);
    int delta_f = fabs(f_file-c_file);

    if (delta_r == delta_f) {
        if (board[f_rank][f_file].mOccupant != nullptr) {
            if (board[f_rank][f_file].mOccupant->mColor == board[c_rank][c_file].mOccupant->mColor) {return false;}
            else {return true;}
        }
        else {return true;}
    }
    else {return false;}
}

bool queen_algo(array<array<chess_square,8>,8>& board, int c_rank, int c_file, int f_rank, int f_file) {

}

bool king_algo(array<array<chess_square,8>,8>& board, int c_rank, int c_file, int f_rank, int f_file) {

}

bool is_legal(array<array<chess_square,8>,8>& board, int c_rank, int c_file, int f_rank, int f_file) {
    if (board[c_rank][c_file].mOccupant->mType == piece_names::Pawn) {return pawn_algo(board, c_rank, c_file, f_rank, f_file);}
    else if (board[c_rank][c_file].mOccupant->mType == piece_names::Knight) {return knight_algo(board, c_rank, c_file, f_rank, f_file);}
    else if (board[c_rank][c_file].mOccupant->mType == piece_names::Rook) {return rook_algo(board, c_rank, c_file, f_rank, f_file);}
    else if (board[c_rank][c_file].mOccupant->mType == piece_names::Bishop) {return bishop_algo(board, c_rank, c_file, f_rank, f_file);}
}

void board_move(chess_square& present, chess_square& future) { 
    if (present.mOccupant == nullptr) {
        cout << "\nError: No piece exsists on this square.";
        return;
    }
    else {
        future.mOccupant = present.mOccupant;
        present.mOccupant = nullptr;
    }
}

void user_move(array<array<chess_square,8>,8>& board) {
    string move;
    bool valid_move = false;

    while(valid_move == false) { 
        cout << "\nPlease enter a move in LAN notation (capitalized): ";
        cin >> move;
        int inp_size = move.size();

        if (inp_size == 4) {
            valid_move = true;
        }
    }

    int c_rank;
    int f_rank;

    if (move.at(0) >= 'A' && move.at(0) <= 'H') {
        c_rank = static_cast<int>(move.at(0)) - 65;
    }
    if (move.at(2) >= 'A' && move.at(2) <= 'H') {
        f_rank = static_cast<int>(move.at(2)) - 65;
    }
    int c_file = static_cast<int>(move.at(1)) - 49;
    int f_file = static_cast<int>(move.at(3)) - 49;

    board[c_rank][c_file].board_info();
    board[f_rank][f_file].board_info();

    if (is_legal(board, c_rank, c_file, f_rank, f_file)) {
        board_move(board[c_rank][c_file], board[f_rank][f_file]);
    } else {
        cout << "\n\nThat is not a legal move.";
    }
    
    board[c_rank][c_file].board_info();
    board[f_rank][f_file].board_info();

}

int main () {

    array<array<chess_square,8>,8> chess_board = {};

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            chess_board[i][j].mRank = static_cast<ranks>(i);
            chess_board[i][j].mFile = j;
        }
    }

    chess_piece white_knight (piece_names::Knight, colors::White);
    chess_piece black_pawn(piece_names::Pawn, colors::Black);
    chess_piece white_rook(piece_names::Rook, colors::White);
    chess_piece white_bishop(piece_names::Bishop, colors::White);

    chess_board[3][2].mOccupant = &white_bishop;
    chess_board[5][4].mOccupant = &black_pawn;
    chess_board[4][1].mOccupant = &white_knight;

    user_move(chess_board);

}