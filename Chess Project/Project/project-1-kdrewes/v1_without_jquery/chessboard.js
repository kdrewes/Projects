/*
  Create your javascript functions for Project 1 here, using vanilla javascript syntax to manipulate the DOM...
*/

// Declare json object of each chess piece
// Key = piece, value = color
const CHESS_PIECES =
{
  'whiteKing': '&#9812;',
  'blackKing': '&#9818;',
  'whiteQueen': '&#9813;',
  'blackQueen': '&#9819;',
  'whiteRook': '&#9814;',
  'blackRook': '&#9820;',
  'whiteBishop': '&#9815;',
  'blackBishop': '&#9821;',
  'whiteKnight': '&#9816;',
  'blackKnight': '&#9822;',
  'whitePawn': '&#9817;',
  'blackPawn': '&#9823;',
  'empty': '&nbsp;'
};

// Declare JSON object of board positioning in beginning of match
const POSITION =
{
  'a8': CHESS_PIECES.blackRook, 'b8': CHESS_PIECES.blackKnight, 'c8': CHESS_PIECES.blackBishop, 'd8': CHESS_PIECES.blackQueen,
  'e8': CHESS_PIECES.blackKing, 'f8': CHESS_PIECES.blackBishop, 'g8': CHESS_PIECES.blackKnight, 'h8': CHESS_PIECES.blackRook,
  'a7': CHESS_PIECES.blackPawn, 'b7': CHESS_PIECES.blackPawn, 'c7': CHESS_PIECES.blackPawn, 'd7': CHESS_PIECES.blackPawn,
  'e7': CHESS_PIECES.blackPawn, 'f7': CHESS_PIECES.blackPawn, 'g7': CHESS_PIECES.blackPawn, 'h7': CHESS_PIECES.blackPawn,
  'a6': CHESS_PIECES.empty, 'b6': CHESS_PIECES.empty, 'c6': CHESS_PIECES.empty, 'd6': CHESS_PIECES.empty,
  'e6': CHESS_PIECES.empty, 'f6': CHESS_PIECES.empty, 'g6': CHESS_PIECES.empty, 'h6': CHESS_PIECES.empty,
  'a5': CHESS_PIECES.empty, 'b5': CHESS_PIECES.empty, 'c5': CHESS_PIECES.empty, 'd5': CHESS_PIECES.empty,
  'e5': CHESS_PIECES.empty, 'f5': CHESS_PIECES.empty, 'g5': CHESS_PIECES.empty, 'h5': CHESS_PIECES.empty,
  'a4': CHESS_PIECES.empty, 'b4': CHESS_PIECES.empty, 'c4': CHESS_PIECES.empty, 'd4': CHESS_PIECES.empty,
  'e4': CHESS_PIECES.empty, 'f4': CHESS_PIECES.empty, 'g4': CHESS_PIECES.empty, 'h4': CHESS_PIECES.empty,
  'a3': CHESS_PIECES.empty, 'b3': CHESS_PIECES.empty, 'c3': CHESS_PIECES.empty, 'd3': CHESS_PIECES.empty,
  'e3': CHESS_PIECES.empty, 'f3': CHESS_PIECES.empty, 'g3': CHESS_PIECES.empty, 'h3': CHESS_PIECES.empty,
  'a2': CHESS_PIECES.whitePawn, 'b2': CHESS_PIECES.whitePawn, 'c2': CHESS_PIECES.whitePawn, 'd2': CHESS_PIECES.whitePawn,
  'e2': CHESS_PIECES.whitePawn, 'f2': CHESS_PIECES.whitePawn, 'g2': CHESS_PIECES.whitePawn, 'h2': CHESS_PIECES.whitePawn,
  'a1': CHESS_PIECES.whiteRook, 'b1': CHESS_PIECES.whiteKnight, 'c1': CHESS_PIECES.whiteBishop, 'd1': CHESS_PIECES.whiteQueen,
  'e1': CHESS_PIECES.whiteKing, 'f1': CHESS_PIECES.whiteBishop, 'g1': CHESS_PIECES.whiteKnight, 'h1': CHESS_PIECES.whiteRook
};

// Declare chessboard dataset
let chessBoard = {};


// --------------------------------------------------------------------------------------------------------

// Generate design of chessboard
function Render_Board() {
  // Fetch chessBoard div from DOM and store it in variable (chessBoardDiv)
  const board = document.getElementById('chessBoard');

  // Produce table variable
  const table = document.createElement('table');

  // Insert 8 rows (from 8 to 1)
  for (let row = 8; row >= 1; row--) {
    // Declare tr tag variable
    const tr = document.createElement('tr');

    // Declare th element
    const th = document.createElement('th')

    // Assign header value (1-8) displayed vertically on chessboard 
    th.textContent = row;

    // Store head value 
    tr.appendChild(th);

    // Assign coordinates for each square on chessboard
    for (let column = 0; column < 8; column += 1) {
      // Declare td element
      const td = document.createElement('td');

      // Assign id (coordinate) of each individual square --> String.fromCharCode(97) = 'a' + row #
      td.id = String.fromCharCode(97 + column) + row;

      // Store data value
      tr.appendChild(td);
    }

    // Store row value in table
    table.appendChild(tr);

  }

  // Insert column letters at bottom of chessboard (a-h)
  const row = document.createElement('tr');
  const emptyCorner = document.createElement('th');
  emptyCorner.textContent = '';
  row.appendChild(emptyCorner);

  // Traverse through column numbers
  for (let column = 0; column < 8; column += 1) {
    const th = document.createElement('th');
    th.textContent = String.fromCharCode(97 + column);
    row.appendChild(th);
  }

  // Add row to table
  table.appendChild(row);

  // Render chessboard
  board.appendChild(table);

}

// ---------------------------------------------------------------

// Render logic of each chess board piece 
function Render_Pieces() {
  // Reset chessboard dataset 
  chessBoard = {};

  // Key = position of board, value = unicode character of chess piece
  for (let p in POSITION)
    chessBoard[p] = POSITION[p];

  // Display chess pieces by traversing through each square on chessbaord
  for (let coordinate in chessBoard) {
    // Retreive id of each coordinate
    const id = document.getElementById(coordinate);

    // If id exists, assign chess piece to each coordinate
    if (id)
      id.innerHTML = chessBoard[coordinate];
  }

}

// --------------------------------------------------------------------------------------------------------

// Logic used to move each individual chess piece
function Move_Piece()
{
  // Retreive input value of source and destination.  Convert strings to lower case and trims extra spaces
  const source = document.getElementById('source').value.toLowerCase().trim();
  const destination = document.getElementById('destination').value.toLowerCase().trim();

  // Input validation - Determine if user enter correct input
  if (!/^[a-h][1-8]$/.test(source) || !/^[a-h][1-8]$/.test(destination)) {
    alert('Invalid coordinate - please use correct format.  Ex - "e2" or "a1"');
    return;
  }

  // Retreive id for source cell
  const sourceCell = document.getElementById(source);

  // Retreive id for destination cell
  const destinationCell = document.getElementById(destination);

  // Verify if cell is valid
  if (!sourceCell || !destinationCell) {
    alert('Error - invalid coordinate.\n\nPlease re-enter');
    return;
  }

  //  Assign unicode value of piece
  const piece = chessBoard[source] || sourceCell.innerHTML;

  // Assign value
  destinationCell.innerHTML = piece;
  chessBoard[destination] = piece;

  // Clear source square
  sourceCell.innerHTML = CHESS_PIECES.empty;
  chessBoard[source] = CHESS_PIECES.empty;

  // Clear text field data
  document.getElementById('source').value = '';
  document.getElementById('destination').value = '';

}

// Logic used reset game
function Reset() {
  // Re-render pieces
  Render_Pieces();

  // Clear text field data
  document.getElementById('source').value = '';
  document.getElementById('destination').value = '';
}

// --------------------------------------------------------------------------------------------------------

// Generate board once page loads
window.onload = function () {
  // Generate board
  Render_Board();

  // Generate chess pieces
  Render_Pieces();
}

// --------------------------------------------------------------------------------------------------------